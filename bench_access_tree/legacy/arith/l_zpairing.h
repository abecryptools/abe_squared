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
/// \file   zpairing.h
///
/// \brief  Class definition for bilinear maps (or pairings).
///
/// \author Matthew Green and J. Ayo Akinyele
///

#ifndef __L_ZPAIRING_H__
#define __L_ZPAIRING_H__

#include "l_zelement_bp.h"

/// \class	OpenABEPairing
/// \brief	Generic container for pairing functionality.
//namespace oabe {

class L_OpenABEPairing : public L_ZObject {
public:

  L_OpenABEPairing(const std::string &pairingParams, bn_t m_order);   
  L_OpenABEPairing(const std::string &pairingParams);
  L_OpenABEPairing(const L_OpenABEPairing &copyFrom);
  ~L_OpenABEPairing();
  void     L_initZP(L_ZP& z, uint32_t v);
  L_ZP       L_initZP();
  L_G1       L_initG1();
  L_G2       L_initG2();
  L_GT       L_initGT();

  L_ZP       L_randomZP();
  L_G1       L_randomG1();
  L_G2       L_randomG2();

  L_OpenABEByteString hashToBytes(uint8_t*, uint32_t);
  L_OpenABEByteString hashFromBytes(L_OpenABEByteString &buf, uint32_t target_len, uint8_t hash_prefix);

  L_G1       hashToG1(L_OpenABEByteString&, std::string);
  L_GT       pairing(L_G1& g1, L_G2& g2);
  void     l_multi_pairing(L_GT& gt, std::vector<L_G1>& g1, std::vector<L_G2>& g2);

  std::string  getPairingParams() const;
  L_OpenABECurveID   L_getCurveID() const;
  std::shared_ptr<L_ZGroup> getGroup() { return this->bpgroup; }
  l_bignum_t     order;

protected:
  bool         isSymmetric;
  L_OpenABECurveID   curveID;
  std::string  pairingParams;
  std::shared_ptr<L_BPGroup>  bpgroup;
};

// Global library initialization and shutdown functions
void L_zMathInitLibrary();
void L_zMathShutdownLibrary();
// Convert a security level (in symmetric-equivalent bits) to pairing params
//std::string OpenABE_pairingParamsForSecurityLevel(L_OpenABESecurityLevel securityLevel);
// Pairing creation functions
L_OpenABEPairing* L_OpenABE_createNewPairing(const std::string &pairingParams);
// Utility functions
L_OpenABECurveID  L_getPairingCurveID(const std::string &paramsID);


#endif	// __ZPAIRING_H__
