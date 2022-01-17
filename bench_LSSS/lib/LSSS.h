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

/* LSSS definitions */

#ifndef __L_LSSS_H__
#define __L_LSSS_H__

#include <stdint.h>

             
   #include <relic/relic.h>
           

void bn_t_sub_order(bn_t r, const bn_t x, const bn_t y,
                  const bn_t o);

void bn_t_mul(bn_t r, const bn_t x, const bn_t y,    
                   const bn_t o); 
struct LSSS {
  bn_t coeff_or_share;
  bn_t attr;
};

void native_share_secret_access_tree_and(bn_t elt, int n_attr, struct      LSSS *shares);
void native_recover_coeff_access_tree_and(int n_attr, struct LSSS *shares); 
void compute_lambda_values(char **m, bn_t * v, bn_t * lambda, uint32_t N_ATTR, bn_t order);

#endif	// __LSSS_H__

