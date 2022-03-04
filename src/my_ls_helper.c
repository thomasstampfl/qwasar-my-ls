#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>


#include "../include/ls_node.h"
#include "../include/my_string.h"
#include "../include/my_ls_types.h"


long int get_mtim(char* path)
{
    struct stat st;
    stat(path, &st);    
    return st.st_mtim.tv_sec * 1000000000 + st.st_mtim.tv_nsec;
}


int is_file(char* path)
{
    int res = 0;
    struct stat st;
    
    res = lstat(path, &st);
    if(res == -1)
        printf("my_ls: cannot access '%s': No such file or directory\n", path);
    else if((st.st_mode & S_IFMT) == S_IFDIR)
        res = 0;    
    else
        res = 1;

    return res;
}


char* concat_dir_and_file_name(char* dir, char* file)
{
    char* ret;
    char* temp;

    if(dir[my_strlen(dir) - 1] != '/')
    {
        temp = my_strconcat(dir, "/");
        ret = my_strconcat(temp, file);
    }
    else
        ret = my_strconcat(dir, file);

    free(temp);
    return ret;
}


ls_node* get_files_in_dir(char* dirname, arg_flags* flags)
{
    long int mtim = 0;
    char* full_filename;
    
    ls_node* head = NULL;

    struct dirent *de;    
    DIR *dr = opendir(dirname);

    while ((de = readdir(dr)) != NULL)
    {
        if(de->d_name[0] != '.' || (de->d_name[0] == '.' && flags->a == 1))
        {
            if(flags->t == 1)
            {
                full_filename = concat_dir_and_file_name(dirname, de->d_name);
                mtim = get_mtim(full_filename);
                free(full_filename);
            }

            head = ls_node_push_element(head, de->d_name, mtim);              
        }
    }
    
    closedir(dr);
    return head;
}


void check_input_flags(char c, arg_flags* flags)
{
    if(c == 'a')
        flags->a = 1;
    else if(c == 't')
        flags->t = 1;
    else
        printf("my_ls: invalid option --'%c'\n", c);
}


void process_input_args(int argc, char** argv, my_ls* obj)
{
    int res_is_file = 0;

    for(int i = 1; i < argc; i++)
    {
        if(argv[i][0] == '-')
            for(int j = 1; argv[i][j] != '\0'; j++)
                check_input_flags(argv[i][j], obj->flags);

        else
        {
            res_is_file = is_file(argv[i]);
            if(res_is_file == 1)
                obj->head_file = ls_node_push_element(obj->head_file, argv[i], get_mtim(argv[i]));

            else if(res_is_file == 0)
                obj->head_dir = ls_node_push_element(obj->head_dir, argv[i], get_mtim(argv[i]));
        }
    }

    if( (obj->flags->a == 1 || obj->flags->t == 1) &&
            obj->head_file == NULL && obj->head_dir == NULL)
        obj->head_dir = ls_node_push_element(obj->head_dir, ".", 0);
}


ls_node* order_ls_node_by_flags(ls_node* head, arg_flags* flags)
{
    if(flags->t == 1)
        return ls_node_order_by_ptr(head, &prt_time);
    else
        return ls_node_order_by_ptr(head, &prt_lexico);
}


void process_files(my_ls* obj)
{
    if(obj->head_file != NULL)
    {
        obj->head_file = order_ls_node_by_flags(obj->head_file, obj->flags);
        ls_node_print(obj->head_file, "  ", ONLY_BETWEEN);
        printf("\n");
    }
}


void process_dirs(my_ls* obj)
{
    ls_node* help_dir = NULL;
    ls_node* help_ls_node = obj->head_dir;

    if(obj->head_dir != NULL)
    {
        if(obj->head_file != NULL)
            printf("\n");
        
        if(obj->head_dir->next != NULL)
            obj->head_dir = order_ls_node_by_flags(obj->head_dir, obj->flags);

        while(help_ls_node != NULL)
        {
            if(obj->head_dir->next != NULL)
                printf("%s:\n", help_ls_node->name);

            help_dir = get_files_in_dir(help_ls_node->name, obj->flags);
            help_dir = order_ls_node_by_flags(help_dir, obj->flags);
            ls_node_print(help_dir, "  ", ONLY_BETWEEN);
            // ls_node_print(help_dir, "\n", ONLY_BETWEEN);

            ls_node_free(help_dir);

            printf("%s", (help_ls_node->next != NULL) ? "\n\n" : "\n");
            help_ls_node = help_ls_node->next;
        }
    }
    ls_node_free(help_ls_node);    
}
