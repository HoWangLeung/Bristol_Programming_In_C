

CFLAGS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99
SANI := -fsanitize=undefined -fsanitize=address
NLBS := $(wildcard *.nlb)
RESULTS :=$(NLBS:.nlb=.result)

all: parse parse_s parse_v interp interp_s interp_v

# interp: nlab.c nlab.h General/general.h
# 		gcc nlab.c $(CFLAGS) -O2 -DINTERP -o interp -lm

main: main.c
		gcc main.c $(CFLAGS) $(SANI) -g3 -DINTERP -o main -lm

iv: main
	valgrind --leak-check=full --track-origins=yes --dsymutil=yes ./main
