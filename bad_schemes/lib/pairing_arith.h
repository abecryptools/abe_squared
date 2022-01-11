
/* General pairing functions */

#ifndef __PAIRING_ARITH_H__                                           
#define __PAIRING_ARITH_H__

extern "C" {                                                                    
 #include <relic/relic.h>                                                        
}  

void do_pairing(gt_t gt, g1_t g1, g2_t g2);                             

void do_multi_pairing(gt_t gt, g1_t * g1_list, g2_t * g2_list, size_t n);

#endif

