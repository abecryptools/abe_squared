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

#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include <stdint.h>
#include <relic/relic.h>                                                        

struct public_key_wat11_i_ok {
         uint32_t N_ATTR;                    
         g1_t g;                             
         g2_t h;
         gt_t A;
         g2_t B;                
         struct attribute_blind_wat11_i_ok * attributes;
 };                  


struct k_attribute_wat11_i_ok {
        uint32_t attr; 
        g1_t k_attr;
};


struct secret_key_wat11_i_ok {
        uint32_t N_ATTR;
        g1_t K;
        g1_t K_PRIMA;
        struct k_attribute_wat11_i_ok * attributes;
};


struct c_attribute_wat11_i_ok {
        uint32_t attr; 
        g2_t c_attr;
};

struct ciphertext_wat11_i_ok {
        uint32_t N_ATTR;
        gt_t C;
        g2_t C_PRIMA;
        struct c_attribute_wat11_i_ok * C_1;
        struct c_attribute_wat11_i_ok * C_2;
};


void get_b_attr_blind_wat11_i_ok(const uint32_t attr, const struct public_key_wat11_i_ok p, g2_t g2_o);

int init_secret_key_wat11_i_ok(const uint32_t n_attr, struct secret_key_wat11_i_ok *s);
int init_ciphertext_wat11_i_ok(const uint32_t n_attr, struct ciphertext_wat11_i_ok *c);


int init_public_key_wat11_i_ok(const uint32_t n_attr, struct public_key_wat11_i_ok *p      );   

struct attribute_blind_wat11_i_ok {
         uint32_t attr;                                                         g2_t h_b_attr;
 };



struct public_key_rw13_ok {
        uint32_t N_ATTR;                    
        g1_t g;                             
        g2_t h;
        g2_t h_b;
        g2_t h_b_0;
        g2_t h_b_1;
        g2_t h_b_prima;
        gt_t A;
};


// rw13 ok
struct c_attribute_rw13_ok_1 {
        uint32_t attr; 
        g2_t c_attr;
};

struct c_attribute_rw13_ok_2 {
        uint32_t attr; 
        g2_t c_attr;
};

struct c_attribute_rw13_ok_3 {
        uint32_t attr; 
        g2_t c_attr;
};

struct ciphertext_rw13_ok {
        uint32_t N_ATTR;
        gt_t C;
        g2_t C_PRIMA;
        struct c_attribute_rw13_ok_1 * C_1;
        struct c_attribute_rw13_ok_2 * C_2;
        struct c_attribute_rw13_ok_3 * C_3;
};

int init_ciphertext_rw13_ok(const uint32_t n_attr, struct ciphertext_rw13_ok *c);

struct k_attribute_K_1_ok {
        uint32_t attr; 
        g1_t k_attr;
};

struct k_attribute_K_2_ok {
        uint32_t attr; 
        g1_t k_attr;
};

struct secret_key_rw13_ok {
        uint32_t N_ATTR;
        g1_t K;
        g1_t K_PRIMA;
        struct k_attribute_K_1_ok * attributes_K_1;
        struct k_attribute_K_2_ok * attributes_K_2;
};

int init_secret_key_rw13_ok(const uint32_t n_attr, struct secret_key_rw13_ok *s);

void get_k_attr_rw13_ok(const uint32_t attr, const struct secret_key_rw13_ok s, g1_t k_attr_1, g1_t k_attr_2);

int init_public_key_rw13_ok(const uint32_t n_attr, struct public_key_rw13_ok *p);

// rw13 ok

// rw13 oe

struct c_attribute_rw13_oe_1 {
        uint32_t attr; 
        g1_t c_attr;
};

struct c_attribute_rw13_oe_2 {
        uint32_t attr; 
        g1_t c_attr;
};

struct c_attribute_rw13_oe_3 {
        uint32_t attr; 
        g1_t c_attr;
};

struct ciphertext_rw13_oe {
        uint32_t N_ATTR;
        gt_t C;
        g1_t C_PRIMA;
        struct c_attribute_rw13_oe_1 * C_1;
        struct c_attribute_rw13_oe_2 * C_2;
        struct c_attribute_rw13_oe_3 * C_3;
};

struct public_key_rw13_oe {
        uint32_t N_ATTR;                    
        g1_t g;                             
        g2_t h;
        g1_t g_b;
        g1_t g_b_0;
        g1_t g_b_1;
        g1_t g_b_prima;
        gt_t A;
};


struct master_key_rw13_oe {
        uint32_t N_ATTR;
        struct attribute * attributes;
        bn_t b;
        bn_t alpha;
        bn_t b_0;
        bn_t b_1;
        bn_t b_prima;
};



int init_ciphertext_rw13_oe(const uint32_t n_attr, struct ciphertext_rw13_oe *c);


struct k_attribute_K_1_oe {
        uint32_t attr; 
        g2_t k_attr;
};

struct k_attribute_K_2_oe {
        uint32_t attr; 
        g2_t k_attr;
};

struct secret_key_rw13_oe {
        uint32_t N_ATTR;
        g2_t K;
        g2_t K_PRIMA;
        struct k_attribute_K_1_oe * attributes_K_1;
        struct k_attribute_K_2_oe * attributes_K_2;
};

struct ciphertext_wat11_i_oe {
        uint32_t N_ATTR;
        gt_t C;
        g1_t C_PRIMA;
        struct c_attribute_wat11_i_oe * C_1;
        struct c_attribute_wat11_i_oe * C_2;
};

struct ciphertext_wat11_iv_oe {
        uint32_t N_ATTR;
        gt_t C;
        g1_t C_PRIMA;
        struct c_attribute_wat11_iv_oe_1 * C_1;
        struct c_attribute_wat11_iv_oe_2 * C_2;
};


struct attribute_blind_wat11_i_oe {
        uint32_t attr; 
        g1_t g_b_attr;
};

struct public_key_wat11_i_oe {
        uint32_t N_ATTR;
        g1_t g;
        g2_t h;
        gt_t A;
        g1_t B;
        struct attribute_blind_wat11_i_oe * attributes;
};




int init_secret_key_rw13_oe(const uint32_t n_attr, struct secret_key_rw13_oe *s);

void get_k_attr_rw13_oe(const uint32_t attr, const struct secret_key_rw13_oe s, g2_t k_attr_1, g2_t k_attr_2);


int init_public_key_rw13_oe(const uint32_t n_attr, struct public_key_rw13_oe *p);

int init_master_key_rw13_oe(const uint32_t n_attr, struct master_key_rw13_oe *m);

//end rw13 oe


// wat11-i-oe

int init_ciphertext_wat11_i_oe(const uint32_t n_attr, struct ciphertext_wat11_i_oe *c);
struct c_attribute_wat11_i_oe {
        uint32_t attr; 
        g1_t c_attr;
};

struct c_attribute_wat11_iv_oe_1 {
        uint32_t attr; 
        g1_t c_attr;
};
struct c_attribute_wat11_iv_oe_2 {
        uint32_t attr; 
        g2_t c_attr;
};

int init_public_key_wat11_i_oe(const uint32_t n_attr, struct public_key_wat11_i_oe *p);


struct attribute {
        uint32_t attr; 
        bn_t b_attr;
};

struct attribute_blind {
        uint32_t attr; 
        g1_t g_b_attr;
};

struct attribute_blind_ok {
        uint32_t attr; 
        g2_t h_b_attr;
};


struct k_attribute {
        uint32_t attr; 
        g2_t k_attr;
};

struct k_attribute_lu_oe {
        uint32_t attr; 
        g1_t k_attr;
};

struct k_attribute_lu_ok {
        uint32_t attr; 
        g1_t k_attr;
};



struct k_attribute_ok {
        uint32_t attr; 
        g1_t k_attr;
};

struct k_attribute_od {
        uint32_t attr; 
        g1_t k_attr;
};

struct k_attribute_cp {
        uint32_t attr; 
        g1_t k_attr;
};

struct c_attribute {
        uint32_t attr; 
        g1_t c_attr;
};


struct c_attribute_lu_oe_1 {
        uint32_t attr; 
        g1_t c_attr;
};

struct c_attribute_lu_oe_2 {
        uint32_t attr; 
        g2_t c_attr;
};

struct c_attribute_lu_ok_1 {
        uint32_t attr; 
        g1_t c_attr;
};

struct c_attribute_lu_ok_2 {
        uint32_t attr; 
        g2_t c_attr;
};



struct c_attribute_ok {
        uint32_t attr; 
        g2_t c_attr;
};

struct c_attribute_od {
        uint32_t attr; 
        g2_t c_attr;
};

struct c_attribute_cp {
        uint32_t attr; 
        g2_t c_attr;
};

struct master_key {
        uint32_t N_ATTR;
        struct attribute * attributes;
        bn_t b;
        bn_t alpha;
};

struct public_key {
        uint32_t N_ATTR;
        g1_t g;
        g2_t h;
        gt_t A;
        g1_t B;
        struct attribute_blind * attributes;
};

struct public_key_lu_ok {
        uint32_t N_ATTR;
        g1_t g;
        g2_t h;
        gt_t A;
        g1_t B;
        struct attribute_blind * attributes;
};



struct public_key_ok {
        uint32_t N_ATTR;
        g1_t g;
        g2_t h;
        gt_t A;
        g2_t B;
        struct attribute_blind_ok * attributes;
};

struct public_key_cp {
        uint32_t N_ATTR;
        g1_t g;
        g2_t h;
        gt_t A;
        g1_t B;
        struct attribute_blind * attributes;
};

struct secret_key {
        uint32_t N_ATTR;
        g2_t K;
        g2_t K_PRIMA;
        struct k_attribute * attributes;
};

struct secret_key_lu_ok {
        uint32_t N_ATTR;
        g1_t K;
        g2_t K_PRIMA;
        struct k_attribute_lu_ok * attributes;
};



struct secret_key_lu_oe {
        uint32_t N_ATTR;
        g2_t K;
        g2_t K_PRIMA;
        struct k_attribute_lu_oe * attributes;
};


struct secret_key_od {
        uint32_t N_ATTR;
        g2_t K;
        g2_t K_PRIMA;
        struct k_attribute_od * attributes;
};

struct secret_key_ok {
        uint32_t N_ATTR;
        g1_t K;
        g1_t K_PRIMA;
        struct k_attribute_ok * attributes;
};

struct secret_key_cp {
        uint32_t N_ATTR;
        g1_t K;
        g2_t K_PRIMA;
        struct k_attribute_cp * attributes;
};

struct ciphertext {
        uint32_t N_ATTR;
        gt_t C;
        g1_t C_PRIMA;
        struct c_attribute * C_1;
        struct c_attribute * C_2;
};

struct ciphertext_lu_oe {
        uint32_t N_ATTR;
        gt_t C;
        g1_t C_PRIMA;
        struct c_attribute_lu_oe_1 * C_1;
        struct c_attribute_lu_oe_2 * C_2;
};

struct ciphertext_lu_ok {
        uint32_t N_ATTR;
        gt_t C;
        g2_t C_PRIMA;
        struct c_attribute_lu_ok_1 * C_1;
        struct c_attribute_lu_ok_2 * C_2;
};



struct ciphertext_ok {
        uint32_t N_ATTR;
        gt_t C;
        g2_t C_PRIMA;
        struct c_attribute_ok * C_1;
        struct c_attribute_ok * C_2;
};

struct ciphertext_od {
        uint32_t N_ATTR;
        gt_t C;
        g1_t C_PRIMA;
        struct c_attribute * C_1;
        struct c_attribute_od * C_2;
};

struct ciphertext_cp {
        uint32_t N_ATTR;
        gt_t C;
        g2_t C_PRIMA;
        struct c_attribute * C_1;
        struct c_attribute_cp * C_2;
};


int init_master_key(const uint32_t n_attr, struct master_key *m);
int init_public_key(const uint32_t n_attr, struct public_key *p);
int init_public_key_ok(const uint32_t n_attr, struct public_key_ok *p);
int init_public_key_cp(const uint32_t n_attr, struct public_key_cp *p);
int init_public_key_lu_ok(const uint32_t n_attr, struct public_key_lu_ok *p);


int init_secret_key(const uint32_t n_attr, struct secret_key *s);
int init_secret_key_lu_oe(const uint32_t n_attr, struct secret_key_lu_oe *s);
int init_secret_key_lu_ok(const uint32_t n_attr, struct secret_key_lu_ok *s);




int init_secret_key_ok(const uint32_t n_attr, struct secret_key_ok *s);
int init_secret_key_od(const uint32_t n_attr, struct secret_key_od *s);
int init_secret_key_cp(const uint32_t n_attr, struct secret_key_cp *s);

int init_ciphertext(const uint32_t n_attr, struct ciphertext *c);
int init_ciphertext_ok(const uint32_t n_attr, struct ciphertext_ok *c);
int init_ciphertext_od(const uint32_t n_attr, struct ciphertext_od *c);
int init_ciphertext_cp(const uint32_t n_attr, struct ciphertext_cp *c);
int init_ciphertext_lu_oe(const uint32_t n_attr, struct ciphertext_lu_oe *c);
int init_ciphertext_lu_ok(const uint32_t n_attr, struct ciphertext_lu_ok *c);





void set_b_attr(const uint32_t attr, bn_t b_attr, struct master_key *m); 
void get_b_attr(const uint32_t attr, const struct master_key m, bn_t bn_o);     

void get_b_attr_blind(const uint32_t attr, const struct public_key p, g1_t g1_o);
void get_b_attr_blind_ok(const uint32_t attr, const struct public_key_ok p, g2_t g2_o);
void get_b_attr_blind_cp(const uint32_t attr, const struct public_key_cp p, g1_t g1_o);

void set_b_attr_blind(const uint32_t attr, g1_t g_b_attr, struct public_key *p);
void set_b_attr_blind_ok(const uint32_t attr, g2_t h_b_attr, struct public_key_ok *p);
void set_b_attr_blind_cp(const uint32_t attr, g1_t g_b_attr, struct public_key_cp *p);

void get_k_attr(const uint32_t attr, const struct secret_key s, g2_t k_attr);
void get_k_attr_lu_oe(const uint32_t attr, const struct secret_key_lu_oe s, g1_t k_attr);




void get_k_attr_ok(const uint32_t attr, const struct secret_key_ok s, g1_t k_attr);
void get_k_attr_wat11_i_ok(const uint32_t attr, const struct secret_key_wat11_i_ok s, g1_t k_attr);

void get_k_attr_lu_ok(const uint32_t attr, const struct secret_key_lu_ok s, g1_t k_attr);



void get_k_attr_od(const uint32_t attr, const struct secret_key_od s, g1_t k_attr);
void get_k_attr_cp(const uint32_t attr, const struct secret_key_cp s, g1_t k_attr);
void get_k_attr_wat11_iv_oe(const uint32_t attr, const struct secret_key_wat11_iv_oe s, g1_t k_attr);


void set_k_attr(const uint32_t attr, g2_t k_attr, struct secret_key *s);
void set_k_attr_lu_oe(const uint32_t attr, g1_t k_attr, struct secret_key_lu_oe *s);
void set_k_attr_lu_ok(const uint32_t attr, g1_t k_attr, struct secret_key_lu_ok *s);


void set_k_attr_ok(const uint32_t attr, g1_t k_attr, struct secret_key_ok *s);
void set_k_attr_od(const uint32_t attr, g1_t k_attr, struct secret_key_od *s);
void set_k_attr_cp(const uint32_t attr, g1_t k_attr, struct secret_key_cp *s);

void get_c_attr_c_1(const uint32_t attr, const struct ciphertext c, g1_t c_1);

void get_c_attr_c_1_wat11_i_ok(const uint32_t attr, const struct ciphertext_wat11_i_ok c, g2_t c_1);
void get_c_attr_c_2_wat11_i_ok(const uint32_t attr, const struct ciphertext_wat11_i_ok c, g2_t c_2);

void get_c_attr_c_1_lu_oe(const uint32_t attr, const struct ciphertext_lu_oe c, g1_t c_1);

void get_c_attr_c_1_lu_ok(const uint32_t attr, const struct ciphertext_lu_ok c, g1_t c_1);
void get_c_attr_c_2_lu_ok(const uint32_t attr, const struct ciphertext_lu_ok c, g2_t c_2);

void get_c_attr_c_1_ok(const uint32_t attr, const struct ciphertext_ok c, g2_t c_1);
void get_c_attr_c_1_od(const uint32_t attr, const struct ciphertext_od c, g1_t c_1);
void get_c_attr_c_1_cp(const uint32_t attr, const struct ciphertext_cp c, g1_t c_1);

void set_c_attr_c_1(const uint32_t attr, g1_t c_1, struct ciphertext *c);
void set_c_attr_c_1_lu_oe(const uint32_t attr, g1_t c_1, struct ciphertext_lu_oe *c);



void set_c_attr_c_1_lu_ok(const uint32_t attr, g1_t c_1, struct ciphertext_lu_ok *c);
void set_c_attr_c_2_lu_ok(const uint32_t attr, g2_t c_2, struct ciphertext_lu_ok *c);


void set_c_attr_c_1_ok(const uint32_t attr, g2_t c_1, struct ciphertext_ok *c);
void set_c_attr_c_1_od(const uint32_t attr, g1_t c_1, struct ciphertext_od *c);
void set_c_attr_c_1_cp(const uint32_t attr, g1_t c_1, struct ciphertext_cp *c);

void get_c_attr_c_2(const uint32_t attr, const struct ciphertext c, g1_t c_2);
void get_c_attr_c_2_lu_oe(const uint32_t attr, const struct ciphertext_lu_oe c, g2_t c_2);




//void get_c_attr_c_2_lu_oe(const uint32_t attr, const struct ciphertext c, g2_t c_2);


void get_c_attr_c_2_ok(const uint32_t attr, const struct ciphertext_ok c, g2_t c_2);
void get_c_attr_c_2_od(const uint32_t attr, const struct ciphertext_od c, g2_t c_2);
void get_c_attr_c_2_cp(const uint32_t attr, const struct ciphertext_cp c, g2_t c_2);

void set_c_attr_c_2(const uint32_t attr, g1_t c_2, struct ciphertext *c);
void set_c_attr_c_2_lu_oe(const uint32_t attr, g2_t c_2, struct ciphertext_lu_oe *c);




void set_c_attr_c_2_lu_oe(const uint32_t attr, g2_t c_2, struct ciphertext_lu_oe *c);


void set_c_attr_c_2_ok(const uint32_t attr, g2_t c_2, struct ciphertext_ok *c);
void set_c_attr_c_2_od(const uint32_t attr, g2_t c_2, struct ciphertext_od *c);
void set_c_attr_c_2_cp(const uint32_t attr, g2_t c_2, struct ciphertext_cp *c);



// wat11-i-oe

#endif


