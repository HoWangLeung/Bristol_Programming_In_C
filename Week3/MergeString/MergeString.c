#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
typedef enum bool
{
    false,
    true
} bool;
void strmerge(const char *s1, const char *s2, char *s3);
#define LARGESTRING 1000
int main(void)
{
    char s[LARGESTRING];
    strmerge("Hello World!", "World! & Everyone.", s);
    assert(strcmp(s, "Hello World! & Everyone.") == 0);
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
    printf("S3 = %s\n", s);
    return 0;
}

void strmerge(const char *s1, const char *s2, char *s3)
{
    bool hasSame = false;
    char _s1[100];
    char _s2[100];
    memset(s3, 0, strlen(s3));
    int ls1 = strlen(s1);
    int ls2 = strlen(s2);
    printf("length of s1 = %d\n", ls1);
    printf("length of s2 = %d\n", ls2);
    if (ls2 == 0)
    {
        strcpy(s3, s1);
        return;
    }
    if (ls2 > ls1)
    {
        for (int i = 0; i < ls1; i++)
        {
            strncpy(_s1, s1 + i, ls1);
            strncpy(_s2, s2, ls2 - i);
            if ((strncmp(_s1, s2, strlen(_s1))) == 0)
            {
                hasSame = true;
                printf("hit S1 = %s\n", _s1);
                strncpy(s3, s1, i);
            }
        }

        strcat(s3, s2);
    }
    else if (ls1 > ls2)
    {
        printf("S1 IS LONGER\n");
        //"123412341234", "1234"
        for (int i = 0; i < ls1; i++)
        {
            strncpy(_s1, s1 + (ls1 - ls2), ls1);
            strncpy(_s2, s2, ls2);
            if ((strncmp(_s1, s2, strlen(_s2))) == 0)
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
    printf("hasSame = %s\n", hasSame == 0 ? "false" : "true");
}