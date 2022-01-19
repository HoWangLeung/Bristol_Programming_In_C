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


void test_prog(Program *p);
void test_binaryop(Program*p);
void test_cols(Program*p);
void test_create(Program*p);
void test_filename(Program*p);
void test_instrc(Program*p);
void test_instrclist(Program*p);
void test_integer(Program*p);
void test_loop(Program*p);
void test_polish(Program*p);
void test_polishlist(Program*p);
void test_print(Program*p);
void test_pushdown(Program*p);
void test_rows(Program*p);
void test_set(Program*p);
void test_string(Program*p);
void test_unaryop(Program*p);
void test_varname(Program*p);

