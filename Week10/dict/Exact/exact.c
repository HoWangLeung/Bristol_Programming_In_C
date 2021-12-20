#include "specific.h"
#include <assert.h>
#define MAG_HASH_1 5381
#define MAG_HASH_2 33
#define MAX_FACTOR 2

int hashcode(dict *x, const char *s);
void test();
dict *create_new_dict(int maxwords);
node *create_new_node(const char *s);
bool append_new_node(dict *x, const char *s, node *new_node, int hash_value);
bool search(node **temp, const char *s);
void free_node(node *n);

bool dict_add(dict *x, const char *s)
{
    if (x == NULL)
    {
        return false;
    }

    int hash_value = hashcode(x, s);
    node *new_node = create_new_node(s);
    if (x->arr[hash_value] == NULL)
    {
        x->arr[hash_value] = new_node;
    }
    else
    {
        //first check if s had already been added
        // if yes return true early, else append the node and return true
        if (append_new_node(x, s, new_node, hash_value))
        {
            return true;
        }
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
    if ((temp != NULL && strcmp(x->arr[hash_value]->value, s) == 0) || search(&temp, s))
    {
        return true;
    }
    return false;
}

dict *dict_init(unsigned int maxwords)
{
    test();
    dict *d = create_new_dict(maxwords);
    return d;
}

void dict_free(dict *x)
{
    int i;
    for (i = 0; i < x->max_size; i++)
    {
        node *start = x->arr[i];
        while (start != NULL)
        {
            node *temp = start;
            start = start->next;
            free_node(temp);
        }
        free(start);
    }
    free(x->arr);
    free(x);
}

int hashcode(dict *x, const char *s)
{
    unsigned long hash = MAG_HASH_1;
    int c;
    while ((c = (*s++)))
    {
        hash = MAG_HASH_2 * hash ^ c;
    }
    return (int)(hash % x->max_size);
}



bool search(node **temp, const char *s)
{
    while (*temp != NULL && (*temp)->next)
    {
        *temp = (*temp)->next;
        if (strcmp((*temp)->value, s) == 0)
        {
            return true;
        }
    }

    return false;
}

bool append_new_node(dict *x, const char *s, node *new_node, int hash_value)
{
    node *temp = x->arr[hash_value];
    if (strcmp(temp->value, s) == 0 || search(&temp, s))
    {
        free_node(new_node);
        return true;
    }
    temp->next = new_node;

    return false;
}

node *create_new_node(const char *s)
{
    node *new_node = (node *)ncalloc(1, sizeof(node));
    new_node->value = (char *)ncalloc(strlen(s) + 1, sizeof(char));
    strcpy(new_node->value, s);
    new_node->next = NULL;
    return new_node;
}

dict *create_new_dict(int maxwords)
{
    if (maxwords <= 0)
    {
        //on_error("maxwords must be greater then 0 ");
        exit(EXIT_FAILURE);
    }
    dict *t = (dict *)ncalloc(1, sizeof(dict));
    t->arr = (node **)ncalloc(maxwords * MAX_FACTOR, sizeof(node *));
    t->max_size = maxwords * MAX_FACTOR;
    for (int i = 0; i < t->max_size; i++)
    {
        t->arr[i] = NULL;
    }

    return t;
}

void test()
{

    //====================================================================
    //========= Test create_new_dict() ===================================
    //====================================================================
    const char *s0 = "Hello";
    const char *s1 = "World";
    const char *s2 = "christmas";
    const char *s2_1 = "holidayaaaaaa";
    // dict *t0 = allocateData(-999);
    dict *t0 = create_new_dict(50);
    assert(t0->max_size == 100);
    assert(t0->arr[rand() % t0->max_size] == NULL);

    dict *t1 = create_new_dict(150);
    assert(t1->max_size == 300);
    assert(t1->arr[rand() % t1->max_size] == NULL);

    dict *t2 = create_new_dict(10);
    assert(t2->max_size == 20);
    assert(t2->arr[rand() % t2->max_size] == NULL);

    //====================================================================
    //========= Test if hashcode is always the same ======================
    //====================================================================
    assert(hashcode(t0, "one") == 61);
    assert(hashcode(t0, "Christmas") == 9);
    assert(hashcode(t0, "computer") == 42);

    //====================================================================
    //========= Test if hash_value is within boundary ====================
    //====================================================================
    assert(hashcode(t0, "any_word") <= t0->max_size);
    assert(hashcode(t0, "!@#)(*)*(*&") <= t0->max_size);

    assert(hashcode(t0, "any_word") >= 0);
    assert(hashcode(t0, "!@#)(*)*(*&") >= 0);

    //====================================================================
    //========= Test if node can be created properly =====================
    //====================================================================

    node *test_node_0 = create_new_node(s0);
    assert(strcmp(test_node_0->value, s0) == 0);
    assert(test_node_0->next == NULL);
    //  free_node(test_node_0);

    node *test_node_1 = create_new_node(s1);
    int hash_value = hashcode(t0, s0);

    //======================================================================
    //========= Test if first node in linkedlist can be assigned ===========
    //======================================================================
    assert(t0->arr[hash_value] == NULL);
    t0->arr[hash_value] = test_node_1;
    assert(t0->arr[hash_value] != NULL);
    assert(strcmp(t0->arr[hash_value]->value, "World") == 0);

    //=====================================================
    //==========Test if linkedlist can be chained =========
    //=====================================================
    node *temp = t0->arr[hash_value];
    temp = temp->next;
    assert(temp == NULL);
    temp = test_node_0;
    assert(temp != NULL);
    assert(strcmp(temp->value, "Hello") == 0);
    //====================================================================================
    //==========Assert that the function append_new_node() works==========================
    //====================================================================================
    node *test_node_2 = create_new_node(s2);
    int hash_value_s2 = hashcode(t2, s2);
    assert(t2->arr[hash_value_s2] == NULL);
    t2->arr[hash_value_s2] = test_node_2;
    assert(t2->arr[hash_value_s2] != NULL);
    assert(strcmp(t2->arr[hash_value_s2]->value, s2) == 0);

    node *test_node_2_1 = create_new_node(s2_1);
    append_new_node(t2, s2_1, test_node_2_1, hash_value_s2);
    assert(test_node_2->next != NULL);
    assert(strcmp(t2->arr[hash_value_s2]->value, s2) == 0);
    assert(strcmp(t2->arr[hash_value_s2]->next->value, s2_1) == 0);

    //====================================================================================
    //==========Assert that the function search() works===================================
    //====================================================================================
    assert(search(&test_node_2, s2_1));
    assert(!search(&test_node_2, "unrelated_word_1"));

    free_node(temp);
    dict_free(t0);
    dict_free(t1);
    dict_free(t2);

}

void free_node(node *n)
{
    free(n->value);
    free(n);
}
