/* 
*  AC17 scheme LU-CP-ABE
*  Only correctness check at the end.
*/

#include <iostream>
#include <string>
#include <cassert>

#include "../bench_defs.h"

unsigned char * uint32_to_u_char_array(const uint32_t n)
{
    unsigned char *a;

    a = (unsigned char *) malloc(4*sizeof(unsigned char));

    a[0] = (n >> 24) & 0xff; 
    a[1] = (n >> 16) & 0xff;  
    a[2] = (n >>  8) & 0xff; 
    a[3] = n         & 0xff;  

    return a;
}

long long cpucycles(void)
{
  unsigned long long result;
  asm volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax"
    : "=a" (result) ::  "%rdx");
  return result;
}


static int cmp_llu(const void *a, const void*b)
{
  if(*(unsigned long long *)a < *(unsigned long long *)b) return -1;
  if(*(unsigned long long *)a > *(unsigned long long *)b) return 1;
  return 0;
}

static unsigned long long median(unsigned long long *l, size_t llen)
{
  qsort(l,llen,sizeof(unsigned long long),cmp_llu);

  if(llen%2) return l[llen/2];
  else return (l[llen/2-1]+l[llen/2])/2;
}

static unsigned long long average(unsigned long long *t, size_t tlen)
{
  unsigned long long acc=0;
  size_t i;
  for(i=0;i<tlen;i++)
    acc += t[i];
  return acc/(tlen);
}

static void print_results(const char *s, unsigned long long *t, size_t tlen)
{
  size_t i;
  for(i=0;i<tlen-1;i++)
  {
    t[i] = t[i+1] - t[i];
  }
  printf("%llu,", average(t, tlen-1));
}

unsigned long long t[NTESTS];

using namespace std;

int main(int argc, char **argv) {

  int test_attr = atoi(argv[1]);

  std::string keyInput = "";
  std::string encInput = "";
 
  uint32_t N_ATTR = test_attr;
  uint32_t attr_int_list[test_attr];

  int d = 1;

  for (int k = 0; k < test_attr; k++) {
    keyInput = keyInput + "attr" + std::to_string(d);
    encInput = encInput + "attr" + std::to_string(d); 

    if (k < test_attr - 1) {
      keyInput = keyInput + "|";
      encInput = encInput + " and ";
    }

    attr_int_list[k] = d;

    d++;
 
  }

  struct master_key_lu msk;
  struct public_key_lu mpk;

  core_init();

  bn_t order;
  pc_param_set_any();
  pc_param_print();
  pc_get_ord(order);

  //* 1. generateParams (master public key, secret key)

  unique_ptr<L_OpenABEFunctionInput> keyFuncInput = nullptr;             
  keyFuncInput = L_createAttributeList(keyInput);                      

  if (keyFuncInput == nullptr) {
      printf("Invalid attribute key input\n");
      return -1;
  }

  L_OpenABEAttributeList *attrList = nullptr;                            

  if ((attrList = dynamic_cast<L_OpenABEAttributeList *>(keyFuncInput.get())) == nullptr) {                                                           printf("Error in attribute list\n");
      exit(-1);
  }  

  g1_rand(mpk.g);
  g2_rand(mpk.h);

  // generate precomputation tables
  // for g, h

  g1_t t_pre_g[RLC_EP_TABLE_MAX];
  g2_t t_pre_h[RLC_EP_TABLE_MAX];

  for (int i = 0; i < RLC_EP_TABLE; i++) {
      g1_new(t_pre_g[i]);
      g2_new(t_pre_h[i]);
  }

  gt_new(mpk.A);
  fp12_set_dig(mpk.A, 1);

  for(int j=0; j<NTESTS; j++) {

      t[j] = cpucycles();

      g1_mul_pre(t_pre_g, mpk.g);
      g2_mul_pre(t_pre_h, mpk.h);

      bn_rand_mod(msk.b, order);
      bn_rand_mod(msk.alpha, order);

      pp_map_oatep_k12(mpk.A, mpk.g, mpk.h);                                           
      gt_exp(mpk.A, mpk.A, msk.alpha);
      g1_mul_fix(mpk.B, t_pre_g, msk.b);

  } printf("["); print_results("Results gen param():           ", t, NTESTS);   

  //* 2. Key Generation

  struct secret_key_cp sk;
  init_secret_key_cp(N_ATTR, &sk);
  bn_t exp_tmp; bn_null(exp_tmp); bn_new(exp_tmp);
  g1_t k_attr; g1_null(k_attr); g1_new(k_attr);
  g1_t map_attr; g1_null(map_attr); g1_new(map_attr);
  bn_t exp_tmp_x; bn_null(exp_tmp_x); bn_new(exp_tmp_x); 
  bn_t r; bn_null(r); bn_new(r); 
  bn_rand_mod(r, order);
  bn_t r_mul_b; bn_null(r_mul_b); bn_new(r_mul_b);

  // XXX: only for generating the right order in the loop 

  unique_ptr<L_OpenABEFunctionInput> funcInput1 = nullptr;                

  L_OpenABEPolicy *policy1;
  L_OpenABELSSS lsss1(1);                        
  L_OpenABELSSSRowMap lsssRows1;

  funcInput1 = L_createPolicyTree(encInput);
  policy1 = dynamic_cast< L_OpenABEPolicy *>(funcInput1.get());
  bn_t s1;
  bn_null(s1); bn_new(s1);

  bn_rand_mod(s1, order);

  L_ZP s_aux1; s_aux1.isOrderSet=true; bn_copy(s_aux1.order, order);
  bn_copy(s_aux1.m_ZP, s1);
  lsss1.l_shareSecret(policy1, s_aux1);                                       
  lsssRows1 = lsss1.l_getRows();                          

  // XXX: only for generating the right order in the loop

  for(int j=0; j<NTESTS; j++) {
      t[j] = cpucycles();

      bn_t_mul(r_mul_b, r, msk.b, order);
      bn_t_sub_order(exp_tmp_x, msk.alpha, r_mul_b, order);

      g1_mul_fix(sk.K, t_pre_g, exp_tmp_x); 
      g2_mul_fix(sk.K_PRIMA, t_pre_h, r); 
      int i = 0;
      for (auto it = lsssRows1.begin(); it != lsssRows1.end(); ++it) {     
          string attr = it->second.label(); 
          attr.erase(0, std::string("|attr").length() - 1);
          uint32_t attr_int_1 = stoi(attr);
          unsigned char * input_data =  uint32_to_u_char_array(attr_int_1); 
          g1_map(map_attr, input_data, 4);
          g1_mul(sk.attributes[i].k_attr, map_attr, r);
          i++;
      }

  } print_results("Results key gen():           ", t, NTESTS);

  //* 3. Encryption
  unique_ptr<L_OpenABEFunctionInput> funcInput = nullptr;                

  g1_t C_1; g2_null(C_1); g2_new(C_1);
  g2_t C_2; g2_null(C_2); g2_new(C_2);

  struct ciphertext_cp CT_A;
  init_ciphertext_cp(N_ATTR, &CT_A);
  gt_new(CT_A.C);
  fp12_set_dig(CT_A.C, 1);
  L_OpenABEPolicy *policy;
  L_OpenABELSSS lsss(1);                        
  L_OpenABELSSSRowMap lsssRows;

  funcInput = L_createPolicyTree(encInput);
  if (!funcInput) {
      printf("Create policy error in encryption\n");
      return -1;
  }                                                                  

  policy = dynamic_cast< L_OpenABEPolicy *>(funcInput.get());

  if (policy == nullptr) {                                                 printf("Error in input policy\n");
      return -1;
  }                                                                  

  bn_t s;
  bn_null(s); bn_new(s);
  bn_t ri; bn_null(ri); bn_new(ri);

  for(int j=0; j<NTESTS; j++)  {
      t[j] = cpucycles();

      bn_rand_mod(s, order);
      gt_exp(CT_A.C, mpk.A, s);
      g2_mul_fix(CT_A.C_PRIMA, t_pre_h, s);                              

      L_ZP s_aux; s_aux.isOrderSet=true; bn_copy(s_aux.order, order);
      bn_copy(s_aux.m_ZP, s);
      lsss.l_shareSecret(policy, s_aux);                                       
      lsssRows = lsss.l_getRows();                          
      int i = 0;

      bn_rand_mod(ri, order);
      g2_mul_fix(CT_A.C_2[0].c_attr, t_pre_h, ri);

      for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {     

          string attr = it->second.label(); 
          attr.erase(0, std::string("|attr").length() - 1);
          uint32_t attr_int_1 = stoi(attr);
          unsigned char * input_data =  uint32_to_u_char_array(attr_int_1); 
          g1_map(map_attr, input_data, 4);
          g1_mul_sim(CT_A.C_1[i].c_attr, mpk.B, it->second.element().m_ZP, map_attr, ri);
          i++;
      }                                                                  
  } print_results("Results encryption():           ", t, NTESTS);

  // 4. Decryption

  g1_t pack_g1[N_ATTR];
  bn_t pack_bn[N_ATTR];
  g1_t pairing_g1[N_ATTR];
  g2_t pairing_g2[N_ATTR];

  gt_t P_3; gt_null(P_3); gt_new(P_3);
  fp12_set_dig(P_3, 1);      

  gt_t P_3_prod; gt_null(P_3_prod); gt_new(P_3_prod);
  fp12_set_dig(P_3_prod, 1);      

  g1_t C1_prod; g1_null(C1_prod); g1_new(C1_prod);
  g1_set_infty(C1_prod);
  g1_t K_prod; g1_null(K_prod); g1_new(K_prod);
  g1_set_infty(K_prod);


  g1_null(k_attr); g1_new(k_attr);
  g1_t c_1_elem; g1_null(c_1_elem); g1_new(c_1_elem);
  g2_t c_2_elem; g2_null(c_2_elem); g2_new(c_2_elem);


  bn_t coeff; 
  bn_null(coeff); bn_new(coeff);

  gt_t z; gt_null(z); gt_new(z);
  lsssRows = lsss.l_getRows();                       
  int i = 0;

  for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {     
      g1_null(pack_g1[i]); g1_new(pack_g1[i]);
      bn_null(pack_bn[i]); bn_new(pack_bn[i]);

      g1_null(pairing_g1[i]); g1_new(pairing_g1[i]);
      g2_null(pairing_g2[i]); g2_new(pairing_g2[i]);
      i++;
  }

  gt_t P_1; gt_null(P_1); gt_new(P_1);
  gt_t P_2; gt_null(P_2); gt_new(P_2);
  gt_t final; gt_null(final); gt_new(final);                                                                     

  for(int j=0; j<NTESTS; j++) {
      t[j] = cpucycles();

      lsss.l_recoverCoefficients(policy, attrList);    
      lsssRows = lsss.l_getRows();                       
      i = 0;

      for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {     
          g1_copy(pack_g1[i], CT_A.C_1[i].c_attr);
          g1_copy(pairing_g1[i], sk.attributes[i].k_attr);
          bn_copy(pack_bn[i], it->second.element().m_ZP);
          i++;
      }     

      g1_mul_sim_lot(C1_prod, pack_g1, pack_bn, N_ATTR);
      g1_mul_sim_lot(K_prod, pairing_g1, pack_bn, N_ATTR); 

      g1_neg(pairing_g1[0], K_prod);
      g1_copy(pairing_g1[1], sk.K);
      g1_copy(pairing_g1[2], C1_prod);

      g2_copy(pairing_g2[0], CT_A.C_2[0].c_attr);
      g2_copy(pairing_g2[1], CT_A.C_PRIMA);
      g2_copy(pairing_g2[2], sk.K_PRIMA);

      pp_map_sim_oatep_k12(z, pairing_g1, pairing_g2, 3);

  } print_results("Results decryption():           ", t, NTESTS);
  printf("]\n");
  // uncomment for correctness check
  //assert(gt_cmp(z, CT_A.C) == RLC_EQ);
  //cout << "[*] PASSED" << endl;
  return 0;
}
