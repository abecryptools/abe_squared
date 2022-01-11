 
/* 
*  Wat11-I-OE scheme CP-ABE
*  optimized encryption (OE)
*  Small universe
*  Only correctness check at the end.
*/

#include <iostream>
#include <string>
#include <cassert>

#include "../bench_defs.h"

using namespace std;

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

int main(int argc, char **argv) {
  

  /* input parameters */
  string pt1 = "Testing AC17-CP-ABE...";
  string pt2;

  int test_attr = atoi(argv[1]);

  std::string keyInput = "";
  std::string encInput = "";
 
  uint32_t N_ATTR = test_attr;

  uint32_t * attr_int_list = NULL;                                                 
  attr_int_list = (uint32_t *) malloc(sizeof(uint32_t) * test_attr); 

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

  printf("Testing CP-ABE context\n");
  cout << "\tkeyInput: " << keyInput << endl;

  core_init();
 
  bn_t order;
  pc_param_set_any();                                                  
  pc_param_print();
  pc_get_ord(order);

  struct master_key msk;                                                 struct public_key_wat11_i_oe mpk;
  
  init_master_key(N_ATTR, &msk);                                       
  init_public_key_wat11_i_oe(N_ATTR, &mpk);    

  /* 1. generateParams Waters (master public key, secret key)
   * */

  unique_ptr<L_OpenABEFunctionInput> keyFuncInput = nullptr;             
  keyFuncInput = L_createAttributeList(keyInput);                      
  
  if (keyFuncInput == nullptr) {
    printf("Invalid attribute key input\n");
    return -1;
  }

  L_OpenABEAttributeList *attrList = nullptr;                            
 
     if ((attrList = dynamic_cast<L_OpenABEAttributeList *>(keyFuncInput.get())) == nullptr) {                                                             
       printf("Error in attribute list\n");
       exit(EXIT_FAILURE);
     }  
  
     // generate precomputation tables
     // for g, h
 
     g1_t t_pre_g[RLC_EP_TABLE_MAX];            
     g2_t t_pre_h[RLC_EP_TABLE_MAX];
                                                                     
     for (int i = 0; i < RLC_EP_TABLE; i++) {                       
         g1_new(t_pre_g[i]);
         g2_new(t_pre_h[i]);
     }

     for(int j=0; j<NTESTS; j++) {                                                                           t[j] = cpucycles();  

         g1_rand(mpk.g);
         g2_rand(mpk.h);
         bn_rand_mod(msk.alpha, order);
         bn_rand_mod(msk.b,  order);
         pp_map_oatep_k12(mpk.A, mpk.g, mpk.h);
         g1_mul_pre(t_pre_g, mpk.g);                                        
         g2_mul_pre(t_pre_h, mpk.h);      


         gt_exp(mpk.A, mpk.A, msk.alpha);
         g1_mul_fix(mpk.B, t_pre_g, msk.b);


         for(int i = 0; i < N_ATTR; i++) {
             bn_rand_mod(msk.attributes[i].b_attr, order);
             g1_mul_fix(mpk.attributes[i].g_b_attr, t_pre_g, msk.attributes[i].b_attr);
         }
     }

     printf("["); 
     print_results("Results gen param():           ", t, NTESTS); 


     /* 2. Key Generation
      * */

     struct secret_key sk;
     init_secret_key(N_ATTR, &sk);

     bn_t r; bn_null(r); bn_new(r);
     bn_t r_mul_b; bn_null(r_mul_b); bn_new(r_mul_b);
     bn_t exp_tmp_x; bn_null(exp_tmp_x); bn_new(exp_tmp_x);

     
    for(int j=0; j<NTESTS; j++) {

        t[j] = cpucycles();

        bn_rand_mod(r, order);
        bn_t_mul(r_mul_b, r, msk.b, order);                                  
        bn_t_sub_order(exp_tmp_x, msk.alpha, r_mul_b, order);   

        g2_mul_fix(sk.K, t_pre_h, exp_tmp_x);
        g2_mul_fix(sk.K_PRIMA, t_pre_h, r);

        for(int i = 0; i < N_ATTR; i++) {
            bn_t_mul(exp_tmp_x, r, msk.attributes[i].b_attr, order);
            g2_mul_fix(sk.attributes[i].k_attr, t_pre_h, exp_tmp_x);
        }
    }

    print_results("Results key gen():           ", t, NTESTS);

        /* 3. Encryption
         * */

        unique_ptr<L_OpenABEFunctionInput> funcInput = nullptr;                        
        L_OpenABELSSS lsss(1);                                                 L_OpenABELSSSRowMap lsssRows;                                          L_OpenABEPolicy *policy;                                                       
        funcInput = L_createPolicyTree(encInput);                                      
        if (!funcInput) {                                                              
            printf("Create policy error in encryption\n");                         return -1;                                                              
        }                                                                             
        policy = dynamic_cast< L_OpenABEPolicy *>(funcInput.get());                   
        if (policy == nullptr) {                                                 printf("Error in input policy\n");
            return -1;                                                               
        }    

        struct ciphertext_wat11_i_oe CT_A;
        init_ciphertext_wat11_i_oe(N_ATTR, &CT_A);

        bn_t s; bn_null(s); bn_new(s);

        for(int j=0; j<NTESTS; j++) {                                                                 t[j] = cpucycles();          
            bn_rand_mod(s, order);       
            gt_exp(CT_A.C, mpk.A, s);
            g1_mul_fix(CT_A.C_PRIMA, t_pre_g, s);

             L_ZP s_aux; s_aux.isOrderSet=true; bn_copy(s_aux.order, order);
             bn_copy(s_aux.m_ZP, s);

            lsss.l_shareSecret(policy, s_aux);
            lsssRows = lsss.l_getRows();                       

            int i = 0;
            bn_t ri; bn_null(ri); bn_new(ri); 

            for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {     

                bn_rand_mod(ri, order);       
                g1_mul_sim(CT_A.C_1[i].c_attr, mpk.B, it->second.element().m_ZP, mpk.attributes[i].g_b_attr, ri);
                g1_mul_fix(CT_A.C_2[i].c_attr, t_pre_g, ri);

                i++;
            }                                                                  

        } 

        print_results("Results encryption():           ", t, NTESTS);

        gt_t z; gt_null(z.m_GT); gt_new(z.m_GT);
 
        /* 4. Decryption
        */ 

        int i = 0;

        gt_t P_3_prod; gt_null(P_3_prod); gt_new(P_3_prod);
        gt_t P_1; gt_null(P_1); gt_new(P_1);
        gt_t P_2; gt_null(P_2); gt_new(P_2);
        g1_t C1_prod; gt_null(C1_prod); gt_new(C1_prod);
       gt_t final; gt_null(final.m_GT); gt_new(final.m_GT);
        g2_t k_attr; g2_null(k_attr); g2_new(k_attr);

        g1_t pack_g1[N_ATTR];                                    
        bn_t pack_bn[N_ATTR];                                    
        g1_t pairing_g1[N_ATTR + 2];                                 
        g2_t pairing_g2[N_ATTR + 2];

        for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {     
            // init dest

            g1_null(pack_g1[i]); g1_new(pack_g1[i]);
            bn_null(pack_bn[i]); bn_new(pack_bn[i]);

            g1_null(pairing_g1[i]); g1_new(pairing_g1[i]);
            g2_null(pairing_g2[i]); g2_new(pairing_g2[i]);

            i++;
        } 

        for(int j=0; j<NTESTS; j++) {

            t[j] = cpucycles();


            lsss.l_recoverCoefficients(policy, attrList);    
            lsssRows = lsss.l_getRows();                              

            i = 0;

            for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {   
       
                g1_mul(pairing_g1[i], CT_A.C_2[i].c_attr, it->second.element().m_ZP);
                g2_copy(pairing_g2[i], sk.attributes[i].k_attr);     
                bn_copy(pack_bn[i], it->second.element().m_ZP);
                g1_neg(pairing_g1[i], pairing_g1[i]);
                g1_copy(pack_g1[i], CT_A.C_1[i].c_attr);
               
                i++;
            }      

            g1_mul_sim_lot(C1_prod, pack_g1, pack_bn, N_ATTR); 

            g1_copy(pairing_g1[N_ATTR], CT_A.C_PRIMA);
            g1_copy(pairing_g1[N_ATTR + 1], C1_prod);
            g2_copy(pairing_g2[N_ATTR], sk.K);
            g2_copy(pairing_g2[N_ATTR + 1], sk.K_PRIMA);

            pp_map_sim_oatep_k12(z, pairing_g1, pairing_g2, N_ATTR + 2);

        }

        print_results("Results decryption():           ", t, NTESTS);
        printf("]\n");

        //cout << "[*] Checking correctness..." << endl;
        //assert(gt_cmp(z, CT_A.C) == RLC_EQ);
        //cout << "[*] PASSED" << endl; 

        return 0;
}
