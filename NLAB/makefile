

CFLAGS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99
SANI := -fsanitize=undefined -fsanitize=address
NLBS := $(wildcard *.nlb)
RESULTS :=$(NLBS:.nlb=.result)

#COMMON DIRECTORIES
NLABC:=Functions/nlab.c
NLABH:=$(NLABH)
GENERALC:=General/general.c
GENERALH:=General/general.h

#Directories:
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
EXTENSION_ROTATION:= Extension/ROTATION/rotation.c
EXTENSION_SORT:= Extension/SORT/sort.c
EXTENSION_FLIP:= Extension/FLIP/flip.c
EXTENSION_IF:= Extension/IF/if.c
EXTENSIONS:= $(EXTENSION_ROTATION) $(EXTENSION_SORT) $(EXTENSION_FLIP) $(EXTENSION_IF)
FUNCTIONS:= $(SET) $(PRINT) $(CREATE) $(BINARYOP) $(LOOP) $(UNARYOP) $(HELPER) $(STACK) $(POLISH) $(POLISHLIST) $(PUSHDOWN) $(EXTENSIONS)

#Testing Directories
TEST:=Testing/test.c
PARSE_TEST_DATAC:=Testing/PARSER_DATA/parse_test_data.c
INTERP_TEST_DATAC:=Testing/INTERP_DATA/interp_test_data.c
TEST_PROG:=Testing/INTERP_DATA/PROG/test_prog.c
TEST_HELPER:=Testing/HELPER/helper.c
TEST_BINARYOP:=Testing/INTERP_DATA/BINARYOP/test_binaryop.c
TEST_COLS:=Testing/INTERP_DATA/COLS/test_cols.c
TEST_CREATE:=Testing/INTERP_DATA/CREATE/test_create.c
TEST_FILENAME:=Testing/INTERP_DATA/FILENAME/test_filename.c
TEST_INSTRC:=Testing/INTERP_DATA/INSTRC/test_instrc.c
TEST_INSTRCLIST:=Testing/INTERP_DATA/INSTRCLIST/test_instrclist.c
TEST_INTEGER:=Testing/INTERP_DATA/INTEGER/test_integer.c
TEST_LOOP:=Testing/INTERP_DATA/LOOP/test_loop.c
TEST_POLISH:=Testing/INTERP_DATA/POLISH/test_polish.c
TEST_POLISHLIST:=Testing/INTERP_DATA/POLISHLIST/test_polishlist.c
TEST_PRINT:=Testing/INTERP_DATA/PRINT/test_print.c
TEST_PUSHDOWN:=Testing/INTERP_DATA/PUSHDOWN/test_pushdown.c
TEST_ROWS:=Testing/INTERP_DATA/ROWS/test_rows.c
TEST_SET:=Testing/INTERP_DATA/SET/test_set.c
TEST_STRING:=Testing/INTERP_DATA/STRING/test_string.c
TEST_UNARYOP:=Testing/INTERP_DATA/UNARYOP/test_unaryop.c
TEST_VARNAME:=Testing/INTERP_DATA/VARNAME/test_varname.c




ALL_TEST:=$(TEST) $(PARSE_TEST_DATAC) $(INTERP_TEST_DATAC) $(TEST_PROG) $(TEST_HELPER) \
$(TEST_BINARYOP) $(TEST_COLS) $(TEST_CREATE) $(TEST_FILENAME) $(TEST_INSTRC) \
$(TEST_INSTRCLIST) $(TEST_INTEGER)  $(TEST_LOOP) $(TEST_POLISH) $(TEST_POLISHLIST) \
$(TEST_PRINT) $(TEST_PUSHDOWN) $(TEST_ROWS) $(TEST_SET) $(TEST_STRING) $(TEST_UNARYOP) $(TEST_VARNAME) \


all: parse parse_s parse_v interp interp_s interp_v

# interp: nlab.c nlab.h $(GENERALH)
# 		gcc nlab.c $(CFLAGS) -O2 -DINTERP -o interp -lm

interp: $(NLABC) $(NLABH) $(GENERALH) main.c $(GENERALC) $(FUNCTIONS)
		gcc main.c $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) $(SANI) -g3 -DINTERP -o interp -lm

interp_s: nlab.c nlab.h $(GENERALH)
		gcc nlab.c $(CFLAGS) $(SANI) -g3 -DINTERP -o interp_s -lm

interp_v: $(NLABC) $(NLABH) $(GENERALH) main.c $(GENERALC) $(FUNCTIONS)
		gcc -g main.c $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) -g3 -DINTERP -o interp_v -lm

parse: $(NLABC) $(NLABH) $(GENERALH) main.c $(GENERALC)
	gcc main.c $(NLABC) $(GENERALC) $(CFLAGS) $(SANI) -g3 -o parse -lm

# parse_s: $(NLABC) $(NLABH) $(GENERALH) main.c
# 	gcc main.c $(NLABC) $(GENERALC) $(CFLAGS) $(SANI) -g3 -o parse_s -lm

parse_v: $(NLABC) $(NLABH) $(GENERALH) main.c $(GENERALC)
	gcc main.c $(NLABC) $(GENERALC) $(CFLAGS) -g3 -o parse_v -lm

runall: $(RESULTS)

%.result:
		./interp $.nlb > $*.result
clean:
	rm -f parse parse_s parse_v interp interp_s interp_v  $(RESULTS)

test:  $(ALL_TEST) $(NLABC) $(NLABH) $(GENERALH)  $(FUNCTIONS)
	gcc  $(ALL_TEST) $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) $(SANI) -DPARSER -DTESTMODE -o Testing/test -lm

test_interp: $(ALL_TEST) $(NLABC) $(NLABH) $(GENERALH) $(FUNCTIONS)
	gcc $(ALL_TEST) $(NLABC) $(GENERALC) $(FUNCTIONS) $(CFLAGS) $(SANI) -DINTERP -DTESTMODE -o Testing/test_interp -lm

test_v: test.c $(NLABC) $(NLABH) $(GENERALH) 
	gcc test.c  $(NLABC) $(GENERALC) $(CFLAGS) -DPARSER -DTESTMODE -o test_v -lm

test_interp_v: test.c $(NLABC) $(NLABH) $(GENERALH) 
	gcc test.c  $(NLABC) $(GENERALC) $(CFLAGS) -DINTERP -DTESTMODE -o test_interp_v -lm

tpv: test_v
	valgrind --leak-check=full --track-origins=yes ./test_v

tiv: test_interp_v
	valgrind --leak-check=full --track-origins=yes ./test_interp_v

pv: parse_v
	valgrind --leak-check=full --track-origins=yes ./parse_v trivial.nlb

iv: interp_v
	valgrind --leak-check=full --track-origins=yes --dsymutil=yes ./interp_v trivial.nlb


