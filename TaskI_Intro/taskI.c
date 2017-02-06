
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>


#include <gmp.h>

mpz_t* new_number() {
   mpz_t *num = malloc(sizeof(mpz_t));
   mpz_init(*num);

   return num;
}

void cleanup_number(mpz_t *num) {
   mpz_clear(*num);
   free(num);
}

mpz_t* rand_512() {
   static gmp_randstate_t rand;
   static bool init = true;
   
   mpz_t* num = new_number();
   
   if (init) {
      int dev_rand = open("/dev/random", O_RDONLY);
      unsigned long seed;

      read(dev_rand, &seed, sizeof(unsigned long));
      gmp_randinit_default(rand);
      gmp_randseed_ui(rand, seed);
      
      close(dev_rand);

      init = false;
   }

   mpz_urandomb(*num, rand, 512);

   return num;
}

bool check_prime(mpz_t *num) {
   return mpz_probab_prime_p(*num, 50) > 0;
}

bool print_num(mpz_t *num) {
   return mpz_out_str (stdout, 10, *num) > 0;
}

bool write_num(mpz_t *num, FILE *f) {
   return mpz_out_raw(f, *num) > 0;
}

mpz_t *read_num(FILE *f) {
   mpz_t *num = new_number();

   if (!mpz_inp_raw(*num, f)) {
//      cleanup_number(num);
//      return NULL;
   }

   return num;
}


mpz_t *add(mpz_t *x, mpz_t *y) {
   mpz_t *num = new_number();

   mpz_add(*num, *x, *y);

   return num;
}


mpz_t *sub(mpz_t *x, mpz_t *y) {
   mpz_t *num = new_number();

   mpz_sub(*num, *x, *y);

   return num;
}


mpz_t *mul(mpz_t *x, mpz_t *y) {
   mpz_t *num = new_number();

   mpz_mul(*num, *x, *y);

   return num;
}


mpz_t *exp_mod(mpz_t *a, mpz_t *b, mpz_t *c) {
   mpz_t *num = new_number();

   mpz_powm(*num, *a, *b, *c);

   return num;
}

int main() {
   mpz_t *p1 = rand_512();
   mpz_t *p2 = rand_512();

   printf("p1 is %sprime.\n", check_prime(p1) ? "" : "not ");
   printf("p2 is %sprime.\n", check_prime(p2) ? "" : "not ");

   printf("\nWriting p1 to disk...\n");
   
   FILE *out = fopen("p1.out", "w+");
   write_num(p1, out);

   fflush(out);
   rewind(out);
   printf("Reading p1 from disk...\n\n");

   mpz_t *p1b = read_num(out);

   fclose(out);

   printf("p1 was        : ");
   print_num(p1);
   putchar('\n');

   printf("Value read was: ");
   print_num(p1b);
   putchar('\n');
   putchar('\n');

   cleanup_number(p1b);

   mpz_t *sum = add(p1, p2);
   mpz_t *diff = sub(p1, p2);
   mpz_t *prod = mul(p1, p2);

   mpz_t *mod = exp_mod(p1, p2, diff);
   
   printf("p1 + p2 = ");
   print_num(sum);
   putchar('\n');

   printf("p1 - p2 = ");
   print_num(diff);
   putchar('\n');
   
   printf("p1 * p2 = ");
   print_num(prod);
   putchar('\n');

   printf("(p1 ^ p2) mod (p1 - p2) = ");
   print_num(mod);
   putchar('\n');
   
   cleanup_number(sum);
   cleanup_number(diff);
   cleanup_number(prod);
   cleanup_number(mod);

   cleanup_number(p1);
   cleanup_number(p2);
}
