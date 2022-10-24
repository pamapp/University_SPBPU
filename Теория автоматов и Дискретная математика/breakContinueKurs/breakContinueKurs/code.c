//
//  code.c
//  breakContinueKurs
//
//  Created by Alina Potapova on 24.04.2021.
//

#include <string.h>

const int BREAK_ADDR_MAX_SIZE = 128; //max размер массива break_addr
int break_addr[128][128] = {{0}};  //адрес вставки инструкции JMP
int break_counter[128] = {0}; //счетчик break на каждом уровне вложенности
int in_while = 0;

unsigned int generate_code(FILE* stream, unsigned int address, ast_node* ast)
{
        ast_node* ptr;
        opcode op;
        unsigned int tmpaddr1, tmpaddr2;
        unsigned int new_address;
    int i = 0;
        
        if(ast) {
                switch(ast->type) {
                        case Node_Block:
                                ptr = ast->sub[0];
                                new_address = address;
                                while(ptr) {
                                        new_address = generate_code(stream, new_address, ptr);
                                        ptr = ptr->next;
                                }
                                break;

                        case Node_Const:
                                new_address = generate_command(stream, address, PUSH, ast->data.integer_value);
                                break;

                        case Node_Var:
                                new_address = generate_command(stream, address, LOAD, get_var_address(ast));
                                break;

                        case Node_Read:
                                new_address = generate_command(stream, address, INPUT, 0);
                                break;
                                
                        case Node_Expr:
                                new_address = generate_code(stream, address, ast->sub[0]);
                                
                                if(ast->data.integer_value != OP_NEG) {
                                        new_address = generate_code(stream, new_address, ast->sub[1]);
                                }
                                        
                                switch(ast->data.integer_value) {
                                        case OP_ADD: op = ADD; break;
                                        case OP_SUB: op = SUB; break;
                                        case OP_MUL: op = MULT; break;
                                        case OP_DIV: op = DIV; break;
                                        case OP_NEG: op = INVERT; break;
                                        default:
                                                     milan_error("Unknown arithmetical operator");
                                                     break;
                                }

                                new_address = generate_command(stream, new_address, op, 0);
                                break;
                                
                        case Node_Assign:
                                new_address = generate_code(stream, address, ast->sub[0]);
                                new_address = generate_command(stream, new_address, STORE, get_var_address(ast));
                                break;
                                
                        case Node_Write:
                                new_address = generate_code(stream, address, ast->sub[0]);
                                new_address = generate_command(stream, new_address, PRINT, 0);
                                break;
                                
                        case Node_Cond:
                                new_address = generate_code(stream, address, ast->sub[0]);
                                new_address = generate_code(stream, new_address, ast->sub[1]);
                                new_address = generate_command(stream, new_address, COMPARE, ast->data.integer_value);
                                break;
                                
                        case Node_If:
                                new_address = generate_code(stream, address, ast->data.ast_value);
                                tmpaddr1 = new_address++;
                                new_address = generate_code(stream, new_address, ast->sub[0]);

                                if(ast->sub[1]) {
                                        generate_command(stream, tmpaddr1, JUMP_NO, new_address + 1);
                                        tmpaddr1 = new_address++;
                                        new_address = generate_code(stream, new_address, ast->sub[1]);
                                        generate_command(stream, tmpaddr1, JUMP, new_address);
                                }
                                else {
                                        generate_command(stream, tmpaddr1, JUMP_NO, new_address);
                                }
                                break;
                                
                        case Node_While:
                            ++in_while;
                            if (in_while > 128)
                                milan_error("too many nested loops");
                            tmpaddr1 = address;
                            new_address = generate_code(stream, address, ast->data.ast_value);
                            tmpaddr2 = new_address++;

                            new_address = generate_code(stream, new_address, ast->sub[0]);
                            new_address = generate_command(stream, new_address, JUMP, tmpaddr1);
                            generate_command(stream, tmpaddr2, JUMP_NO, new_address);
                        
                            for (i = 0; i < break_counter[in_while - 1]; ++i) {
                                generate_command(stream, break_addr[in_while - 1][i], JUMP, new_address); //записываем JUMP во все сохраненные адреса break_addr
                            }
                        
                            memset(break_addr[in_while-1], 0, sizeof(int)*BREAK_ADDR_MAX_SIZE);  //обнуляем массив break_addr на данном уровне вложенности
                        
                            break_counter[in_while-1] = 0; //обнулили счетчик
                        
                            --in_while; //уменьшаем счетчик уровня вложенности
                            break;

                        case Node_Break:
                            if (in_while > 0) {
                                if (break_counter[in_while-1] < BREAK_ADDR_MAX_SIZE) {
                                new_address = address; //первая свободная адресная ячейка после кода
                                break_addr[in_while-1][break_counter[in_while-1]++] = new_address++;
                                //присваиваем ячейке break_addr адрес, куда поместим команду JMP и увеличиваем счетчик break_counter
                                    if (ast->data.ast_value != NULL) {
                                        new_address = generate_code(stream, new_address, ast->data.ast_value); //если за BREAK есть код, то будем его генерировать
                                    }
                                }
                                else {
                                    milan_error("too much breaks in while");
                                }
                            }
                            else {
                                milan_error("break should be in loop");
                            }
                            break;
                                
                default:
                        milan_error("Unknown node type");
                        break;
            }

            return new_address;
        }
        else {
                return address;
        }
}

