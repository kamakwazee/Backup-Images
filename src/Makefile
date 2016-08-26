#
# Makefile
#
# image backup prgram
#

CC = mingw32-gcc

CFLAGS = -ggdb -std=c11 -Wall -Werror

EXE = backup

HDRS = mvfile.h

LIBS =

SRCS = backup.c mvfile.c

OBJS = $(SRCS:.c=.o)

$(EXE): $(OBJS) $(HDRS) Makefile
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(OBJS): $(HDRS) Makefile

clean:
	rm -f core $(EXE) *.o *.exe
