#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
// #include <limits.h>
// #include "../nlab.h"
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

void on_error(const char* s);
void* ncalloc(int n, size_t size);
void** n2dcalloc(int h, int w, size_t size);
void** n2drecalloc(void** p, int oh, int nh, int ow, int nw, size_t szelem);
void n2dfree(void**p, int h);
void* nrecalloc(void* p, int oldsz, int newsz);
void* nremalloc(void* p, int bytes);
void* nfopen(char* fname, char* mode);

bool digits_only(const char *s);

bool is_variable(const char *s);
FILE *h_open(char *filename);
bool is_string(const char *s);

