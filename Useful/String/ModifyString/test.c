#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#define MAX_NAME_LEN 50

void modify(char **s)
{
    char *new_name = "new";
    *s = new_name;
}
void modify2(char *s)
{
    char *new_name = "new";
    strcpy(s, new_name);
}

int main()
{
    //approach 1 - equal
    char *name1 = "old text";
    modify(&name1);
    printf("%s\n", name1);


    char name2[100] = "random text";
    modify2(name2);
    printf("%s\n", name2);
    //name2[strlen(name2)] = '\0';

    assert(strcmp(name1, name2) == 0);

    return 0;
}
