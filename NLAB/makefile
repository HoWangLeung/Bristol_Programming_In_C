

CFLAGS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99
SANI := -fsanitize=undefined -fsanitize=address
NLBS := $(wildcard *.nlb)
RESULTS :=$(NLBS:.nlb=.result)

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

all: parse parse_s parse_v interp interp_s interp_v

# interp: nlab.c nlab.h General/general.h
# 		gcc nlab.c $(CFLAGS) -O2 -DINTERP -o interp -lm

interp: Functions/nlab.c Functions/nlab.h General/general.h main.c General/general.c $(FUNCTIONS)
		gcc main.c Functions/nlab.c General/general.c $(FUNCTIONS) $(CFLAGS) $(SANI) -g3 -DINTERP -o interp -lm

interp_s: nlab.c nlab.h General/general.h
		gcc nlab.c $(CFLAGS) $(SANI) -g3 -DINTERP -o interp_s -lm

interp_v: Functions/nlab.c Functions/nlab.h General/general.h main.c General/general.c $(FUNCTIONS)
		gcc -g main.c Functions/nlab.c General/general.c $(FUNCTIONS) $(CFLAGS) -g3 -DINTERP -o interp_v -lm

parse: Functions/nlab.c Functions/nlab.h General/general.h main.c General/general.c
	gcc main.c Functions/nlab.c General/general.c $(CFLAGS) $(SANI) -g3 -o parse -lm

# parse_s: Functions/nlab.c Functions/nlab.h General/general.h main.c
# 	gcc main.c Functions/nlab.c General/general.c $(CFLAGS) $(SANI) -g3 -o parse_s -lm

parse_v: Functions/nlab.c Functions/nlab.h General/general.h main.c General/general.c
	gcc main.c Functions/nlab.c General/general.c $(CFLAGS) -g3 -o parse_v -lm

runall: $(RESULTS)

%.result:
		./interp $.nlb > $*.result
clean:
	rm -f parse parse_s parse_v interp interp_s interp_v  $(RESULTS)

test:  Testing/test.c Functions/nlab.c Functions/nlab.h General/general.h Testing/PARSER_DATA/parse_test_data.c Testing/INTERP_DATA/interp_test_data.c $(FUNCTIONS)
	gcc  Testing/test.c Testing/PARSER_DATA/parse_test_data.c Testing/INTERP_DATA/interp_test_data.c  Functions/nlab.c General/general.c $(FUNCTIONS) $(CFLAGS) $(SANI) -DPARSER -DTESTMODE -o Testing/test -lm

test_interp: Testing/test.c Functions/nlab.c Functions/nlab.h General/general.h Testing/PARSER_DATA/parse_test_data.c Testing/INTERP_DATA/interp_test_data.c $(FUNCTIONS)
	gcc Testing/test.c Testing/PARSER_DATA/parse_test_data.c Testing/INTERP_DATA/interp_test_data.c Functions/nlab.c General/general.c $(FUNCTIONS) $(CFLAGS) $(SANI) -DINTERP -DTESTMODE -o Testing/test_interp -lm

test_v: test.c Functions/nlab.c Functions/nlab.h General/general.h 
	gcc test.c  Functions/nlab.c General/general.c $(CFLAGS) -DPARSER -DTESTMODE -o test_v -lm

test_interp_v: test.c Functions/nlab.c Functions/nlab.h General/general.h 
	gcc test.c  Functions/nlab.c General/general.c $(CFLAGS) -DINTERP -DTESTMODE -o test_interp_v -lm

tpv: test_v
	valgrind --leak-check=full --track-origins=yes ./test_v

tiv: test_interp_v
	valgrind --leak-check=full --track-origins=yes ./test_interp_v

pv: parse_v
	valgrind --leak-check=full --track-origins=yes ./parse_v trivial.nlb

iv: interp_v
	valgrind --leak-check=full --track-origins=yes --dsymutil=yes ./interp_v trivial.nlb


