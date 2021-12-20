#include "specific.h"
#include <assert.h>
#define KHASHES 11
#define MAG_HASH_1 5381
#define MAG_HASH_2 33
#define MAX_FACTOR 22

unsigned long *_hashes(const char *s, int max_size);
int hashcode(const char *s);

void test();
dict *create_new_dict(int maxwords);

dict *create_new_dict(int maxwords)
{
    dict *d = (dict *)ncalloc(1, sizeof(dict));
    d->max_size = maxwords * MAX_FACTOR;
    d->arr = (bool *)ncalloc(d->max_size, sizeof(bool));
    return d;
}

void test()
{
    //====================================================================
    //========= Test create_new_dict() ===================================
    //====================================================================
    dict *t0 = create_new_dict(20);
    assert(t0->max_size == 440);

    dict *t1 = create_new_dict(100);
    assert(t1->max_size == 2200);
    //====================================================================
    //========= Test hashcode() ==========================================
    //====================================================================
    unsigned long *hash_value = _hashes("Hello", t0->max_size);
    for (int i = 0; i < KHASHES; i++)
    {
        assert(hash_value[i] >= 0);
        assert((int)hash_value[i] <= t0->max_size);
    }
    free(hash_value);
    dict_free(t0);
    dict_free(t1);
    
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
            x->arr[hash_value[i]] = true;
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
    int max_size = x->max_size;
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
    dict *d = create_new_dict(maxwords);
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
        h2 = MAG_HASH_2 * h2 ^ rand();
        hashes[i] = (unsigned long)(h2 % max_size);
    }
    return hashes;
}

int hashcode(const char *s)
{
    unsigned long hash = MAG_HASH_1;
    int c;
    while ((c = (*s++)))
    {
        hash = MAG_HASH_2 * hash ^ c;
    }
    return (hash);
}
