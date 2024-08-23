CC = gcc
CFLAGS = -Wall -Wextra -std=c99
TARGET = count
SRC = count.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	cd .. && ./misc/$(TARGET)

clean:
	rm -f $(TARGET)