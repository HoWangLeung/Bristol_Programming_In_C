CFLAGS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99  -O2 -g
SANITIZE= -fsanitize=undefined -fsanitize=address
# You need to provide Exact/exact.c and Exact/specific.h
# All other files are mine including the general.c/.h files which
# are copied from ADTS/General

all: testexact spellexact

testexact_s: Exact/exact.c testdict.c general.c
	clang testdict.c Exact/exact.c general.c $(CFLAGS) ${SANITIZE} -o testexact_s -lm
	
testexact: Exact/exact.c testdict.c general.c
	clang testdict.c Exact/exact.c general.c $(CFLAGS)  -o testexact -lm

spellexact: Exact/exact.c spelling.c general.c
	clang spelling.c Exact/exact.c general.c $(CFLAGS)  ${SANITIZE} -o spellexact -lm

v:testexact
	valgrind --leak-check=full --track-origins=yes  --show-leak-kinds=all ./testexact
