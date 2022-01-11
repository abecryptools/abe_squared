
/* Methods for G2 arithmetic (RELIC) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
 
//#include <openabe/openabe.h>
//#include <openabe/zsymcrypto.h>
 
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



