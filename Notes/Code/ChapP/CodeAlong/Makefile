CC := clang
CWARNS := -Wall -Wpedantic -Wextra -Wfloat-equal -Wvla
CFLAGNOABORT := $(CWARNS) -std=c99 -O3
CFLAGS := $(CFLAGNOABORT) -Werror
LDLIBS := -lm
SOURCES := $(wildcard *.c)
EXES := $(SOURCES:.c=)
AUTORUNS := $(wildcard *.autorun)
AUTOOUTS := $(AUTORUNS:.autorun=.autoout)
MANINPS := $(wildcard *.maninp)
MANOUTS := $(MANINPS:.maninp=.manout)
GENC := ./general.c

llist: llist.c $(GENC)
	$(CC) $(CFLAGS) $< $(GENC) $(LDLIBS) -o $@



