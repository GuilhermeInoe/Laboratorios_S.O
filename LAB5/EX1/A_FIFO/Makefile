CC=gcc -Wall

PROGS=read_fifo_a write_fifo_a

all: $(PROGS)

clean:
	rm -f $(PROGS)

read_fifo_a:	read_fifo_a.c
	$(CC) read_fifo_a.c -o read_fifo_a

write_fifo_a:	write_fifo_a.c
	$(CC) write_fifo_a.c -o write_fifo_a
