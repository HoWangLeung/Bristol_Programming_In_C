#include"../dict.h"

#define FORMATSTR "%i"
#define ELEMSIZE 20

#define STACKTYPE "FIXED"

#define FIXEDSIZE 16
#define SCALEFACTOR 2
#define SIZE 400000
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
