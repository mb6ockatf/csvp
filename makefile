#!/usr/bin/make -f
CFLAGS = -std=c17 -Ofast -march=native -Werror -Wall -Wextra -Wpedantic \
	 -Wshadow -Wconversion -pedantic-errors -Wstrict-prototypes \
	 -Wold-style-definition -O3 -g
cc_link = -lgmp
OBJ = main.o functions.o

build: $(OBJ)
	$(CC) ${CFLAGS} $^ -o $@ ${cc_link}

main.o: main.c functions.h macro_defs.h
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h macro_defs.h
	$(CC) $(CFLAGS) -c functions.c

style:
	astyle -rvA8T8xeyxC70z2xWYK "*.c"
	astyle -rvA8T8xeyxC70z2xWYK "*.h"
	find . -name '*.orig' -exec rm -f {} +


clean:
	rm -f $(OBJ) build orig
