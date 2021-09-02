CC=gcc
CFLAGS=-g -Wall
OBJS=fileOpenClose.o
TARGET=fileOpenClose.out

all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
