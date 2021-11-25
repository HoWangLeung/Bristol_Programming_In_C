#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <stdbool.h>

bool derange(const char *s1, const char *s2);

int main(void)
{
    assert(derange("elvis", "lives") == 0);
    assert(derange("dreads", "sadder") == 1);
    assert(derange("replays", "parsley") == 1);
    assert(derange("listen", "silent") == 0);
    assert(derange("orchestra", "carthorse") == 1);
    return 0;
}
