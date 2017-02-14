CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -O3 -lgmp -std=gnu99

.PHONY: clean

threaded: threaded_gcd.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o threaded_gcd
