CC = gcc
LIBS = -lgmp
CFLAGS = 

driver: driver.o librsa.so
	$(CC) $(CFLAGS) $(LIBS) -L. -lrsa -o $@ $<

librsa.so: RSA.c
	$(CC) -fPIC -shared $(CFLAGS) $(LIBS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.c: %.h
	touch $@

clean:
	$(RM) *.o *.so driver
