
/* Methods for G1 arithmetic (RELIC) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

//#include <openabe/openabe.h>
//#include <openabe/zsymcrypto.h>

#include "g1_arith.h"

void g1_ar_init(g1_t *e) {
  g1_null(*e);
  g1_new(*e);
}

void g1_ar_set_to_infinity(g1_t *e) {
  g1_null(*e);
  g1_new(*e);
  g1_set_infty(*e);
}

void g1_ar_add_op(g1_t z,  g1_t x,  g1_t y) {
  //g1_add_projc(z, x, y);
   g1_add(z, x, y);
  g1_norm(z, z);
}

void g1_ar_mul_op(g1_t z,  g1_t x,  bn_t r) {
  g1_mul(z, x, r);
}

void g1_ar_rand_op(g1_t g) {
    g1_rand(g);
}

void g1_ar_map_op(g1_t g, uint8_t *msg, int msg_len) {
  g1_map(g, msg, msg_len);
}


