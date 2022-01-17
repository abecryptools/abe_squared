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


#ifndef __G_T_ARITH_H__                                               
#define __G_T_ARITH_H__     

extern "C" {                                                                    
  #include <relic/relic.h>                                                        
} 


void gt_ar_init(gt_t *e);                   
void gt_ar_set_to_infinity(gt_t *e);              
void gt_ar_mul_op(gt_t z, gt_t x, gt_t y);  
void gt_ar_div_op(gt_t z, gt_t x, gt_t y);           
void gt_ar_exp_op(gt_t y, gt_t x, bn_t r);         
int gt_ar_is_unity_check(gt_t r);      

#endif
