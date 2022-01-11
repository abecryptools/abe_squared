/*
 * ZP arithmetic function declarations
 */

#ifndef __ZP_ARITH_H__
#define __ZP_ARITH_H__

//#include <openabe/openabe.h>                                                    
//#include <openabe/zsymcrypto.h>    

extern "C" {                                                                    
        #include <relic/relic.h>                                                        
}   

#define bn_t_inits(bp){\
        bn_null(bp);\
        bn_new(bp);\
}

#define TRUE   1
#define FALSE  0

void bn_t_init(bn_t *a);
void bn_t_copy(bn_t to, const bn_t from);
int bn_t_sign(const bn_t a);
int bn_t_cmp(const bn_t a, const bn_t b);
void bn_t_setzero(bn_t a);
int bn_t_countbytes(const bn_t a);
int bn_t_mod_inv(bn_t a, const bn_t b, const bn_t o);
void bn_t_mod(bn_t x, const bn_t o);
void bn_t_negate(bn_t b, const bn_t o);
void bn_t_add(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_sub(bn_t r, const bn_t x, const bn_t y);
void bn_t_sub_order(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_mul(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_div(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_exp(bn_t r, const bn_t x, const bn_t y, const bn_t o);
void bn_t_lshift(bn_t r, const bn_t a, int n);
void bn_t_rshift(bn_t r, const bn_t a, int n);
void bn_t_copy_const(bn_t c, const bn_t a);                                       
int bn_t_is_one(const bn_t a);                                                  
void bn_t_rand(bn_t a, bn_t o); 



#endif /* ifdef __ZP_ARITH_H__ */
