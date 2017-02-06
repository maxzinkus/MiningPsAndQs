CC = gcc
CFLAGS = -Wall -Werror -Wpedantic -lgmp -std=gnu99

.PHONY: clean

gmp_gcd: gmp_gcd.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(RM) *.o gmp_gcd
