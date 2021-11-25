#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

void strmerge(const char *s1, const char *s2, char *s3);
#define LARGESTRING 1000
int main(void)
{
    char s[LARGESTRING];
    strmerge("Hello World!", "World! & Everyone Hello.", s);
    assert(strcmp(s, "Hello World! & Everyone Hello.") == 0);
    strmerge("The cat sat", "sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.") == 0);
    strmerge("The cat sat on the mat", "The cat sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.") == 0);
    strmerge("One ", "Two", s);
    assert(strcmp(s, "One Two") == 0);
    strmerge("", "The cat sat on the mat.", s);
    assert(strcmp(s, "The cat sat on the mat.") == 0);
    strmerge("The cat sat on the mat.", "", s);
    assert(strcmp(s, "The cat sat on the mat.") == 0);
    strmerge("123412341234", "1234", s);
    assert(strcmp(s, "123412341234") == 0);

    return 0;
}

void strmerge(const char *s1, const char *s2, char *s3) //s3 will store the merged result
{
    bool hasSame = false;
    char _s1[100];
    char _s2[100];
    memset(s3, 0, strlen(s3));
    int ls1 = strlen(s1);
    int ls2 = strlen(s2);
    if (ls2 == 0) // if s2 is empty, then simply copy s1 to s3
    {
        strcpy(s3, s1);
        return;
    }
    if (ls2 > ls1) // if length of s2 > s1, loop s1
    {
        for (int i = 0; i < ls1; i++)
        {
            strncpy(_s1, s1 + i, ls1);

            if ((strncmp(_s1, s2, strlen(_s1))) == 0)
            {
                hasSame = true;
                strncpy(s3, s1, i);
            }
        }
        strcat(s3, s2);
    }
    else if (ls1 > ls2) // if length of s2 > s1, loop s2
    {
        for (int i = 0; i < ls1; i++)
        {
            strncpy(_s1, s1 + (ls1 - ls2), ls1);

            if ((strncmp(_s1, s2, strlen(s2))) == 0)
            {
                hasSame = true;
                strcpy(s3, s1);
                return;
            }
            if (!hasSame)
            {
                strcpy(s3, s1);
            }
            strcat(s3, s2);
        }
    }
    printf("My answer : %s\n", s3);
}