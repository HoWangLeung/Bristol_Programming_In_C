
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
// #include "driver.c"

bool check(const char *s);

int main(void)
{

    assert(check("A man, a plan, a canal: Panama"));
    assert(check("racecar"));
    assert(!check("racecard"));
    return 0;
}
