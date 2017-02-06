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

#endif
