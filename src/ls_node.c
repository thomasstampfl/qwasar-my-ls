#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>


#include "../include/ls_node.h" 
#include "../include/my_string.h"


ls_node* ls_node_create_element(char* str, long int mtim)
{
    ls_node* new = malloc(sizeof(ls_node));
    new->name = my_strdup(str);
    new->mtim = mtim;
    new->next = NULL;
    return new;
}


ls_node* ls_node_push_element(ls_node* head, char* str, long int mtim)
{
    ls_node* helper = head;
    if(helper == NULL)
    {
        helper = ls_node_create_element(str, mtim);
        return helper;
    }
    else
    {
        while(helper->next != NULL)
            helper = helper->next;

        helper->next = ls_node_create_element(str, mtim);
    }
    return head;
}


void switch_ls_nodes(ls_node* sn1, ls_node* sn2)
{
    /*
        Works well for small data
        For bigger data change pointers
    */

    long int mtim;
    char* name; 

    mtim = sn1->mtim;
    name = sn1->name;

    sn1->mtim = sn2->mtim;
    sn1->name = sn2->name;

    sn2->mtim = mtim;
    sn2->name = name;
}


ls_node* ls_node_order_by_ptr(ls_node* head, int (*sort)(ls_node*, ls_node*))
{
    bool swapped = false;

    ls_node* helper = head;
    ls_node* runner;

    if(head == NULL || head->next == NULL)
        return head;

    while(helper->next != NULL)
    {
        runner = head;

        while(runner != NULL && runner->next != NULL)
        {
            if(sort(runner, runner->next) == 1)
                swapped = true;

            runner = runner->next;
        }
        
        // optimization
        if(swapped == false)
            break;

        helper = helper->next;
    }

    return head;
}

int prt_time(ls_node* current, ls_node* next)
{
    long int diff = current->mtim - next->mtim;
    if(diff < 0)
    {
        switch_ls_nodes(current, next);
        return 1;
    }
    else if(diff == 0)
        return prt_lexico(current, next);

    return 0;
}


int prt_lexico(ls_node* current, ls_node* next)
{    
    if(my_strcmp(current->name, next->name) > 0)
    {
        switch_ls_nodes(current, next);
        return 1;
    }

    return 0;
}


void ls_node_print(ls_node* head, char* sep, uint print_at_end)
{
    while(head != NULL)
    {
        printf("%s", head->name);
        
        if(print_at_end == 1 || head->next != NULL)
            printf("%s", sep);

        head = head->next;
    }
}


void ls_node_free(ls_node* head)
{
    ls_node* tmp = head;
    while(head != NULL)
    {
        tmp = head;
        head = head->next;

        free(tmp->name);
        free(tmp);       
    }
}
