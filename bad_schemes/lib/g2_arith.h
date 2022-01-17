
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

/* Arithmetic in G2, function declarations */                          

#ifndef __G_2_ARITH_H__                                               
#define __G_2_ARITH_H__     

extern "C" {                                                                    
 #include <relic/relic.h>                                                        
}

void g2_ar_init(g2_t *e);                         
void g2_ar_set_to_infinity(g2_t *e);              
int g2_ar_cmp_op(g2_t x, g2_t y);               
void g2_ar_mul_op(g2_t z, g2_t x, bn_t r);  

void g2_ar_point_add(g2_t z, g2_t y);


#endif
