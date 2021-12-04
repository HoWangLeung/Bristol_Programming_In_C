#include "specific.h"
// #include "../dict.h"
// #include <stdio.h>
// #include <string.h>

int hashcode(dict *x, const char *s);


bool dict_add(dict *x, const char *s)
{
    if (x == NULL)
    {
        return false;
    }
    // char *str = NULL;
    // str = (char *)ncalloc(strlen(s) + 1, sizeof(char));
    // strcpy(str, s);
    // printf("str = %s\n", str);

    int hash_value = hashcode(x, s);
    node *new_word = (node *)ncalloc(1, sizeof(node));
    new_word->value = (char *)ncalloc(strlen(s) + 1, sizeof(char));
    strcpy(new_word->value, s);
    new_word->next = NULL;
    //printf("v = %s\n",x->arr[hash_value]);
    if (x->arr[hash_value] == NULL)
    {
        x->arr[hash_value] = new_word;
    }
    else
    {
        //printf("already occupied\n");
        node *temp = x->arr[hash_value];
        while (temp->next)
        {
            temp = temp->next;
        }

        temp->next = new_word;
        // free(temp);
    }

    return true;
}

bool dict_spelling(dict *x, const char *s)
{
    // printf("\nBEGIN------------>\n");
    // printf("in spell check \n");
    // printf("in spell check , checking < %s > -> \n", s);
    if (x == NULL)
    {
        return false;
    }

    int hash_value = hashcode(x, s);
    //printf("hashcode = %d\n", hash_value);
    //  printf(" proceed 2 %s , hashcode = %d\n", x->arr[hash_value]->value, hash_value);
    node *temp = x->arr[hash_value];
    // printf("temp value = %d\n", temp);

    if (temp != 0 && strcmp(x->arr[hash_value]->value, s) == 0)
    {
        //printf("<<=========true============>>\n");
        return true;
    }
    // printf("need to check next in the chain ----->>\n");

    while (temp != 0 && temp->next)
    {
        temp = temp->next;
        if (strcmp(temp->value, s) == 0)
        {
            // printf("<<=========true 2nd============>>\n");
            return true;
        }
    }
    //printf("<<=====================>>\n");
    return false;

    //return true;
}

dict *dict_init(unsigned int maxwords)
{
    dict *d = (dict *)ncalloc(1, sizeof(dict));
    d->arr = (node **)ncalloc(maxwords * 2, sizeof(node *));

    int m = maxwords * 2;

    for (int i = 0; i < m; i++)
    {
        d->arr[i] = NULL;
    }

    d->size = maxwords;
    d->max_size = maxwords * 2;

    return d;
}

void dict_free(dict *x)
{
    printf("freeing\n");
    int i;
    for (i = 0; i < x->max_size; i++)
    {
        node *start = x->arr[i];
        while (start != NULL)
        {
            node *temp = start;
            start = start->next;
             free(temp->value);
            free(temp);
        }
        free(start);
    }
    free(x->arr);
   
    free(x);
}

int hashcode(dict *x, const char *s)
{

    unsigned long hash = 5381;
    int c;
    while ((c=(*s++)))
    {
        hash=33*hash^c;
    }
    return (int)(hash%x->max_size);

   // int length = strlen(name);
    // unsigned int hash_value = 0;

    // for (int i = 0; i < (int)strlen(name); i++)
    // {
    //     hash_value += name[i];
    //     hash_value = hash_value * name[i] % x->max_size;
    // }

    // // printf("hash_values for %s = %d\n", name, hash_value);

    // return hash_value;
}
// int hashcode(int key)
// {
// 	return (key % max);
// }

void mysprinter(dict *x)
{

    int i;

    for (i = 0; i < x->max_size; i++)
    //for (i = 0; i < 251909; i++)
    {
        node *temp = x->arr[i];
        printf("dict[%d]-->", i);
        while (temp)
        {
            printf("%s -->", temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}
