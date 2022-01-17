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
 *  RW13-OK scheme
 *  Only correctness check at the end.
 */

#include <iostream>
#include <string>
#include <cassert>

#include "../bench_defs.h"

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

using namespace std;

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

    core_init();
    bn_t order;
    pc_param_set_any();
    pc_param_print();
    pc_get_ord(order);

    printf("Testing CP-ABE context\n");
    cout << "\tkeyInput: " << keyInput << endl;

    /* Setup */

    struct master_key_rw13_oe msk;
    struct public_key_rw13_ok mpk;

    init_public_key_rw13_ok(N_ATTR, &mpk);

    g1_rand(mpk.g);
    g2_rand(mpk.h);

    g1_t t_pre_g[RLC_EP_TABLE_MAX];
    g2_t t_pre_h[RLC_EP_TABLE_MAX];
    g2_t t_pre_h_b[RLC_EP_TABLE_MAX];
    g2_t t_pre_h_b_prima[RLC_EP_TABLE_MAX];
    g2_t t_pre_h_b_0[RLC_EP_TABLE_MAX];
    g2_t t_pre_h_b_1[RLC_EP_TABLE_MAX];

    for (int i = 0; i < RLC_EP_TABLE; i++) {
        g1_new(t_pre_g[i]);
        g2_new(t_pre_h[i]);
        g2_new(t_pre_g[i]);
        g2_new(t_pre_h_b[i]);
        g2_new(t_pre_h_b_0[i]);
        g2_new(t_pre_h_b_1[i]);
        g2_new(t_pre_h_b_prima[i]);
    }

    for(int j=0; j<NTESTS; j++)
    {
        t[j] = cpucycles();


        g1_mul_pre(t_pre_g, mpk.g);
        g2_mul_pre(t_pre_h, mpk.h);

        bn_rand_mod(msk.alpha, order);
        bn_rand_mod(msk.b, order);
        bn_rand_mod(msk.b_0, order);
        bn_rand_mod(msk.b_1, order);
        bn_rand_mod(msk.b_prima, order);

        g2_mul_fix(mpk.h_b, t_pre_h, msk.b);
        g2_mul_fix(mpk.h_b_0, t_pre_h, msk.b_0);
        g2_mul_fix(mpk.h_b_1, t_pre_h, msk.b_1);
        g2_mul_fix(mpk.h_b_prima, t_pre_h, msk.b_prima);

        g2_mul_pre(t_pre_h_b, mpk.h_b);
        g2_mul_pre(t_pre_h_b_0, mpk.h_b_0);
        g2_mul_pre(t_pre_h_b_1, mpk.h_b_1);
        g2_mul_pre(t_pre_h_b_prima, mpk.h_b_prima);

        pp_map_oatep_k12(mpk.A, mpk.g, mpk.h);
        gt_exp(mpk.A, mpk.A, msk.alpha);

    }
    printf("["); print_results("Results gen param():           ", t, NTESTS);

    /* Key Generation */

    int i = 0;

    struct secret_key_rw13_ok sk;
    init_secret_key_rw13_ok(N_ATTR, &sk);

    unique_ptr<L_OpenABEFunctionInput> keyFuncInput = nullptr;
    keyFuncInput = L_createAttributeList(keyInput);

    if (keyFuncInput == nullptr) {
        printf("Invalid attribute key input\n");
        return(EXIT_FAILURE);
    }

    L_OpenABEAttributeList *attrList = nullptr;
    if ((attrList = dynamic_cast<L_OpenABEAttributeList *>(keyFuncInput.get())) == nullptr) {
        printf("Error in attribute list\n");
        return(EXIT_FAILURE);
    }

    bn_t r; bn_null(r); bn_new(r);
    bn_t r1; bn_null(r1); bn_new(r1);



    bn_t r_mul_b; bn_null(r_mul_b); bn_new(r_mul_b);
    bn_t r_mul_b_prima; bn_null(r_mul_b_prima); bn_new(r_mul_b_prima);
    bn_t exp_tmp_x; bn_null(exp_tmp_x); bn_new(exp_tmp_x);
    bn_t tmp_t; bn_null(tmp_t); bn_new(tmp_t);

    const vector<string> *attrStrings = attrList->getAttributeList();

    for(int j=0; j<NTESTS; j++) {
        t[j] = cpucycles();

        bn_rand_mod(r, order);
        bn_t_mul(r_mul_b, r, msk.b, order);
        bn_t_mul(r_mul_b_prima, r, msk.b_prima, order);
        bn_t_sub_order(exp_tmp_x, msk.alpha, r_mul_b, order);

        g1_mul_fix(sk.K, t_pre_g, exp_tmp_x);
        g1_mul_fix(sk.K_PRIMA, t_pre_g, r);

        string attr, attr_deckey;
        int attr_int;

        i = 0;

        for (auto it = attrStrings->begin(); it != attrStrings->end(); ++it    ) {
            attr = *it;
            attr.erase(0, std::string("|attr").length() - 1);

            bn_rand_mod(r1, order);

            attr_int = stoi(attr);
            L_ZP attr_int_z = attr_int;

            bn_t_mul(r_mul_b_prima, r, msk.b_prima, order);
            bn_t_mul(tmp_t, msk.b_1, attr_int_z.m_ZP, order);
            bn_add(tmp_t, tmp_t, msk.b_0);
            bn_t_mul(tmp_t, tmp_t, r1, order);
            bn_add(tmp_t, tmp_t, r_mul_b_prima);

            g1_mul_fix(sk.attributes_K_1[i].k_attr, t_pre_g, tmp_t);
            g1_mul_fix(sk.attributes_K_2[i].k_attr, t_pre_g, r1);

            sk.attributes_K_1[i].attr = attr_int_list[i];
            sk.attributes_K_2[i].attr = attr_int_list[i];

            i++;

        }

    }
    print_results("Results key gen():           ", t, NTESTS);

    /* Encryption */

    L_OpenABELSSS lsss(1);
    L_OpenABELSSSRowMap lsssRows;
    L_OpenABEPolicy *policy;

    i = 0;

    struct ciphertext_rw13_ok CT_A;
    init_ciphertext_rw13_ok(N_ATTR, &CT_A);

    unique_ptr<L_OpenABEFunctionInput> funcInput = nullptr;
    L_ZP s;

    funcInput = L_createPolicyTree(encInput);

    if (!funcInput) {
        printf("Create policy error in encryption\n");
        return -1;
    }

    policy = dynamic_cast<L_OpenABEPolicy *>(funcInput.get());

    if (policy == nullptr) {
        printf("Error in input policy\n");
        return -1;
    }
    s.isOrderSet = true;
    bn_copy(s.order, order);
    bn_t ri; bn_null(ri); bn_new(ri);

    for(int j=0; j<NTESTS; j++) {
        t[j] = cpucycles();


        bn_rand_mod(s.m_ZP, order);

        gt_exp(CT_A.C, mpk.A, s.m_ZP);
        g2_mul_fix(CT_A.C_PRIMA, t_pre_h, s.m_ZP);

        lsss.l_shareSecret(policy, s);

        lsssRows = lsss.l_getRows();

        i = 0;
        for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {

            bn_rand_mod(ri, order);

            string attr = it->second.label(); //, attr_deckey;
            attr.erase(0, std::string("|attr").length() - 1);
            int attr_int = stoi(attr);

            g2_t tmp_g1; g2_null(tmp_g1); g2_new(tmp_g1);

            g2_mul_fix(CT_A.C_1[i].c_attr, t_pre_h_b, it->second.element().m_ZP);
            g2_mul_fix(tmp_g1, t_pre_h_b_prima, ri);
            g2_add(CT_A.C_1[i].c_attr, CT_A.C_1[i].c_attr, tmp_g1);

            L_ZP attr_t = attr_int;
            bn_t exp_1; bn_null(exp_1); bn_new(exp_1);

            bn_t_mul(exp_1, ri, attr_t.m_ZP, order);
            g2_mul_fix(CT_A.C_2[i].c_attr, t_pre_h_b_1, exp_1);
            g2_mul_fix(tmp_g1, t_pre_h_b_0, ri);
            g2_add(CT_A.C_2[i].c_attr, CT_A.C_2[i].c_attr, tmp_g1);

            g2_mul_fix(CT_A.C_3[i].c_attr, t_pre_h, ri);

            CT_A.C_1[i].attr = (uint32_t)attr_int;                                 CT_A.C_2[i].attr = (uint32_t)attr_int;
            CT_A.C_3[i].attr = (uint32_t)attr_int;

            i++;

        }

    }

    print_results("Results encryption():           ", t, NTESTS);


    /* Decryption */

    g2_t prod_C1; g2_null(prod_C1); g2_new(prod_C1);

    gt_t tmp_inv; gt_null(tmp_inv); gt_new(tmp_inv);
    gt_t final; gt_null(final); gt_new(final);
    g1_t k_attr_1; g1_null(k_attr_1); g1_new(k_attr_1);
    g1_t k_attr_2; g1_null(k_attr_2); g1_new(k_attr_2);
    gt_t P_0; gt_null(P_0); gt_new(P_0);
    gt_t P_1; gt_null(P_1); gt_new(P_1);

    gt_t denom; gt_null(denom); gt_new(denom);
    gt_t num; gt_null(num); gt_new(num);
    gt_t num_div_denom; gt_null(num_div_denom); gt_new(num_div_denom);
    gt_t tmp; gt_null(tmp); gt_new(tmp);

    gt_set_unity(num_div_denom);

    g2_t pack_g2[N_ATTR];
    bn_t pack_bn[N_ATTR];

    g1_t pairing_g1_n[N_ATTR];
    g2_t pairing_g2_n[N_ATTR];
    g1_t pairing_g1_d[N_ATTR];
    g2_t pairing_g2_d[N_ATTR];
    gt_t P_N; gt_null(P_N); gt_new(P_N);
    gt_t P_D; gt_null(P_D); gt_new(P_D);

    i = 0;

    for (int i = 0; i < N_ATTR; i ++) {
        g2_null(pack_g2[i]); g2_new(pack_g2[i]);
        bn_null(pack_bn[i]); bn_new(pack_bn[i]);
    }
    for (int i = 0; i < N_ATTR + 2; i ++) {
        g1_null(pairing_g1[i]); g1_new(pairing_g1[i]);
        g2_null(pairng_g2[i]); g2_new(pairing_g2[i]);
    }

    g1_t p_1[2 + N_ATTR*2];
    g2_t p_2[2 + N_ATTR*2];

    for(int j=0; j<NTESTS; j++)  {
        t[j] = cpucycles();


        lsss.l_recoverCoefficients(policy, attrList);
        lsssRows = lsss.l_getRows();


        i = 0;
        for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {

            string attr = it->second.label(); //, attr_deckey;
            attr.erase(0, std::string("|attr").length() - 1);
            int attr_int = stoi(attr);

            get_k_attr_rw13_ok(attr_int, sk, k_attr_1, k_attr_2);

            g2_copy(pack_g2[i], CT_A.C_1[i].c_attr);
            bn_copy(pack_bn[i], it->second.element().m_ZP);

            g1_mul(p_1[i], k_attr_2, it->second.element().m_ZP);
            g1_mul(pairing_g1_d[i], k_attr_1, it->second.element().m_ZP);
            g2_copy(p_2[i], CT_A.C_2[i].c_attr);
            g1_neg(pairing_g1_d[i], pairing_g1_d[i]);
            g2_copy(pairing_g2_d[i], CT_A.C_3[i].c_attr);
            i++;
        }

        g2_mul_sim_lot(prod_C1, pack_g2, pack_bn, N_ATTR);

        g1_copy(p_1[N_ATTR], sk.K);
        g1_copy(p_1[N_ATTR+1], sk.K_PRIMA);
        g2_copy(p_2[N_ATTR], CT_A.C_PRIMA);
        g2_copy(p_2[N_ATTR+1], prod_C1);

        for(int i =0; i < N_ATTR; i++) {
            g1_copy(p_1[N_ATTR + 2 +i], pairing_g1_d[i]);
            g2_copy(p_2[N_ATTR + 2 +i], pairing_g2_d[i]);
        }

        pp_map_sim_oatep_k12(final, p_1, p_2, 2 + 2*N_ATTR);

    }
    print_results("Results decryption():           ", t, NTESTS);
    printf("]\n");


    // uncomment for checking correctness
    // cout << "[*] Checking correctness..." << endl;
    // assert(gt_cmp(final, CT_A.C) == RLC_EQ);

    return 0;
}
