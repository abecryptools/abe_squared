/* 
 * This file is part of the ABE Squared (https://github.com/abecryptools/abe_squared).
 * Copyright (c) 2022 Antonio de la Piedra, Marloes Venema and Greg Alpár
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* General pairing functions */

#ifndef __PAIRING_ARITH_H__                                           
#define __PAIRING_ARITH_H__

extern "C" {                                                                    
 #include <relic/relic.h>                                                        
}  

void do_pairing(gt_t gt, g1_t g1, g2_t g2);                             

void do_multi_pairing(gt_t gt, g1_t * g1_list, g2_t * g2_list, size_t n);

#endif

