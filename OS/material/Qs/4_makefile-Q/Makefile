CC=gcc
CFLAGS=-I.
DEPS=speed.h
OBJ=convert_speed.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

output: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f output *.o