/// 
/// Copyright (c) 2018 Zeutro, LLC. All rights reserved.
/// 
/// This file is part of Zeutro's OpenABE.
/// 
/// OpenABE is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Affero General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// 
/// OpenABE is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/// GNU Affero General Public License for more details.
/// 
/// You should have received a copy of the GNU Affero General Public
/// License along with OpenABE. If not, see <http://www.gnu.org/licenses/>.
/// 
/// You can be released from the requirements of the GNU Affero General
/// Public License and obtain additional features by purchasing a
/// commercial license. Buying such a license is mandatory if you
/// engage in commercial activities involving OpenABE that do not
/// comply with the open source requirements of the GNU Affero General
/// Public License. For more information on commerical licenses,
/// visit <http://www.zeutro.com>.
///
/// \file   zelement.h
///
/// \brief  Base class definition for ZTK groups (EC/pairings)
///
/// \author J. Ayo Akinyele
///

#ifndef __L_ZELEMENT_H__
#define __L_ZELEMENT_H__

                                                                    
#include <relic/relic.h>                                                        
    

/*************************** BN Definitions *********************/
#define TRUE   1
#define FALSE  0

/* BEGIN RELIC macro definitions (default if BN_WITH_OEPNSSL not set) */

typedef bn_t l_bignum_t;

#define l_zml_bignum_free(b)            bn_free(b)
#define l_zml_bignum_safe_free(b)       if(b != NULL) free(b)

#define l_zml_bignum_fromHex(b, str, len)   bn_read_str(b, str, len, 16)
#define l_zml_bignum_fromBin(b, ustr, len)  bn_read_bin(b, ustr, len)
#define l_zml_bignum_toBin(b, str, len)     bn_write_bin(str, len, b)

#define l_zml_bignum_setuint(b, x)          bn_set_dig(b, x)
// returns 1 if true, otherwise 0
#define l_zml_bignum_is_zero(b)             bn_is_zero(b)
#define l_zml_bignum_is_one(b)              bn_is_one(b)

#define BN_CMP_LT                     RLC_LT
#define BN_CMP_EQ                     RLC_EQ
#define BN_CMP_GT                     RLC_GT

#define BN_POSITIVE                   RLC_POS
#define BN_NEGATIVE                   RLC_NEG
#define G_CMP_EQ                      RLC_EQ

int l_bn_is_one(const bn_t a);
/* END of RELIC macro definitions */
int l_zml_check_error();
void l_zml_bignum_rand(l_bignum_t a, l_bignum_t o);

/*************************** EC Definitions *********************/

/* if EC_WITH_OPENSSL not specifically defined,
 * then we use RELIC EC operations by default */

 /* BEGIN RELIC macro definitions */
typedef ep_t l_ec_point_t;
typedef void* l_ec_group_t;

#define l_ep_inits(g) \
        ep_null(g); \
        ep_new(g);

#define l_ec_point_free(e)        ep_free(e)
#define l_ec_group_free(g)        g = NULL;

#define l_ec_point_set_null(e)    /* do nothing here */
#define l_is_ec_point_null(e)     false
#define l_ec_get_ref(a)           &a

/* END of RELIC macro definitions */

// init/clean internal structures
void l_zml_init();
void l_zml_clean();

// abstract bignum operations
void l_zml_bignum_init(l_bignum_t *a);
void l_zml_bignum_copy(l_bignum_t to, const l_bignum_t from);
int l_zml_bignum_sign(const l_bignum_t a);
int l_zml_bignum_cmp(const l_bignum_t a, const l_bignum_t b);
void l_zml_bignum_setzero(l_bignum_t a);
int l_zml_bignum_countbytes(const l_bignum_t a);
int l_zml_bignum_mod_inv(l_bignum_t a, const l_bignum_t b, const l_bignum_t o);
void l_zml_bignum_mod(l_bignum_t x, const l_bignum_t o);
void l_zml_bignum_negate(l_bignum_t b, const l_bignum_t o);
void l_zml_bignum_add(l_bignum_t r, const l_bignum_t x, const l_bignum_t y, const l_bignum_t o);
void l_zml_bignum_sub(l_bignum_t r, const l_bignum_t x, const l_bignum_t y);
void l_zml_bignum_sub_order(l_bignum_t r, const l_bignum_t x, const l_bignum_t y, const l_bignum_t o);
void l_zml_bignum_mul(l_bignum_t r, const l_bignum_t x, const l_bignum_t y, const l_bignum_t o);
void l_zml_bignum_div(l_bignum_t r, const l_bignum_t x, const l_bignum_t y, const l_bignum_t o);
void l_zml_bignum_exp(l_bignum_t r, const l_bignum_t x, const l_bignum_t y, const l_bignum_t o);

// logical operators for bignums
void l_zml_bignum_lshift(l_bignum_t r, const l_bignum_t a, int n);
void l_zml_bignum_rshift(l_bignum_t r, const l_bignum_t a, int n);

// NOTE: must free the memory that is returned from bignum_toHex and bignum_toDec using bignum_safe_free
char *l_zml_bignum_toHex(const l_bignum_t b, int *length);
char *l_zml_bignum_toDec(const l_bignum_t b, int *length);

// abstract elliptic curve operations
/*int l_ec_group_init(l_ec_group_t *group, uint8_t id);
void l_ec_get_order(l_ec_group_t group, l_bignum_t order);
void l_ec_point_init(l_ec_group_t group, l_ec_point_t *e);
void l_ec_point_copy(l_ec_point_t to, const l_ec_point_t from);
void l_ec_point_set_inf(l_ec_group_t group, l_ec_point_t p);
int  l_ec_point_cmp(l_ec_group_t group, const l_ec_point_t a, const l_ec_point_t b);
int  l_ec_point_is_inf(l_ec_group_t group, l_ec_point_t p);
void l_ec_get_generator(l_ec_group_t group, l_ec_point_t p);
void l_ec_get_coordinates(l_ec_group_t group, l_bignum_t x, l_bignum_t y, const l_ec_point_t p);
int l_ec_convert_to_point(l_ec_group_t group, l_ec_point_t p, uint8_t *xstr, int len);
int  l_ec_point_is_on_curve(l_ec_group_t group, l_ec_point_t p);
void l_ec_point_add(l_ec_group_t g, l_ec_point_t r, const l_ec_point_t x, const l_ec_point_t y);
void l_ec_point_mul(l_ec_group_t g, l_ec_point_t r, const l_ec_point_t x, const l_bignum_t y);

size_t l_ec_point_elem_len(const l_ec_point_t g);
void l_ec_point_elem_in(l_ec_point_t g, uint8_t *in, size_t len);
void l_ec_point_elem_out(const l_ec_point_t g, uint8_t *out, size_t len);
*/
/*************************** BP Definitions *********************/

/* if BP_WITH_OPENSSL not specifically defined,
 * then we use RELIC EC operations by default */

 /* BEGIN RELIC macro definitions */

// ZTK-specific macros for RELIC
#define l_bn_inits(b) \
        bn_null(b); \
        bn_new(b);

#define l_g1_inits(g) \
        ep_null(g); \
        ep_new(g);

#define l_ep2_inits(g) \
        ep2_null(g); \
        ep2_new(g);

#define l_fp12_inits(g) \
        fp12_null(g); \
        fp12_new(g);

#define l_g1_copy_const    l_ep_copy_const //AT(G1_LOWER, copy_const)
#define l_g2_copy_const    l_ep2_copy_const //CAT(G2_LOWER, copy_const)
#define l_gt_copy_const    l_fp12_copy_const // CAT(GT_LOWER, copy_const)
#define l_g1_set_rand      CAT(G1_LOWER, set_rand)
#define l_g2_set_rand      CAT(G2_LOWER, set_rand)
#define l_gt_set_rand      CAT(GT_LOWER, set_rand)
#define l_g1_write_ostream CAT(G1_LOWER, write_ostream)
#define l_g2_write_ostream CAT(G2_LOWER, write_ostream)
#define l_gt_write_ostream CAT(GT_LOWER, write_ostream)
#define l_gt_is_zero       CAT(GT_LOWER, is_zero)

void l_bn_copy_const(bn_t c, const bn_t a);
void l_ep_copy_const(ep_t r, const ep_t p);
void l_fp_copy_const(fp_t c, const fp_t a);
void l_ep2_copy_const(ep2_t r, const ep2_t p);
void l_fp2_copy_const(fp2_t c, const fp2_t a);
void l_fp12_copy_const(fp12_t c, const fp12_t a);
void l_fp6_copy_const(fp6_t c, const fp6_t a);

int l_bn_cmp_const(bn_t a, const bn_t b);
int l_bn_cmp_abs_const(const bn_t a, const bn_t b);
int l_bn_cmpn_low_const(const dig_t *a, const dig_t *b, const int size);
int l_ep_cmp_const(ep_t p, const ep_t q);
int l_ep2_cmp_const(ep2_t p, const ep2_t q);
int l_fp12_cmp_const(fp12_t a, const fp12_t b);
int l_fp6_cmp_const(fp6_t a, const fp6_t b);
int l_fp2_cmp_const(fp2_t a, const fp2_t b);
int l_fp_cmp_const(fp_t a, const fp_t b);
int l_fp_cmpn_low_const(dig_t *a, const dig_t *b);

typedef void* l_bp_group_t;
#define l_bp_group_free(g)   g = nullptr;

typedef ep_t l_g1_ptr;
typedef ep2_t l_g2_ptr;
typedef fp12_t l_gt_ptr;

#define l_g_set_null(g)
#define l_g1_element_free   g1_free
#define l_g2_element_free   g2_free
#define l_gt_element_free   gt_free

#define l_is_elem_null(e)   FALSE
/* END of RELIC macro definitions */

// C helper functions to handle (OpenSSL/RELIC)
int l_bp_group_init(l_bp_group_t *group, uint8_t id);
void l_bp_get_order(l_bp_group_t group, l_bignum_t order);

// ZML abstract methods for G1
void l_g1_init(l_bp_group_t group, l_g1_ptr *e);
void l_g1_set_to_infinity(l_bp_group_t group, l_g1_ptr *e);
void l_g1_add_op(l_bp_group_t group, l_g1_ptr z, const l_g1_ptr x, const l_g1_ptr y);
void l_g1_sub_op(l_bp_group_t group, l_g1_ptr z, const l_g1_ptr x);
void l_g1_mul_op(l_bp_group_t group, l_g1_ptr z,  l_g1_ptr x,  l_bignum_t r);
void l_g1_rand_op(l_g1_ptr g);
void l_g1_map_op(const l_bp_group_t group, l_g1_ptr g, uint8_t *msg, int msg_len);

size_t l_g1_elem_len(const l_g1_ptr g);
void l_g1_elem_in(l_g1_ptr g, uint8_t *in, size_t len);
void l_g1_elem_out(const l_g1_ptr g, uint8_t *out, size_t len);
size_t l_g2_elem_len(l_g2_ptr g);
void l_g2_elem_in(l_g2_ptr g, uint8_t *in, size_t len);
void l_g2_elem_out(l_g2_ptr g, uint8_t *out, size_t len);
size_t l_gt_elem_len(l_gt_ptr g, int should_compress);
void l_gt_elem_in(l_gt_ptr g, uint8_t *in, size_t len);
void l_gt_elem_out(l_gt_ptr g, uint8_t *out, size_t len, int should_compress);

// ZML abstract methods for G2
void l_g2_init(l_bp_group_t group, l_g2_ptr *e);
void l_g2_set_to_infinity(l_bp_group_t group, l_g2_ptr *e);
int l_g2_cmp_op(l_bp_group_t group, l_g2_ptr x, l_g2_ptr y);
void l_g2_mul_op(l_bp_group_t group, l_g2_ptr z, l_g2_ptr x, l_bignum_t r);

// ZML abstract methods for GT
void l_gt_init(const l_bp_group_t group, l_gt_ptr *e);
void l_gt_set_to_infinity(l_bp_group_t group, l_gt_ptr *e);
void l_gt_mul_op(const l_bp_group_t group, l_gt_ptr z, l_gt_ptr x, l_gt_ptr y);
void l_gt_div_op(const l_bp_group_t group, l_gt_ptr z, l_gt_ptr x, l_gt_ptr y);
void l_gt_exp_op(const l_bp_group_t group, l_gt_ptr y, l_gt_ptr x, l_bignum_t r);
int l_gt_is_unity_check(const l_bp_group_t group, l_gt_ptr r);

// ZML (pairings & multi-pairings)
void l_bp_map_op(const l_bp_group_t group, l_gt_ptr gt, l_g1_ptr g1, l_g2_ptr g2);

#endif /* ifdef __ZELEMENT_H__ */
