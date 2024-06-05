CC = gcc
CFLAGS = -Wall -Wextra -I.

TARGET = libmysyslog.so
SRC = mysyslog.c
OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
