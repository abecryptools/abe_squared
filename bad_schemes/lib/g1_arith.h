
/* Arithmetic in G1, function declarations */

#ifndef __G1_ARITH_H__
#define __G1_ARITH_H__

extern "C" {
#include <relic/relic.h>
}


//#include <openabe/openabe.h>
//#include <openabe/zsymcrypto.h>

void g1_ar_init(g1_t *e);                         
void g1_ar_set_to_infinity(g1_t *e);              
void g1_ar_add_op(g1_t z, g1_t x,  g1_t y);     
void g1_ar_mul_op(g1_t z,  g1_t x, bn_t r);   
void g1_ar_rand_op(g1_t g);                                         
void g1_ar_map_op(g1_t g, uint8_t *msg, int msg_len);    


#endif


