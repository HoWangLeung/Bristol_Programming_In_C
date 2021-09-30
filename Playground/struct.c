#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

typedef struct
{
    int length;
    int width;
} rectangle;

typedef struct position
{
    int x;
    int y;
} position;

typedef struct buildingPlan
{
   rectangle rectangle;
   position position;
};


int main()
{
    rectangle myRectangle = {5, 10};

    printf("Length: %d. Width:%d\n", myRectangle.length, myRectangle.width);

    printf("finished");

    return 0;
}