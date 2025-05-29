
---

### `Makefile`

```makefile
CC = gcc
CFLAGS = -Wall -pthread
TARGET = filosofos
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

