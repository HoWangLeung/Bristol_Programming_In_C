#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include<assert.h>
int isogram(char *s);

int main(void)
{
    assert(isogram("programming") == 0);
    assert(isogram("housewarmings") == 0);
    assert(isogram("abductions") == 1);
    assert(isogram("housewarming") == 1);
    assert(isogram("hydromagnetics") == 1);
    assert(isogram("uncopyrightable") == 1);
    return 0;
}
