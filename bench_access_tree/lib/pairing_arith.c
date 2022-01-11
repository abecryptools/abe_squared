
/* Methods for pairing arithmetic (RELIC) */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
 
//#include <openabe/openabe.h>
//#include <openabe/zsymcrypto.h>
 
#include "pairing_arith.h"
#include "gt_arith.h"

void do_pairing(gt_t gt, g1_t g1, g2_t g2) {                             
        pp_map_oatep_k12(gt, g1, g2);                                          
        if (gt_ar_is_unity_check(gt))                                      gt_set_unity(gt);                                                                        
}

/* Example of preparing the list of g1 and g2 elements in
 * code:

      g1_t g_1[n];                                                           g2_t g_2[n];                                                                                       
      for (size_t i = 0; i < n; i++) {                                          g1_inits(g_1[i]);                       
         g1_copy_const(g_1[i], g1.at(i).m_G1);                                                            
         ep2_inits(g_2[i]);                                                     g2_copy_const(g_2[i], g2.at(i).m_G2);                               }     
*/

 void do_multi_pairing(gt_t gt, g1_t * g1_list, g2_t * g2_list, size_t n) {                             

        pp_map_sim_oatep_k12(gt, g1_list, g2_list, n);                         for (size_t i = 0; i < n; i++) {                                         g1_free(g1_list[i]);                                                   g2_free(g2_list[i]);                                                 }           

        //if (l_gt_is_unity_check(group, gt))
        if (fp12_cmp_dig(gt, 1) == 0)
                gt_set_unity(gt);                                       
}


