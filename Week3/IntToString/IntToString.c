#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum bool
{
    false,
    true
};
typedef enum bool bool;
char *my_itoa(int num, char *str, int base);
char *my_reverse(char *str);
void int2string(int i, char s[]);
int string_length(char *pointer);

int main(void)
{
    int i;
    char s[256];
    scanf("%d", &i);
    int2string(i, s);

    printf("result = %s\n", s);

    return 0;
}

void int2string(int i, char s[])
{
    char *c = my_itoa(i, s, 10);
}
int string_length(char *pointer)
{
    int c = 0;

    while (*(pointer + c) != '\0')
        c++;

    return c;
}
char *my_reverse(char *string)
{
   	char temp;
	int i, j, n;
	n = string_length(string)-1;

	// swapping string[i] and string[j] until i<j
  for(i=0;i<n/2;i++){
      temp=string[i];
      string[i]=string[n];
      string[n]=temp;
      n--;
   }

    return string;
}
// Implementation of itoa()
char *my_itoa(int num, char str[], int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i] = '0';
        i++;
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        //because '0' is 48 in ASCII
        str[i] = rem + '0';
        num = num / base;
        i++;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
     my_reverse(str);

    return str;
}