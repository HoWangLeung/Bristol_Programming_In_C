# Which compiler to use e.g. gcc, clang, gcc-8 etc.
CC := clang

# The house-style flags
CWARNS := -Wall -Wextra -Wpedantic -Wfloat-equal -Wvla -std=c99 -Werror

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


testexact: Exact/exact.c testdict.c general.c
	$(CC) testdict.c Exact/exact.c general.c $(PRODUCTION) -o testexact -lm
testexact_s: Exact/exact.c testdict.c general.c
	$(CC) testdict.c Exact/exact.c general.c $(SANITIZE) -o testexact_s -lm
spellexact: Exact/exact.c spelling.c general.c
	$(CC) spelling.c Exact/exact.c general.c $(PRODUCTION) -o spellexact -lm
spellexact_s: Exact/exact.c spelling.c general.c
	$(CC) spelling.c Exact/exact.c general.c $(SANITIZE) -o spellexact_s -lm


testapprox: Approx/approx.c testdict.c general.c
	$(CC) testdict.c Approx/approx.c general.c $(PRODUCTION) -o testapprox -lm
testapprox_s: Approx/approx.c testdict.c general.c
	$(CC) testdict.c Approx/approx.c general.c $(SANITIZE) -o testapprox_s -lm
spellapprox: Approx/approx.c spelling.c general.c
	$(CC) spelling.c Approx/approx.c general.c $(PRODUCTION) -o spellapprox -lm
spellapprox_s: Approx/approx.c spelling.c general.c
	$(CC) spelling.c Approx/approx.c general.c $(SANITIZE) -o spellapprox_s -lm

# 'make clean' removes all executables
clean: 
	rm -f spellapprox spellexact spellapprox_s spellexact_s testapprox testexact testapprox_s testexact_s
