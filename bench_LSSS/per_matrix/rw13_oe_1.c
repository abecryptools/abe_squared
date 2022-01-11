 
/* 
*  RW13-OE scheme 
*  Only correctness check at the end.
*/

#include <stdio.h>
#include "../bench_defs_ng.h"

char *m_1[1][1] = {
    {"1"},
};

int main(int argc, char **argv) {
  
  unsigned long long t[NTESTS];

  if (argv[1] == NULL) {
    return EXIT_FAILURE;
  }

  int test_attr = atoi(argv[1]);

  if (test_attr < 1) {
    return EXIT_FAILURE;
  }


  fprintf(stdout, "Testing AND policy with: %d components.\n", test_attr);


  uint32_t N_ATTR = test_attr;

  uint32_t * attr_int_list = NULL;                                                 
  attr_int_list = (uint32_t *) malloc(sizeof(uint32_t) * test_attr); 

  int d = 1;

  for (int k = 0; k < test_attr; k++) {
    attr_int_list[k] = d;
    d++;
  }

  core_init();                                                         
  bn_t order;                                                          
  pc_param_set_any();                                                  
  pc_param_print();                                                    
  ep_curve_get_ord(order);

  printf("Testing rw13-cp-oe\n");

  /* generate params */

  struct master_key_rw13_oe msk;
  struct public_key_rw13_oe mpk;

  init_master_key_rw13_oe(N_ATTR, &msk);
  init_public_key_rw13_oe(N_ATTR, &mpk);

  g1_rand(mpk.g);
  g2_rand(mpk.h);

  g1_t t_pre_g[RLC_EP_TABLE_MAX];
  g2_t t_pre_h[RLC_EP_TABLE_MAX];
  g1_t t_pre_g_b[RLC_EP_TABLE_MAX]; 
  g1_t t_pre_g_b_prima[RLC_EP_TABLE_MAX]; 
  g1_t t_pre_g_b_0[RLC_EP_TABLE_MAX]; 
  g1_t t_pre_g_b_1[RLC_EP_TABLE_MAX]; 

  for (int i = 0; i < RLC_EP_TABLE; i++) {
    g1_new(t_pre_g[i]);
    g2_new(t_pre_h[i]);    
    g1_new(t_pre_g[i]);
    g1_new(t_pre_g_b[i]);
    g1_new(t_pre_g_b_0[i]);
    g1_new(t_pre_g_b_1[i]);
    g1_new(t_pre_g_b_prima[i]);
  }

  for(int j=0; j<NTESTS; j++)                                          
      {                                                                    
  t[j] = cpucycles();  


  g1_mul_pre(t_pre_g, mpk.g);
  g2_mul_pre(t_pre_h, mpk.h);

  bn_rand(msk.alpha, RLC_POS, bn_bits(order));
  bn_rand(msk.b, RLC_POS, bn_bits(order));
  bn_rand(msk.b_0, RLC_POS, bn_bits(order));
  bn_rand(msk.b_1, RLC_POS, bn_bits(order));
  bn_rand(msk.b_prima, RLC_POS, bn_bits(order));

  g1_mul_fix(mpk.g_b, t_pre_g, msk.b);
  g1_mul_fix(mpk.g_b_0, t_pre_g, msk.b_0);
  g1_mul_fix(mpk.g_b_1, t_pre_g, msk.b_1);
  g1_mul_fix(mpk.g_b_prima, t_pre_g, msk.b_prima);

  g1_mul_pre(t_pre_g_b, mpk.g_b);
  g1_mul_pre(t_pre_g_b_0, mpk.g_b_0);
  g1_mul_pre(t_pre_g_b_1, mpk.g_b_1);
  g1_mul_pre(t_pre_g_b_prima, mpk.g_b_prima);

  pp_map_oatep_k12(mpk.A, mpk.g, mpk.h);
  gt_exp(mpk.A, mpk.A, msk.alpha);

      } 
  printf("["); print_results("Results gen param():           ", t, NTESTS);


  /* 2. Key Generation
   * */

  int i = 0;

  struct secret_key_rw13_oe sk;
  init_secret_key_rw13_oe(N_ATTR, &sk);


  bn_t r; bn_null(r); bn_new(r);
  bn_t r1; bn_null(r1); bn_new(r1);


  bn_t r_mul_b; bn_null(r_mul_b); bn_new(r_mul_b);
  bn_t r_mul_b_prima; bn_null(r_mul_b_prima); bn_new(r_mul_b_prima);
  bn_t exp_tmp_x; bn_null(exp_tmp_x); bn_new(exp_tmp_x);               
  bn_t tmp_t; bn_null(tmp_t); bn_new(tmp_t);               

    for(int j=0; j<NTESTS; j++) {                                                                                                                            
  t[j] = cpucycles();


  bn_rand(r, RLC_POS, bn_bits(order));
  bn_t_mul(r_mul_b, r, msk.b, order);
  bn_t_mul(r_mul_b_prima, r, msk.b_prima, order);
  bn_t_sub_order(exp_tmp_x, msk.alpha, r_mul_b, order);   

  g2_mul_fix(sk.K, t_pre_h, exp_tmp_x);
  g2_mul_fix(sk.K_PRIMA, t_pre_h, r);

  int attr_int;

  bn_t attr_zp; bn_new(attr_zp);

  i = 0;
  for (i = 0; i < N_ATTR; i++) {
    bn_rand(r1, RLC_POS, bn_bits(order));       
    bn_set_dig(attr_zp, i+1);

    bn_t_mul(r_mul_b_prima, r, msk.b_prima, order);                        bn_t_mul(tmp_t, msk.b_1, attr_zp, order);
    bn_add(tmp_t, tmp_t, msk.b_0);
    bn_t_mul(tmp_t, tmp_t, r1, order);
    bn_add(tmp_t, tmp_t, r_mul_b_prima);

    g2_mul_fix(sk.attributes_K_1[i].k_attr, t_pre_h, tmp_t);
    g2_mul_fix(sk.attributes_K_2[i].k_attr, t_pre_h, r1);

    sk.attributes_K_1[i].attr = attr_int_list[i];                   
    sk.attributes_K_2[i].attr = attr_int_list[i];
  }

  } print_results("Results key gen():           ", t, NTESTS);

  /* 3. Encryption
   * */

  struct LSSS *shares = (struct LSSS *) malloc(sizeof(struct LSSS) * N_ATTR);

  i = 0;

  struct ciphertext_rw13_oe CT_A;
  init_ciphertext_rw13_oe(N_ATTR, &CT_A);

  g1_t tmp_g1; g1_null(tmp_g1); g1_new(tmp_g1);
  bn_t ri; bn_null(ri); bn_new(ri);
  bn_t exp_1; bn_null(exp_1); bn_new(exp_1);
  bn_t attr_t;


  /* v and s computation for LSSS */
    for(int j=0; j<NTESTS; j++) {                                                                                                                            
  t[j] = cpucycles();


  bn_t *v = (bn_t *)malloc(N_ATTR * sizeof(bn_t));
  bn_t *lambda = (bn_t *)malloc(N_ATTR * sizeof(bn_t));


  for(i = 0; i < N_ATTR; i++) {
      bn_new(v[i]); bn_new(lambda[i]);
      bn_rand(v[i], RLC_POS, bn_bits(order));
  }

  //bn_rand(v[0], RLC_POS, bn_bits(order));       
  //bn_rand(v[1], RLC_POS, bn_bits(order));       
  bn_t s; bn_new(s);
  bn_copy(s, v[0]);

  gt_exp(CT_A.C, mpk.A, s);
  g1_mul_fix(CT_A.C_PRIMA, t_pre_g, s);
  //native_share_secret_access_tree_and(s, N_ATTR, shares);                                       
  i = 0;

  //bn_t lambda[2];
  //bn_new(lambda[0]);
  //bn_new(lambda[1]);
 
  compute_lambda_values(m_1, v, lambda, N_ATTR, order);

  for (i = 0; i < N_ATTR; i++) {
      bn_rand(ri, RLC_POS, bn_bits(order));       
      g1_mul_fix(CT_A.C_1[i].c_attr, t_pre_g_b, lambda[i]); //shares[i].coeff_or_share);
      g1_mul_fix(tmp_g1, t_pre_g_b_prima, ri);
      g1_add(CT_A.C_1[i].c_attr, CT_A.C_1[i].c_attr, tmp_g1);

      bn_set_dig(attr_t, i+1);
      bn_t_mul(exp_1, ri, attr_t, order);


      g1_mul_fix(CT_A.C_2[i].c_attr, t_pre_g_b_1, exp_1);
      g1_mul_fix(tmp_g1, t_pre_g_b_0, ri);
      g1_add(CT_A.C_2[i].c_attr, CT_A.C_2[i].c_attr, tmp_g1);

      g1_mul_fix(CT_A.C_3[i].c_attr, t_pre_g, ri);

      //CT_A.C_1[i].attr = (uint32_t)attr_int;                                 CT_A.C_2[i].attr = (uint32_t)attr_int;
      //CT_A.C_3[i].attr = (uint32_t)attr_int;    

      // i++;

  }                                                                  

  } print_results("Results encryption():           ", t, NTESTS);

  /* 4. Decryption
  */ 

  g1_t prod_C1; g1_null(prod_C1); g1_new(prod_C1);

  gt_t tmp_inv; gt_null(tmp_inv); gt_new(tmp_inv);
  gt_t final; gt_null(final); gt_new(final);
  g2_t k_attr_1; g2_null(k_attr_1); g2_new(k_attr_1);
  g2_t k_attr_2; g2_null(k_attr_2); g2_new(k_attr_2);
  gt_t P_0; gt_null(P_0); gt_new(P_0);
  gt_t P_1; gt_null(P_1); gt_new(P_1);

  gt_t denom; gt_null(denom); gt_new(denom);
  gt_t num; gt_null(num); gt_new(num);
  gt_t num_div_denom; gt_null(num_div_denom); gt_new(num_div_denom);
  gt_t tmp; gt_null(tmp); gt_new(tmp);

  gt_set_unity(num_div_denom);

  g1_t pack_g1[N_ATTR];
  bn_t pack_bn[N_ATTR];

  g1_t p_1[2 + (N_ATTR*2)];
  g2_t p_2[2 + (N_ATTR*2)];

  g1_t pairing_g1_n[N_ATTR];                                 
  g2_t pairing_g2_n[N_ATTR];  
  g1_t pairing_g1_d[N_ATTR];                                 
  g2_t pairing_g2_d[N_ATTR];  
  gt_t P_N; gt_null(P_N); gt_new(P_N);
  gt_t P_D; gt_null(P_D); gt_new(P_D);


  i = 0;
  for (i = 0; i< N_ATTR; i++) {
      g1_null(pack_g1[i]); g1_new(pack_g1[i]);
      bn_null(pack_bn[i]); bn_new(pack_bn[i]);
      g1_null(pairing_g1_n[i]); g1_new(pairing_g1_n[i]);
      g2_null(pairing_g2_n[i]); g2_new(pairing_g2_n[i]);
      g1_null(pairing_g1_d[i]); g1_new(pairing_g1_d[i]);
      g2_null(pairing_g2_d[i]); g2_new(pairing_g2_d[i]);
  }

   for(int j=0; j<NTESTS; j++)  {
     t[j] = cpucycles();
  //native_recover_coeff_access_tree_and(N_ATTR, shares);

      bn_set_dig(attr_t, 1);
 
  i = 0;
  for (i = 0; i < N_ATTR; i++) {
      g1_copy(pack_g1[i], CT_A.C_1[i].c_attr);
      bn_copy(pack_bn[i], attr_t);

      g1_copy(p_1[i], CT_A.C_2[i].c_attr);
      g2_copy(p_2[i], sk.attributes_K_2[i].k_attr);

      g1_neg(pairing_g1_d[i], CT_A.C_3[i].c_attr);
      g2_copy(pairing_g2_d[i], sk.attributes_K_1[i].k_attr);
  }      

  g1_mul_sim_lot(prod_C1, pack_g1, pack_bn, N_ATTR);

  g1_copy(p_1[N_ATTR], CT_A.C_PRIMA);
  g1_copy(p_1[N_ATTR + 1], prod_C1);
  g2_copy(p_2[N_ATTR], sk.K);
  g2_copy(p_2[N_ATTR + 1], sk.K_PRIMA);

  for(int i = 0; i<N_ATTR; i++) {
      g1_copy(p_1[N_ATTR + 2 + i], pairing_g1_d[i]);
      g2_copy(p_2[N_ATTR + 2 + i], pairing_g2_d[i]);

  }

  pp_map_sim_oatep_k12(final, p_1, p_2, 2*N_ATTR + 2);

   } print_results("Results decryption():           ", t, NTESTS);
   printf("]\n");


   printf("[*] Checking correctness...\n");
   assert(gt_cmp(final, CT_A.C) == RLC_EQ);

   return 0;
}


