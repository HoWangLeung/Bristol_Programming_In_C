#include "../nlab.h"

struct StackNode *newNode(var *data)
{
    struct StackNode *stackNode =
        (struct StackNode *)
            malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

bool isEmpty(struct StackNode *root)
{
    return !root;
}

void push(struct StackNode **root, var *data)
{

    struct StackNode *stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
}

var *pop(struct StackNode **root)
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



