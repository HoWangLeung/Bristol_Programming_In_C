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
    strcpy(dictionary[i++], input);
    // sort_string(input);
    // printf("%s\n", input);
  }

  //sort the dictionary
  sort_dictionary(dictionary);

  // for (int i = 0; i < MAX; i++)
  // {
  //   printf("%s\n", dictionary[i]);
  // }

  // int l = 0;
  // int r = 370119 - 1;
  // int targetIndex = binary_search(user_input, l, r, dictionary);

  free(dictionary);
  return 0;
}

void sort_dictionary(char **dictionary)
{
  char temp[225];
  // for (int i = 0; i <MAX; i++)
  // {
  //   for (int j = i + 1; j <MAX; j++)
  //   {
  //     if (strcmp(dictionary[i], dictionary[j]) > 0)
  //     {
  //      // printf(" i = %d j = %d\n", i, j);
  //       strcpy(temp, dictionary[i]);
  //       strcpy(dictionary[i], dictionary[j]);
  //       strcpy(dictionary[j], temp);
  //     }
  //   }
  // }
  //qsort(dictionary, MAX, sizeof(*dictionary), comp);

  // for (int i = 0; i < MAX; i++)
  // {
  //   printf("%s\n", dictionary[i]);
  // }
}

int comp(const void *a, const void *b)
{
  char *const *pp1 = a;
  char *const *pp2 = b;
  return strcmp(*pp1, *pp2);
}

// int binary_search(char **dictionary, int l, int r, char *str)
// {

//   if (r >= l)
//   {
//     int mid = l + (r - l) / 2;

//     // If the element is present at the middle
//     // itself
//     if (dictionary[mid] == str)
//       return mid;

//     // If element is smaller than mid, then
//     // it can only be present in left subarray
//     if (arr[mid] > x)
//       return binarySearch(arr, l, mid - 1, x);

//     // Else the element can only be present
//     // in right subarray
//     return binarySearch(arr, mid + 1, r, x);
//   }

//   // We reach here when element is not
//   // present in array
//   return -1;
//   return -1;
// }

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

// int check_anagram(char a[], char b[])
// {
//   int first[26] = {0}, second[26] = {0}, c=0;

//   // Calculating frequency of characters of the first string

//   while (a[c] != '\0') {
//     printf("%d\n",a[c]-'a');
//     first[a[c]-'a']+=1;

//     c++;
//   }
// //   for(int i =0;i<26;i++){
// //       printf("%d\n",first[i]);
// //   }

//   c = 0;

//   while (b[c] != '\0') {
//     second[b[c]-'a']++;
//     c++;
//   }

//   // Comparing the frequency of characters

//   for (c = 0; c < 26; c++)
//     if (first[c] != second[c])
//       return 0;

//   // return 1;
// }