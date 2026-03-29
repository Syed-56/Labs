CC=gcc
CFLAGS=-I.
DEPS=hellofunc.h
OBJ=hellofunc.o hello.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

output: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f output *.o