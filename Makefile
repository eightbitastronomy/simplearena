CC=gcc
DEPS=simplearena.h

example: example.o simplearena.o
	$(CC) example.o simplearena.o -o example
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<
clean:
	rm *.o
