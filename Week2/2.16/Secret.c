#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#define MAX 50

int main()
{
   char input[MAX];
   fgets(input, MAX, stdin);
    printf("string is: %s\n", input);
    printf("length = %lu\n", strlen(input)-1);
    int n = strlen(input)-1;

    for(int i = 0; i< n;i++){
      
       if(islower(input[i])){
          printf("%c",'z'-input[i]+'a');
       }else if(isupper(input[i])){
          
         printf("%c",'Z'-input[i]+'A');
       }else{
          printf("%c",input[i]);
       }
        


    }
    printf("\n");
   

   
}
