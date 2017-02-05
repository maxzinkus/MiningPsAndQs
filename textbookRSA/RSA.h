#ifndef RSA_H
#define RSA_H

#include <gmp.h>

#define MOD_SIZE 1024
#define PUB_KEY 65537

typedef struct pub_key {
   int e
   mpz_t n
} pub_key;

typedef struct priv_key {
   mpz_t d
   mpz_t n
} priv_key;

#endif
