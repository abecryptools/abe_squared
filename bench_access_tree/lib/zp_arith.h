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
///

/*
 * ZP arithmetic function declarations
 */

#ifndef __ZP_ARITH_H__
#define __ZP_ARITH_H__

extern "C" {                                                                    
        #include <relic/relic.h>                                                        
}   

#define bn_t_inits(bp){\
        bn_null(bp);\
        bn_new(bp);\
}

#define TRUE   1
#define FALSE  0

void bn_t_init(bn_t *a);
void bn_t_copy(bn_t to, const bn_t from);
int bn_t_sign(const bn_t a);
int bn_t_cmp(const bn_t a, const bn_t b);
void bn_t_setzero(bn_t a);
int bn_t_countbytes(const bn_t a);
int bn_t_mod_inv(bn_t a, const bn_t b, const bn_t o);
void bn_t_mod(bn_t x, const bn_t o);
void bn_t_negate(bn_t b, const bn_t o);
void bn_t_add(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_sub(bn_t r, const bn_t x, const bn_t y);
void bn_t_sub_order(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_mul(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_div(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_exp(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_lshift(bn_t r, const bn_t a, int n);
void bn_t_rshift(bn_t r, const bn_t a, int n);
void bn_t_copy_const(bn_t c, const bn_t a);                                       
int bn_t_is_one(const bn_t a);                                                  
void bn_t_rand(bn_t a, bn_t o); 



#endif /* ifdef __ZP_ARITH_H__ */
