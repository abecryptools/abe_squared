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
/// \file   zpolicy.h
///
/// \brief  Class definition for OpenABE policy which is a subclass
///         of OpenABEFunctionInput (represents ABE policies).
///
/// \author Matthew Green and J. Ayo Akinyele
///

#ifndef __L_ZPOLICY_H__
#define __L_ZPOLICY_H__

#include <iostream>
#include <memory>
#include <sstream>
#include <map>

#include "l_zobject.h"
#include "l_zfunctioninput.h"
#include "l_zbytestring.h"

//namespace oabe {

// forward declare
//class OpenABEByteString;
#define PREFIX_SEP  ':'

typedef enum _zGateType {
  GATE_TYPE_NONE = 0,
  GATE_TYPE_LEAF,
  GATE_TYPE_AND,
  GATE_TYPE_OR,
  GATE_TYPE_THRESHOLD,
  GATE_TYPE_XOR,
  GATE_TYPE_NOT,
  GATE_TYPE_NAND,
  GATE_TYPE_NOR,
  GATE_TYPE_XNOR
} zGateType;

///
/// @class  OpenABETreeNode
///
/// @brief  Helper class that describes a single node in a policy tree.
///

class L_OpenABETreeNode : public L_ZObject {
protected:
  zGateType                   m_nodeType;
  uint32_t                    m_thresholdValue;
  uint32_t                    m_numSubnodes;
  bool                        m_Mark;
  int                         m_Satisfied;
  std::vector<L_OpenABETreeNode*>   m_Subnodes;
  std::string                 m_Prefix;
  std::string                 m_Label;
  int                         m_Index;
    
public:
  // Constructors/destructors
  L_OpenABETreeNode();
  L_OpenABETreeNode(std::string label, std::string prefix = "", int index = 0);
  L_OpenABETreeNode(L_OpenABETreeNode *copy);
  ~L_OpenABETreeNode();
  bool m_Visited;
    
  uint32_t l_getNumSubnodes()  { return this->m_Subnodes.size(); }
  const bool l_getMark() const { return this->m_Mark; }
  const int l_getNumSatisfied() const { return this->m_Satisfied; }
  bool l_setMark(bool mark, int satisfied)  {
    this->m_Mark = mark;
    this->m_Satisfied = satisfied;
    return mark;
  }
  const uint32_t  l_getNodeType() const { return this->m_nodeType; }
  void  l_setNodeType(zGateType type) { this->m_nodeType = type; }
  L_OpenABETreeNode*  l_getSubnode(uint32_t index);

  void l_addSubnode(L_OpenABETreeNode* subnode);
  void l_setLabel(const std::string label) { this->m_Label = label; }
  const std::string& l_getPrefix() const  { return this->m_Prefix; }
  const std::string& l_getLabel() const	{ return this->m_Label; }
  const std::string l_getCompleteLabel() const {
    if(this->m_Prefix != "") {
      std::string full_label(this->m_Prefix + PREFIX_SEP);
      full_label += this->m_Label;
      return full_label;
    } else {
      return this->m_Label;
    }
  }
  const int l_getIndex() const   { return this->m_Index; }
  void l_setThresholdValue(uint32_t k) { if (this->m_Subnodes.size() > 0) { this->m_thresholdValue = k; } }
  uint32_t l_getThresholdValue();
  std::string l_toString();
};

///
/// @class  OpenABEPolicy
///
/// @brief  Subclass of OpenABEFunctionInput that represents ABE policies.
///

class L_OpenABEPolicy : public L_OpenABEFunctionInput {
protected:
  std::unique_ptr<L_OpenABETreeNode> m_rootNode;
  bool m_hasDuplicates, m_enabledRevocation;
  std::map<std::string, int> m_attrDuplicateCount;
  std::set<std::string> m_attrCompleteSet;
  std::string m_originalInputString;

public:
  // Constructors/destructors
  L_OpenABEPolicy();
  L_OpenABEPolicy(const L_OpenABEPolicy &copy);
  virtual ~L_OpenABEPolicy();

  void l_setRootNode(L_OpenABETreeNode* subtree);
  L_OpenABETreeNode *l_getRootNode() const { return this->m_rootNode.get(); }
  //L_OpenABEPolicy*    clone() const { return new L_OpenABEPolicy(*this); }
  void serialize(L_OpenABEByteString &result) const;
  bool isEqual(L_ZObject* z) const {
    return false;
  }
  L_OpenABEPolicy&    operator=(const L_OpenABEPolicy &rhs);
  std::string  l_toString() const {
      return this->m_rootNode->l_toString();
  }
  void l_setCompactString(const std::string& input) {
      m_originalInputString = input;
  }
  std::string l_toCompactString() const {
      return m_originalInputString;
  }

  // methods for storing/retrieving duplicate node info
  bool l_hasDuplicateNodes() const { return this->m_hasDuplicates; }
  void l_setDuplicateInfo(std::map<std::string, int>& attr_count, std::set<std::string>& attr_list);
  void l_setPrefixSet(std::set<std::string>& prefix_set);
  void l_getDuplicateInfo(std::map<std::string, int>& attr_count) const {
      attr_count = this->m_attrDuplicateCount;
  }
  bool l_getRevocationStatus() { return this->m_enabledRevocation; }
  void l_enableRevocation() { this->m_enabledRevocation = true; }

  std::set<std::string>& l_getAttrCompleteSet() {
    return this->m_attrCompleteSet;
  }

#if 0
  void		ConstructTestPolicy();
#endif
  friend std::ostream& operator<<(std::ostream& s, const L_OpenABEPolicy& z) {
    s << z.l_getRootNode()->l_toString();
    return s;
  }

  void l_deserialize(const L_OpenABEByteString &input);
};

// split a string based on a delimiter and return a vector
std::vector<std::string> split(const std::string &s, char delim);
// print the string of the internal tree node gate
const char* OpenABETreeNode_ToString(zGateType type);
std::unique_ptr<L_OpenABEPolicy> L_createPolicyTree(std::string s);
// reset all the flags in a policy tree
bool l_resetFlags(L_OpenABETreeNode *root);
// use to add an attribute at the OpenABEPolicy structure
std::unique_ptr<L_OpenABEPolicy> l_addToRootOfInput(
            zGateType type,
            const std::string attribute, L_OpenABEPolicy* policy);
//}

#endif /* ifdef  __ZPOLICY_H__ */
