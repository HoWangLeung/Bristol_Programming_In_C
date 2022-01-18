#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>
#define MAXNUMTOKENS 100
#define MAXTOKENSIZE 20
#include "../General/general.h"

#ifdef TESTMODE
#define ERROR(PHRASE)                                             \
   {                                                              \
      fprintf(stderr,                                             \
              "Fatal Error %s occurred in %s, line %d\n", PHRASE, \
              __FILE__, __LINE__);                                \
      return false;                                               \
   }
#else
#define ERROR(PHRASE)                                             \
   {                                                              \
      fprintf(stderr,                                             \
              "Fatal Error %s occurred in %s, line %d\n", PHRASE, \
              __FILE__, __LINE__);                                \
      exit(EXIT_FAILURE);                                         \
   }
#endif
#define strsame(A, B) (strcmp(A, B) == 0)

struct var
{
   int **num;
   int y;
   int x;
   int max_loop;
   int start;
   int pos;
   // int count;
   // int count;
};
typedef struct var var;

struct StackNode
{
   var *data;
   struct StackNode *next;
};
typedef struct StackNode StackNode;
struct prog
{
   char wds[MAXNUMTOKENS][MAXTOKENSIZE];
   int cw; // Current Word
   var variables[26];
   int pos;
   StackNode *stacknode;
   int start;
   int count;
};
typedef struct prog Program;

//LEVEL1
bool PROG(Program *p);
bool INSTRCLIST(Program *p);
bool INSTRC(Program *p);

//LEVEL2
bool PRINT(Program *p);
bool SET(Program *p);
bool CREATE(Program *p);
bool LOOP(Program *p);

//LEVEL3
bool POLISHLIST(Program *p);
bool POLISH(Program *p);
bool VARNAME(Program *p);
bool STRING(Program *p);

bool FILENAME(Program *p);
bool ROWS(Program *p);
bool COLS(Program *p);
bool INTEGER(Program *p);

//LEVEL4
bool PUSHDOWN(Program *p);
bool UNARYOP(Program *p);
bool BINARYOP(Program *p);
void printCur(Program *p, int line);

//other
bool LEFTBRACKET(Program *p);

void read_file(FILE *file_pointer, Program *p);
bool testmode();

void allocate_space(Program *p);
bool set_value(Program *p, var *v);

int get_pos(Program *p);

bool print_variable(var v);
//A-Z
//2d-array | INTEGER |

//STACK

var get_value(Program *p);

StackNode *newNode(var *data);

bool isEmpty(struct StackNode *root);

void push(struct StackNode **root, var *data);

var *pop(struct StackNode **root);

void free_stack_node(var *v);
void increment_cw(Program *p);

//EXTENSION

bool IF(Program *p);
bool COND(Program *p);

bool EQUALS(Program *p);

bool COMPARE(Program *p);

int search_next_right_bracket(Program *p);

//SORT OP


