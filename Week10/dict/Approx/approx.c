#include "specific.h"
#define KHASHES 11

unsigned long *_hashes(const char *s, int max_size);
int hashcode(const char *s);
void test();

void test()
{

    printf("END OF OWN TESTING\n");
}

bool dict_add(dict *x, const char *s)
{
    if (x == NULL)
    {
        return false;
    }
    int max_size = x->max_size;
    unsigned long *hash_value = _hashes(s, max_size);

    if (!dict_spelling(x, s))
    {
        for (int i = 0; i < KHASHES; i++)
        {
            x->arr[hash_value[i]] = 1;
        }
    }

    free(hash_value);

    return true;
}

bool dict_spelling(dict *x, const char *s)
{
    if (x == NULL)
    {
        return false;
    }
    //("==================\n");
    int max_size = x->max_size;
    // printf("max size = %d\n", max_size);
    unsigned long *hash_value = _hashes(s, max_size);
    for (int j = 0; j < KHASHES; j++)
    {
        if (x->arr[hash_value[j]] != 1)
        {
            free(hash_value);
            return false;
        }
    }
    free(hash_value);
    return true;
}

dict *dict_init(unsigned int maxwords)
{
    test();
    dict *d = (dict *)ncalloc(1, sizeof(dict));
    d->arr = (bool *)ncalloc(maxwords * 22, sizeof(bool));
    d->max_size = maxwords * 22;
    return d;
}

void dict_free(dict *x)
{
    free(x->arr);
    free(x);
}

unsigned long *_hashes(const char *s, int max_size)
{
    unsigned long *hashes = ncalloc(KHASHES, sizeof(unsigned long));

    unsigned long bh = hashcode(s);
    int ln = strlen(s);
    srand(bh * (ln * s[0] + s[ln - 1]));
    unsigned long h2 = bh;
    for (int i = 0; i < KHASHES; i++)
    {
        h2 = 33 * h2 ^ rand();
        hashes[i] = (unsigned long)(h2 % max_size);
        //  printf("hashes[%d] = %lu \n", i, hashes[i]);
    }

    return hashes;
}

int hashcode(const char *s)
{

    unsigned long hash = 5381;
    int c;
    while ((c = (*s++)))
    {
        hash = 33 * hash ^ c;
    }
    return (hash);
}
