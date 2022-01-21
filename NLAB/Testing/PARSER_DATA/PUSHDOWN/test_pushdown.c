#include "../../test.h"
void get_pushdown_data(Program *p, int test_number);
void get_pushdown_data(Program *p, int test_number)
{
  //PUSHDOWN GRAMMAR: <PUSHDOWN> ::== <VARNAME> | <INTEGER>
  clear_previous_data(p);
  char test_instructions[ARR_RANGE][ARR_RANGE] = {
      //========================================
      //=====<testcase No.>:<description>=======
      //========================================
      {"5"},           //0:Valid
      {"$A"},          //1:Valid
      {"$B"},          //2:Valid
      {"$C"},          //3:Valid
      {"$D"},          //4:Valid
      {"$E"},          //5:Valid
      {"$F"},          //6:Valid
      {"$G"},          //7:Valid
      {"$H"},          //8:Valid
      {"$I"},          //9:Valid
      {"$J"},          //10:Valid
      {"$K"},          //11:Valid
      {"$L"},          //12:Valid
      {"$M"},          //13:Valid
      {"$N"},          //14:Valid
      {"$O"},          //15:Valid
      {"$P"},          //16:Valid
      {"$Q"},          //17:Valid
      {"$R"},          //18:Valid
      {"$S"},          //19:Valid
      {"$T"},          //20:Valid
      {"$U"},          //21:Valid
      {"$V"},          //22:Valid
      {"$W"},          //23:Valid
      {"$X"},          //24:Valid
      {"$Y"},          //25:Valid
      {"$Z"},          //26:Valid
      {"@"},           //27:Invalid
      {"1"},           //28:Valid
      {"12"},          //29:Valid
      {"123"},         //30:Valid
      {"1234"},        //31:Valid
      {"12345"},       //32:Valid
      {"123!!!@@@@5"}, //33:Invalid

  };
  copy_test_data(p, test_instructions, test_number);
}
void test_pushdown(Program *p)
{
  get_pushdown_data(p, 0);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 1);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 2);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 3);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 4);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 5);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 6);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 7);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 8);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 9);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 10);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 11);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 12);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 13);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 14);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 15);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 16);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 17);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 18);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 19);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 20);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 21);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 22);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 23);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 24);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 25);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 26);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 27);
  assert(!PUSHDOWN(p));

  get_pushdown_data(p, 28);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 29);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 30);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 31);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 32);
  assert(PUSHDOWN(p));

  get_pushdown_data(p, 33);
  assert(!PUSHDOWN(p));
}
