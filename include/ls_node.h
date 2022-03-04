#ifndef MY_LS_NODE_H
#define MY_LS_NODE_H

#define PRINT_AT_END 1
#define ONLY_BETWEEN 0

typedef struct s_ls_node
{
    char* name;
    long int mtim;
    struct s_ls_node* next;
} ls_node;


void switch_ls_nodes(ls_node*, ls_node*);

ls_node* ls_node_create_element(char*, long int);
ls_node* ls_node_push_element(ls_node*, char*, long int);

void ls_node_print(ls_node*, char*, uint);
void ls_node_free(ls_node*);

ls_node* ls_node_order_by_ptr(ls_node* head, int (*sort)(ls_node*, ls_node*));
int prt_time(ls_node* runner, ls_node* helper);
int prt_lexico(ls_node* runner, ls_node* helper);

#endif
