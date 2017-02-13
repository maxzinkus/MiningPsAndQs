
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gmp.h>
#include <pthread.h>

#define MAX_LINE 1024

static mpz_t *mods;
static unsigned long num_mods;

char *readmods(char *filename) {
    char *data;
    struct stat buf;
    int fd = open(filename, O_RDONLY);
    
    fstat(fd, &buf);
    data = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    num_mods = 0;
    
    for (int i = 0; i < buf.st_size; i++) {
        if (data[i] == '\0') {
            num_mods++;
        }
    }
    return data;
}

void *pairwise(void *arg) {
    int i = (int) arg;
    mpz_t res;
    
    mpz_init(res);
    
    for (int j = i + 1; j < num_mods; j++) {
        mpz_gcd(res, mods[i], mods[j]);
        if (mpz_cmp_si(res, 1) > 0) {
            flockfile(stdout);
            printf("%d with %d: ", i, j);
            mpz_out_str(stdout, 10, res);
            putchar('\n');
            funlockfile(stdout);
        }
    }
    
    mpz_clear(res);
    
    return NULL;
}

int main(int argc, char **argv) {
    pthread_t *threads;
    char *filename;
    char *data;
    unsigned long i;
    
    if (argc < 2) {
        printf("Usage: ./gmp_gcd mods.txt\n");
        return 1;
    }
    
    filename = argv[1];
    
    data = readmods(filename);
    
    mods = malloc(sizeof(mpz_t) * num_mods);
    threads = malloc(sizeof(pthread_t) * num_mods);
    
    
    for (i = 0; i < num_mods; i++) {
        mpz_init_set_str(mods[i], data, 10);
        while (*data++)
            ;
    }
    
    for (i = 0; i < num_mods; i++) {
        pthread_create(threads + i, NULL, pairwise, (void *) i);
    }
    
    for (i = 0; i < num_mods; i++) {
        pthread_join(threads[i], NULL);
    }
    
    /* Really should call mpz_clear */
    free(mods);
    
    return 0;
}
