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


/* Methods for G2 arithmetic (RELIC) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "g2_arith.h"

void g2_ar_init(g2_t *e) {                             g2_null(*e); g2_new(*e);
}                                                                               
void g2_ar_set_to_infinity(g2_t *e) {            
   g2_null(*e); g2_new(*e);
   g2_set_infty(*e);                                                
}                                                                               

void g2_ar_mul_op(g2_t z, g2_t x, bn_t r) {              
   g2_mul(z, x, r);                                                       
 }                                                                               
int g2_ar_cmp_op(g2_t x, g2_t y) {             
   return g2_cmp(x, y);                                           
}


void g2_ar_point_add(g2_t z, g2_t y) {                           
   g2_add(z, z, y);
   g2_norm(z, z);
}



