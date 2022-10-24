//
//  ast.h
//  breakContinueKurs
//
//  Created by Alina Potapova on 24.04.2021.
//

#ifndef ast_h
#define ast_h

typedef enum {
        Node_Block = 0,
        Node_Const,
        Node_Var,
        Node_Read,
        Node_Expr,
        Node_Assign,
        Node_Write,
        Node_Cond,
        Node_If,
        Node_While,
    Node_Break
} node_type;

ast_node* new_break(ast_node* arg1);


#endif /* ast_h */
