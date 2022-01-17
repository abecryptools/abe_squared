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

/* Arithmetic in G1, function declarations */

#ifndef __G1_ARITH_H__
#define __G1_ARITH_H__

extern "C" {
#include <relic/relic.h>
}

void g1_ar_init(g1_t *e);                         
void g1_ar_set_to_infinity(g1_t *e);              
void g1_ar_add_op(g1_t z, g1_t x,  g1_t y);     
void g1_ar_mul_op(g1_t z,  g1_t x, bn_t r);   
void g1_ar_rand_op(g1_t g);                                         
void g1_ar_map_op(g1_t g, uint8_t *msg, int msg_len);    


#endif


