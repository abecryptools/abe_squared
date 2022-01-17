/* 
 * This file is part of the ABE Squared (https://github.com/abecryptools/abe_squared).
 * Copyright (c) 2022 Antonio de la Piedra, Marloes Venema and Greg Alpár
 * 
 * This program is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 *  Wat11-I-OK scheme CP-ABE
 *  Small universe
 *  Only correctness check at the end.
 */

#include <iostream>
#include <string>
#include <cassert>

#include "../bench_defs.h"

using namespace std;

/* Measurement functions based 
 * on https://github.com/newhopecrypto/newhope/blob/master/ref/speed.c 
 * (public domain)
 */

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

    /* Setup */

    struct master_key msk;
    struct public_key_wat11_i_ok mpk;

    init_master_key(N_ATTR, &msk);
    init_public_key_wat11_i_ok(N_ATTR, &mpk);

    unique_ptr<L_OpenABEFunctionInput> keyFuncInput = nullptr;             
    keyFuncInput = L_createAttributeList(keyInput);                      

    if (keyFuncInput == nullptr) {
        printf("Invalid attribute key input\n");
        return -1;
    }

    L_OpenABEAttributeList *attrList = nullptr;                            
    if ((attrList = dynamic_cast<L_OpenABEAttributeList *>(keyFuncInput.get())) == nullptr) {                                                             
        printf("Error in attribute list\n");
        return(EXIT_FAILURE);
    }  


    g1_t t_pre_g[RLC_EP_TABLE_MAX];
    g2_t t_pre_h[RLC_EP_TABLE_MAX];

    for (int i = 0; i < RLC_EP_TABLE; i++) {
        g1_new(t_pre_g[i]);
        g2_new(t_pre_h[i]);
    }

    for(int j=0; j<NTESTS; j++) {

        t[j] = cpucycles();  

        g1_rand(mpk.g);
        g2_rand(mpk.h);

        bn_rand_mod(msk.alpha, order);
        bn_rand_mod(msk.b, order);

        pp_map_oatep_k12(mpk.A, mpk.g, mpk.h);

        g1_mul_pre(t_pre_g, mpk.g);
        g2_mul_pre(t_pre_h, mpk.h);

        gt_exp(mpk.A, mpk.A, msk.alpha);
        g2_mul_fix(mpk.B, t_pre_h, msk.b);

        for(int i = 0; i < N_ATTR; i++) {
            bn_rand_mod(msk.attributes[i].b_attr, order);
            g2_mul_fix(mpk.attributes[i].h_b_attr, t_pre_h, msk.attributes[i].b_attr);
        }


    }

    printf("["); 
    print_results("Results gen param():           ", t, NTESTS); 

    /* Key Generation */

    struct secret_key_wat11_i_ok sk;
    init_secret_key_wat11_i_ok(N_ATTR, &sk);



    bn_t r; bn_null(r); bn_new(r);
    bn_t r_mul_b; bn_null(r_mul_b); bn_new(r_mul_b);
    bn_t exp_tmp_x; bn_null(exp_tmp_x); bn_new(exp_tmp_x);

    for(int j=0; j<NTESTS; j++) {

        t[j] = cpucycles();

        bn_rand_mod(r, order);       
        bn_t_mul(r_mul_b, r, msk.b, order);
        bn_t_sub_order(exp_tmp_x, msk.alpha, r_mul_b, order);

        g1_mul_fix(sk.K, t_pre_g, exp_tmp_x);
        g1_mul_fix(sk.K_PRIMA, t_pre_g, r);

        for(int i = 0; i < N_ATTR; i++) {
            bn_t_mul(exp_tmp_x, r, msk.attributes[i].b_attr, order);
            g1_mul_fix(sk.attributes[i].k_attr, t_pre_g, exp_tmp_x);
        }
    }

    print_results("Results key gen():           ", t, NTESTS);

    /* Encryption */

    struct ciphertext_wat11_i_ok ct;
    init_ciphertext_wat11_i_ok(N_ATTR, &ct);

    unique_ptr<L_OpenABEFunctionInput> funcInput = nullptr;

    L_OpenABELSSS lsss(1);
    L_OpenABELSSSRowMap lsssRows;
    L_OpenABEPolicy *policy;

    funcInput = L_createPolicyTree(encInput);
    if (!funcInput) {
        printf("Create policy error in encryption\n");
        return -1;
    }
    policy = dynamic_cast< L_OpenABEPolicy *>(funcInput.get());

    if (policy == nullptr) {
        printf("Error in input policy\n");
        return -1;
    }



    bn_t s; bn_null(s); bn_new(s);

    for(int j=0; j<NTESTS; j++) {                                                                       t[j] = cpucycles();


        bn_rand_mod(s, order);
        gt_exp(ct.C, mpk.A, s);
        g2_mul_fix(ct.C_PRIMA, t_pre_h, s);

        L_ZP s_aux;
        s_aux.isOrderSet = true; 
        bn_copy(s_aux.order, order); 
        bn_copy(s_aux.m_ZP, s);

        lsss.l_shareSecret(policy, s_aux);                                       
        bn_t ri; bn_null(ri); bn_new(ri);

        lsssRows = lsss.l_getRows();                       
        g2_t b_attr_blind; g2_null(b_attr_blind); g2_new(b_attr_blind);  
        g1_t k_attr; g1_null(k_attr); g1_new(k_attr);  


        int i = 0;
        for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {     
            bn_rand_mod(ri, order); 
            g2_mul_sim(ct.C_1[i].c_attr, mpk.B, it->second.element().m_ZP, mpk.attributes[i].h_b_attr, ri); 
            g2_mul_fix(ct.C_2[i].c_attr, t_pre_h, ri);
            i++;
        }                                                                  

    } 

    print_results("Results encryption():           ", t, NTESTS);

    /* Decryption */

    gt_t P_1; gt_null(P_1); gt_new(P_1);
    gt_t P_2; gt_null(P_2); gt_new(P_2);
    gt_t P_3; gt_null(P_3); gt_new(P_3);
    gt_t final; gt_null(final); gt_new(final);
    gt_t z; gt_null(z); gt_new(z);

    gt_t P_3_prod; gt_null(P_3_prod); gt_new(P_3_prod); 
    gt_set_unity(P_3_prod);

    g2_t C1_prod; g2_null(C1_prod); g2_new(C1_prod);
    g2_t C_2_p; g2_null(C_2_p); g2_new(C_2_p);
    g2_t C_1_p; g2_null(C_1_p); g2_new(C_1_p);

    g2_t pack_g2[N_ATTR];
    bn_t pack_bn[N_ATTR];
    g1_t pairing_g1[N_ATTR + 2];
    g2_t pairing_g2[N_ATTR + 2];

    for (int i = 0; i < N_ATTR; i ++) {
        g2_null(pack_g2[i]); g2_new(pack_g2[i]);
        bn_null(pack_bn[i]); bn_new(pack_bn[i]);
    }
    for (int i = 0; i < N_ATTR + 2; i ++) {
        g1_null(pairing_g1[i]); g1_new(pairing_g1[i]);
        g2_null(pairng_g2[i]); g2_new(pairing_g2[i]);
    }

    for(int j=0; j<NTESTS; j++) {

        t[j] = cpucycles();


        lsss.l_recoverCoefficients(policy, attrList);    
        lsssRows = lsss.l_getRows();                       
        int i = 0;

        for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {
            g1_mul(pairing_g1[i], sk.attributes[i].k_attr, it->second.element().m_ZP);
            g2_copy(pack_g2[i], ct.C_1[i].c_attr);
            bn_copy(pack_bn[i], it->second.element().m_ZP);
            g1_neg(pairing_g1[i], pairing_g1[i]);
            g2_copy(pairing_g2[i], ct.C_2[i].c_attr);

            i++;
        }

        g2_mul_sim_lot(C1_prod, pack_g2, pack_bn, N_ATTR);

        g2_copy(pairing_g2[N_ATTR], ct.C_PRIMA);
        g2_copy(pairing_g2[N_ATTR + 1], C1_prod);
        g1_copy(pairing_g1[N_ATTR], sk.K);
        g1_copy(pairing_g1[N_ATTR + 1], sk.K_PRIMA);

        pp_map_sim_oatep_k12(z, pairing_g1, pairing_g2, N_ATTR + 2);

    }

    print_results("Results decryption():           ", t, NTESTS);
    printf("]\n");

    // uncomment testing part in decryption
    // before uncommenting this part for correctness
    //cout << "[*] Checking correctness..." << endl;
    //assert(gt_cmp(z, ct.C) == RLC_EQ);


    return 0;
}
