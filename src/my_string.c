#include <stdio.h>
#include <stdlib.h>


#include "../include/my_string.h"



int my_strlen(char* str)
{
    int c = 0;
    
    while(*str++ != '\0')
        c++;

    return c;
}


char* my_strconcat(char* str1, char* str2)
{
    int length = my_strlen(str1) + my_strlen(str2) + 1;

    char* concat = malloc(length * sizeof(char));
    char* ret = concat;
    
    while(*str1 != '\0')
        *concat++ = *str1++;

    while(*str2 != '\0')
        *concat++ = *str2++;

    *concat = '\0';
    return ret;
}


char* my_strdup(char* str)
{
    char* dup = malloc((my_strlen(str) + 1) * sizeof(char));
    char* ret = dup;

    while(*str != '\0')
        *dup++ = *str++;

    *dup = '\0';
    return ret;
}


int my_strcmp(char* str1, char* str2)
{
    while(*str1 != '\0' && *str2 != '\0')
    {
        if(*str1 > *str2 || *str1 < *str2)
            return *str1 - *str2;
        
        str1++;
        str2++;
    }
    return *str1 - *str2;
}
