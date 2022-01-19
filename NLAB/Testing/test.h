#include "../Functions/nlab.h"
#define ARR_RANGE 500
void get_parser_data(Program *p, int test_number, char *func_name);
void set_up_testdata(Program *p, int test_number, char *func_name);
void RUN_PARSER_TEST(char *testcase_name);
void copy_test_data(Program *p, char test_instructions[ARR_RANGE][ARR_RANGE], int test_number);
void RUN_INTERP_TEST(char *testcase_name);
void get_interp_data(Program *p, int test_number, char *func_name);
void clear_previous_data(Program *p);
void free_struct(Program *p);

