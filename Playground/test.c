
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
bool test();
int main(int argc, char **argv)
{
    printf("%d\n", test());

    return 0;
}

bool test()
{

    for (int i = 0; i < 10; i++)
    {
        if (i == 5)
        {
            return false;
        }
    }
    return true;
}
