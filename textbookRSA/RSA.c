#include <stdio.h>
#include <unistd.h>

#include "RSA.h"

void init_keypair(pub_key *pub, priv_key *priv) {
   pub->e = PUBLIC_KEY;
   mpz_init2(pub->n, MOD_SIZE);

   mpz_init(priv->n);
   mpz_init2(priv->n, MOD_SIZE);

}

void generatePrime(mpz_t prime) {
   gmp_randstate_t state;

   gmp_randinit_default(state);
   mpz_urandomb(prime, state, MOD_SIZE/2);

   mpz_nextprime(prime, prime);
}

void key_gen(pub_key *pub, priv_key *priv) {
   mpz_t p, q

   mpz_inits(p, q, NULL);
   generatePrime(p);
   generatePrime(q);
   mpz_out_str(stdout, 10, p);
   mpz_out_str(stdout, 10, q);
}

void main(int argc, char **argv) {
   key_gen(NULL, NULL);
}
