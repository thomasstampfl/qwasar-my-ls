#ifndef MY_LS_TYPES_H
#define MY_LS_TYPES_H

/*
    TYPES / STRUCTS
*/
typedef struct s_arg_flags
{
    uint a;
    uint t;
} arg_flags;

typedef struct s_my_ls
{
    arg_flags* flags;
    ls_node* head_file;
    ls_node* head_dir;
} my_ls;



/*
    FUNCTION PROTOTYPES
    (deviating from naming conventions the functions are implemented in my_ls_helper.c)
*/
long int get_mtim(char*);
int is_file(char*);
char* concat_dir_and_file_name(char*, char*);
ls_node* get_files_in_dir(char*, arg_flags*);

void check_input_flags(char, arg_flags*);
void process_input_args(int, char**, my_ls*);

ls_node* order_ls_node_by_flags(ls_node*, arg_flags*);

void process_files(my_ls*);
void process_dirs(my_ls*);

#endif
