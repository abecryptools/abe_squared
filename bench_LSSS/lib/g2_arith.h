
/* Arithmetic in G2, function declarations */                          

#ifndef __G_2_ARITH_H__                                               
#define __G_2_ARITH_H__     

//#include <openabe/openabe.h>                                           
//#include <openabe/zsymcrypto.h>

extern "C" {                                                                    
 #include <relic/relic.h>                                                        
}

void g2_ar_init(g2_t *e);                         
void g2_ar_set_to_infinity(g2_t *e);              
int g2_ar_cmp_op(g2_t x, g2_t y);               
void g2_ar_mul_op(g2_t z, g2_t x, bn_t r);  

void g2_ar_point_add(g2_t z, g2_t y);


void g2_ar_point_sub(g2_t z, g2_t x);

#endif
