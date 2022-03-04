#include <stdio.h>
#include <stdlib.h>


#include "../include/ls_node.h"
#include "../include/my_string.h"
#include "../include/my_ls_types.h"


void init(my_ls*);
void cleanup(my_ls*);


int main(int argc, char** argv)
{
    my_ls* opts = malloc(sizeof(my_ls));
    init(opts);

    if(argc == 1)
    {
        char* arr[2] = {"\0", "."};
        process_input_args(2, arr, opts);
    }
    else
        process_input_args(argc, argv, opts);
    
    process_files(opts);
    process_dirs(opts);

    cleanup(opts);

    return 0;
}


void init(my_ls* obj)
{
    obj->flags = malloc(sizeof(arg_flags));
    obj->flags->a = 0;
    obj->flags->t = 0;
    obj->head_file = NULL;
    obj->head_dir = NULL;
}


void cleanup(my_ls* obj)
{
    free(obj->flags);
    ls_node_free(obj->head_file);
    ls_node_free(obj->head_dir);
    free(obj);
}
