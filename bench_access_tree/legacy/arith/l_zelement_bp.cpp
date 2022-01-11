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
/// \file   zelement_bp.cpp
///
/// \brief  Class implementation for OpenABE group elements.
///
/// \author Matthew Green and J. Ayo Akinyele
///

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//#include <openabe/openabe.h>
//#include <openssl/rand.h>

#include <list>                                                                 
#include <memory>                                                               
                                                                                 
extern "C" {                                                                    
   #include "l_zelement.h"                                                        
}                                                                               
                                                                                 
#include "../l_zbytestring.h"                                                    
#include "l_zgroup.h"                                                           
#include "../l_zobject.h"     
#include "l_zelement_bp.h"

using namespace std;

string L_OpenABE_convertCurveIDToString(L_OpenABECurveID id) {                      
   switch (id) {                                                                 
   case L_OpenABE_NIST_P256_ID:                                                    
     return "NIST_P256";                                                         
     break;                                                                      
   case L_OpenABE_NIST_P384_ID:                                                    
     return "NIST_P384";                                                         
     break;                                                                      
   case L_OpenABE_NIST_P521_ID:                                                    
     return "NIST_P521";                                                         
     break;                                                                      
   case L_OpenABE_BN_P254_ID:                                                      
     return "BN_P254";                                                           
     break;                                                                      
   case L_OpenABE_BN_P256_ID:                                                      
     return "BN_P256";                                                           
     break;                                                                      
   case L_OpenABE_BN_P382_ID:                                                      
     return "BN_P382";                                                           
     break;                                                                      
   case L_OpenABE_BN_P638_ID:                                                      
     return "BN_P638";                                                           
     break;                                                                      
   default:
     return "";
     //throw OpenABE_ERROR_INVALID_PARAMS_ID;                                      
   }                                                                             
 } 

/*
const string print_point(char *x, int x_len, char *y, int y_len) {
  string s;
  s = "[" + string(x, x_len);
  s += ",";
  s += string(y, y_len) + "]";
  return s;
}

const string g1_point_to_string(bp_group_t group, const g1_ptr p) {
  bignum_t x, y;
  zml_bignum_init(&x);
  zml_bignum_init(&y);
#if defined(BP_WITH_OPENSSL)
  G1_ELEM_get_affine_coordinates(group, p, x, y, NULL);
#endif
  int x_size, y_size;
  char *xstr = zml_bignum_toDec(x, &x_size);
  char *ystr = zml_bignum_toDec(y, &y_size);
  string s = print_point(xstr, x_size, ystr, y_size);
  //    s  = "[" + string(xstr, x_size);
  //    s += ",";
  //    s += string(ystr, y_size) + "]";

  zml_bignum_safe_free(xstr);
  zml_bignum_safe_free(ystr);
  zml_bignum_free(x);
  zml_bignum_free(y);
  return s;
}
*/
/*
void g1_convert_to_bytestring(bp_group_t group, oabe::OpenABEByteString &s,
                              const g1_ptr p) {
#if defined(BP_WITH_OPENSSL)
  uint8_t buf[MAX_BUFFER_SIZE];
  memset(buf, 0, MAX_BUFFER_SIZE);
  size_t len = G1_ELEM_point2oct(group, p, POINT_CONVERSION_COMPRESSED, buf,
                                 MAX_BUFFER_SIZE, NULL);
  s.appendArray(buf, len);
#else
  size_t len = g1_elem_len(p);
  s.fillBuffer(0, len);
  g1_elem_out(p, s.getInternalPtr(), len);
#endif
}

void g1_convert_to_point(bp_group_t group, oabe::OpenABEByteString &s, g1_ptr p) {
  uint8_t *xstr = s.getInternalPtr();
  size_t xstr_len = s.size();
#if defined(BP_WITH_OPENSSL)
  G1_ELEM_oct2point(group, p, xstr, xstr_len, NULL);
#else
  g1_elem_in(p, xstr, xstr_len);
  ASSERT(oabe::checkRelicError(), oabe::OpenABE_ERROR_SERIALIZATION_FAILED);
#endif
}

const string g2_point_to_string(bp_group_t group, const g2_ptr p) {
  bignum_t x[2], y[2];
  zml_bignum_init(&x[0]);
  zml_bignum_init(&y[0]);
  zml_bignum_init(&x[1]);
  zml_bignum_init(&y[1]);
#if defined(BP_WITH_OPENSSL)
  G2_ELEM_get_affine_coordinates(group, p, x, y, NULL);
#endif
  int x1_size, y1_size, x2_size, y2_size;
  char *x1str = zml_bignum_toDec(x[0], &x1_size);
  char *y1str = zml_bignum_toDec(y[0], &y1_size);
  char *x2str = zml_bignum_toDec(x[1], &x2_size);
  char *y2str = zml_bignum_toDec(y[1], &y2_size);

  std::string s = "";
  s += print_point(x1str, x1_size, y1str, y1_size) + ",";
  s += print_point(x2str, x1_size, y2str, y2_size);

  //    std::string s1, s2;
  //    s1  = "[" + string(x1str, x1_size);
  //    s1 += ",";
  //    s1 += string(y1str, y1_size) + "]";
  //    s2  = ", [" + string(x2str, x2_size);
  //    s2 += ",";
  //    s2 += string(y2str, y2_size) + "]";

  zml_bignum_safe_free(x1str);
  zml_bignum_safe_free(y1str);
  zml_bignum_safe_free(x2str);
  zml_bignum_safe_free(y2str);

  zml_bignum_free(x[0]);
  zml_bignum_free(y[0]);
  zml_bignum_free(x[1]);
  zml_bignum_free(y[1]);

  return s;
}

void g2_convert_to_bytestring(bp_group_t group, oabe::OpenABEByteString &s,
                              g2_ptr p) {
#if defined(BP_WITH_OPENSSL)
  uint8_t buf[MAX_BUFFER_SIZE];
  memset(buf, 0, MAX_BUFFER_SIZE); // ideal => POINT_CONVERSION_COMPRESSED
  size_t len = G2_ELEM_point2oct(group, p, POINT_CONVERSION_UNCOMPRESSED, buf,
                                 MAX_BUFFER_SIZE, NULL);
  s.appendArray(buf, len);
#else
  size_t len = g2_elem_len(p);
  s.fillBuffer(0, len);
  g2_elem_out(p, s.getInternalPtr(), len);

//  size_t len = g2_size_bin(p, COMPRESS);
//  // cout << "G1::serialize => " << len << endl;
//  s.fillBuffer(0, len);
//  g2_write_bin(s.getInternalPtr(), len, p, COMPRESS);
#endif
}

void g2_convert_to_point(bp_group_t group, oabe::OpenABEByteString &s, g2_ptr p) {
  uint8_t *xstr = s.getInternalPtr();
  size_t xstr_len = s.size();
#if defined(BP_WITH_OPENSSL)
  G2_ELEM_oct2point(group, p, xstr, xstr_len, NULL);
#else
  g2_elem_in(p, xstr, xstr_len);
  ASSERT(oabe::checkRelicError(), oabe::OpenABE_ERROR_SERIALIZATION_FAILED);
#endif
}

void gt_convert_to_bytestring(bp_group_t group, oabe::OpenABEByteString &s, gt_ptr p,
                              int should_compress) {
#if defined(BP_WITH_OPENSSL)
  uint8_t buf[MAX_BUFFER_SIZE];
  memset(buf, 0, MAX_BUFFER_SIZE);
  size_t len = GT_ELEM_elem2oct(group, p, buf, MAX_BUFFER_SIZE, NULL);
  s.appendArray(buf, len);
#else
  size_t len = gt_elem_len(p, should_compress);
  s.fillBuffer(0, len);
  gt_elem_out(p, s.getInternalPtr(), len, should_compress);
//  size_t len = gt_size_bin(p, should_compress);
//  // cout << "G1::serialize => " << len << endl;
//  s.fillBuffer(0, len);
//  gt_write_bin(s.getInternalPtr(), len, p, should_compress);
#endif
}

void gt_convert_to_point(bp_group_t group, oabe::OpenABEByteString &s, gt_ptr p) {
  uint8_t *xstr = s.getInternalPtr();
  size_t xstr_len = s.size();
#if defined(BP_WITH_OPENSSL)
  GT_ELEM_oct2elem(group, p, xstr, xstr_len, NULL);
#else
  gt_elem_in(p, xstr, xstr_len);
  ASSERT(oabe::checkRelicError(), oabe::OpenABE_ERROR_SERIALIZATION_FAILED);
#endif
}
*/

void l_multi_bp_map_op(const l_bp_group_t group, L_GT &gt,
                     std::vector<L_G1> &g1, std::vector<L_G2> &g2) {
  if (g1.size() != g2.size()) {
    //throw oabe::OpenABE_ERROR_INVALID_LENGTH;
    return;
  }
  const size_t n = g1.size();
  g1_t g_1[n];
  g2_t g_2[n];
  for (size_t i = 0; i < n; i++) {
    l_g1_inits(g_1[i]);
    g1_copy(g_1[i], g1.at(i).m_G1);
    l_ep2_inits(g_2[i]);
    g2_copy(g_2[i], g2.at(i).m_G2);
  }
  pp_map_sim_oatep_k12(gt.m_GT, g_1, g_2, n);
  for (size_t i = 0; i < n; i++) {
    g1_free(g_1[i]);
    g2_free(g_2[i]);
  }
}


/********************************************************************************
 * RNG trampoline from RELIC
 ********************************************************************************/

void ro_error(void) {
  cout << "Writing to read only object." << endl;
  exit(0);
}

//namespace oabe {


bool checkRelicError() {
  //return (zml_check_error() == TRUE);
}

/********************************************************************************
 * Implementation of the Group class
 ********************************************************************************/

L_BPGroup::L_BPGroup(L_OpenABECurveID id) : L_ZGroup(id) {
  l_bp_group_init(&group, id);
  group_param = L_OpenABE_convertCurveIDToString(id);
  l_zml_bignum_init(&order);
  l_bp_get_order(group, order);
}

L_BPGroup::~L_BPGroup() {
  l_bp_group_free(group);
  l_zml_bignum_free(order);
}

void L_BPGroup::getGroupOrder(l_bignum_t o) {
  l_zml_bignum_copy(o, order);
}

/********************************************************************************
 * Implementation of the ZP class
 ********************************************************************************/

// Begin ZP-specific classes

L_ZP::L_ZP() {
  l_zml_bignum_init(&this->m_ZP);
  l_zml_bignum_init(&this->order);
  isOrderSet = false;
  isInit = true;
}

L_ZP::L_ZP(uint32_t x) {
  l_zml_bignum_init(&this->m_ZP);
  l_zml_bignum_init(&this->order);
  l_zml_bignum_setuint(this->m_ZP, x);
  isOrderSet = false;
  isInit = true;
}

L_ZP::L_ZP(char *hex_str, l_bignum_t o) {
  l_zml_bignum_init(&m_ZP);
  l_zml_bignum_init(&order);
  l_zml_bignum_copy(order, o);
  l_zml_bignum_fromHex(m_ZP, (const char *)hex_str, strlen(hex_str));
  isOrderSet = true;
  isInit = true;
}

L_ZP::L_ZP(uint8_t *bstr, uint32_t bstr_len, l_bignum_t o) {
  l_zml_bignum_init(&m_ZP);
  l_zml_bignum_init(&order);
  l_zml_bignum_copy(order, o);
  l_zml_bignum_fromBin(m_ZP, bstr, bstr_len);
  l_zml_bignum_mod(m_ZP, order);
  isOrderSet = true;
  isInit = true;
}

L_ZP::L_ZP(l_bignum_t y) {
  l_zml_bignum_init(&m_ZP);
  l_zml_bignum_copy(m_ZP, y);
  l_zml_bignum_init(&order);
  // g1_get_ord(this->order);
  isOrderSet = false;
  isInit = true;
}

L_ZP::L_ZP(const L_ZP& w)
{
  l_zml_bignum_init(&this->m_ZP);
  l_zml_bignum_copy(this->m_ZP, w.m_ZP);
  l_zml_bignum_init(&this->order);
  l_zml_bignum_copy(this->order, w.order);
  isInit = w.isInit;
  isOrderSet = w.isOrderSet;
}

L_ZP::~L_ZP() {
  l_zml_bignum_free(m_ZP);
  l_zml_bignum_free(order);
}

L_ZP &L_ZP::operator+=(const L_ZP &x) {
  L_ZP r(*this);
  *this = r + x;
  return *this;
}

L_ZP &L_ZP::operator*=(const L_ZP &x) {
  L_ZP r(*this);
  *this = r * x;
  return *this;
}

L_ZP &L_ZP::operator=(const L_ZP &w) {
  if (isInit) {
    l_zml_bignum_copy(m_ZP, w.m_ZP);
    l_zml_bignum_copy(order, w.order);
    isOrderSet = w.isOrderSet;
  } else
    ro_error();
  return *this;
}

L_ZP operator+(const L_ZP &x, const L_ZP &y) {
  //ASSERT(x.isOrderSet || y.isOrderSet, OpenABE_ERROR_INVALID_INPUT);
  L_ZP zr;
  if (x.isOrderSet)
    zr.setOrder(x.order);
  else
    zr.setOrder(y.order);

  l_zml_bignum_add(zr.m_ZP, x.m_ZP, y.m_ZP, zr.order);
  return zr;
}

L_ZP operator-(const L_ZP &x, const L_ZP &y) {
  //ASSERT(x.isOrderSet || y.isOrderSet, OpenABE_ERROR_INVALID_INPUT);
  L_ZP zr;
  if (x.isOrderSet)
    zr.setOrder(x.order);
  else
    zr.setOrder(y.order);

  l_zml_bignum_sub_order(zr.m_ZP, x.m_ZP, y.m_ZP, zr.order);
  return zr;
}

L_ZP operator-(const L_ZP &x) {
  //ASSERT(x.isInit && x.isOrderSet, OpenABE_ERROR_INVALID_INPUT);
  L_ZP zr = x;
  l_zml_bignum_negate(zr.m_ZP, zr.order);
  return zr;
}

L_ZP operator*(const L_ZP &x, const L_ZP &y) {
  //ASSERT(x.isOrderSet || y.isOrderSet, OpenABE_ERROR_INVALID_INPUT);
  L_ZP zr;
  if (x.isOrderSet)
    zr.setOrder(x.order);
  else
    zr.setOrder(y.order);

  l_zml_bignum_mul(zr.m_ZP, x.m_ZP, y.m_ZP, zr.order);
  return zr;
}

void L_ZP::multInverse() {
  // compute c = (1 / zr) mod o
  if (this->isInit && this->isOrderSet) {
    l_zml_bignum_mod_inv(this->m_ZP, this->m_ZP, this->order);
  }
}

L_ZP operator/(const L_ZP &x, const L_ZP &y) {
  L_ZP c;
  if (l_zml_bignum_is_zero(y.m_ZP)) {
    cout << "Divide by zero error!" << endl;
    exit(-1);
    //return;
  }

  //ASSERT(x.isOrderSet || y.isOrderSet, OpenABE_ERROR_INVALID_INPUT);
  L_ZP r;
  if (x.isOrderSet)
    r.setOrder(x.order);
  else
    r.setOrder(y.order);

  l_zml_bignum_div(r.m_ZP, x.m_ZP, y.m_ZP, r.order);
  return r;
}

L_ZP power(const L_ZP &x, unsigned int r) {
  L_ZP zr;
  //ASSERT(x.isOrderSet, OpenABE_ERROR_INVALID_INPUT);
  zr.setOrder(x.order);

  l_bignum_t p;
  l_zml_bignum_init(&p);
  l_zml_bignum_setuint(p, r);
  l_zml_bignum_exp(zr.m_ZP, x.m_ZP, p, zr.order);
  l_zml_bignum_free(p);
  return zr;
}

L_ZP power(const L_ZP &x, const L_ZP &r) {
  L_ZP zr;
  //ASSERT(x.isOrderSet || r.isOrderSet, OpenABE_ERROR_INVALID_INPUT);
  if (x.isOrderSet)
    zr.setOrder(x.order);
  else
    zr.setOrder(r.order);

  l_zml_bignum_exp(zr.m_ZP, x.m_ZP, r.m_ZP, zr.order);
  return zr;
}

bool L_ZP::ismember(void) {
  //ASSERT(isInit && isOrderSet, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);
  bool result;
  // CMP_LT if a < b, CMP_EQ if a == b and CMP_GT if a > b.
  result = (l_zml_bignum_cmp(m_ZP, order) == BN_CMP_LT &&
            l_zml_bignum_sign(m_ZP) == BN_POSITIVE);
  return result;
}

void L_ZP::setOrder(const l_bignum_t o) {
  //ASSERT(isInit, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);
  if (!isOrderSet) {
    l_zml_bignum_copy(order, o);
    isOrderSet = true;
  }
}

void L_ZP::setRandom(l_bignum_t o) {
  //ASSERT(isInit, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);
  // 1. get some number of bytes
  if (!this->isOrderSet) {
    this->isOrderSet = true;
    l_zml_bignum_copy(this->order, o);
  }
  int length = l_zml_bignum_countbytes(this->order);
  // 2. call bignum_fromBin on the bytes obtained
  uint8_t buf[length];
  memset(buf, 0, length);
  l_zml_bignum_rand(this->m_ZP, this->order);
  l_zml_bignum_mod(this->m_ZP, this->order);
}

void L_ZP::setFrom(L_ZP &z, uint32_t index) {
  // hash z + index?
  //ASSERT(isInit, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);
  l_zml_bignum_copy(this->m_ZP, z.m_ZP);
  *this = *this + index;
}

ostream &operator<<(ostream &os, const L_ZP &zr) {
  int len = 0;
  char *str = l_zml_bignum_toDec(zr.m_ZP, &len);
  string s0 = string(str, len-1);
  l_zml_bignum_safe_free(str);
  os << s0 << " (orderSet: " << (zr.isOrderSet ? "true)" : "false)");
  return os;
}

bool operator<(const L_ZP &x, const L_ZP &y) {
  return (l_zml_bignum_cmp(x.m_ZP, y.m_ZP) == BN_CMP_LT);
}

bool operator<=(const L_ZP &x, const L_ZP &y) {
  return (l_zml_bignum_cmp(x.m_ZP, y.m_ZP) <= BN_CMP_EQ);
}

bool operator>(const L_ZP &x, const L_ZP &y) {
  return (l_zml_bignum_cmp(x.m_ZP, y.m_ZP) == BN_CMP_GT);
}

bool operator>=(const L_ZP &x, const L_ZP &y) {
  return (l_zml_bignum_cmp(x.m_ZP, y.m_ZP) >= BN_CMP_EQ);
}

bool operator==(const L_ZP &x, const L_ZP &y) {
  //ASSERT(x.isOrderSet || y.isOrderSet, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);
  return (l_zml_bignum_cmp(x.m_ZP, y.m_ZP) == BN_CMP_EQ);
}

bool operator!=(const L_ZP &x, const L_ZP &y) {
  return (l_zml_bignum_cmp(x.m_ZP, y.m_ZP) != BN_CMP_EQ);
}

L_ZP operator<<(const L_ZP &a, int b) {
  // left shift
  L_ZP zr = a;
  l_zml_bignum_lshift(zr.m_ZP, zr.m_ZP, b);
  return zr;
}

L_ZP operator>>(const L_ZP &a, int b) {
  // right shift
  L_ZP zr = a;
  l_zml_bignum_rshift(zr.m_ZP, zr.m_ZP, b);
  return zr;
}

void L_ZP::serialize(L_OpenABEByteString &result) const {
  //ASSERT(isInit, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);
  result.clear();
  result.insertFirstByte(L_OpenABE_ELEMENT_ZP);
  this->getLengthAndByteString(result);
}

void L_ZP::deserialize(L_OpenABEByteString &input) {
  size_t inputSize = input.size(), hdrLen = 3;
  //ASSERT(isInit, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);

  // first byte is the group type
  if (input.at(0) == L_OpenABE_ELEMENT_ZP && inputSize > hdrLen) {
    uint16_t len = 0;
    // read 2 bytes from right to left
    len |= input.at(2);           // Moves to 0x00FF
    len |= (input.at(1) << 8);    // Moves to 0xFF00
    //ASSERT(input.size() == (len + hdrLen), OpenABE_ERROR_SERIALIZATION_FAILED);

    uint8_t *bstr = (input.getInternalPtr() + hdrLen);
    l_zml_bignum_fromBin(this->m_ZP, bstr, len);
    if (isOrderSet && l_zml_bignum_cmp(this->m_ZP, this->order) == BN_CMP_GT) {
      l_zml_bignum_mod(this->m_ZP, this->order);
    }
  }
}

bool L_ZP::isEqual(L_ZObject *z) const {
  L_ZP *z1 = dynamic_cast<L_ZP *>(z);
  if (z1 != NULL) {
    return *z1 == *this;
  }
  return false;
}

L_OpenABEByteString L_ZP::getByteString() const {
  size_t length = l_zml_bignum_countbytes(this->m_ZP);

  uint8_t data[length+1];
  memset(data, 0, length);
  l_zml_bignum_toBin(this->m_ZP, data, length);

  L_OpenABEByteString z;
  z.appendArray(data, length);
  return z;
}

string L_ZP::getBytesAsString() {
  L_OpenABEByteString z;
  z = this->getByteString();
  return z.toHex();
}


void L_ZP::getLengthAndByteString(L_OpenABEByteString &z) const {
  size_t length = l_zml_bignum_countbytes(this->m_ZP);

  uint8_t data[length];
  memset(data, 0, length);
  l_zml_bignum_toBin(this->m_ZP, data, length);

  z.pack16bits((uint16_t)length);
  z.appendArray(data, length);
}


/********************************************************************************
 * Implementation of the G1 class
 ********************************************************************************/

L_G1::L_G1(std::shared_ptr<L_BPGroup> bgroup) {
  this->isInit = true;
  this->bgroup = bgroup;
  // does init and sets the point to infinity
  l_g1_set_to_infinity(L_GET_BP_GROUP(this->bgroup), &this->m_G1);
}

L_G1::L_G1(const L_G1 &w) {
  if (w.bgroup != nullptr) {
    this->bgroup = w.bgroup;
  } else {
    //throw OpenABE_ERROR_INVALID_GROUP_PARAMS;
  }
  l_g1_init(L_GET_BP_GROUP(this->bgroup), &this->m_G1);
  g1_copy(this->m_G1, w.m_G1);
  this->isInit = true;
}

L_G1 &L_G1::operator=(const L_G1 &w) {
  if (this->isInit) {
    if (w.bgroup != nullptr) {
      this->bgroup = w.bgroup;
    }
    if (l_is_elem_null(this->m_G1)) {
      if (this->bgroup)
        l_g1_init(L_GET_BP_GROUP(this->bgroup), &this->m_G1);
      else
        ro_error();
    }
    g1_copy(this->m_G1, w.m_G1);
  } else
    ro_error();

  return *this;
}

L_G1::~L_G1() {
  if (this->isInit) {
    l_g1_element_free(this->m_G1);
    this->isInit = false;
  }
}

/*!
 * Field addition (rep. as multiplication operator) on elements of G1.
 *
 * @param[in]   - G1 element on lhs
 * @param[in]   - G1 element on rhs
 */
L_G1 operator*(const L_G1 &x, const L_G1 &y) {
  L_G1 z = x;
  l_g1_add_op(L_GET_BP_GROUP(z.bgroup), z.m_G1, z.m_G1, y.m_G1);
//#if defined(BP_WITH_OPENSSL)
//  G1_ELEM_add(GET_BP_GROUP(z.bgroup), z.m_G1, z.m_G1, y.m_G1, NULL);
//#else
  g1_add(z.m_G1, z.m_G1, y.m_G1);
  g1_norm(z.m_G1, z.m_G1);
//#endif
  return z;
}

L_G1 &L_G1::operator*=(const L_G1 &x) {
  L_G1 r(*this);
  *this = r * x;
  return *this;
}

/*!
 * Field subtraction (represented as division operator) on elements of G1.
 *
 * @param[in]   - G1 element on lhs
 * @param[in]   - G1 element on rhs
 */
L_G1 operator/(const L_G1 &x, const L_G1 &y) {
  // z = (x / y) => Point z = y; z = x - z;
  L_G1 z = y;
//ok  l_g1_sub_op(L_GET_BP_GROUP(z.bgroup), z.m_G1, x.m_G1);
//#if defined(BP_WITH_OPENSSL)
//  int rc = G1_ELEM_invert(GET_BP_GROUP(z.bgroup), z.m_G1, NULL);
//  ASSERT(rc == 1, OpenABE_ERROR_INVALID_INPUT);
//  G1_ELEM_add(GET_BP_GROUP(z.bgroup), z.m_G1, x.m_G1, z.m_G1, NULL);
//#else
//ok  g1_sub(z.m_G1, x.m_G1, z.m_G1);
//ok  g1_norm(z.m_G1, z.m_G1);
//#endif
  return z;
}

/*!
 * Negation operator on elements of G1.
 *
 * @param[in]   - G1 element to negate on rhs.
 */
L_G1 operator-(const L_G1 &x) {
//ok  L_G1 z = x;
//#if defined(BP_WITH_OPENSSL)
//  G1_ELEM_invert(GET_BP_GROUP(z.bgroup), z.m_G1, NULL);
//#else
//ok  g1_neg(z.m_G1, z.m_G1);
//#endif
  //return z;
}

/*!
 * Field multiplication (or exponentiation operator) on elements of G1.
 *
 * @param[in]   - ZP to multiply with this element.
 */
L_G1 L_G1::exp(L_ZP z) {
  L_G1 g1(this->bgroup);
  l_g1_mul_op(L_GET_BP_GROUP(g1.bgroup), g1.m_G1, this->m_G1, z.m_ZP);
  return g1;
}

/*!
 * Check whether G1 element is a member of a subgroup of the elliptic curve.
 *
 * @param[in]   - order of elliptic curve points in G1.
 */
bool L_G1::ismember(l_bignum_t order) {
  bool result;
  g1_t r;
  l_g1_inits(r);

  g1_mul(r, this->m_G1, order);
  if (g1_is_infty(r) == 1)
    result = true;
  else
    result = false;
  g1_free(r);
  return result;
}

/*!
 * Select random group element in G1.
 *
 * @param[in]   - an OpenABERNG object.
 */
void L_G1::setRandom() {
  if (this->isInit) {
// cout << "G1: ";
    // g1_rand(this->m_G1);
    l_g1_rand_op(this->m_G1);
  }
}

/*
ostream &operator<<(ostream &os, const G1 &g1) {
#if defined(BP_WITH_OPENSSL)
  os << g1_point_to_string(GET_BP_GROUP(g1.bgroup), g1.m_G1);
#else
  ep_write_ostream(os, const_cast<G1 &>(g1).m_G1, DEC);
#endif
  return os;
}
*/
bool operator==(const L_G1 &x, const L_G1 &y) {
  bool result;
  result = (g1_cmp(x.m_G1, y.m_G1) == RLC_EQ);
  return result;
}

bool operator!=(const L_G1 &x, const L_G1 &y) {
  bool result;
  result = (g1_cmp(x.m_G1, y.m_G1) != RLC_EQ);
  return result;
}

/*
void L_G1::serialize(L_OpenABEByteString &result) const {
  L_OpenABEByteString tmp;

  if (this->isInit) {
    g1_convert_to_bytestring(GET_BP_GROUP(this->bgroup), tmp, this->m_G1);
    result.clear();
    result.insertFirstByte(OpenABE_ELEMENT_G1);
    result.smartPack(tmp);
  }
}

void G1::deserialize(OpenABEByteString &input) {
  OpenABEByteString g1_bytes;
  size_t index = 0;

  if (this->isInit && this->bgroup != nullptr) {
    // first byte is the group type
    uint8_t element_type = input.at(index);
    if (element_type == OpenABE_ELEMENT_G1) {
      index++;
      g1_bytes = input.smartUnpack(&index);
      // read the binary buffer into a G1 element, then check for error
      // condition
      if (is_elem_null(this->m_G1)) {
        g1_init(GET_BP_GROUP(this->bgroup), &this->m_G1);
      }
      g1_convert_to_point(GET_BP_GROUP(this->bgroup), g1_bytes, this->m_G1);
      return;
    }
  }
  ASSERT(false, OpenABE_ERROR_SERIALIZATION_FAILED);
}
*/
bool L_G1::isEqual(L_ZObject *z) const {
  L_G1 *z1 = dynamic_cast<L_G1 *>(z);
  if (z1 != NULL) {
    return *z1 == *this;
  }
  return false;
}

/********************************************************************************
 * Implementation of the G2 class
 ********************************************************************************/

L_G2::L_G2(std::shared_ptr<L_BPGroup> bgroup)
{
    this->isInit = true;
    this->bgroup = bgroup;
    // does init and sets the point to infinity
    l_g2_set_to_infinity(L_GET_BP_GROUP(this->bgroup), &this->m_G2);
}

L_G2::L_G2(const L_G2& w)
{
    if (w.bgroup != nullptr) {
        this->bgroup = w.bgroup;
    } else {
        //throw OpenABE_ERROR_INVALID_GROUP_PARAMS;
    }
    l_g2_init(L_GET_BP_GROUP(this->bgroup), &this->m_G2);
    //g2_copy(this->m_G2, w.m_G2);
    this->isInit = true;
}

L_G2&
L_G2::operator=(const L_G2& w)
{
    if (this->isInit) {
        if(w.bgroup != nullptr) {
            this->bgroup = w.bgroup;
        }
        if (l_is_elem_null(this->m_G2)) {
            if (this->bgroup)
                l_g2_init(L_GET_BP_GROUP(this->bgroup), &this->m_G2);
            else
                ro_error();
        }
        //g2_copy(this->m_G2, w.m_G2);
    }
    else ro_error();

    return *this;
}

L_G2::~L_G2()
{
    if (this->isInit) {
        l_g2_element_free(this->m_G2);
        this->isInit = false;
    }
}

/* multiplicative notation for point addition*/
L_G2 operator*(const L_G2& x,const L_G2& y)
{
	L_G2 z = x;
	g2_add(z.m_G2, z.m_G2, const_cast<L_G2&>(y).m_G2);
	g2_norm(z.m_G2, z.m_G2);
	return z;
}

L_G2&
L_G2::operator*=(const L_G2& x)
{
	L_G2 r(*this);
	*this = r * x;
	return *this;
}

/* multiplicative notation for point subtraction*/
L_G2 operator/(const L_G2& x,const L_G2& y)
{
    L_G2 z = y;
    //okg2_sub(z.m_G2, const_cast<L_G2&>(x).m_G2, z.m_G2);
    //okg2_norm(z.m_G2, z.m_G2);
    return z;
}

L_G2 operator-(const L_G2& x)
{
	L_G2 z = x;
	//okg2_neg(z.m_G2, z.m_G2);
	return z;
}

L_G2 L_G2::exp(L_ZP z)
{
	L_G2 g2(this->bgroup);
    l_g2_mul_op(L_GET_BP_GROUP(g2.bgroup), g2.m_G2, this->m_G2, z.m_ZP);
    return g2;
}

bool L_G2::ismember(l_bignum_t order)
{
	bool result;
	g2_t r;
	l_fp12_inits(r);

	g2_mul(r, this->m_G2, order);
	if(g2_is_infty(r) == 1)
		result = true;
	else
		result = false;
	g2_free(r);
	return result;
}

void L_G2::setRandom()
{
	if(this->isInit) {
		// cout << "G2: ";
		g2_rand(this->m_G2);
	}
}
/*
ostream& operator<<(ostream& os, const G2& g2)
{
#if defined(BP_WITH_OPENSSL)
    os << g2_point_to_string(GET_BP_GROUP(g2.bgroup), g2.m_G2);
#else
	g2_write_ostream(os, const_cast<G2&>(g2).m_G2, DEC);
#endif
	return os;
}
*/
bool operator==(const L_G2& x,const L_G2& y)
{
    return (l_g2_cmp_op(L_GET_BP_GROUP(x.bgroup), const_cast<L_G2&>(x).m_G2, const_cast<L_G2&>(y).m_G2) == G_CMP_EQ);
}

bool operator!=(const L_G2& x,const L_G2& y)
{
    return (l_g2_cmp_op(L_GET_BP_GROUP(x.bgroup), const_cast<L_G2&>(x).m_G2, const_cast<L_G2&>(y).m_G2) != G_CMP_EQ);
}

/*
void
G2::serialize(OpenABEByteString &result) const
{
    OpenABEByteString tmp;

    if(this->isInit) {
        g2_convert_to_bytestring(GET_BP_GROUP(this->bgroup), tmp, const_cast<G2*>(this)->m_G2);
        result.clear();
        result.insertFirstByte(OpenABE_ELEMENT_G2);
        result.smartPack(tmp);
    }
}

void
G2::deserialize(OpenABEByteString &input)
{
    OpenABEByteString g2_bytes;
    size_t index = 0;

    if(this->isInit && this->bgroup != nullptr) {
        // first byte is the group type
        uint8_t element_type = input.at(index);
        if(element_type == OpenABE_ELEMENT_G2) {
            index++;
            g2_bytes = input.smartUnpack(&index);
            if (is_elem_null(this->m_G2)) {
                g2_init(GET_BP_GROUP(this->bgroup), &this->m_G2);
            }
            g2_convert_to_point(GET_BP_GROUP(this->bgroup), g2_bytes, this->m_G2);
            return;
        }
    }
    ASSERT(false, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);
}
*/
bool
L_G2::isEqual(L_ZObject *z) const
{
	L_G2 *z1 = dynamic_cast<L_G2*>(z);
	if(z1 != NULL) {
		return *z1 == *this;
	}
	return false;
}

/********************************************************************************
 * Implementation of the GT class
 ********************************************************************************/

L_GT::L_GT(std::shared_ptr<L_BPGroup> bgroup)
{
    this->isInit = true;
    this->bgroup = bgroup;
    // does init and sets the point to infinity
    l_gt_set_to_infinity(L_GET_BP_GROUP(this->bgroup), &this->m_GT);
    shouldCompress_ = true;
}

L_GT::L_GT(const L_GT& w)
{
    if (w.bgroup != nullptr) {
        this->bgroup = w.bgroup;
    } else {
        //throw OpenABE_ERROR_INVALID_GROUP_PARAMS;
    }
    l_gt_init(L_GET_BP_GROUP(this->bgroup), &this->m_GT);
    //gt_copy(this->m_GT, w.m_GT);
    this->isInit = true;
    this->shouldCompress_ = w.shouldCompress_;
}

L_GT&
L_GT::operator=(const L_GT& w)
{
    if (this->isInit) {
        if(w.bgroup != nullptr) {
            this->bgroup = w.bgroup;
        }
        if (l_is_elem_null(this->m_GT)) {
            if (this->bgroup)
                l_gt_init(L_GET_BP_GROUP(this->bgroup), &this->m_GT);
            else
                ro_error();
        }
        //gt_copy(this->m_GT, w.m_GT);
        this->shouldCompress_ = w.shouldCompress_;
    }
    else ro_error();
    return *this;
}

L_GT::~L_GT()
{
    if (this->isInit) {
        l_gt_element_free(this->m_GT);
        this->isInit = false;
    }
}


L_GT operator*(const L_GT& x,const L_GT& y)
{
	L_GT z = x; // , y1 = y;
	l_gt_mul_op(L_GET_BP_GROUP(z.bgroup), z.m_GT, z.m_GT, const_cast<L_GT&>(y).m_GT);
	return z;
}

L_GT&
L_GT::operator*=(const L_GT& x)
{
	L_GT r(*this);
	*this = r * x;
	return *this;
}

L_GT operator/(const L_GT& x,const L_GT& y)
{
	L_GT z = x;
	// z = x * y^-1
	l_gt_div_op(L_GET_BP_GROUP(z.bgroup), z.m_GT, const_cast<L_GT&>(x).m_GT, const_cast<L_GT&>(y).m_GT);
	return z;
}

L_GT L_GT::exp(L_ZP z)
{
	L_GT gt(*this);
    gt_exp(gt.m_GT, gt.m_GT, z.m_ZP);
	return gt;
}

L_GT operator-(const L_GT& g)
{
	L_GT gt(g);
	//okgt_inv(gt.m_GT, gt.m_GT);
	return gt;
}

void L_GT::setIdentity()
{
    gt_set_unity(this->m_GT);
}

bool L_GT::isInfinity()
{
    return l_gt_is_unity_check(L_GET_BP_GROUP(this->bgroup), this->m_GT);
}

bool L_GT::ismember(l_bignum_t order)
{
	bool result;
	l_gt_ptr r;
	l_gt_init(L_GET_BP_GROUP(this->bgroup), &r);
	l_gt_exp_op(L_GET_BP_GROUP(this->bgroup), r, this->m_GT, order);
	result = l_gt_is_unity_check(L_GET_BP_GROUP(this->bgroup), r);
	l_gt_element_free(r);
	return result;
}
/*
ostream& operator<<(ostream& os, const GT& gt)
{
#if defined(BP_WITH_OPENSSL)
    OpenABEByteString s;
    gt_convert_to_bytestring(GET_BP_GROUP(gt.bgroup), s, gt.m_GT, NO_COMPRESS);
    os << "(" << s.toHex() << ")";
#else
	gt_write_ostream(os, const_cast<GT&>(gt).m_GT, DEC);
#endif
	return os;
}
*/
bool operator==(const L_GT& x,const L_GT& y)
{
    bool result;
    result = (gt_cmp(const_cast<L_GT&>(x).m_GT, const_cast<L_GT&>(y).m_GT) == G_CMP_EQ);
    return result;
}

bool operator!=(const L_GT& x, const L_GT& y)
{
    bool result;
    result = (gt_cmp(const_cast<L_GT&>(x).m_GT, const_cast<L_GT&>(y).m_GT) != G_CMP_EQ);
    return result;
}

/*

void
l_GT::serialize(OpenABEByteString &result) const
{
    OpenABEByteString tmp;
    int compress = shouldCompress_ ? COMPRESS : NO_COMPRESS;

    if(this->isInit) {
        gt_convert_to_bytestring(GET_BP_GROUP(this->bgroup), tmp, const_cast<GT&>(*this).m_GT, compress);
        // pack the resulting ciphertext in result
        result.clear();
        result.insertFirstByte(OpenABE_ELEMENT_GT);
        result.smartPack(tmp);
    }
}

void
GT::deserialize(OpenABEByteString &input)
{
    OpenABEByteString gt_bytes;
    size_t index = 0;

    if(this->isInit && this->bgroup != nullptr) {
        // first byte is the group type
        uint8_t element_type = input.at(index);
        if(element_type == OpenABE_ELEMENT_GT) {
            index++;
            gt_bytes = input.smartUnpack(&index);
            if (is_elem_null(this->m_GT)) {
                gt_init(GET_BP_GROUP(this->bgroup), &this->m_GT);
            }
            gt_convert_to_point(GET_BP_GROUP(this->bgroup), gt_bytes, this->m_GT);
            return;
        }
    }
    ASSERT(false, OpenABE_ERROR_ELEMENT_NOT_INITIALIZED);
}
*/
bool
L_GT::isEqual(L_ZObject *z) const
{
	L_GT *z1 = dynamic_cast<L_GT*>(z);
	if(z1 != NULL) {
		return *z1 == *this;
	}
	return false;
}

/*
#if !defined(BP_WITH_OPENSSL)
void fp12_write_ostream(ostream& os, fp12_t a, int radix) {
    os << "[(";
    fp6_write_ostream(os, a[0], radix);
    os << "),(";
    fp6_write_ostream(os, a[1], radix);
    os << "]";
}

void fp6_write_ostream(ostream &os, fp6_t a, int radix) {
    os << "{";
    fp2_write_ostream(os, a[0], radix);
    os << ",";
    fp2_write_ostream(os, a[1], radix);
    os << ",";
    fp2_write_ostream(os, a[2], radix);
    os << "}";
}

void fp2_write_ostream(ostream& os, fp2_t a, int radix) {
    os << "<";
    fp_write_ostream(os, a[0], radix);
    os << ",";
    fp_write_ostream(os, a[1], radix);
    os << ">";
}

void fp_write_ostream(ostream& os, fp_t a, int radix) {
    char strBuf[MAX_BYTES];
    fp_write_str(strBuf, MAX_BYTES, a, radix);
    os << strBuf;
}

void ep2_write_ostream(ostream &os, ep2_t p, int radix) {
    os << "[";
    fp2_write_ostream(os, p->x, radix);
    os << ",";
    fp2_write_ostream(os, p->y, radix);
//    os << ",";
//    fp2_write_ostream(os, p->z, radix);
    os << "]";
}

void ep_write_ostream(ostream &os, ep_t p, int radix) {
    // base field
    os << "[";
    fp_write_ostream(os, p->x, radix);
    os << ",";
    fp_write_ostream(os, p->y, radix);
    os << "]";
}
#endif
*/
//}
