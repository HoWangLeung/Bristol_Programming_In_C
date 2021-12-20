# Which compiler to use e.g. gcc, clang, gcc-8 etc.
CC := clang

# The house-style flags
CWARNS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99 

# Optimized version
PRODUCTION := $(CWARNS) -O2

SANITIZE := $(CWARNS) -fsanitize=address -fsanitize=undefined -g3

# Unused here, but might be interesting to try :-)
VALGRIND := $(CWARNS) -g3
PROFILE := $(CWARNS) -pg -g3

# 'make allexact' builds production and sanitize exectuables
# against the exact/hashing implementation and testdict.c or spelling.c
allexact: spellexact spellexact_s testexact testexact_s

# 'make allapprox' builds production and sanitize exectuables
# against the approx/Bloom implementation and testdict.c or spelling.c
allapprox : spellapprox spellapprox_s testapprox testapprox_s

# 'make all' builds production and sanitize exectuables
# against both implementations
all : allexact allapprox

test: main.c test.c check.h
	gcc sum_test.c sum.c $(PRODUCTION) -o test -lm

testexact:  nlab.c general.c Test/test.c
	$(CC) Test/tests.c general.c $(PRODUCTION) -o testexact -lm
testexact_s: Exact/exact.c testdict.c general.c
	$(CC) testdict.c Exact/exact.c general.c $(SANITIZE) -o testexact_s -lm


# 'make clean' removes all executables
clean: 
	rm -f spellapprox spellexact spellapprox_s spellexact_s testapprox testexact testapprox_s testexact_s

ve: testexact
	valgrind --leak-check=full --track-origins=yes  ./testexact
vspell_exact: spellexact
	valgrind --leak-check=full --track-origins=yes  ./spellexact dictionary.txt test.txt

va: testapprox
	valgrind --leak-check=full --track-origins=yes  ./testapprox
vspell_approx: spellapprox
	valgrind --leak-check=full --track-origins=yes  ./spellapprox dictionary.txt test.txt
