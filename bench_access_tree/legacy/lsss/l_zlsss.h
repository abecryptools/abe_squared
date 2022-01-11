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
/// \file   zlsss.h
///
/// \brief  Class definition files for a secret sharing context.
///         Includes all routines necessary for secret sharing in the OpenABE.
///
/// \author Matthew Green and J. Ayo Akinyele
///

#ifndef __L_ZLSSS_H__
#define __L_ZLSSS_H__

#include <stack>
#include <vector>
#include <map>

#include "../l_zobject.h"
#include "../arith/l_zelement_bp.h"
//#include "../arith/l_zpairing.h"
#include "../l_zpolicy.h"
#include "../l_zattributelist.h"

//namespace oabe {

/// \class  ZLSSSElement
/// \brief  Individual element of a secret sharing structure.
class L_OpenABELSSSElement : public L_ZObject {
protected:
  std::string m_Prefix, m_Label;
  L_ZP m_Element;
    
public:
  L_OpenABELSSSElement() { }
  L_OpenABELSSSElement(std::string label, L_ZP &element);
  L_OpenABELSSSElement(const L_OpenABELSSSElement &copy)
     : m_Prefix(copy.prefix()), m_Label(copy.label()), m_Element(copy.element()) { }
    
  // Public methods
  std::string label() const   { return this->m_Label; }
  std::string prefix() const { return this->m_Prefix; }
  L_ZP  element() const       { return this->m_Element; }
    
  // This method allows you to use the STL count() method to count the
  // number of entries that match a given label. Note that it only
  // compares to m_Label.
  bool operator==(const std::string &label) { return (label == this->m_Label); }
  friend std::ostream& operator<<(std::ostream& s, const L_OpenABELSSSElement& z) {
    L_OpenABELSSSElement z2(z);
    // note that label includes the prefix implicitly
    s << z2.m_Label << " -> " << z2.m_Element << "\n";
    return s;
  }
};

/// \typedef    OpenABELSSSRowMap
/// \brief      Key/value map of results in an LSSS
typedef std::map<const std::string, L_OpenABELSSSElement> L_OpenABELSSSRowMap;

/// \typedef    OpenABELSSSRowMapIterator
/// \brief      Iterator for vector of results in an LSSS
typedef L_OpenABELSSSRowMap::iterator L_OpenABELSSSRowMapIterator;

/// \class	ZLSSS
/// \brief	Secret sharing class.

class L_OpenABELSSS : public L_ZObject {
protected:
  //L_OpenABEPairing *m_Pairing;
  //L_OpenABERNG *m_RNG;
  L_OpenABELSSSRowMap	m_ResultMap;
  bool debug;
  L_ZP zero, iPlusOne, indexPlusOne;
  std::map<std::string, int> m_AttrCount;
  bn_t order;

  // Protected methods
  void l_performSecretSharing(const L_OpenABEPolicy *policy, L_ZP &elt);
  bool l_performCoefficientRecovery(L_OpenABEPolicy *policy, L_OpenABEAttributeList *attrList);

  void l_addShareToResults(L_OpenABETreeNode *treeNode, L_ZP &elt);
  bool l_clearExistingResults() { this->m_ResultMap.clear(); return true; }
  inline std::string l_makeUniqueLabel(const L_OpenABETreeNode *treeNode);
  inline L_ZP l_evaluatePolynomial(std::vector<L_ZP> &coefficients, uint32_t x);

  void l_iterativeShareSecret(L_OpenABETreeNode *treeNode, L_ZP &elt);
  bool l_iterativeCoefficientRecover(L_OpenABETreeNode *treeNode, L_ZP &inCoeff);
  inline L_ZP l_calculateCoefficient(L_OpenABETreeNode *treeNode, uint32_t index, uint32_t threshold, uint32_t total);

public:
   //L_OpenABELSSS(L_OpenABEPairing *pairing);                      
    L_OpenABELSSS(int d);                      
  L_OpenABELSSS(bn_t m_order);
  ~L_OpenABELSSS();
    
  // Public secret sharing and recovery methods
  void l_shareSecret(const L_OpenABEFunctionInput *input, L_ZP &elt);
  bool l_recoverCoefficients(L_OpenABEPolicy *policy, L_OpenABEAttributeList *attrList);

  // Methods for obtaining the rows
  L_OpenABELSSSRowMap&            l_getRows() { return m_ResultMap; }
	
//#ifndef OpenABE_NO_TEST_ROUTINES
	//
	// Test routine we use to make sure secret sharing is working
	//
//	ZP LSSStestSecretRecovery(const OpenABELSSSRowMap& coefficients, const OpenABELSSSRowMap& shares);
//#endif // OpenABE_NO_TEST_ROUTINES
};

bool l_iterativeScanTree(L_OpenABETreeNode *treeNode, L_OpenABEAttributeList *attributeList);
bool l_determineIfNodeShouldBeMarked(uint32_t threshold, L_OpenABETreeNode *node);
std::pair<bool,int> l_checkIfSatisfied(L_OpenABEPolicy *policy, L_OpenABEAttributeList *attr_list, bool reset_flags=true);

//}

#endif	// __ZLSSS_H__
