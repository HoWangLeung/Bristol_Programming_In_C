#include "../nlab.h"

 StackNode *newNode(var *data)
{
     StackNode *stackNode =
        ( StackNode *)
            malloc(sizeof( StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

bool isEmpty( StackNode *root)
{
    return !root;
}

void push( StackNode **root, var *data)
{

     StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

var *pop( StackNode **root)
{

    if (isEmpty(*root))
    {
        //  printf("EMPTY!!!!!!!!!!\n");
        return NULL;
    }
    struct StackNode *temp = *root;
    *root = (*root)->next;
    var *popped = temp->data;
    free(temp);
    return popped;
}

void free_stack_node(var *v)
{
    for (int y = 0; y < v->y; y++)
    {
        free(v->num[y]);
    }
    free(v->num);
    free(v);
}



