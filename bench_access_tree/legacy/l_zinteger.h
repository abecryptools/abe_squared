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
/// \file   zinteger.h
///
/// \brief  Class definition files for integers.
///
/// \author Matthew Green and J. Ayo Akinyele
///

#ifndef __L_ZINTEGER_H__
#define __L_ZINTEGER_H__

#include "l_zobject.h"
#include "l_zconstants.h"
#include "l_zbytestring.h"

#include <map>

//namespace oabe {

/// \class	OpenABEUInteger
/// \brief	Generic container for unsigned integers.
class L_OpenABEUInteger : public L_ZObject {
public:
  L_OpenABEUInteger(const L_OpenABEUInteger& val) {
      this->m_Val  = val.m_Val;
      this->m_Bits = val.m_Bits;
  }
  // defines expressive integers
  L_OpenABEUInteger(uint32_t val) {
      this->m_Val  = val;
      this->m_Bits = 0;
  }
  // defines explicit integers
  L_OpenABEUInteger(uint32_t val, uint16_t bits) {
      this->m_Val  = val;
      this->m_Bits = bits;
  }

  bool  isFlexInt() { return (this->m_Bits == 0 || this->m_Bits == MAX_INT_BITS); }
  L_OpenABEUInteger* clone() const { return new L_OpenABEUInteger(*this); }
  uint32_t getVal() const { return this->m_Val; }
  uint16_t getBits() const { return this->m_Bits; }
  void setBits(uint16_t bits) { this->m_Bits = bits; }
  friend std::ostream& operator<<(std::ostream& s, const L_OpenABEUInteger& z) {
    L_OpenABEUInteger z2(z);
    s << z2.m_Val;
    if(z2.m_Bits > 0 && z2.m_Bits < MAX_INT_BITS) {
        s << "#" << std::to_string(z2.m_Bits);
    }
    return s;
  }

  L_OpenABEUInteger& operator+=(int x) {
      this->m_Val = this->m_Val + x;
      return *this;
  }

  L_OpenABEUInteger& operator-=(int x) {
      this->m_Val = this->m_Val - x;
      return *this;
  }

  void serialize(L_OpenABEByteString& result) const {
    result.clear();
    // insert the type
    result.insertFirstByte(L_OpenABE_ELEMENT_INT);
    // pack the unsigned integer
    uint32_t x = this->m_Val;
    int bitLen = sizeof(uint32_t);
    uint8_t b[sizeof(uint32_t)] = {0};
    for(int i = bitLen-1; i >= 0; i--) {
        b[i] = (x & 0xFF); // record last byte
        x >>= 8; // shift right by 8-bits
    }
    result.appendArray(b, bitLen);
  }

  void deserialize(L_OpenABEByteString& input) {
    uint32_t x = 0;
    int bitLen = sizeof(uint32_t);
    //ASSERT(input.at(0) == OpenABE_ELEMENT_INT, OpenABE_ERROR_SERIALIZATION_FAILED);
    for(int i = 1; i <= bitLen; i++) {
      x <<= 8; // shift left by 8-bits
      x += input.at(i); // add byte at position i
    }
    this->m_Val = x;
  }

  bool isEqual(L_ZObject* z) const {
    L_OpenABEUInteger *z1 = dynamic_cast<L_OpenABEUInteger*>(z);
    if(z1 != NULL) {
        return z1->getVal() == this->getVal() && z1->getBits() == this->getBits();
    }
    return false;
  }

  friend bool operator==(const L_OpenABEUInteger& x, const L_OpenABEUInteger& y) {
      return x.getVal() == y.getVal() && x.getBits() == y.getBits();
  }

private:
  uint32_t m_Val;
  uint16_t m_Bits;
};

//}

#endif	// __ZINTEGER_H__

