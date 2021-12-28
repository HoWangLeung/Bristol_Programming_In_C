#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <ctype.h>
#define MAXNUMTOKENS 100
#define MAXTOKENSIZE 20
#include "../General/general.h"

#ifdef TESTMODE
#define ERROR(PHRASE) \
   {                                                              \
     fprintf(stderr,                                             \
              "Fatal Error %s occurred in %s, line %d\n", PHRASE, \
              __FILE__, __LINE__);                                \
      return false;   \
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

struct var {
   int ** num;
   int y;
   int x;
};
typedef struct var var;
struct prog
{
   char wds[MAXNUMTOKENS][MAXTOKENSIZE];
   int cw; // Current Word
   var* variables[26];
   int pos;
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
bool testmode(char *PHRASE);

void allocate_space(Program *p);
bool set_value(Program *p);


var* get_value(Program *p);

int get_pos(Program *p);

bool print_variable(var * v);

//A-Z
//2d-array | INTEGER |
