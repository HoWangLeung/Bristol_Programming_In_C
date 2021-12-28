

CFLAGS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99
SANI := -fsanitize=undefined -fsanitize=address
NLBS := $(wildcard *.nlb)
RESULTS :=$(NLBS:.nlb=.result)

all: parse parse_s parse_v interp interp_s interp_v

# interp: nlab.c nlab.h General/general.h
# 		gcc nlab.c $(CFLAGS) -O2 -DINTERP -o interp -lm

interp: Functions/nlab.c Functions/nlab.h General/general.h main.c General/general.c
		gcc main.c Functions/nlab.c General/general.c $(CFLAGS) $(SANI) -g3 -DINTERP -o interp -lm

interp_s: nlab.c nlab.h General/general.h
		gcc nlab.c $(CFLAGS) $(SANI) -g3 -DINTERP -o interp_s -lm

interp_v: Functions/nlab.c Functions/nlab.h General/general.h main.c General/general.c
		gcc main.c Functions/nlab.c General/general.c $(CFLAGS) -g3 -DINTERP -o interp_v -lm

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
	rm -f parse parse_s parse_v interp interp_s interp_v $(RESULTS)

test: test.c Functions/nlab.c Functions/nlab.h General/general.h 
	gcc test.c  Functions/nlab.c General/general.c $(CFLAGS) $(SANI) -DPARSER -DTESTMODE -o test -lm

test_interp: test.c Functions/nlab.c Functions/nlab.h General/general.h 
	gcc test.c  Functions/nlab.c General/general.c $(CFLAGS) $(SANI) -DINTERP -DTESTMODE -o test_interp -lm


test_v: test.c Functions/nlab.c Functions/nlab.h General/general.h 
	gcc test.c  Functions/nlab.c General/general.c $(CFLAGS) -DPARSER -DTESTMODE -o test_v -lm

tv: test_v
	valgrind --leak-check=full --track-origins=yes ./test_v

pv: parse_v
	valgrind --leak-check=full --track-origins=yes ./parse_v trivial.nlb

iv: interp_v
	valgrind --leak-check=full --track-origins=yes ./interp_v trivial.nlb
