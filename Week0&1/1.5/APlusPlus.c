#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>
#define HEIGHT 5

int main(void)
{
    int a, b = 0, c = 0;
    a = ++b + ++c;
    assert(a == 2);
    assert(b == 1);
    assert(c == 1);

    a = b++ + c++;
    assert(a == 2);
    assert(b == 2);
    assert(c == 2);

    a = ++b + c++;
    assert(a == 5);
    assert(b == 3);
    assert(c == 3);

    a = (b--) + (--c);
    assert(a == 5);
    assert(b == 2);
    assert(c == 2);
}
