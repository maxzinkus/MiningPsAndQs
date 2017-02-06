CC = gcc
LIBS = -lgmp
CFLAGS = -g

RSA: RSA.o
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.c: %.h
	touch $@

clean:
	$(RM) *.o *.so RSA
