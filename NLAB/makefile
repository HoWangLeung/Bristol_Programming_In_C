

CFLAGS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99
SANI := -fsanitize=undefined -fsanitize=address
NLBS := $(wildcard *.nlb)
RESULTS :=$(NLBS:.nlb=.result)

#COMMON DIRECTORIES
NLABC:=Functions/nlab.c
NLABH:=Functions/nlab.h
NLABS:= $(NLABC) $(NLABH)
GENERALC:=General/general.c
GENERALH:=General/general.h
GENERALS:= $(GENERALC) $(GENERALH) 

#Directories:
INSTRCLIST:=Functions/INSTRCLIST/instrclist.c
INSTRC:=Functions/INSTRC/instrc.c
SET:= Functions/SET/set.c
PRINT:= Functions/PRINT/print.c
CREATE:= Functions/CREATE/create.c
BINARYOP:= Functions/BINARYOP/binaryop.c
LOOP:= Functions/LOOP/loop.c
UNARYOP:=Functions/UNARYOP/unaryop.c
HELPER:=Functions/HELPER/helper.c
STACK:=Functions/STACK/stack.c
POLISH:=Functions/POLISH/polish.c
POLISHLIST:=Functions/POLISHLIST/polishlist.c
PUSHDOWN:=Functions/PUSHDOWN/pushdown.c
EXTENSION_ROTATION:= Extensions/ROTATION/rotation.c
EXTENSION_SORT:= Extensions/SORT/sort.c
EXTENSION_FLIP:= Extensions/FLIP/flip.c
EXTENSION_IF:= Extensions/IF/if.c
EXTENSIONS:= $(EXTENSION_ROTATION) $(EXTENSION_SORT) $(EXTENSION_FLIP) $(EXTENSION_IF)
FUNCTIONS:= $(INSTRCLIST) $(INSTRC) $(SET) $(PRINT) $(CREATE) $(BINARYOP) $(LOOP) $(UNARYOP) $(HELPER) $(STACK) $(POLISH) $(POLISHLIST) $(PUSHDOWN) $(EXTENSIONS)

#Testing Directories
TEST:=Testing/test.c
PARSE_TEST_DATAC:=Testing/PARSER_TEST/parse_test_data.c
TEST_PROG:=Testing/PARSER_TEST/PROG/test_prog.c
TEST_HELPER:=Testing/HELPER/helper.c
TEST_BINARYOP:=Testing/PARSER_TEST/BINARYOP/test_binaryop.c
TEST_COLS:=Testing/PARSER_TEST/COLS/test_cols.c
TEST_CREATE:=Testing/PARSER_TEST/CREATE/test_create.c
TEST_FILENAME:=Testing/PARSER_TEST/FILENAME/test_filename.c
TEST_INSTRC:=Testing/PARSER_TEST/INSTRC/test_instrc.c
TEST_INSTRCLIST:=Testing/PARSER_TEST/INSTRCLIST/test_instrclist.c
TEST_INTEGER:=Testing/PARSER_TEST/INTEGER/test_integer.c
TEST_LOOP:=Testing/PARSER_TEST/LOOP/test_loop.c
TEST_POLISH:=Testing/PARSER_TEST/POLISH/test_polish.c
TEST_POLISHLIST:=Testing/PARSER_TEST/POLISHLIST/test_polishlist.c
TEST_PRINT:=Testing/PARSER_TEST/PRINT/test_print.c
TEST_PUSHDOWN:=Testing/PARSER_TEST/PUSHDOWN/test_pushdown.c
TEST_ROWS:=Testing/PARSER_TEST/ROWS/test_rows.c
TEST_SET:=Testing/PARSER_TEST/SET/test_set.c
TEST_STRING:=Testing/PARSER_TEST/STRING/test_string.c
TEST_UNARYOP:=Testing/PARSER_TEST/UNARYOP/test_unaryop.c
TEST_VARNAME:=Testing/PARSER_TEST/VARNAME/test_varname.c
TEST_PROG_INTERP:=Testing/INTERP_TEST/Prog/test_prog.c
ALL_TEST:=$(TEST) $(PARSE_TEST_DATAC)  $(TEST_PROG) $(TEST_HELPER) \
$(TEST_BINARYOP) $(TEST_COLS) $(TEST_CREATE) $(TEST_FILENAME) $(TEST_INSTRC) \
$(TEST_INSTRCLIST) $(TEST_INTEGER)  $(TEST_LOOP) $(TEST_POLISH) $(TEST_POLISHLIST) \
$(TEST_PRINT) $(TEST_PUSHDOWN) $(TEST_ROWS) $(TEST_SET) $(TEST_STRING) $(TEST_UNARYOP) $(TEST_VARNAME) \
$(TEST_PROG_INTERP) \

########################
#PARSER
########################
parse: $(NLABC) $(NLABH) $(GENERALS) main.c  $(FUNCTIONS)
	clang main.c $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) $(SANI) -g3 -o parse -lm

parse_v: $(NLABC) $(NLABH) $(GENERALS) main.c $(FUNCTIONS)
	clang main.c $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) -g3 -o parse_v -lm
########################
#INTERPRETER
########################
interp: $(NLABC) $(NLABH) $(GENERALS) main.c  $(FUNCTIONS)
		clang main.c $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) $(SANI) -g3 -DINTERP -o interp -lm

interp_v: $(NLABC) $(NLABH) $(GENERALS) main.c  $(FUNCTIONS)
		clang -g main.c $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) -g3 -DINTERP -o interp_v -lm
########################
#EXTENSIONS (basically the same as interp)
########################
extension: $(NLABC) $(NLABH) $(GENERALS) main.c  $(FUNCTIONS)
		clang main.c $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) $(SANI) -g3 -DINTERP -o extension -lm

extension_v: $(NLABC) $(NLABH) $(GENERALS) main.c  $(FUNCTIONS)
		clang -g main.c $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) -g3 -DINTERP -o extension_v -lm


#Testing
test_parse:  $(ALL_TEST) $(NLABC) $(NLABH) $(GENERALS)  $(FUNCTIONS)
	clang  $(ALL_TEST) $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) $(SANI) -DPARSER -DTESTMODE -o Testing/test_parse -lm

test_interp: $(ALL_TEST) $(NLABC) $(NLABH) $(GENERALS) $(FUNCTIONS)
	clang $(ALL_TEST) $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) $(SANI) -DINTERP -DTESTMODE -o Testing/test_interp -lm

test_parse_v: $(ALL_TEST)$(NLABC) $(NLABH) $(GENERALS) $(FUNCTIONS)
	clang $(ALL_TEST)  $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) -DPARSER -DTESTMODE -o Testing/test_parse_v -lm

test_interp_v: $(ALL_TEST) $(NLABC) $(NLABH) $(GENERALS) $(FUNCTIONS)
	clang $(ALL_TEST)  $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) -DINTERP -DTESTMODE -o Testing/test_interp_v -lm

clean:
	rm -f parse parse_s parse_v interp interp_s interp_v Testing/test_v Testing/test_interp_v Testing/test_parse_v extension


tpv: test_parse_v
	valgrind --leak-check=full --track-origins=yes Testing/test_parse_v

tiv: test_interp_v
	valgrind --leak-check=full --track-origins=yes Testing/test_interp_v

pv: parse_v
	valgrind --leak-check=full --track-origins=yes ./parse_v Data/trivial.nlb

iv: interp_v
	valgrind --leak-check=full --track-origins=yes --dsymutil=yes ./interp_v Data/trivial.nlb


