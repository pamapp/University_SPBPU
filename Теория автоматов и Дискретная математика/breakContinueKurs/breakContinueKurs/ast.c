//
//  main.c
//  breakContinueKurs
//
//  Created by Alina Potapova on 24.04.2021.
//

ast_node* new_break(ast_node* arg1) {
  ast_node* node;
  node = (ast_node*)malloc(sizeof(ast_node));
  if(node) {
    node->type = Node_Break;
    node->data.ast_value = arg1;
  }
  return node;
}
