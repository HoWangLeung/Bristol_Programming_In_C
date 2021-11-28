CC=gcc
COMMON= -Wall -Wextra -Wfloat-equal -Wvla -Wpedantic -std=c99 
DEBUG= -g3
SANITIZE= $(COMMON) -fsanitize=undefined -fsanitize=address $(DEBUG)
VALGRIND= $(COMMON) $(DEBUG)
PRODUCTION= $(COMMON) -O3
LDLIBS =

testlinked_s: stack.h Linked/specific.h Linked/linked.c teststack.c ../General/general.h ../General/general.c
	$(CC) teststack.c Linked/linked.c ../General/general.c -o testlinked_s -I./Linked $(SANITIZE) $(LDLIBS)
