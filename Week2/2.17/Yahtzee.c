#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#define MAXTHROW 6
#define NUMDICE 5
#define TESTS 10000000
enum bool
{
    false,
    true
};
typedef enum bool bool;
/* Fill the array d with random numbers 1..6 */
void randomthrow(int d[NUMDICE]);
// /* Decide if the number n occurs anywhere in the histogram h */
bool histo_has(const int h[MAXTHROW], const int n);
// /* Compute a histogram, given a dice hand */
void makehist(const int d[NUMDICE], int h[MAXTHROW]);
// /* Check that the histograms h1 & h2 are the same */
bool hists_same(const int h1[MAXTHROW], const int h2[MAXTHROW]);
// /* Does this hand have 2 lots of one number and 3 lots of another */
bool isfullhouse(const int d[NUMDICE]);
// /* Does this hand have 4 lots of one number and 1 of another ? */
bool is4ofakind(const int d[NUMDICE]);
// /* Do some testing of the functions required */
void test(void);
int main(void)
{
    srand(time(NULL));
    int dice[NUMDICE];
    int k4 = 0;
    int fh = 0;
    int i;
    test();
    for (i = 0; i < TESTS; i++)
    {
        randomthrow(dice);

        if (isfullhouse(dice))
        {
            fh++;
        }
        if (is4ofakind(dice))
        {
            k4++;
        }
    }
    printf("FH=%.2f%% 4oK=%.2f%%\n", (double)fh * 100.0 / (double)TESTS,
           (double)k4 * 100.0 / (double)TESTS);
    return 0;
}

bool isfullhouse(const int d[])
{
    bool hasThree = false;
    bool hasTwo = false;
    int histogram[MAXTHROW];
    makehist(d, histogram);
    for (int i = 0; i < MAXTHROW; i++)
    {
        printf("%d ", histogram[i]);
        if (histogram[i] == 2)
        {
            hasTwo = true;
        }
        if (histogram[i] == 3)
        {
            hasThree = true;
        }
    }
    return hasTwo && hasThree;
}

bool is4ofakind(const int d[])
{
    bool hasOne = false;
    bool hasFour = false;
    int histogram[MAXTHROW];
    makehist(d, histogram);
    for (int i = 0; i < MAXTHROW; i++)
    {
        if (histogram[i] == 1)
        {
            hasOne = true;
        }
        if (histogram[i] == 4)
        {
            hasFour = true;
        }
    }
    return hasOne && hasFour;
}

void randomthrow(int d[NUMDICE])
{

    for (int i = 0; i < 5; i++)
    {
        d[i] = rand() % ((6 + 1) - 1) + 1;
        // printf("%d\n", d[i]);
    }

    //SORT BY VALUE
    int temp;

    for (int i = 0; i < 5; i++)
    {

        for (int j = i + 1; j < 5; j++)
        {
            if (d[j] < d[i])
            {
                temp = d[i];
                d[i] = d[j];
                d[j] = temp;
            }
        }
    }
    // for(int i = 0;i<5;i++){
    //     printf("%d ,",d[i]);
    // }
    // printf("\n");
}

bool hists_same(const int h1[MAXTHROW], const int h2[MAXTHROW])
{
    for (int i = 0; i < MAXTHROW; i++)
    {
        if (h1[i] != h2[i])
        {
            return false;
        }
    }
    return true;
}

bool histo_has(const int h[MAXTHROW], const int n)
{
    for (int i = 0; i < MAXTHROW; i++)
    {
        if (h[i] == n)
        {
            return true;
        }
    }
    return false;
}

void makehist(const int d[NUMDICE], int h[MAXTHROW])
{
    int num_of_1 = 0;
    int num_of_2 = 0;
    int num_of_3 = 0;
    int num_of_4 = 0;
    int num_of_5 = 0;
    int num_of_6 = 0;

    for (int i = 0; i < NUMDICE; i++)
    {
        if (d[i] == 1)
        {
            num_of_1++;
        }
        else if (d[i] == 2)
        {
            num_of_2++;
        }
        else if (d[i] == 3)
        {
            num_of_3++;
        }
        else if (d[i] == 4)
        {
            num_of_4++;
        }
        else if (d[i] == 5)
        {
            num_of_5++;
        }
        else if (d[i] == 6)
        {
            num_of_6++;
        }
    }

    h[0] = num_of_1;
    h[1] = num_of_2;
    h[2] = num_of_3;
    h[3] = num_of_4;
    h[4] = num_of_5;
    h[5] = num_of_6;
}

void test(void)
{
    int i, j;
    int h1[MAXTHROW] = {0, 0, 0, 0, 0, 5}; /* 5−of−a−kind */
    int h2[MAXTHROW] = {0, 0, 5, 0, 0, 0}; /* 5−of−a−kind */
    int h3[MAXTHROW] = {0, 2, 0, 0, 3, 0}; /* Full−House */
    int h4[MAXTHROW] = {2, 0, 3, 0, 0, 0}; /* Full−House */
    int h5[MAXTHROW] = {3, 2, 0, 0, 0, 0}; /* Histo of d1 */
    int h6[MAXTHROW] = {0, 0, 0, 2, 3, 0}; /* Histo of d2 */
    int h7[MAXTHROW] = {4, 1, 0, 0, 0, 0}; /* Histo of d3 */
    int h8[MAXTHROW] = {0, 0, 0, 0, 1, 4}; /* Histo of d4 */
    int h9[MAXTHROW];                      /* Temp */
    int d1[NUMDICE] = {1, 1, 1, 2, 2};     /* Full House */
    int d2[NUMDICE] = {5, 4, 5, 4, 5};     /* Full House */
    int d3[NUMDICE] = {2, 1, 1, 1, 1};     /* 4−of−a−kind */
    int d4[NUMDICE] = {6, 6, 6, 6, 5};     /* 4−of−a−kind */
    int d5[NUMDICE] = {6, 6, 6, 6, 5};     /* Temp */
    /* Tricky to test a random throw ... */
    for (i = 0; i < 100; i++)
    {
        randomthrow(d5);
        for (j = 0; j < NUMDICE; j++)
        {
            assert((d5[j] >= 1) && (d5[j] <= MAXTHROW));
        }

        makehist(d5, h9);

        for (j = 0; j < MAXTHROW; j++)
        {
            assert((h9[j] >= 0) && (h9[j] <= NUMDICE));
        }
    }
    assert(hists_same(h1, h1) == true);
    assert(hists_same(h5, h5) == true);
    assert(hists_same(h1, h2) == false);
    assert(hists_same(h4, h5) == false);
    makehist(d1, h9);
    assert(hists_same(h9, h5));
    makehist(d2, h9);
    assert(hists_same(h9, h6));
    makehist(d3, h9);
    assert(hists_same(h9, h7));
    makehist(d4, h9);
    assert(hists_same(h9, h8));
    assert(histo_has(h1, 5) == true);
    assert(histo_has(h1, 0) == true);
    assert(histo_has(h1, 2) == false);
    assert(histo_has(h2, 5) == true);
    assert(histo_has(h2, 0) == true);
    assert(histo_has(h2, 2) == false);
    assert(histo_has(h3, 3) == true);
    assert(histo_has(h3, 2) == true);
    assert(histo_has(h3, 1) == false);
    assert(histo_has(h4, 3) == true);
    assert(histo_has(h4, 2) == true);
    assert(histo_has(h4, 1) == false);
    assert(isfullhouse(d1) == true);
    assert(isfullhouse(d2) == true);
    assert(is4ofakind(d1) == false);
    assert(is4ofakind(d2) == false);
    assert(isfullhouse(d3) == false);
    assert(isfullhouse(d4) == false);
    assert(is4ofakind(d3) == true);
    assert(is4ofakind(d4) == true);
}
