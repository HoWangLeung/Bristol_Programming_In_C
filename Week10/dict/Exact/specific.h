#include"../dict.h"

struct node
{
	// int key;
	 char *value;
	struct node *next;
};
typedef struct node node;

struct dict
{
	node **arr;
	int size;
	int max_size;
};
void mysprinter(dict *x);
