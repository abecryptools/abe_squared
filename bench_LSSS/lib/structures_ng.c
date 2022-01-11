 
//#include <openabe/openabe.h>                                          
//#include <openabe/zsymcrypto.h>  
#include <stdlib.h>

#include "structures_ng.h"
//#include "zp_arith.h"
//#include "g1_arith.h"
//#include "g2_arith.h"
//#include "gt_arith.h"

int init_ciphertext_wat11_i_ok(const uint32_t n_attr, struct ciphertext_wat11_i_ok *c) {
  c->N_ATTR = n_attr;

  c->C_1 = (struct c_attribute_wat11_i_ok *) malloc (n_attr * sizeof(struct c_attribute_wat11_i_ok));
  c->C_2 = (struct c_attribute_wat11_i_ok *) malloc (n_attr * sizeof(struct c_attribute_wat11_i_ok));

  if (c->C_1 == NULL || c->C_2 == NULL) {
    return EXIT_FAILURE;
  } else {

    g2_null(&c->C_PRIMA);
    g2_new(&c->C_PRIMA);
 
    for (uint32_t i = 0; i < n_attr; i++) {
      g2_null(&c->C_1[i].c_attr);
      g2_new(&c->C_1[i].c_attr);

      g2_null(&c->C_2[i].c_attr);
      g2_new(&c->C_2[i].c_attr);
    }

    return EXIT_SUCCESS;
  }
}


int init_secret_key_wat11_i_ok(const uint32_t n_attr, struct secret_key_wat11_i_ok *s) {
  s->N_ATTR = n_attr;
  s->attributes = (struct k_attribute_wat11_i_ok *) malloc (n_attr * sizeof(struct k_attribute_wat11_i_ok));

  if (s->attributes == NULL) {
    return EXIT_FAILURE;
  } else {

    g1_null(&s->K_PRIMA);
    g1_new(&s->K_PRIMA)
    g1_null(&s->K);
    g1_new(&s->K)

    for (uint32_t i = 0; i < n_attr; i++) {
      g1_null(&s->attributes[i].k_attr);
      g1_new(&s->attributes[i].k_attr);
    }

    return EXIT_SUCCESS;
  }
} 


void get_k_attr_wat11_i_ok(const uint32_t attr, const struct secret_key_wat11_i_ok s, g1_t k_attr) { 
  for (uint32_t i = 0; i < s.N_ATTR; i++) {
    if (s.attributes[i].attr == attr)
      g1_copy(k_attr, s.attributes[i].k_attr);
  }
}


void get_b_attr_blind_wat11_i_ok(const uint32_t attr, const struct public_key_wat11_i_ok p, g2_t g2_o) {
  for (uint32_t i = 0; i < p.N_ATTR; i++) {
    if (p.attributes[i].attr == attr)
      g2_copy(g2_o, p.attributes[i].h_b_attr);
  }
}



int init_public_key_wat11_i_ok(const uint32_t n_attr, struct public_key_wat11_i_ok *p) {
                                                                        
   p->N_ATTR = n_attr;                                                  
   p->attributes = (struct attribute_blind_wat11_i_ok *) malloc (n_attr     * sizeof(struct attribute_blind_wat11_i_ok));
                                                                        
   if (p->attributes == NULL) {                                         
     return EXIT_FAILURE;                                               
   } else {                                                             
                                                                        
     g1_null(&p->g); g1_new(&p->g);                                     
     g2_null(&p->B); g2_new(&p->B);                                     
     g2_null(&p->h); g2_new(&p->h);                                     
                                                                        
     for (uint32_t i = 0; i < n_attr; i++) {                            
       g2_null(&p->attributes[i].h_b_attr);                             
       g2_new(&p->attributes[i].h_b_attr);                              
     }                                                                  
     return EXIT_SUCCESS;                                               
   }                                                                    
 }      



// rw13 oe


int init_ciphertext_rw13_oe(const uint32_t n_attr, struct ciphertext_rw13_oe *c) { 
  
  c->N_ATTR = n_attr;

  c->C_1 = (struct c_attribute_rw13_oe_1 *) malloc (n_attr * sizeof(struct c_attribute_rw13_oe_1));
  c->C_2 = (struct c_attribute_rw13_oe_2 *) malloc (n_attr * sizeof(struct c_attribute_rw13_oe_2));
  c->C_3 = (struct c_attribute_rw13_oe_3 *) malloc (n_attr * sizeof(struct c_attribute_rw13_oe_3));

  if (c->C_1 == NULL || c->C_2 == NULL || c->C_3 == NULL) {
    return EXIT_FAILURE;
  } else {

    g1_null(&c->C_PRIMA);
    g1_new(&c->C_PRIMA);

    for (uint32_t i = 0; i < n_attr; i++) {
      g1_null(&c->C_1[i].c_attr);
      g1_new(&c->C_1[i].c_attr);

      g1_null(&c->C_2[i].c_attr);
      g1_new(&c->C_2[i].c_attr);

      g1_null(&c->C_3[i].c_attr);
      g1_new(&c->C_3[i].c_attr);
    }

    return EXIT_SUCCESS;
  }
}



void get_k_attr_rw13_oe(const uint32_t attr, const struct secret_key_rw13_oe s, g2_t k_attr_1, g2_t k_attr_2) { 
  for (uint32_t i = 0; i < s.N_ATTR; i++) {
    if (s.attributes_K_1[i].attr == attr) {
      g2_copy(k_attr_1, s.attributes_K_1[i].k_attr);
      g2_copy(k_attr_2, s.attributes_K_2[i].k_attr);
    }
  }
}


int init_secret_key_rw13_oe(const uint32_t n_attr, struct secret_key_rw13_oe *s) {
  s->N_ATTR = n_attr;

  s->attributes_K_1 = (struct k_attribute_K_1_oe *) malloc (n_attr * sizeof(struct k_attribute_K_1_oe));
  s->attributes_K_2 = (struct k_attribute_K_2_oe *) malloc (n_attr * sizeof(struct k_attribute_K_2_oe));

  if (s->attributes_K_1 == NULL || s->attributes_K_2 == NULL) {
    return EXIT_FAILURE;
  } else {

    g2_null(&s->K);
    g2_new(&s->K)
      g2_null(&s->K_PRIMA);
    g2_new(&s->K_PRIMA);

    for (uint32_t i = 0; i < n_attr; i++) {
      g2_null(&s->attributes_K_1[i].k_attr);
      g2_null(&s->attributes_K_2[i].k_attr);
      g2_new(&s->attributes_K_1[i].k_attr);
      g2_new(&s->attributes_K_2[i].k_attr);
    }

    return EXIT_SUCCESS;
  }
} 


int init_public_key_rw13_oe(const uint32_t n_attr, struct public_key_rw13_oe *p)
{

  p->N_ATTR = n_attr;                                                  
  g1_null(&p->g); g1_new(&p->g);                                        g2_null(&p->h); g2_new(&p->h);
  g1_null(&p->g_b); g1_new(&p->g_b);
  g1_null(&p->g_b_0); g1_new(&p->g_b_0);
  g1_null(&p->g_b_1); g1_new(&p->g_b_1);
  g1_null(&p->g_b_prima); g1_new(&p->g_b_prima);

  return EXIT_SUCCESS;                                               
}      

int init_master_key_rw13_oe(const uint32_t n_attr, struct master_key_rw13_oe *m) {

  m->N_ATTR = n_attr;
  m->attributes = (struct attribute *) malloc (n_attr * sizeof(struct attribute));

  if (m->attributes == NULL) {
    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
} 

// rw13 oe
int init_ciphertext_rw13_ok(const uint32_t n_attr, struct ciphertext_rw13_ok *c) { 
  
  c->N_ATTR = n_attr;

  c->C_1 = (struct c_attribute_rw13_ok_1 *) malloc (n_attr * sizeof(struct c_attribute_rw13_ok_1));
  c->C_2 = (struct c_attribute_rw13_ok_2 *) malloc (n_attr * sizeof(struct c_attribute_rw13_ok_2));
  c->C_3 = (struct c_attribute_rw13_ok_3 *) malloc (n_attr * sizeof(struct c_attribute_rw13_ok_3));

  if (c->C_1 == NULL || c->C_2 == NULL || c->C_3 == NULL) {
    return EXIT_FAILURE;
  } else {

    g2_null(&c->C_PRIMA);
    g2_new(&c->C_PRIMA);

    for (uint32_t i = 0; i < n_attr; i++) {
      g2_null(&c->C_1[i].c_attr);
      g2_new(&c->C_1[i].c_attr);

      g2_null(&c->C_2[i].c_attr);
      g2_new(&c->C_2[i].c_attr);

      g2_null(&c->C_3[i].c_attr);
      g2_new(&c->C_3[i].c_attr);
    }

    return EXIT_SUCCESS;
  }
}

int init_secret_key_rw13_ok(const uint32_t n_attr, struct secret_key_rw13_ok *s) {
  s->N_ATTR = n_attr;

  s->attributes_K_1 = (struct k_attribute_K_1_ok *) malloc (n_attr * sizeof(struct k_attribute_K_1_ok));
  s->attributes_K_2 = (struct k_attribute_K_2_ok *) malloc (n_attr * sizeof(struct k_attribute_K_2_ok));

  if (s->attributes_K_1 == NULL || s->attributes_K_2 == NULL) {
    return EXIT_FAILURE;
  } else {

    g1_null(&s->K);
    g1_new(&s->K)
    g1_null(&s->K_PRIMA);
    g1_new(&s->K_PRIMA);

    for (uint32_t i = 0; i < n_attr; i++) {
      g1_null(&s->attributes_K_1[i].k_attr);
      g1_null(&s->attributes_K_2[i].k_attr);
      g1_new(&s->attributes_K_1[i].k_attr);
      g1_new(&s->attributes_K_2[i].k_attr);
    }

    return EXIT_SUCCESS;
  }
} 

int init_public_key_rw13_ok(const uint32_t n_attr, struct public_key_rw13_ok *p)
{

  p->N_ATTR = n_attr;                                                  
  g1_null(&p->g); g1_new(&p->g);                                        g2_null(&p->h); g2_new(&p->h);
  g2_null(&p->g_b); g2_new(&p->g_b);
  g2_null(&p->g_b_0); g2_new(&p->g_b_0);
  g2_null(&p->g_b_1); g2_new(&p->g_b_1);
  g2_null(&p->g_b_prima); g2_new(&p->g_b_prima);

  return EXIT_SUCCESS;                                               
}      

int init_public_key_wat11_i_oe(const uint32_t n_attr, struct public_key_wat11_i_oe *p) {

  p->N_ATTR = n_attr;
  p->attributes = (struct attribute_blind_wat11_i_oe *) malloc (n_attr * sizeof(struct attribute_blind_wat11_i_oe));

  if (p->attributes == NULL) {
    return EXIT_FAILURE;
  } else {

    g1_null(&p->g); g1_new(&p->g);
    g1_null(&p->B); g1_new(&p->B);
    g2_null(&p->h); g2_new(&p->h);
    
    for (uint32_t i = 0; i < n_attr; i++) {
      g1_null(&p->attributes[i].g_b_attr);
      g1_new(&p->attributes[i].g_b_attr);
    }

    return EXIT_SUCCESS;
  }
} 

int init_secret_key(const uint32_t n_attr, struct secret_key *s) {
  s->N_ATTR = n_attr;
  s->attributes = (struct k_attribute *) malloc (n_attr * sizeof(struct k_attribute));

  if (s->attributes == NULL) {
    return EXIT_FAILURE;
  } else {

    bn_new(&s->K_PRIMA);
    bn_new(&s->K);
 
    for (uint32_t i = 0; i < n_attr; i++)
      bn_new(&s->attributes[i].k_attr);

    return EXIT_SUCCESS;
  }
} 

int init_ciphertext_wat11_i_oe(const uint32_t n_attr, struct ciphertext_wat11_i_oe *c) {
  c->N_ATTR = n_attr;

  c->C_1 = (struct c_attribute_wat11_i_oe *) malloc (n_attr * sizeof(struct c_attribute_wat11_i_oe));
  c->C_2 = (struct c_attribute_wat11_i_oe *) malloc (n_attr * sizeof(struct c_attribute_wat11_i_oe));

  if (c->C_1 == NULL || c->C_2 == NULL) {
    return EXIT_FAILURE;
  } else {

    g1_null(&c->C_PRIMA);
    g1_new(&c->C_PRIMA);
 
    for (uint32_t i = 0; i < n_attr; i++) {
      g1_null(&c->C_1[i].c_attr);
      g1_new(&c->C_1[i].c_attr);

      g1_null(&c->C_2[i].c_attr);
      g1_new(&c->C_2[i].c_attr);
    }

    return EXIT_SUCCESS;
  }
}

int init_master_key(const uint32_t n_attr, struct master_key *m) {

  m->N_ATTR = n_attr;
  m->attributes = (struct attribute *) malloc (n_attr * sizeof(struct attribute));

  if (m->attributes == NULL) {
    return EXIT_FAILURE;
  } else {
    return EXIT_SUCCESS;
  }
} 




