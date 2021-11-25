
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdbool.h>
// #include "driver.c"

bool check(const char *s1, const char *s2);

int main(void)
{

    check("Hello World!", "World! & Everyone Helloo.");
    return 0;
}
