CC = gcc
CFLAGS = -Wall -O3 -pedantic

.PHONY: clean

taskI: taskI.c
	$(CC) -o taskI -lgmp taskI.c
clean:
	@-rm taskI 
