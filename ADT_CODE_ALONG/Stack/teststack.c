#include "stack.h"
#include "specific.h"

int main(void){

   printf("Test Stack (%s) Start ... ", STACKTYPE);
   char str[100];
   unsigned int i;
   stack *s;
   stacktype d;

   s = stack_init();

   stack_push(s, 'A');
   stack_push(s, 'B');
   stack_push(s, 'C');

   stack_pop(s, &d);
   stack_pop(s, &d);
   stack_push(s, 'C');

   printf("value at 0 = %c\n", s->start->i);

   printf("End\n");
   return 0;
}
