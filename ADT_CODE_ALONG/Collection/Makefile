CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wpedantic -Wvla -std=c99 
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

all: testfixed_s testrealloc_s testlinked_s testfixed_v testrealloc_v testlinked_v testfixed testrealloc testlinked

testfixed_s : coll.h Fixed/specific.h Fixed/fixed.c testcoll.c ../General/general.h ../General/general.c
	$(CC) testcoll.c Fixed/fixed.c ../General/general.c -o testfixed_s -I./Fixed $(SANITIZE) $(LDLIBS)
testrealloc_s : coll.h Realloc/specific.h Realloc/realloc.c testcoll.c ../General/general.h ../General/general.c
	$(CC) testcoll.c Realloc/realloc.c ../General/general.c -o testrealloc_s -I./Realloc $(SANITIZE) $(LDLIBS)