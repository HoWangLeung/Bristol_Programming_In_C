

#define FORMATSTR "%i"
#define ELEMSIZE 20

#define STACKTYPE "Realloc"

#define FIXEDSIZE 16
#define SCALEFACTOR 2
struct boolarr {
   /* Underlying array */
   int* a;
   int size;
   int capacity;
};
typedef struct boolarr boolarr;