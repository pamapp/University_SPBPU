//
//  parser.c
//  breakContinueKurs
//
//  Created by Alina Potapova on 24.04.2021.
//

%token T_BREAK

//записываем правила оператора break в правую часть нетерминала stmt
stmt            : /* Empty */                         { $$ = NULL;                                       }
                | T_WRITE '(' expr ')'                { $$ = new_write($3);                              }
                | T_IDENT T_ASSIGN expr               { $$ = new_assign($1, $3);                         }
                | T_WHILE  cond T_DO stmt_list T_OD   { $$ = new_while($2, new_block($4));               }
                | T_IF cond T_THEN stmt_list rest_if  { $$ = new_if($2, new_block($4), $5);              }
                | T_BREAK ';' stmt_list             { $$ = new_break(new_block($3));                   }
        //$3 - stmt_list
                | T_BREAK                             { $$ = new_break(NULL);                            }
                ;
