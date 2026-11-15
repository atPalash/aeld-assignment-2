CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall -Werror

SRC := writer.c
TARGET = writer
OBJS := $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o $(TARGET) *.elf *.map

.PHONY: all clean