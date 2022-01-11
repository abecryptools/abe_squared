
/* Methods for ZP (RELIC bn_t) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "zp_arith.h"

//#include <openabe/openabe.h>                                                    
//#include <openabe/zsymcrypto.h>        

void bn_t_init(bn_t *b) {
    bn_null(*b);
    bn_new(*b);
}

void bn_t_copy(bn_t to, const bn_t from) {
  bn_t_copy_const(to, from);
  return;
}

int bn_t_sign(const bn_t a) {
    return bn_sign(a);
}

int bn_t_cmp(const bn_t a, const bn_t b) {
    return bn_cmp(a, b);
}

void bn_t_setzero(bn_t a) {
    bn_zero(a);
}

int bn_t_countbytes(const bn_t a) {
    return bn_size_bin(a);
}

void bn_t_rand(bn_t a, bn_t o) {
  bn_rand(a, RLC_POS, bn_bits(o));
}

void bn_t_mod(bn_t x, const bn_t o) {
  bn_mod(x, x, o);
}

void bn_t_add(bn_t r, const bn_t x, const bn_t y,
                const bn_t o) {
  bn_add(r, x, y);
  bn_mod(r, r, o);

  return;
}

void bn_t_sub(bn_t r, const bn_t x, const bn_t y) {
  bn_sub(r, x, y);
}

void bn_t_sub_order(bn_t r, const bn_t x, const bn_t y,
                const bn_t o) {
  bn_sub(r, x, y);
  if (bn_sign(r) == RLC_NEG) {
    bn_add(r, r, o);
  } else {
    bn_mod(r, r, o);
  }
}

void bn_t_mul(bn_t r, const bn_t x, const bn_t y,
                const bn_t o) {
  bn_mul(r, x, y);
  if (bn_sign(r) == RLC_NEG) {
    bn_add(r, r, o);
  } else {
    bn_mod(r, r, o);
  }
}

int bn_t_is_one(const bn_t a) {
  if (a->used == 0)
    return 0; // false
  else if ((a->used == 1) && (a->dp[0] == 1))
    return 1; // true
  else
    return 0; // false
}

void bn_t_div(bn_t r, const bn_t x, const bn_t y,
                const bn_t o) {
  // r = (1 / y) mod o
  bn_t_mod_inv(r, y, o);
  if (bn_t_is_one(x))
    return; // return r
  // r = (r * x) mod o
  bn_t_mul(r, r, x, o);
}

void bn_t_exp(bn_t r, const bn_t x, const bn_t y,
                const bn_t o) {
  // r = (x^y) mod o
  bn_mxp(r, x, y, o);
}

void bn_t_lshift(bn_t r, const bn_t a, int n) {
  bn_lsh(r, a, n);
}

void bn_t_rshift(bn_t r, const bn_t a, int n) {
  bn_rsh(r, a, n);
}

void bn_t_negate(bn_t b, const bn_t o) {
  // 0 for +, != 0 for -
  bn_neg(b, b);
  if (bn_sign(b) == RLC_NEG) {
    bn_add(b, b, o);
  }
}

int bn_t_mod_inv(bn_t a, const bn_t b, const bn_t o) {
  bn_t s;
  bn_t_inits(s);
  // computes (1 / b) mod o
  bn_gcd_ext(s, a, NULL, b, o);
  // check if negative
  if (bn_sign(a) == RLC_NEG) {
    bn_add(a, a, o);
  }

  bn_free(s);
  return 1;
}

void bn_t_copy_const(bn_t c, const bn_t a) {                                      
     int i;                                                                      
                                                                                 
     if (c->dp == a->dp)                                                         
         return;                                                                 
                                                                                 
     bn_grow(c, a->used);                                                        
                                                                                 
     for (i = 0; i < a->used; i++) {                                             
         c->dp[i] = a->dp[i];                                                     
     }                                                                           
                                                                                 
     c->used = a->used;                                                          
     c->sign = a->sign;                                                          
}


