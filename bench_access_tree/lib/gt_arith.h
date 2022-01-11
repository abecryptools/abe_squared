
#ifndef __G_T_ARITH_H__                                               
#define __G_T_ARITH_H__     

//#include <openabe/openabe.h>                                           
//#include <openabe/zsymcrypto.h>

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
