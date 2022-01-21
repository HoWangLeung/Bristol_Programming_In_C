#include "../../test.h"
void get_loop_data(Program *p, int test_number);
void get_loop_data(Program *p, int test_number)
{
  clear_previous_data(p);
  char test_instructions[ARR_RANGE][ARR_RANGE] = {
      //========================================
      //=====<testcase No.>:<description>=======
      //========================================
      {"LOOP $I 10 { SET $F := $F $I B-TIMES; PRINT $F } "},               //0:Valid
      {"LOOP $I 10 { } "},                                                 //1:Valid
      {"LOOP $I 5 { LOOP $J 5 {  SET $A := $I $J B-TIMES ; PRINT $A } }"}, //2:Valid
      {"LOOP $ABC 10 { } "},                                               //3:InValid
      {"LOOP $A 10 { LOOP $B 10 { LOOP $C 10 { } } } "},                   //4:Valid, triple nested loop
      {"LOOP LOOP $A 10 { } "},                                            //5:InValid, invalid keyword
      {"LOOP $A 10 B-ADD { } "},                                           //6:InValid
      {"LOOP $A $B { } "},                                                 //7:InValid
      {"LOOP $A $B $C { } "},                                              //8:InValid
      {"LOOP 9 $B $C { } "},                                               //9:InValid
      {"LOOP 9 19 $C { } "},                                               //10:InValid
      {"LOOP $A5 { } "},                                                   //11:InValid
      {"LOOP $A 5{ } "},                                                   //12:InValid
      {"LOOP $A 5 } { "},                                                  //13:InValid
      {"LOOP $A 5 [ ] "},                                                  //14:InValid
      {"LOOP $A 5 ( ) "},                                                  //15:InValid

  };
  copy_test_data(p, test_instructions, test_number);
}

void test_loop(Program *p)
{
  get_loop_data(p, 0);
  assert(LOOP(p));

  get_loop_data(p, 1);
  assert(LOOP(p));

  get_loop_data(p, 2);
  assert(LOOP(p));

  get_loop_data(p, 3);
  assert(!LOOP(p));

  get_loop_data(p, 4);
  assert(LOOP(p));

  get_loop_data(p, 5);
  assert(!LOOP(p));

  get_loop_data(p, 6);
  assert(!LOOP(p));

  get_loop_data(p, 7);
  assert(!LOOP(p));

  get_loop_data(p, 8);
  assert(!LOOP(p));

  get_loop_data(p, 9);
  assert(!LOOP(p));

  get_loop_data(p, 10);
  assert(!LOOP(p));

  get_loop_data(p, 11);
  assert(!LOOP(p));

  get_loop_data(p, 12);
  assert(!LOOP(p));

  get_loop_data(p, 13);
  assert(!LOOP(p));

  get_loop_data(p, 14);
  assert(!LOOP(p));

  get_loop_data(p, 15);
  assert(!LOOP(p));
}
