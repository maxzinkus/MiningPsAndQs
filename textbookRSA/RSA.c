#include <stdio.h>
#include <unistd.h>

#include "RSA.h"

void init_keypair(pub_key *pub, priv_key *priv) {
   mpz_init(pub->e);
   mpz_init2(pub->n, MOD_SIZE);
   mpz_set_ui(pub->e, 65537L);

   mpz_init(priv->d);
   mpz_init2(priv->p, MOD_SIZE/2);
   mpz_init2(priv->q, MOD_SIZE/2);
}

void generatePrimes(mpz_t p, mpz_t q) {
   gmp_randstate_t state;

   gmp_randinit_default(state);

   mpz_urandomb(p, state, MOD_SIZE/2);
   mpz_nextprime(p, p);

   mpz_urandomb(q, state, MOD_SIZE/2);
   mpz_nextprime(q, q);
}

void key_gen(pub_key *pub, priv_key *priv) {
   mpz_t phi, p_1, q_1;

   mpz_inits(p_1, q_1, phi, NULL);

   mpz_mul(pub->n, priv->p, priv->q);

   mpz_sub_ui(p_1, priv->p, 1);
   mpz_sub_ui(q_1, priv->q, 1);
   mpz_mul(phi, p_1, q_1);

   mpz_invert(priv->d, pub->e, phi);
}

void encrypt(mpz_t ret, pub_key *pub, mpz_t mt) {
   mpz_powm(ret, mt, pub->e, pub->n);
}

void decrypt(mpz_t ret, priv_key *priv, mpz_t ct) {
   mpz_t n;

   mpz_init(n);
   mpz_mul(n, priv->p, priv->q);

   mpz_powm(ret, ct, priv->d, n);
}
