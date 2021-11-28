#define FORMATSTR "%i"
#define ELEMSIZE 20
#define STACKTYPE "Linked"

struct dataframe
{
    stacktype i;
    struct dataframe*next;
};
typedef struct dataframe dataframe;

struct stack
{
    dataframe*start;
    int size;
    /* data */
};
