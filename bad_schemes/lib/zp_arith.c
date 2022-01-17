/// 
/// Copyright (c) 2018 Zeutro, LLC. All rights reserved.
/// 
/// This file is part of Zeutro's OpenABE.
/// 
/// OpenABE is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Affero General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// 
/// OpenABE is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Affero General Public License for more details.
/// 
/// You should have received a copy of the GNU Affero General Public
/// License along with OpenABE. If not, see <http://www.gnu.org/licenses/>.
/// 
/// You can be released from the requirements of the GNU Affero General
/// Public License and obtain additional features by purchasing a
/// commercial license. Buying such a license is mandatory if you
/// engage in commercial activities involving OpenABE that do not
/// comply with the open source requirements of the GNU Affero General
/// Public License. For more information on commerical licenses,
/// visit <http://www.zeutro.com>.

/* Methods for ZP (RELIC bn_t) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "zp_arith.h"

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


