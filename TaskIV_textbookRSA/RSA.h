#ifndef RSA_H
#define RSA_H

#include <gmp.h>

#define MOD_SIZE 1024
#define PUB_KEY 65537L

typedef struct pub_key {
   mpz_t e;
   mpz_t n;
} pub_key;

typedef struct priv_key {
   mpz_t d;
   mpz_t p;
   mpz_t q;
} priv_key;

void init_keypair(pub_key *pub, priv_key *priv);
void key_gen(pub_key *pub, priv_key *priv);
void generatePrimes(mpz_t p, mpz_t q);
void encrypt(mpz_t ret, pub_key *pub, mpz_t mt);
void decrypt(mpz_t ret, priv_key *priv, mpz_t ct);

#endif
