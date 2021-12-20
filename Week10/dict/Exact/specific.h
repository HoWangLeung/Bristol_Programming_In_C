#include"../dict.h"

struct node
{
	 char *value;
	struct node *next;
};
typedef struct node node;

struct dict
{
	node **arr;
	int max_size;
};
void mysprinter(dict *x);
