#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX 150
int my_strlen(char str[]);
char *my_strcpy(char *destination, const char *source);
void reverseArray(int arr[], int start, int end);
void remove_spaces_characters(char *s);
int main(void)
{

    printf("Input  a phrase:");
    char input[MAX];
    char reversed[MAX];
    int n = 0;
    fgets(input, MAX, stdin);

    for (int i = 0; input[i] != '\0'; ++i)
    {
        n = i;
    }
    for (int i = 0; i < n; i++)
    {
        char c = input[i];
        if (isupper(c))
        {
            c = tolower(c);
            input[i] = c;
        }
    }
    remove_spaces_characters(input);
    my_strcpy(reversed, input);
    int end = my_strlen(reversed);
    int start = 0;
    int temp;
    while (start < end)
    {
        temp = reversed[start];
        reversed[start] = reversed[end];
        reversed[end] = temp;
        start++;
        end--;
    }

    printf("string is: %s\n", reversed);
    for (int i = 0; i < my_strlen(reversed); i++)
    {
        if (input[i] != reversed[i])
        {
            printf("NOT a Palindrome\n");
            exit(0);
        }
    }
    printf("Valid Palindrome\n");
    return 0;
}

int my_strlen(char str[])
{
    int count = 0;
    int i = 0;
    while (str[i])
    {
        count++;
        i++;
    }
    // -1 due to \n in fgets
    return count - 1;
}

char *my_strcpy(char *destination, const char *source)
{
    if (destination == NULL)
    {
        return NULL;
    }
    char *ptr = destination;

    while (*source != 0)
    {
        *destination = *source;
        destination++;
        source++;
    };

    *destination = '\0';

    return ptr;
}

void remove_spaces_characters(char *str)
{
    int i, j;
    for (i = 0; str[i] != '\0'; ++i)
    {
        while (!((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z' || str[i] == '\0')))
        {
            for (j = i; str[j] != '\0'; ++j)
            {
                str[j] = str[j + 1];
            }
            str[j] = '\0';
        }
    }
}
