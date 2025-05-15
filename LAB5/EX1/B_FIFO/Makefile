CC=gcc -Wall

PROGS=read_fifo_b write_fifo_b

all: $(PROGS)

clean:
	rm -f $(PROGS)

read_fifo_b:	read_fifo_b.c
	$(CC) read_fifo_b.c -o read_fifo_b

write_fifo_b:	write_fifo_b.c
	$(CC) write_fifo_b.c -o write_fifo_b
