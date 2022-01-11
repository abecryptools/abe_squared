///
/// \file   zelement.c
///
/// \brief  Class implementation for generic ZP_t and G_t elements.
///         Works either with OpenSSL or RELIC.
///
/// \author J. Ayo Akinyele
///

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//#include <openabe/zml/zelement.h>
//#include <openabe/utils/zconstants.h>

#include "../l_zconstants.h"
#include "l_zelement.h"

#include <relic/relic_bn.h>

//#include <openssl/objects.h>

/********************************************************************************
 * ZML abstract C operations for bignum operations
 ********************************************************************************/
void l_zml_init() {
  core_init();
  //ec_core_init();
}

void l_zml_clean() {
  core_clean();
  //ec_core_clean();
}

int l_zml_check_error() {
  ctx_t *ctx = core_get();
  if (ctx != NULL) {
    if (ctx->code == 1) //STS_OK)
      return TRUE;
    else
      return FALSE; /* means there was an error */
  }
  return -1;
}

void l_zml_bignum_init(l_bignum_t *b) {
    bn_null(*b);
    bn_new(*b);
}

void l_zml_bignum_copy(l_bignum_t to, const l_bignum_t from) {
  //l_bn_copy_const(to, from);
  bn_copy(to, from);
  return;
}

int l_zml_bignum_sign(const l_bignum_t a) {
    return bn_sign(a);
}

int l_zml_bignum_cmp(const l_bignum_t a, const l_bignum_t b) {
    return bn_cmp(a, b);
}

void l_zml_bignum_setzero(l_bignum_t a) {
    bn_zero(a);
}

int l_zml_bignum_countbytes(const l_bignum_t a) {
    return bn_size_bin(a);
}

void l_zml_bignum_rand(l_bignum_t a, l_bignum_t o) {
  bn_rand(a, RLC_POS, bn_bits(o));
}

void l_zml_bignum_mod(l_bignum_t x, const l_bignum_t o) {
  bn_mod(x, x, o);
}

void l_zml_bignum_add(l_bignum_t r, const l_bignum_t x, const l_bignum_t y,
                const l_bignum_t o) {
  bn_add(r, x, y);
  bn_mod(r, r, o);
  return;
}

void l_zml_bignum_sub(l_bignum_t r, const l_bignum_t x, const l_bignum_t y) {
  bn_sub(r, x, y);
}

void l_zml_bignum_sub_order(l_bignum_t r, const l_bignum_t x, const l_bignum_t y,
                const l_bignum_t o) {
  bn_sub(r, x, y);
  if (bn_sign(r) == RLC_NEG) {
    bn_add(r, r, o);
  } else {
    bn_mod(r, r, o);
  }
}

void l_zml_bignum_mul(l_bignum_t r, const l_bignum_t x, const l_bignum_t y,
                const l_bignum_t o) {
  bn_mul(r, x, y);
  if (bn_sign(r) == RLC_NEG) {
    bn_add(r, r, o);
  } else {
    bn_mod(r, r, o);
  }
}

int bn_is_one(const bn_t a) {
  if (a->used == 0)
    return 0; // false
  else if ((a->used == 1) && (a->dp[0] == 1))
    return 1; // true
  else
    return 0; // false
}

void l_zml_bignum_div(l_bignum_t r, const l_bignum_t x, const l_bignum_t y,
                const l_bignum_t o) {
  // r = (1 / y) mod o
  l_zml_bignum_mod_inv(r, y, o);
  if (l_zml_bignum_is_one(x))
    return; // return r
  // r = (r * x) mod o
  l_zml_bignum_mul(r, r, x, o);
}

void l_zml_bignum_exp(l_bignum_t r, const l_bignum_t x, const l_bignum_t y,
                const l_bignum_t o) {
  // r = (x^y) mod o
  bn_mxp(r, x, y, o);
}

void l_zml_bignum_lshift(l_bignum_t r, const l_bignum_t a, int n) {
  bn_lsh(r, a, n);
}

void l_zml_bignum_rshift(l_bignum_t r, const l_bignum_t a, int n) {
  bn_rsh(r, a, n);
}

char *l_zml_bignum_toHex(const l_bignum_t b, int *length) {
  char *hex = NULL;
  *length = bn_size_str(b, 16);
  hex = (char *)malloc(*length+1);
  //MALLOC_CHECK_OUT_OF_MEMORY(hex);
  bn_write_str(hex, *length, b, 16);
  return hex;
}

char *l_zml_bignum_toDec(const l_bignum_t b, int *length) {
  char *dec = NULL;
  *length = bn_size_str(b, 10);
  dec = (char *)malloc(*length+1);
  //MALLOC_CHECK_OUT_OF_MEMORY(dec);
  bn_write_str(dec, *length, b, 10);
  return dec;
}

void l_zml_bignum_negate(l_bignum_t b, const l_bignum_t o) {
  bn_neg(b, b);
  if (bn_sign(b) == RLC_NEG) {
    bn_add(b, b, o);
  }
}

int l_zml_bignum_mod_inv(l_bignum_t a, const l_bignum_t b, const l_bignum_t o) {
  bn_t s;
  l_bn_inits(s);
  // computes (1 / b) mod o
  bn_gcd_ext(s, a, NULL, b, o);
  // check if negative
  if (bn_sign(a) == RLC_NEG) {
    bn_add(a, a, o);
  }
  bn_free(s);
  return 1;
}

/********************************************************************************
 * ZML abstract C operations for EC operations
 ********************************************************************************/
/*
int l_ec_group_init(l_ec_group_t *group, uint8_t id) {
  switch (id) {
  case L_OpenABE_NIST_P256_ID:
    l_ec_ep_param_set(NIST_P256);
    break;
  case L_OpenABE_NIST_P384_ID:
    l_ec_ep_param_set(NIST_P384);
    break;
  case L_OpenABE_NIST_P521_ID:
    l_ec_ep_param_set(NIST_P521);
    break;
  default:
      return -1;
  }
  return 0;
}

void ec_get_order(l_ec_group_t group, l_bignum_t order) {
  // EC group structure is defined as static vars in RELIC
  ec_ep_curve_get_ord(order);
}

void l_ec_point_init(l_ec_group_t group, l_ec_point_t *e) {
  ep_null(*e);
  ep_new(*e);
}

void l_ec_point_copy(l_ec_point_t to, const l_ec_point_t from) {
  ep_copy_const(to, from);
}

void l_ec_point_set_inf(l_ec_group_t group, l_ec_point_t p) {
  ec_ep_set_infty(p);
}

int l_ec_point_is_inf(l_ec_group_t group, l_ec_point_t p) {
  // 1 if the point is at infinity, 0 otherise.
  return ec_ep_is_infty(p);
}

int l_ec_point_is_on_curve(l_ec_group_t group, l_ec_point_t p) {
  if (ec_ep_is_valid(p))
    return 1;
  return 0;
}

void l_ec_point_add(l_ec_group_t g, l_ec_point_t r, const l_ec_point_t x,
                  const l_ec_point_t y) {
  ep_add(r, x, y);
  ec_ep_norm(r, r);
}

void l_ec_point_mul(l_ec_group_t g, l_ec_point_t r, const l_ec_point_t x,
                  const l_bignum_t y) {
  //ep_mul(r, x, y);
  ec_ep_mul_lwnaf(r, x, y);
}

int l_ec_point_cmp(l_ec_group_t group, const l_ec_point_t a, const l_ec_point_t b) {
  return ec_ep_cmp(a, b);
}

void l_ec_get_coordinates(l_ec_group_t group, l_bignum_t x, l_bignum_t y,
                        const l_ec_point_t p) {
  ec_fp_prime_back(x, p->x);
  ec_fp_prime_back(y, p->y);
  return;
}

void l_ec_get_generator(l_ec_group_t group, l_ec_point_t p) {
  ec_ep_curve_get_gen(p);
}

size_t l_ec_point_elem_len(const l_ec_point_t g) {
  return ec_ep_size_bin(g, COMPRESS);
}

void l_ec_point_elem_in(l_ec_point_t g, uint8_t *in, size_t len) {
  ec_ep_read_bin(g, in, (int)len);
  ec_fp_zero(g->z);
  ec_fp_set_dig(g->z, 1);
}

void l_ec_point_elem_out(const ec_point_t g, uint8_t *out, size_t len) {
  ec_ep_write_bin(out, len, g, COMPRESS);
}

int l_ec_convert_to_point(l_ec_group_t group, l_ec_point_t p, uint8_t *xstr,
                         int len) {
  ec_point_elem_in(p, xstr, len);
  return TRUE;
}
*/

int l_bp_group_init(l_bp_group_t *group, uint8_t id) {
  /* RELIC definitions */
/*  int twist = EP_DTYPE; // , degree = 2;
  switch (id) {
  case L_OpenABE_BN_P254_ID:
    ep_param_set(BN_P254);
    ep2_curve_set_twist(twist);
    break;
  case L_OpenABE_BN_P256_ID:
    ep_param_set(BN_P256);
    ep2_curve_set_twist(twist);
    break;
  case L_OpenABE_BN_P382_ID:
    ep_param_set(BN_P382);
    ep2_curve_set_twist(twist);
    break;
  default:
      return -1;
  }*/
  return 0;
}

void l_bp_get_order(l_bp_group_t group, l_bignum_t order) {
  // EC group structure is defined as static vars in RELIC
  // assumes we've called bp_group_init on 'group'
  // g1_get_ord
  ep_curve_get_ord(order);
}

/********************************************************************************
 * ZML abstract C operations for G1 init/arithmetic
 ********************************************************************************/

void l_g1_init(l_bp_group_t group, l_g1_ptr *e) {
  l_g1_inits(*e);
}

void l_g1_set_to_infinity(l_bp_group_t group, l_g1_ptr *e) {
  l_g1_inits(*e);
  g1_set_infty(*e);
}

void l_g1_add_op(l_bp_group_t group, l_g1_ptr z, const l_g1_ptr x, const l_g1_ptr y) {
  //ep_add_projc(z, x, y);
   ep_add(z, x, y);
  ep_norm(z, z);
}

void l_g1_sub_op(l_bp_group_t group, l_g1_ptr z, const l_g1_ptr x) {
  //ep_sub_projc(z, x, z);
   //okep_sub(z, x, z);
  //okep_norm(z, z);
}

void l_g1_mul_op(l_bp_group_t group, l_g1_ptr z,  l_g1_ptr x,  l_bignum_t r) {
  g1_mul(z, x, r);
}

void l_g1_rand_op(l_g1_ptr g) {
    ep_rand(g);
}

void l_g1_map_op(const l_bp_group_t group, l_g1_ptr g, uint8_t *msg, int msg_len) {
  g1_map(g, msg, msg_len);
}

size_t l_g1_elem_len(const l_g1_ptr g) {
  return ep_size_bin(g, COMPRESS);
}

void l_g1_elem_in(l_g1_ptr g, uint8_t *in, size_t len) {
    ep_read_bin(g, in, (int)len);
}

void l_g1_elem_out(const l_g1_ptr g, uint8_t *out, size_t len) {
  ep_write_bin(out, len, g, COMPRESS);
}

size_t l_g2_elem_len(l_g2_ptr g) {
  return ep2_size_bin(g, COMPRESS);
}

void l_g2_elem_in(l_g2_ptr g, uint8_t *in, size_t len) {
    ep2_read_bin(g, in, (int)len);
}

void l_g2_elem_out(l_g2_ptr g, uint8_t *out, size_t len) {
  ep2_write_bin(out, len, g, COMPRESS);
}

size_t l_gt_elem_len(l_gt_ptr g, int should_compress) {
  return fp12_size_bin(g, should_compress);
}

void l_gt_elem_in(l_gt_ptr g, uint8_t *in, size_t len) {
    fp12_read_bin(g, in, (int)len);
}

void l_gt_elem_out(l_gt_ptr g, uint8_t *out, size_t len, int should_compress) {
  fp12_write_bin(out, len, g, should_compress);
}


/********************************************************************************
 * ZML abstract C operations for G2 init/arithmetic
 ********************************************************************************/

void l_g2_init(l_bp_group_t group, l_g2_ptr *e) {
  l_ep2_inits(*e);
}

void l_g2_set_to_infinity(l_bp_group_t group, l_g2_ptr *e) {
  l_ep2_inits(*e);
  // g2_set_infty
  ep2_set_infty(*e);
}

void l_g2_mul_op(l_bp_group_t group, l_g2_ptr z, l_g2_ptr x, l_bignum_t r) {
  // g2_mul(z, x, r);
  ep2_mul_lwnaf(z, x, r);
}

int l_g2_cmp_op(l_bp_group_t group, l_g2_ptr x, l_g2_ptr y) {
    return ep2_cmp(x, y);
}

/********************************************************************************
 * abstract C operations for GT init/arithmetic
 ********************************************************************************/

void l_gt_init(const l_bp_group_t group, l_gt_ptr *e) {
  l_fp12_inits(*e);
}

void l_gt_set_to_infinity(l_bp_group_t group, l_gt_ptr *e) {
  l_fp12_inits(*e);
  // gt_set_unity
  fp12_set_dig(*e, 1);
}

void l_gt_mul_op(const l_bp_group_t group, l_gt_ptr z, l_gt_ptr x, l_gt_ptr y) {
  fp12_mul_lazyr(z, x, y);
}

void l_gt_div_op(const l_bp_group_t group, l_gt_ptr z, l_gt_ptr x, l_gt_ptr y) {
  // gt_inv
  fp12_inv(z, y);
  // gt_mul
  fp12_mul_lazyr(z, x, z);
}

void l_gt_exp_op(const l_bp_group_t group, l_gt_ptr y, l_gt_ptr x, l_bignum_t r) {
  fp12_exp(y, x, r);
}

int l_gt_is_unity_check(const l_bp_group_t group, l_gt_ptr r) {
  // gt_is_unity
  return (fp12_cmp_dig(r, 1)) == 0;
}

void l_bp_map_op(const l_bp_group_t group, l_gt_ptr gt, l_g1_ptr g1, l_g2_ptr g2) {
  pp_map_oatep_k12(gt, g1, g2);
}

/****************************************************************
 * RELIC helper functions
 * These may end up as part of RELIC, not the OpenABE.
 * Once testing is complete they could be moved into the RELIC
 * source code and released per LGPL terms. It's not really clear
 * what to do with them.
 ****************************************************************/
/*
void l_bn_copy_const(bn_t c, const bn_t a) {
    int i;

    if (c->dp == a->dp)
        return;

    bn_grow(c, a->used);

    for (i = 0; i < a->used; i++) {
        c->dp[i] = a->dp[i];
    }

    c->used = a->used;
    c->sign = a->sign;
}

void l_ep_copy_const(ep_t r, const ep_t p) {
    l_fp_copy_const(r->x, p->x);
    l_fp_copy_const(r->y, p->y);
    l_fp_copy_const(r->z, p->z);
    r->norm = p->norm;
}

void l_fp_copy_const(fp_t c, const fp_t a) {
    int i;
    for (i = 0; i < FP_DIGS; i++) {
            c[i] = a[i];
    }
}

void l_ep2_copy_const(ep2_t r, const ep2_t p) {
    l_fp2_copy_const(r->x, p->x);
    l_fp2_copy_const(r->y, p->y);
    l_fp2_copy_const(r->z, p->z);
    r->norm = p->norm;
}

void l_fp2_copy_const(fp2_t c, const fp2_t a) {
    l_fp_copy_const(c[0], a[0]);
    l_fp_copy_const(c[1], a[1]);
}

void l_fp12_copy_const(fp12_t c, const fp12_t a) {
    l_fp6_copy_const(c[0], a[0]);
    l_fp6_copy_const(c[1], a[1]);
}

void l_fp6_copy_const(fp6_t c, const fp6_t a) {
    l_fp2_copy_const(c[0], a[0]);
    l_fp2_copy_const(c[1], a[1]);
    l_fp2_copy_const(c[2], a[2]);
}

int l_bn_cmp_const(bn_t a, const bn_t b) {
    if (a->sign == BN_POS && b->sign == BN_NEG) {
        return CMP_GT;
    }
    if (a->sign == BN_NEG && b->sign == BN_POS) {
        return CMP_LT;
    }

    if (a->sign == BN_NEG) {
        return l_bn_cmp_abs_const(b, a);
    }

    return l_bn_cmp_abs_const(a, b);
}

int l_bn_cmp_abs_const(const bn_t a, const bn_t b) {
    if (a->used > b->used) {
        return CMP_GT;
    }

    if (a->used < b->used) {
        return CMP_LT;
    }

    return l_bn_cmpn_low_const(a->dp, b->dp, a->used);
}

int l_bn_cmpn_low_const(const dig_t *a, const dig_t *b, const int size) {
    int i, r;

    a += (size - 1);
    b += (size - 1);

    r = CMP_EQ;
    for (i = 0; i < size; i++, --a, --b) {
        if (*a != *b && r == CMP_EQ) {
            r = (*a > *b ? CMP_GT : CMP_LT);
        }
    }
    return r;
}


int l_ep_cmp_const(ep_t p, const ep_t q) {
    if (l_fp_cmp_const(p->x, q->x) != CMP_EQ) {
        return CMP_NE;
    }

    if (l_fp_cmp_const(p->y, q->y) != CMP_EQ) {
        return CMP_NE;
    }

    if (l_fp_cmp_const(p->z, q->z) != CMP_EQ) {
        return CMP_NE;
    }

    return CMP_EQ;
}

int l_ep2_cmp_const(ep2_t p, const ep2_t q) {
    if (l_fp2_cmp_const(p->x, q->x) != CMP_EQ) {
        return CMP_NE;
    }

    if (l_fp2_cmp_const(p->y, q->y) != CMP_EQ) {
        return CMP_NE;
    }

    if (l_fp2_cmp_const(p->z, q->z) != CMP_EQ) {
        return CMP_NE;
    }

    return CMP_EQ;
}

int l_fp12_cmp_const(fp12_t a, const fp12_t b) {
    return ((l_fp6_cmp_const(a[0], b[0]) == CMP_EQ) &&
            (l_fp6_cmp_const(a[1], b[1]) == CMP_EQ) ? CMP_EQ : CMP_NE);
}

int l_fp6_cmp_const(fp6_t a, const fp6_t b) {
    return ((l_fp2_cmp_const(a[0], b[0]) == CMP_EQ) && (l_fp2_cmp_const(a[1], b[1]) == CMP_EQ)
            && (l_fp2_cmp_const(a[2], b[2]) == CMP_EQ) ? CMP_EQ : CMP_NE);
}

int l_fp2_cmp_const(fp2_t a, const fp2_t b) {
    return (l_fp_cmp_const(a[0], b[0]) == CMP_EQ) &&
    (l_fp_cmp_const(a[1], b[1]) == CMP_EQ) ? CMP_EQ : CMP_NE;
}

int l_fp_cmp_const(fp_t a, const fp_t b) {
    return l_fp_cmpn_low_const(a, b);
}

int l_fp_cmpn_low_const(dig_t *a, const dig_t *b) {
    int i, r;

    a += (FP_DIGS - 1);
    b += (FP_DIGS - 1);

    r = CMP_EQ;
    for (i = 0; i < FP_DIGS; i++, --a, --b) {
        if (*a != *b && r == CMP_EQ) {
            r = (*a > *b ? CMP_GT : CMP_LT);
        }
    }
    return r;
}
*/
