#include "specific.h"
// #include "../dict.h"
// #include <stdio.h>
// #include <string.h>

int hashcode(dict *x, const char *s);
void test();

dict *allocateData(int maxwords);

dict *allocateData(int maxwords)
{
    

    dict *t = (dict *)ncalloc(1, sizeof(dict));
    t->arr = (node **)ncalloc(maxwords * 2, sizeof(node *));
    int m = maxwords * 2;
    for (int i = 0; i < m; i++)
    {
        t->arr[i] = NULL;
    }
    t->max_size = maxwords * 2;

    return t;
}

void test()
{
    dict *t1 = allocateData(50);
    assert(t1->max_size == 100);

    dict *t2 = allocateData(150);
    assert(t2->max_size == 300);



    printf("END OF OWN TESTING --> EXACT \n");
}

bool dict_add(dict *x, const char *s)
{
    if (x == NULL)
    {
        return false;
    }

    int hash_value = hashcode(x, s);
    node *new_node = (node *)ncalloc(1, sizeof(node));
    new_node->value = (char *)ncalloc(strlen(s) + 1, sizeof(char));
    strcpy(new_node->value, s);
    new_node->next = NULL;

    if (x->arr[hash_value] == NULL)
    {
        x->arr[hash_value] = new_node;
    }
    else
    {

        node *temp = x->arr[hash_value];
        if (strcmp(temp->value, s) == 0)
        {
            return true;
        }
        while (temp->next)
        {
            temp = temp->next;
            if (strcmp(temp->value, s) == 0)
            {
                return true;
            }
        }
        temp->next = new_node;
    }

    return true;
}

bool dict_spelling(dict *x, const char *s)
{
    if (x == NULL)
    {
        return false;
    }

    int hash_value = hashcode(x, s);
    node *temp = x->arr[hash_value];

    if (temp != 0 && strcmp(x->arr[hash_value]->value, s) == 0)
    {
        return true;
    }

    while (temp != 0 && temp->next)
    {
        temp = temp->next;
        if (strcmp(temp->value, s) == 0)
        {

            return true;
        }
    }

    return false;
}

dict *dict_init(unsigned int maxwords)
{
    test();
    dict *d = allocateData(maxwords);
    // dict *d = (dict *)ncalloc(1, sizeof(dict));
    // d->arr = (node **)ncalloc(maxwords * 2, sizeof(node *));

    // int m = maxwords * 2;

    // for (int i = 0; i < m; i++)
    // {
    //     d->arr[i] = NULL;
    // }
    // d->max_size = maxwords * 2;

    return d;
}

void dict_free(dict *x)
{
    //printf("freeing\n");
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
    while ((c = (*s++)))
    {
        hash = 33 * hash ^ c;
    }
    return (int)(hash % x->max_size);
}

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
