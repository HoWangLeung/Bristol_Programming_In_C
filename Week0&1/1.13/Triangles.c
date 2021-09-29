#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
void determineType(int a, int b, int c);
bool isValidTriangle(int a, int b, int c);

int main()
{
    double a, b, c;
    printf("To determine the type of a triangle, input the length of each side of:");
    scanf("%lf%lf%lf", &a, &b, &c);

    while (!isValidTriangle(a, b, c))
    {
        printf("To determine the type of a triangle, input the length of each side of:");
        scanf("%lf %lf %lf", &a, &b, &c);
    }
    printf("isValidTriangle ");
    printf("%lf%lf%lf\n", a, b, c);
    determineType(a, b, c);

    return 0;
}

bool isValidTriangle(int a, int b, int c)
{
    if ((a + b > c) && (a + c > b) && (b + c > a))
        return 1;

    return 0;
}

void determineType(int a, int b, int c)
{
    if (a == b && b == c)
    {
        printf("equaliteral\n");
    }
    else if (a == b || b == c || a == c)
    {
        printf("isosceles\n");
    }
    if (
        (a = sqrt(b * b + c * c)) ||
        (b = sqrt(a * a + c * c)) ||
        (c = sqrt(a * a + b * b)))
    {
        printf("right angled");
    }
    else
    {
        printf("unexpected type");
    }
}