#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <gmp.h>

#define MAX_LINE 1024

char *readmods(char *filename) {
   char *data, *modstr;
   struct stat buf;
   int fd = open(filename, O_RDONLY);

   fstat(fd, &buf);
   data = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
   modstr = calloc(buf.st_size, 1);

   for (int i = 0; i < buf.st_size; i++) {
      modstr[i] = data[i];
   }
   munmap(data, buf.st_size);
   return modstr; 
}

void pairwise(char *filename) {
   mpz_t res;
   mpz_t *mod;
   int num;
   char *data = readmods(filename);
   char **dp = &data;

   for (int i = 0; i < strlen(data); i++) {
      if (data[i] == '\n') {
        num++;
      }
   } 

   mod = calloc(sizeof(mpz_t), num);

   mpz_init(res);

   for (int i = 0; i < num; i++) {
      mpz_init_set_str(mod[i], strtok_r(data, "\n", dp), 10);
   }

   for (int i = 0; i < num; i++) {
      for (int j = i; j < num; j++) {
         if (i != j) {
            printf("%d with %d: ", i, j);
            mpz_gcd(res, mod[i], mod[j]);
            mpz_out_str(stdout, 10, res);
            printf("\n");
         }
      }
   }
}

int main(int argc, char **argv) {
   if (argc > 1) {
      pairwise(argv[1]);
   }
   else {
      printf("Usage: ./gmp_gcd mods.txt\n");
   }
   return 0;
}
