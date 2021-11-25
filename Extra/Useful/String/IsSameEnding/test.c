#include <stdio.h>
#include <string.h>

int strend(const char *s, const char *t);

int main(void)
{
    char *s1 = "Man is a rope stretched over an abyss.";
    char *s2 = "an abyss.";

    printf("%s\n", strend(s1, s2) ? "Yes" : "No");
    return 0;
}

int strend(const char *s, const char *t)
{
    int ls = strlen(s); // find length of s
    int lt = strlen(t); // find length of t
    printf("ls = %d\n", ls);
    printf("lt = %d\n", lt);
    printf("%s\n",s+1 );

    if (ls >= lt) // check if t can fit in s
    {
        // point s to where t should start and compare the strings from there
        return (0 == strncmp(t, s + (ls - lt), lt));
    }

    return 0;
}
