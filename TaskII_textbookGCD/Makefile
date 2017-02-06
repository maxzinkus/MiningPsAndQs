CC = gcc

driver: driver.o libgcd.so
	$(CC) -L. -lgcd -o $@ $@.o

libgcd.so: gcd.o
	$(CC) -shared -o $@ $<

%.o: %.c
	$(CC) -c $< -o $@

%.c: %.h
	touch $@

clean:
	$(RM) *.o *.so driver
