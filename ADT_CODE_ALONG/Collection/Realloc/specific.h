#define COLLTYPE "Realloc"
#define FIXEDSIZE 16
#define SCALEFACTOR 2

struct coll
{
    colltype*a;
    int size;
    int capacity;
};
