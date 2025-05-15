# Makefile

CC = gcc
CFLAGS = -Wall -O2

TARGETS = ex_2_a ex_2_b ex_2_c

all: $(TARGETS)

ex_2_a: ex_2_a.c
	$(CC) $(CFLAGS) -o ex_2_a ex_2_a.c

ex_2_b: ex_2_b.c
	$(CC) $(CFLAGS) -o ex_2_b ex_2_b.c

ex_2_c: ex_2_c.c
	$(CC) $(CFLAGS) -o ex_2_c ex_2_c.c

clean:
	rm -f $(TARGETS)
