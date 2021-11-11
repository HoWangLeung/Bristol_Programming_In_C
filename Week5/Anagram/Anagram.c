#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define FNAME "dictionary.txt"
#define BIGSTR 500
#define MAX 370119
int comp(const void *a, const void *b);
int check_anagram(char[], char[]);
void sort_string(char *string);
int binary_search(char **dictionary, int l, int r, char *str);
void sort_dictionary(char **dictionary);
bool is_a_larger_then_b(char *a, char *b);
int getAsciiTotal(char *word);
void swap(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}
void permute(char *a, int l, int r, char **dictionary)
{
  int i;
  if (l == r)
  {
    int res = binary_search(dictionary, 0, MAX, a);
    if (res !=-1)
    {
      printf("anagram = %s\n", dictionary[res]);
    }
  }
  else
  {
    for (i = l; i <= r; i++)
    {
      swap((a + l), (a + i));
      permute(a, l + 1, r,dictionary);
      swap((a + l), (a + i)); 
    }
  }
}
int getAsciiTotal(char *word)
{
  int sum = 0;
  for (int i = 0; i < strlen(word); i++)
  {
    sum += word[i];
  }
  return sum;
}
int main()
{
  char user_input[] = "angriest";
  char s[50];
  FILE *fp = fopen(FNAME, "r");
  char board[100][100];
  int line = 0;
  char input[512];
  char sizeArr[512];
  int sz;
  char **dictionary;
  dictionary = (char **)malloc(100 * MAX * sizeof(char *));
  for (int i = 0; i < MAX; i++)
  {
    dictionary[i] = (char *)malloc(100 * sizeof(char));
  }
  int i = 0;
  while (fgets(input, sizeof(input), fp))
  {
    int len = strlen(input);
    if (input[len - 1] == '\n')
      input[--len] = '\0';
    strcpy(dictionary[i++], input);
  }
  printf("user input = %s\n", user_input);
  sort_dictionary(dictionary);
  int idx = binary_search(dictionary, 0, MAX, user_input);
  printf("res = %s\n", dictionary[idx]);
  permute(dictionary[idx], 0, strlen(dictionary[idx]) - 1, dictionary);
  free(dictionary);
  return 0;
}
bool is_a_larger_then_b(char *a, char *b)
{
  if (strcmp(a, b) > 0)
  {
    return true;
  }
  else
  {
    return false;
  }
}
void sort_dictionary(char **dictionary)
{
  char temp[225];
  qsort(dictionary, MAX, sizeof(*dictionary), comp);
}
int comp(const void *a, const void *b)
{
  char *const *pp1 = a;
  char *const *pp2 = b;
  return strcmp(*pp1, *pp2);
}
int binary_search(char **dictionary, int l, int r, char *str)
{
  if (r >= l)
  {
    int mid = l + (r - l) / 2;
    if (strcmp(dictionary[mid], str) == 0)
    {
      printf("found the match -> ");
      return mid;
    }
    if (strcmp(dictionary[mid], str) > 0)
      return binary_search(dictionary, l, mid - 1, str);
    return binary_search(dictionary, mid + 1, r, str);
  }
  return -1;
}
void sort_string(char *string)
{
  int n = strlen(string);
  for (int i = 0; i < n - 1; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (string[i] > string[j])
      {
        char temp = string[i];
        string[i] = string[j];
        string[j] = temp;
      }
    }
  }
}
