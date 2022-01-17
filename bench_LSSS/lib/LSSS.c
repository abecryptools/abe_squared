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

/* simplified access tructures for the ABE-squared benchmark */

#include <stdio.h>
#include <stdlib.h>
#include "LSSS.h"

// openabe helpers

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

/* access tree structure for AND ops based on openabe 
 * and simplified */

void calculate_coefficient(uint32_t index, uint32_t threshold, uint32_t total, bn_t result)
{
  bn_null(result); bn_new(result); bn_set_dig(result, 1);

  bn_t order_tmp; bn_null(order_tmp); bn_new(order_tmp);                ep_curve_get_ord(order_tmp);

  bn_t index_plus_one; bn_new(index_plus_one);
  bn_set_dig(index_plus_one, index + 1);
  bn_t i_plus_one; bn_new(i_plus_one);
  bn_t zero_val; bn_new(zero_val); bn_set_dig(zero_val, 0);
  bn_t num, den, div, s;
  bn_new(num); bn_new(den); bn_new(div); bn_new(s);

  for (uint32_t i = 0; i < threshold; i++) {

    bn_set_dig(i_plus_one, i+1);

    if (i != index) {

      bn_sub(num, zero_val, i_plus_one);                                                     
      if (bn_sign(num) == RLC_NEG) {                                          
        bn_add(num, num, order_tmp);                                                   
      } else {                                                             
        bn_mod(num, num, order_tmp);                                                   
      }

      bn_sub(den, index_plus_one, i_plus_one);                                                     
      if (bn_sign(den) == RLC_NEG) {                                          
        bn_add(den, den, order_tmp);                                                   
      } else {                                                             
        bn_mod(den, den, order_tmp);                                                   
      }




     bn_gcd_ext(s, den, NULL, den, order_tmp);                                        

      if (bn_sign(den) == RLC_NEG) {                                          
        bn_add(den, den, order_tmp);                                                   
      }                                                                    
      bn_mul(div, num, den);
      bn_mod(div, div, order_tmp);

      bn_mul(result, result, div);
      bn_mod(result, result, order_tmp);
    }
  }
}

void poly_eval(bn_t * coeff_array, uint32_t x, bn_t result)
{

  bn_t share, xpow, tmp_1, tmp_2, tmp_3;
  unsigned int i = 0;

  bn_null(share); bn_new(share); bn_zero(share);
  bn_null(xpow); bn_new(xpow); bn_set_dig(xpow, x);
  bn_null(tmp_1); bn_new(tmp_1); 
  bn_null(tmp_2); bn_new(tmp_2); 
  bn_null(tmp_3); bn_new(tmp_3); 

  bn_t order_tmp; bn_null(order_tmp); bn_new(order_tmp); bn_zero(order_tmp);                                     

  ep_curve_get_ord(order_tmp);                            

  bn_t to_bn; bn_null(to_bn); bn_new(to_bn);

  for (int i = 0; i < 2; i++) {
    bn_set_dig(tmp_3, i);
    bn_mxp(tmp_2, xpow, tmp_3, order_tmp);

    bn_mul(tmp_1, coeff_array[i], tmp_2);                                    
    bn_mod(tmp_1, tmp_1, order_tmp);

    bn_add(share, share, tmp_1); 
  }

  bn_copy(result, share);
  return;
}

void add_share(bn_t e, int i, struct LSSS *shares)
{
  bn_null(shares[i-1].coeff_or_share); bn_new(shares[i-1].coeff_or_share);
  bn_null(shares[i-1].attr); bn_new(shares[i-1].attr);
  bn_copy(shares[i-1].coeff_or_share, e);
  bn_set_dig(shares[i-1].attr, i);
}

void native_share_secret_access_tree_and(bn_t elt, int n_attr, struct LSSS *shares)
{
  bn_t theSecret, order;

  bn_null(theSecret); bn_new(theSecret); bn_zero(theSecret);
  bn_null(order); bn_new(theSecret); 
  ep_curve_get_ord(order);

  bn_t s_list[128];
  int s_list_n = 0;

  bn_copy(s_list[0], elt);
  s_list_n++;

  bn_t coeff_array[3];

  int x = (n_attr*2) - 1;
  int l = n_attr;
  uint32_t threshold = 2, totalSubnodes = 2;

  /* N_ATTR = 1 */
  if (l == 1) {
    bn_copy(theSecret, s_list[s_list_n - 1]);
    add_share(theSecret, l, shares);
    return;
  }

  int j = x;
  int change_op = 0;
  bn_t eval_r_1; bn_new(eval_r_1);
  bn_t eval_r_2; bn_new(eval_r_2);

  while (1) { 

    /* last case */
    if (j == 3) {

      /* AND */
      bn_copy(theSecret, s_list[s_list_n - 1]);

      for (uint32_t i = 0; i < threshold; i++) {
        bn_rand(coeff_array[i+1], RLC_POS, bn_bits(order));
      }

      bn_copy(coeff_array[0], theSecret);
      poly_eval(coeff_array, 1, eval_r_1);
      poly_eval(coeff_array, 2, eval_r_2);

      /* LEAF */
      add_share(eval_r_2, l, shares);
      l--;
      /* LEAF */
      add_share(eval_r_1, l, shares);
      l--;

      break;
    } else {
      /* normal iterations */
      bn_copy(theSecret, s_list[s_list_n - 1]);
      s_list_n -= 1;

      if (change_op == 0) {
        /* AND */
        for (uint32_t i = 0; i < threshold; i++) {
          bn_rand(coeff_array[i+1], RLC_POS, bn_bits(order));
        }
        bn_copy(coeff_array[0], theSecret);
        poly_eval(coeff_array, 1, eval_r_1);

        s_list_n +=1;
        bn_copy(s_list[s_list_n - 1], eval_r_1);
        poly_eval(coeff_array, 2, eval_r_1);
        s_list_n +=1;
        bn_copy(s_list[s_list_n - 1], eval_r_1);
        change_op = 1; 
      } else {
        /* LEAF */
        add_share(theSecret, l, shares);
        l--;
        change_op = 0;
      }
    }
    j--;
  }
}


void native_recover_coeff_access_tree_and(int n_attr, struct LSSS *shares)
{
  bn_t order_tmp; bn_null(order_tmp); bn_new(order_tmp); 
  ep_curve_get_ord(order_tmp);                            

  bn_t tmpInCoeff, coefficient, c, one;

  bn_null(tmpInCoeff); bn_new(tmpInCoeff); bn_zero(tmpInCoeff);
  bn_null(coefficient); bn_new(coefficient); bn_zero(coefficient);
  bn_null(c); bn_new(c);
  bn_null(one); bn_new(one); bn_set_dig(one, 1);

  bn_t c_list[128];
  int c_list_n = 0;                                            
  bn_copy(c_list[0], one);                                            
  c_list_n++;         

  int x = (n_attr*2) - 1;
  int l = n_attr;
  uint32_t threshold = 2, totalSubnodes = 2;

  /* N_ATTR = 1 */
  if (l == 1) {
    bn_copy(tmpInCoeff, c_list[c_list_n - 1]);
    c_list_n -=1;
    add_share(tmpInCoeff, l, shares);
    return;
  }

  int j = x;
  int change_op = 0;

  while (1) { 

    //last case 

    if (j == 3) {

      // AND 
      uint32_t numSubnodes = 2;
      threshold = 2;
      bn_copy(tmpInCoeff, c_list[c_list_n - 1]);                   
      c_list_n -=1;

      for (uint32_t i = 0; i < numSubnodes; i++) {
        calculate_coefficient(i, threshold, numSubnodes, c);
        bn_mul(coefficient, tmpInCoeff, c);
        bn_mod(coefficient, coefficient, order_tmp);

        c_list_n +=1;                                                  
        bn_copy(c_list[c_list_n-1], coefficient);
      }

      // LEAF 
      bn_copy(tmpInCoeff, c_list[c_list_n - 1]);                                                                                            
      c_list_n -=1;  

      add_share(tmpInCoeff, l, shares);
      l--;

      // LEAF 
      bn_copy(tmpInCoeff, c_list[c_list_n - 1]);                                                                                            
      c_list_n -=1;   


      add_share(tmpInCoeff, l, shares);
      l--;

      break;
    } else {

      bn_copy(tmpInCoeff, c_list[c_list_n - 1]);                                                                                            
      c_list_n -=1;

      if (change_op == 0) {
        // AND 
        uint32_t numSubnodes = 2;
        threshold = 2;
        for (uint32_t i = 0; i < numSubnodes; i++) {
          calculate_coefficient(i, threshold, numSubnodes, c);
          bn_mul(coefficient, tmpInCoeff, c);
          bn_mod(coefficient, coefficient, order_tmp);
          c_list_n +=1;

          bn_copy(c_list[c_list_n-1], coefficient);                                                                                            
        }

        change_op = 1; 
      } else {
        // LEAF 
        add_share(tmpInCoeff, l, shares);
        l--;
        change_op = 0;
      }
    }
    j--;
  }
}


/* Precomputed values for AND case */

void compute_lambda_values(char  **m, bn_t * v, bn_t * lambda, uint32_t N_ATTR, bn_t order)
{

    bn_t tmp_1; bn_new(tmp_1); 
    bn_t tmp_2; bn_new(tmp_2);
    int32_t tmp_3 = 0;

    bn_set_dig(tmp_1, 0);

    for (int i = 0; i < N_ATTR; i++) {
       bn_set_dig(lambda[i], 0);
        for (int j = 0; j < N_ATTR; j++) {
            bn_read_str(tmp_2, *((m+i*N_ATTR) + j), 2, 10);

            if (tmp_3 < 0) {
                bn_neg(tmp_2, tmp_2);
            }

            bn_t_mul(tmp_1, v[j], tmp_2, order);
            bn_add(lambda[i], lambda[i], tmp_1);
            bn_mod(lambda[i], lambda[i], order);
        }
    }
}

