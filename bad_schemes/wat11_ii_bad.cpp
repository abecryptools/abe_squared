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
*  Wat11-I-BAD scheme CP-ABE
*  Small universe
*  Only correctness check at the end.
*/

#include <iostream>
#include <string>
#include <cassert>
#include "bench_defs.h"

using namespace std;

/* Measurment functions based 
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

    /* Process input parameters */

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

    /* Internal data structures */

    struct master_key msk;
    struct public_key_wat11_i_oe mpk;

    init_master_key(N_ATTR, &msk);
    init_public_key_wat11_i_oe(N_ATTR, &mpk);

    /* Setup */

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

    /* Generate precomputation tables for g, h*/

    g1_t t_pre_g[RLC_EP_TABLE_MAX];
    g2_t t_pre_h[RLC_EP_TABLE_MAX];

    for (int i = 0; i < RLC_EP_TABLE; i++) {
        g1_new(t_pre_g[i]);
        g2_new(t_pre_h[i]);
    }

    const vector<string> *attrStrings = attrList->getAttributeList();

    int i = 0;
    for(int j=0; j<NTESTS; j++)
    {
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


        int attr_int;

        i = 0;

        for (auto it = attrStrings->begin(); it != attrStrings->end(); ++it    ) {

            bn_rand_mod(msk.attributes[i].b_attr, order);
            g2_mul_fix(mpk.attributes[i].h_b_attr, t_pre_h, msk.attributes[i].b_attr);

            msk.attributes[i].attr = attr_int_list[i];
            i++;
        }
    } printf("["); print_results("Results gen param():           ", t,     NTESTS);

    /* Key Generation */

    struct secret_key sk;
    init_secret_key(N_ATTR, &sk);

    bn_t r; bn_null(r); bn_new(r);
    bn_t r_mul_b; bn_null(r_mul_b); bn_new(r_mul_b);
    bn_t exp_tmp_x; bn_null(exp_tmp_x); bn_new(exp_tmp_x);
    for(int j=0; j<NTESTS; j++)
    {
        t[j] = cpucycles();

        bn_rand_mod(r, order);
        bn_t_mul(r_mul_b, r, msk.b, order);
        bn_t_sub_order(exp_tmp_x, msk.alpha, r_mul_b, order);

        g2_mul_fix(sk.K, t_pre_h, exp_tmp_x);
        g1_mul_fix(sk.K_PRIMA, t_pre_g, r);

        string attr;
        i = 0;

        for (auto it = attrStrings->begin(); it != attrStrings->end(); ++it    ) {
            bn_t_mul(exp_tmp_x, r, msk.attributes[i].b_attr, order);
            g2_mul_fix(sk.attributes[i].k_attr, t_pre_h, exp_tmp_x);
            i++;

        }

    } printf(","); print_results("Results gen param():           ", t,     NTESTS);


    /* Encryption */

    std::string plaintext = pt1;
    unique_ptr<L_OpenABEFunctionInput> funcInput = nullptr;

    funcInput = L_createPolicyTree(encInput);

    if (!funcInput) {
        printf("Create policy error in encryption\n");
        return -1;
    }

    L_OpenABEPolicy *policy = dynamic_cast<L_OpenABEPolicy *>(funcInput.get());

    if (policy == nullptr) {
        printf("Error in input policy\n");
        return -1;
    }

    L_ZP s;
    struct ciphertext_wat11_i_oe CT_A;
    L_OpenABELSSS lsss(1);
    L_OpenABELSSSRowMap lsssRows;

    for(int j=0; j<NTESTS; j++)
    {
        t[j] = cpucycles();

        init_ciphertext_wat11_i_oe(N_ATTR, &CT_A);

        s.isOrderSet = true;
        bn_copy(s.order, order);
        bn_rand_mod(s.m_ZP, order);

        gt_exp(CT_A.C, mpk.A, s.m_ZP);
        g1_mul_fix(CT_A.C_PRIMA, t_pre_g, s.m_ZP);

        lsss.l_shareSecret(policy, s);
        lsssRows = lsss.l_getRows();
        i = 0;
        bn_t ri; bn_null(ri); bn_new(ri);

        g2_t tmp_1;
        g2_t tmp_2;
        g2_new(tmp_1);
        g2_new(tmp_2);

        for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {

            bn_rand_mod(ri, order);

            string attr = it->second.label();
            attr.erase(0, std::string("|attr").length() - 1);
            uint32_t attr_int_1 = stoi(attr);

            g2_mul_sim(CT_A.C_1[i].c_attr, mpk.B, it->second.element().m_ZP, mpk.attributes[i].h_b_attr, ri);

            g1_mul_fix(CT_A.C_2[i].c_attr, t_pre_g, ri);

            CT_A.C_1[i].attr = (uint32_t)attr_int_1;
            CT_A.C_2[i].attr = (uint32_t)attr_int_1;
            i++;
        }
    } printf(","); print_results("Results gen param():           ", t,     NTESTS);

    /* Decryption */
    i = 0;

    gt_t P_3_prod; gt_null(P_3_prod); gt_new(P_3_prod);
    gt_t P_1; gt_null(P_1); gt_new(P_1);
    gt_t P_2; gt_null(P_2); gt_new(P_2);
    g2_t C1_prod; g2_null(C1_prod); g2_new(C1_prod);

    gt_t p_final_2; gt_new(p_final_2);


    gt_t z; gt_null(z.m_GT); gt_new(z.m_GT);
    gt_t final; gt_null(final.m_GT); gt_new(final.m_GT);
    g2_t k_attr; g2_null(k_attr); g2_new(k_attr);

    g2_t pack_g2[N_ATTR];
    bn_t pack_bn[N_ATTR];
    g1_t pairing_g1[N_ATTR + 2];
    g2_t pairing_g2[N_ATTR + 2];

    for (auto it = lsssRows.begin(); it != lsssRows.end(); ++it) {
        g2_null(pack_g2[i]); g2_new(pack_g2[i]);
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
            g2_copy(pack_g2[i], CT_A.C_1[i].c_attr);
            bn_copy(pack_bn[i], it->second.element().m_ZP);
            g1_mul(CT_A.C_2[i].c_attr, CT_A.C_2[i].c_attr, it->second.element().m_ZP);

            g1_neg(CT_A.C_2[i].c_attr, CT_A.C_2[i].c_attr);
            g1_copy(pairing_g1[i], CT_A.C_2[i].c_attr);
            g2_copy(pairing_g2[i], sk.attributes[i].k_attr);

            i++;
        }

        g2_mul_sim_lot(C1_prod, pack_g2, pack_bn, N_ATTR);
        
        g2_copy(pairing_g2[N_ATTR], sk.K);
        g2_copy(pairing_g2[N_ATTR + 1], C1_prod);
        g1_copy(pairing_g1[N_ATTR], CT_A.C_PRIMA);
        g1_copy(pairing_g1[N_ATTR + 1], sk.K_PRIMA);

        pp_map_sim_oatep_k12(P_3_prod, pairing_g1, pairing_g2, N_ATTR + 2);
    }

    print_results("Results decryption():           ", t, NTESTS);
    printf("]\n");

    return 0;
}
