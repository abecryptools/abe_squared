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
/// \file   zelement_bp.h
///
/// \brief  Class definition for a group element.
///
/// \author Matthew Green and J. Ayo Akinyele
///

#ifndef __L_ZELEMENT_BP_H__
#define __L_ZELEMENT_BP_H__

#include <list>
#include <memory>

extern "C" {
  #include "l_zelement.h"
}

#include "../l_zbytestring.h"
#include "l_zgroup.h"
#include "../l_zobject.h"

/*void l_fp12_write_ostream(std::ostream& os, fp12_t a, int radix);
void l_fp6_write_ostream(std::ostream& os, fp6_t a, int radix);
void l_fp2_write_ostream(std::ostream& os, fp2_t a, int radix);
void l_fp_write_ostream(std::ostream& os, fp_t a, int radix);
void l_ep2_write_ostream(std::ostream &os, ep2_t p, int radix);
void l_ep_write_ostream(std::ostream &os, ep_t p, int radix);
*/
//#ifndef __ZPAIRING_H__
//class OpenABEPairing;
//#endif
// forward declaration
class L_OpenABEByteString;
//class OpenABERNG;

//#if !defined(BP_WITH_OPENSSL)
//bool checkRelicError();
//#endif

void l_ro_error(void);

void l_g1_map_op(const l_bp_group_t group, l_g1_ptr g, L_OpenABEByteString& msg);
const std::string l_g1_point_to_string(l_bp_group_t group, const l_g1_ptr p);
/*void g1_convert_to_bytestring(bp_group_t group, oabe::OpenABEByteString & s, const g1_ptr p);
void g1_convert_to_point(bp_group_t group, oabe::OpenABEByteString& s, g1_ptr p);

void g2_convert_to_point(bp_group_t group, oabe::OpenABEByteString& s, g2_ptr p);
const std::string g2_point_to_string(bp_group_t group, const g2_ptr p);
void g2_convert_to_bytestring(bp_group_t group, oabe::OpenABEByteString & s, g2_ptr p);

void gt_convert_to_point(bp_group_t group, oabe::OpenABEByteString& s, gt_ptr p);
void gt_convert_to_bytestring(bp_group_t group, oabe::OpenABEByteString& s, gt_ptr p, int should_compress);
*/
const std::string l_gt_point_to_string(const l_bp_group_t group, l_gt_ptr p);

/// \class	ZP
/// \brief	Class for representing integer elements mod p.

//namespace oabe {

// retrieve the group field of the BPGroup class
#define L_GET_BP_GROUP(g)    g->group

/// \class  ECGroup
/// \brief  Wrapper for managing elliptic curve groups
class L_BPGroup : public L_ZGroup {
public:
  l_bp_group_t   group;
  l_bignum_t     order;

  L_BPGroup(L_OpenABECurveID id);
  ~L_BPGroup();

  void getGroupOrder(l_bignum_t o);
};


/// \class  ZP
/// \brief  Class for ZP elements in ZML.
class L_ZP : public L_ZObject {
public:
  l_bignum_t m_ZP;
  l_bignum_t order;
  bool isInit, isOrderSet;
  L_ZP();
  L_ZP(uint32_t);
  L_ZP(char*, l_bignum_t);
  L_ZP(uint8_t*, uint32_t, l_bignum_t);
  L_ZP(l_bignum_t y);
  L_ZP(const L_ZP& w);

  ~L_ZP();
  L_ZP& operator+=(const L_ZP& x);
  L_ZP& operator*=(const L_ZP& x);
  L_ZP& operator=(const L_ZP& w);

  std::string getBytesAsString();
  L_OpenABEByteString getByteString() const;
  void getLengthAndByteString(L_OpenABEByteString &z) const;
  void setOrder(const l_bignum_t o);
  void setRandom(l_bignum_t o);

  void setFrom(L_ZP&, uint32_t);
  bool ismember();
  void multInverse();

  friend L_ZP power(const L_ZP&, unsigned int);
  friend L_ZP power(const L_ZP&, const L_ZP&);
  friend L_ZP operator-(const L_ZP&);
  friend L_ZP operator-(const L_ZP&,const L_ZP&);
  friend L_ZP operator+(const L_ZP&,const L_ZP&);
  friend L_ZP operator*(const L_ZP&,const L_ZP&);
  friend L_ZP operator/(const L_ZP&,const L_ZP&);
  friend L_ZP operator<<(const L_ZP&, int);
  friend L_ZP operator>>(const L_ZP&, int);

  friend std::ostream& operator<<(std::ostream&, const L_ZP&);
  friend bool operator<(const L_ZP& x, const L_ZP& y);
  friend bool operator<=(const L_ZP& x, const L_ZP& y);
  friend bool operator>(const L_ZP& x, const L_ZP& y);
  friend bool operator>=(const L_ZP& x, const L_ZP& y);
  friend bool operator==(const L_ZP& x, const L_ZP& y);
  friend bool operator!=(const L_ZP& x, const L_ZP& y);

  L_ZP*    clone() const { return new L_ZP(*this); }
  void serialize(L_OpenABEByteString &result) const;
  void deserialize(L_OpenABEByteString &input);
  bool isEqual(L_ZObject*) const;
};

/// \class  G1
/// \brief  Class for G1 base field elements in ZML.
class L_G1 : public L_ZObject {
public:
  l_g1_ptr m_G1;
  bool isInit;
  std::shared_ptr<L_BPGroup> bgroup;

  L_G1(std::shared_ptr<L_BPGroup> bgroup);
  L_G1(const L_G1& w);
  ~L_G1();
  L_G1& operator*=(const L_G1& x);
  L_G1& operator=(const L_G1& w);

  void setRandom();
  bool ismember(l_bignum_t);
  L_G1 exp(L_ZP);
  void multInverse();
  friend L_G1 operator-(const L_G1&);
  friend L_G1 operator/(const L_G1&,const L_G1&);
  friend L_G1 operator*(const L_G1&,const L_G1&);
  friend std::ostream& operator<<(std::ostream&, const L_G1&);
  friend bool operator==(const L_G1& x, const L_G1& y);
  friend bool operator!=(const L_G1& x,const L_G1& y);

  L_G1*    clone() const { return new L_G1(*this); }
  void serialize(L_OpenABEByteString &result) const;
  void deserialize(L_OpenABEByteString &input);
  bool isEqual(L_ZObject*) const;
};

/// \class  G2
/// \brief  Class for G2 field elements in ZML.
class L_G2 : public L_ZObject {
public:
  l_g2_ptr m_G2;
  bool isInit;
  std::shared_ptr<L_BPGroup> bgroup;

  L_G2(std::shared_ptr<L_BPGroup> bgroup);
  L_G2(const L_G2& w);
  ~L_G2();
  L_G2& operator*=(const L_G2& x);
  L_G2& operator=(const L_G2& w);

  void setRandom();
  bool ismember(l_bignum_t);
  L_G2 exp(L_ZP);

  friend L_G2 operator-(const L_G2&);
  friend L_G2 operator/(const L_G2&,const L_G2&);
  friend L_G2 operator*(const L_G2&,const L_G2&);
  friend std::ostream& operator<<(std::ostream&, const L_G2&);
  friend bool operator==(const L_G2& x,const L_G2& y);
  friend bool operator!=(const L_G2& x,const L_G2& y);

  L_G2*    clone() const { return new L_G2(*this); }
  void serialize(L_OpenABEByteString &result) const;
  void deserialize(L_OpenABEByteString &input);
  bool isEqual(L_ZObject*) const;
};

/// \class  GT
/// \brief  Class for GT field elements in RELIC.
class L_GT : public L_ZObject {
public:
  l_gt_ptr m_GT;
  bool isInit;
  std::shared_ptr<L_BPGroup> bgroup;

  L_GT(std::shared_ptr<L_BPGroup> bgroup);
  L_GT(const L_GT& w);
  ~L_GT();
  L_GT& operator*=(const L_GT& x);
  L_GT& operator=(const L_GT& x);

  void enableCompression() { shouldCompress_ = true; };
  void disableCompression() { shouldCompress_ = false; };
  //void setRandom(OpenABERNG *rng);
  void setIdentity();
  bool isInfinity();
  bool ismember(l_bignum_t);
  L_GT exp(L_ZP);

  friend L_GT operator-(const L_GT&);
  friend L_GT operator/(const L_GT&,const L_GT&);
  friend L_GT operator*(const L_GT&,const L_GT&);
  friend std::ostream& operator<<(std::ostream& s, const L_GT&);
  friend bool operator==(const L_GT& x, const L_GT& y);
  friend bool operator!=(const L_GT& x, const L_GT& y);

  L_GT* clone() const { return new L_GT(*this); }
  void serialize(L_OpenABEByteString &result) const;
  void deserialize(L_OpenABEByteString &input);
  bool isEqual(L_ZObject*) const;

private:
  bool shouldCompress_;
};

/// \typedef    OpenABEElementList
/// \brief      Vector or list of elements
typedef std::vector<L_ZP> L_OpenABEElementList;

/// \typedef    OpenABEElementListIterator
/// \brief      Iterator for an OpenABEElementList of rows in an LSSS
typedef L_OpenABEElementList::iterator OpenABEElementListIterator;


// pairings definition
void l_multi_bp_map_op(const l_bp_group_t group, L_GT& gt,
                     std::vector<L_G1>& g1, std::vector<L_G2>& g2);

#endif	// __ZELEMENT_BP_H__
