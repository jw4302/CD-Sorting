CC=gcc
CFLAGS=-I -g.
DEPS = hashing.h
OBJ = hashing.o runner.o hashtable_test.o heap_test.o heap.o

%.o: %.c $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

runner: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)