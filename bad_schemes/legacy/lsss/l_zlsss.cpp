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
/// \file   zlsss.cpp
///
/// \brief  Implementation for linear secret sharing.
///
/// \author Matthew Green and J. Ayo Akinyele
///
///   

#define __L_ZLSSS_CPP__

#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
//#include <openabe/openabe.h>


#include "../l_zobject.h"                                                       
#include "../arith/l_zelement_bp.h"                                             
//#include "../arith/l_zpairing.h"                                                
#include "../l_zpolicy.h"                                                       
#include "../l_zattributelist.h"   
#include "../parser/l_zdriver.h"
#include "l_zlsss.h"

using namespace std;

/********************************************************************************
 * Implementation of the OpenABELSSS class
 ********************************************************************************/
//namespace oabe {

L_OpenABELSSSElement::L_OpenABELSSSElement(std::string label, L_ZP &element)
                             : m_Label(label), m_Element(element) {
  std::pair<std::string,std::string> pr = check_attribute(label);
  this->m_Prefix = pr.first;
}

/*!
 * Constructor for the OpenABELSSS class.
 *
 */

/*L_OpenABELSSS::L_OpenABELSSS(L_OpenABEPairing *pairing) : L_ZObject(), m_Pairing(pairing)
{
  this->debug = false;
  //this->m_Pairing->addRef();
  //this->m_RNG = rng;
  //this->m_Pairing->L_initZP(zero, 0);
  bn_null(zero.m_ZP);
  bn_new(zero.m_ZP);
  bn_zero(zero.m_ZP);

  bn_t order_tmp;
  bn_null(order_tmp); bn_new(order_tmp);
  bn_zero(order_tmp); 

  ep_curve_get_ord(order_tmp);
  zero.setOrder(order_tmp);

}
*/
L_OpenABELSSS::L_OpenABELSSS(int d) : L_ZObject()
{
  this->debug = false;
  //this->m_Pairing->addRef();
  //this->m_RNG = rng;
  //this->m_Pairing->L_initZP(zero, 0);
  bn_null(zero.m_ZP);
  bn_new(zero.m_ZP);
  bn_zero(zero.m_ZP);

  bn_t order_tmp;
  bn_null(order_tmp); bn_new(order_tmp);
  bn_zero(order_tmp); 

  ep_curve_get_ord(order_tmp);
  zero.setOrder(order_tmp);

}




L_OpenABELSSS::L_OpenABELSSS(bn_t m_order) : L_ZObject() {
  /*this->debug = false;
  this->m_Pairing->addRef();
  //this->m_RNG = rng;
  this->m_Pairing->L_initZP(zero, 0);
  zero = (uint32_t)0; zero.setOrder(m_order);

  bn_copy(this->order, m_order);
*/
}


/*!
 * Destructor for the OpenABECiphertext class.
 *
 */

L_OpenABELSSS::~L_OpenABELSSS()
{
  //this->m_Pairing->deRef();
}

/*!
 * Given a secret (an element of ZP) and a OpenABEFunctionInput describing
 * the access structure, performs secret sharing over the given access 
 * structure. At present, the input must be a OpenABEPolicy.
 *
 * The result is a vector of elements (OpenABELSSSElement) each of which
 * contains three values: a label (attribute name), a secret share,
 * an a "unique label" (attribute name made unique to deal with the
 * fact that multiple
 
 recorded within the OpenABELSSS object and may be
 * obtained using the getRows() method.
 *
 * @param[in] input     - OpenABEFunctionInput object describing the access structure
 * @param[in] elt       - a ZP object to share
 * @throw               - an exception if there is a problem sharing the element
 */

void
L_OpenABELSSS::l_shareSecret(const L_OpenABEFunctionInput *input, L_ZP &elt)
{
  // Verify that the input is a supported type (OpenABEPolicy)
  const L_OpenABEPolicy *policy = dynamic_cast<const L_OpenABEPolicy*>(input);
  if (policy == nullptr) {
      //OpenABE_LOG_AND_THROW("Sharing input must be a Policy", OpenABE_ERROR_INVALID_INPUT);
  }
  // Clear any existing results
  this->l_clearExistingResults();

  // Recursively share the secret
  this->l_performSecretSharing(policy, elt);
//  {
//      // If there was an error, clear any partial results and
//      // throw a general exception
//      this->m_ResultMap.clear();
//      OpenABE_LOG_AND_THROW("Could not share secret", OpenABE_ERROR_SECRET_SHARING_FAILED);
//  }
}

/*!
 * Given an access structure (policy) and an input (attribute list)
 * generates the coefficients necessary to recover the secret.
 * In the present implementation left must be a policy and right must
 * an attribute list.
 *
 * @param[in] policy    - OpenABEPolicy object describing the access structure
 * @param[in] attrList  - OpenABEAttributeList object describing the attribute list
 * @throw               - an exception if there is a problem with recovery
 */

bool
L_OpenABELSSS::l_recoverCoefficients(L_OpenABEPolicy *policy, L_OpenABEAttributeList *attrList)
{
  //ASSERT_NOTNULL(policy);
  //ASSERT_NOTNULL(attrList);
  // Clear any existing results
  this->l_clearExistingResults();

  // Recursively compute the coefficients
  if (this->l_performCoefficientRecovery(policy, attrList) == false) {
      // If there was an error, clear any partial results and
      // return false (indicating failure).
      this->m_ResultMap.clear();

  // Return false
  return false;
  }

  // Success, return true
  return true;
}

/*!
 * Utility routine. Given an access structure (policy) and an element,
 * perform secret sharing on the given element.
 *
 * @param[in] left      - OpenABEFunctionInput object describing the access structure
 * @param[in] right     - OpenABEFunctionInput object describing the input
 * @throw               - an exception if there is a problem sharing the element
 */

void
L_OpenABELSSS::l_performSecretSharing(const L_OpenABEPolicy *policy, L_ZP &elt)
{
  L_OpenABETreeNode *node = NULL;

  if(policy->l_hasDuplicateNodes()) {
    policy->l_getDuplicateInfo(this->m_AttrCount);
  }

  node = policy->l_getRootNode();
  assert(node != NULL);

  l_iterativeShareSecret(node, elt);
}

/*!
 * Recursive helper routine. Given a node within a policy tree and an element
 * to be shared, compute the secret shares of all sub-nodes. Then recurse
 * on each one.
 *
 * @param[in] node      - OpenABETreeNode object describing the node
 * @param[in] elt       - Element to be secret shared
 * @throw               - an exception if there is a problem sharing the element
 */

bool
L_OpenABELSSS::l_performCoefficientRecovery(L_OpenABEPolicy *policy, L_OpenABEAttributeList *attrList)
{
  L_OpenABETreeNode *node = NULL;

  if(policy->l_hasDuplicateNodes()) {
    policy->l_getDuplicateInfo(this->m_AttrCount);
  }

  node = policy->l_getRootNode();
  assert(node != NULL);

  // First, scan down through the tree to identify which leaves must be satisfied
  // in order to recover the secret. We will need to compute one coefficient
  // for each leaf. The result is stored as a 'mark' in each tree node --
  // from the leaves up to the root.
  bool result = l_iterativeScanTree(node, attrList);
  if(!result) {
    cout << "Insufficient attributes to recover the secret key." << endl;
    return result;
  }

  // Now that we've marked the nodes, we need to parse back down to the root,
  // computing the necessary coefficients at each stage. When we hit a leaf node,
  // the coefficient will be added to the m_ResultMap result list.
  L_ZP one;
  //this->m_Pairing->L_initZP(one, 1);

 bn_null(one.m_ZP);                
 bn_new(one.m_ZP); 
 bn_set_dig(one.m_ZP, 1);

 bn_t order_tmp;                                         
 bn_null(order_tmp); bn_new(order_tmp);                  
 bn_zero(order_tmp);                                     
                                                           
 ep_curve_get_ord(order_tmp);                            
 one.setOrder(order_tmp);

  return l_iterativeCoefficientRecover(node, one);
}

/*!
 * Utility routine (iterative version). Given an access structure (policy) and an element,
 * perform secret sharing on the given element.
 *
 * @param[in] treeNode      - OpenABETreeNode for the subtree
 * @param[in] elt           - ZP to be shared
 * @return                  - bool indicating success/failure
 * @throw                   - an exception if there is a problem sharing the element
 */

void
L_OpenABELSSS::l_iterativeShareSecret(L_OpenABETreeNode *treeNode, L_ZP &elt)
{
    std::stack<L_OpenABETreeNode*> nodes;
    std::stack<L_ZP> eltList;
    L_OpenABETreeNode *visitedNode = NULL;
    L_ZP theSecret, coefficient;
    //this->m_Pairing->L_initZP(theSecret, 0);
    //this->m_Pairing->L_initZP(coefficient, 0);

  bn_null(theSecret.m_ZP);
  bn_new(theSecret.m_ZP);
  bn_zero(theSecret.m_ZP);

  bn_t order_tmp;
  bn_null(order_tmp); bn_new(order_tmp);
  bn_zero(order_tmp); 

  ep_curve_get_ord(order_tmp);
  theSecret.setOrder(order_tmp);


  bn_null(coefficient.m_ZP);
  bn_new(coefficient.m_ZP);
  bn_zero(coefficient.m_ZP);

  coefficient.setOrder(order_tmp);

    // push the root to the stack
    nodes.push(treeNode);
    eltList.push(elt);
  L_OpenABEElementList coefficients;

  do {
    uint32_t threshold = 0, totalSubnodes = 0;
    coefficients.clear();

    visitedNode  = nodes.top();
    theSecret    = eltList.top();
    nodes.pop();
    eltList.pop();
    //ASSERT_NOTNULL(visitedNode);

    // Base case:
    // If the node is a leaf node, simply add the given element to the results
    // and return.
    if (visitedNode->l_getNodeType() == GATE_TYPE_LEAF) {
      this->l_addShareToResults(visitedNode, theSecret);
    }
    else {
      // First convert this node into a pair of values "threshold" and
      // "totalSubnodes" such that any "threshold"--out-of-"totalSubnodes"
      // shares permit secret recovery.
      totalSubnodes = visitedNode->l_getNumSubnodes();
      assert((threshold = visitedNode->l_getThresholdValue()) != 0);

      // Generate a polynomial consisting of "threshold" coefficients
      for (uint32_t i = 0; i < threshold; i++) {
        // Each coefficient is a random element of same field
        // as the element
        //L_ZP coefficient = this->m_Pairing->L_randomZP();

        bn_t order_tmp;
        bn_null(order_tmp); bn_new(order_tmp);
        ep_curve_get_ord(order_tmp);
        coefficient.setOrder(order_tmp);

        bn_rand(coefficient.m_ZP, RLC_POS, bn_bits(order_tmp));
        bn_mod(coefficient.m_ZP, coefficient.m_ZP, order_tmp);

        coefficients.push_back(coefficient);
      }
      // set position 0 as the passed in secret
      coefficients[0] = theSecret;
      // Now evaluate the polynomial at points (1, 2, ..., totalSubnodes) to
      // obtain the shares
      for (uint32_t i = 0; i < totalSubnodes; i++) {
        // Evaluate the polynomial at point (i+1) and recurse on the resulting value
        L_ZP share = this->l_evaluatePolynomial(coefficients, (i+1));
        nodes.push(visitedNode->l_getSubnode(i));
        eltList.push(share);
      }
    }
  } while(!nodes.empty());

  coefficients.clear();
}

/*!
 * Utility routine (iterative version). Given an access structure (policy) where each node has been
 * 'marked' if it's necessary to recover the secret, move through and calculate
 * the coefficients for each leaf node.
 *
 * @param[in] treeNode      - OpenABETreeNode for the subtree
 * @param[in] inCoeff       - ZP to be shared
 * @return                  - bool indicating success/failure
 * @throw                   - an exception if there is a problem sharing the element
 */

bool
L_OpenABELSSS::l_iterativeCoefficientRecover(L_OpenABETreeNode *treeNode, L_ZP &inCoeff)
{
  std::stack<L_OpenABETreeNode*> nodes;
  std::stack<L_ZP> coeffs;
  L_OpenABETreeNode *visitedNode = NULL;
  L_ZP tmpInCoeff, coefficient;
  //this->m_Pairing->L_initZP(tmpInCoeff, 0);
  //this->m_Pairing->L_initZP(coefficient, 0);


  bn_null(tmpInCoeff.m_ZP);
  bn_new(tmpInCoeff.m_ZP);
  bn_zero(tmpInCoeff.m_ZP);

  bn_t order_tmp;
  bn_null(order_tmp); bn_new(order_tmp);
  bn_zero(order_tmp); 

  ep_curve_get_ord(order_tmp);
  tmpInCoeff.setOrder(order_tmp);


  bn_null(coefficient.m_ZP);
  bn_new(coefficient.m_ZP);
  bn_zero(coefficient.m_ZP);

  coefficient.setOrder(order_tmp);

  // push the root to the stack
  nodes.push(treeNode);
  coeffs.push(inCoeff);
  bool result = false;

  do {
    uint32_t threshold = 0;

    visitedNode = nodes.top();
    tmpInCoeff  = coeffs.top();
    nodes.pop();
    coeffs.pop();
    //ASSERT_NOTNULL(visitedNode);

    // Base case:
    // If the node is a leaf node, simply add the input coefficient  to the results
    // and return.
    if (visitedNode->l_getNodeType() == GATE_TYPE_LEAF) {
      this->l_addShareToResults(visitedNode, tmpInCoeff);
      result = true;
    }
    	else {
      // First get the number of subnodes for this tree node.
      uint32_t numSubnodes = visitedNode->l_getNumSubnodes();

      // Process the node according to its type
      switch (visitedNode->l_getNodeType()) {
        case GATE_TYPE_AND:
          threshold = numSubnodes;    // AND gate: all subnodes satisfied
          break;
        case GATE_TYPE_OR:
          threshold = 1;              // OR gate: any one subnodes satisfied
          break;
#if 0
        case GATE_TYPE_THRESHOLD:
          threshold = visitedNode->getThresholdValue();
          break;
        default:
          // Unrecognized node type
          OpenABE_LOG_AND_THROW("Unrecognized node type", OpenABE_ERROR_SECRET_SHARING_FAILED);
          break;
#endif
      }

      // Now for each subnode in our list, calculate the coefficient and recurse
      for (uint32_t i = 0; i < numSubnodes; i++) {
        if(visitedNode->l_getSubnode(i)->l_getMark() == true) {
          // compute coefficient for this node
          coefficient = tmpInCoeff * l_calculateCoefficient(visitedNode, i, threshold, numSubnodes);
          nodes.push(visitedNode->l_getSubnode(i));
          coeffs.push(coefficient);
          result = true;
        }
      }
    	}
  } while(!nodes.empty());

  return result;
}


/*!
 * Utility routine. Calculates a Lagrange interpolation coefficient for 
 * share "index" out of "total" shares for a "threshold" secret sharing.
 *
 * @param[in] index            - Index of the coefficient
 * @param[in] threshold        - Threshold value
 * @param[in] total            - Total number of elements
 * @return                     - An element containing the coefficient
 * @throw                      - an exception if there is a problem sharing the element
 */

L_ZP
L_OpenABELSSS::l_calculateCoefficient(L_OpenABETreeNode *treeNode, uint32_t index, uint32_t threshold, uint32_t total)
{
  L_ZP result;
  //this->m_Pairing->L_initZP(result, 1);
  //this->m_Pairing->L_initZP(this->indexPlusOne, index + 1);


 bn_null(result.m_ZP);                
 bn_new(result.m_ZP); 
 bn_set_dig(result.m_ZP, 1);

 bn_t order_tmp;                                         
 bn_null(order_tmp); bn_new(order_tmp);                  
 bn_zero(order_tmp);                                     
                                                           
 ep_curve_get_ord(order_tmp);                            
 result.setOrder(order_tmp);

 bn_null(this->indexPlusOne.m_ZP);                
 bn_new(this->indexPlusOne.m_ZP); 
 bn_set_dig(this->indexPlusOne.m_ZP, index + 1);

 this->indexPlusOne.setOrder(order_tmp);

  // Product for all marked subnodes (excluding index) of ( (0 - (X(i))) / (X(subnode_index) - (X(i))) )
  // Note that X(i) = i+1.
  for (uint32_t i = 0; i < threshold; i++) {
    /* Check if this subnode is being used for the recovery.	*/
    //this->m_Pairing->L_initZP(this->iPlusOne, i + 1);

 bn_null(this->iPlusOne.m_ZP);                
 bn_new(this->iPlusOne.m_ZP); 
 bn_set_dig(this->iPlusOne.m_ZP, i+1);

 bn_t order_tmp;                                         
 bn_null(order_tmp); bn_new(order_tmp);                  
 bn_zero(order_tmp);                                     
 ep_curve_get_ord(order_tmp);                            
 this->iPlusOne.setOrder(order_tmp);

    if (treeNode->l_getSubnode(i)->l_getMark() == true) {
      if (i != index) {
        result *= result * ((this->zero - this->iPlusOne) / (this->indexPlusOne - this->iPlusOne));
      }
    }
  }
    
    return result;
}

/*!
 * Utility routine. Add a share to the internal secret sharing results vector.
 *
 * @param[in] treeNode      - OpenABETreeNode object containing label of the leaf node
 * @param[in] elt           - The secret share
 * @return                  - false if there is an error
 * @throw                   - an exception if there is a problem sharing the element
 */

void
L_OpenABELSSS::l_addShareToResults(L_OpenABETreeNode *treeNode, L_ZP &elt)
{
  L_OpenABELSSSElement lsssElement(treeNode->l_getCompleteLabel(), elt);
  this->m_ResultMap[this->l_makeUniqueLabel(treeNode)] = lsssElement;
  // JAA: uncomment to debug labels
  // cout << "Unique label: " << this->makeUniqueLabel(treeNode) << endl;
  // cout << treeNode->getCompleteLabel() << " -> " << elt << endl;
}

/*!
 * Evaluate a polynomial at a specified (integer) x coordinate. Takes a list of coefficients
 * and the x-coord as a uint32_t.
 *
 * @param[in] coefficients      - OpenABEElementList object containing the coordinates
 * @param[in] x                 - The x coordinate to evaluate
 * @return                      - A ZP containing the result
 * @throw                       - an exception if there is a problem
 */

L_ZP
L_OpenABELSSS::l_evaluatePolynomial(L_OpenABEElementList &coefficients,
                               uint32_t x)
{
  // Make sure the coefficients vector is non-trivial
  assert(coefficients.size() > 0);
//  {
//    OpenABE_LOG_AND_THROW("Coefficients vector has no elements", OpenABE_ERROR_SECRET_SHARING_FAILED);
//  }

  L_ZP share, xpow;
  //this->m_Pairing->L_initZP(share, 0);
  //this->m_Pairing->L_initZP(xpow, x);
  unsigned int i = 0;

 bn_null(share.m_ZP);                
 bn_new(share.m_ZP); 
 bn_zero(share.m_ZP);

 bn_t order_tmp;                                         
 bn_null(order_tmp); bn_new(order_tmp);                  
 bn_zero(order_tmp);                                     
                                                           
 ep_curve_get_ord(order_tmp);                            
 share.setOrder(order_tmp);

 bn_null(xpow.m_ZP);                
 bn_new(xpow.m_ZP); 
 bn_set_dig(xpow.m_ZP, x);
 xpow.setOrder(order_tmp);

  for (OpenABEElementListIterator it = coefficients.begin(); it != coefficients.end(); ++it) {
    share += ( *it * power(xpow, i) );
    //JAA cout << "coeff = " << *it << " at x = " << xpow << ", i = " << i << endl;
    i++;
  }

  return share;
}

/*!
 * Utility routine. If the label has previously been used, it makes a new
 * (unique) label by concatenating the label with the number of times
 * this label has been used, e.g.:
 *   Label "attribute" has not been used before: "0%attribute".
 *   Label "attribute" has been used 1 time:     "1%attribute". Etc.
 *
 * @param[in] label         - string containing the label
 * @return                  - unique label
 */

string
L_OpenABELSSS::l_makeUniqueLabel(const L_OpenABETreeNode *treeNode)
{
  // get the label
  string label = treeNode->l_getCompleteLabel();
  // if the label is duplicated in the policy tree, then add index
  if(this->m_AttrCount.count(label) != 0) {
    return label + "%" + to_string(treeNode->l_getIndex());
  }
  return label;
}

/*!
 * Utility routine (iterative version). Given an attribute list, scan the entire tree, 'marking' nodes that are
 * required to satisfy the policy. Returns the number of leaves required to satisfy this
 * subtree.
 *
 * @param[in] treeNode         - root of the subtree
 * @return                     - number of leaves required to satisfy this subtree
 */

bool l_iterativeScanTree(L_OpenABETreeNode *treeNode, L_OpenABEAttributeList *attributeList)
{
  uint32_t threshold;
  std::stack<L_OpenABETreeNode*> nodes;
  L_OpenABETreeNode *topNode = NULL;
  bool isInternalNode, allSubnodesVisited;

  nodes.push(treeNode);

  while(!nodes.empty()) {
    isInternalNode = true;
    // peek at the top
    topNode = nodes.top();
    //ASSERT_NOTNULL(topNode);
    switch (topNode->l_getNodeType()) {
      case GATE_TYPE_AND:
          // AND gate: all subnodes must be present to satisfy subtree
          threshold = topNode->l_getNumSubnodes();
          break;
      case GATE_TYPE_OR:
          // OR gate: any one subnode will satisfy the entire subtree
          threshold = 1;
          break;
#if 0
      case GATE_TYPE_THRESHOLD:
          // THRESHOLD gate: any k-of-n subnodes will satisfy the entire subtree
          threshold = topNode->getThresholdValue();
          break;
#endif
      case GATE_TYPE_LEAF:
          isInternalNode = false;
          break;
      default:
          // Unrecognized node type
          //OpenABE_LOG_AND_THROW("Unrecognized node type", OpenABE_ERROR_SECRET_SHARING_FAILED);
          cout << "unrecognized node type" << endl;
          break;
    }

    allSubnodesVisited = true;
    if (isInternalNode) {
      for (uint32_t i = 0; i < topNode->l_getNumSubnodes(); i++) {
        // push all the subnodes on the stack (that we have not visited so far)
        if(!topNode->l_getSubnode(i)->m_Visited) {
          nodes.push(topNode->l_getSubnode(i));
          allSubnodesVisited = false;
        }
      }
    } else {
      // Visit the node
      // This is a leaf node, so let's see if there's a match
      // cout << "Find attribute: " << topNode->getLabel() << " in " << attributeList->toString() << endl;
      // cout << "Result: " << attributeList->matchAttribute(topNode->getLabel()) << endl;
      bool leaf_matched = attributeList->matchAttribute(topNode->l_getCompleteLabel());
      topNode->l_setMark(leaf_matched, leaf_matched ? 1 : 0);
      // mark this node as visited then pop from the stack
      topNode->m_Visited = true;
      nodes.pop();
    }

    if (allSubnodesVisited && isInternalNode) {
      // visit the internal node
      l_determineIfNodeShouldBeMarked(threshold, topNode);
      // bool internal_node_satisfied = determineIfNodeShouldBeMarked(threshold, topNode);
      // if (internal_node_satisfied) {
      //    cout << "Gate satisfied. Num matches: " << topNode->getNumSatisfied() endl;
      // }
      topNode->m_Visited = true;
      nodes.pop();
    }
  }

  // cout << "Satisfied: " << (treeNode->getMark() ? "true" : "false") << endl;
  // cout << "How many matches: " << treeNode->getNumSatisfied() << endl;
  return treeNode->l_getMark();
}

// comparator for pair of integers
struct less_than {
    bool operator()(const std::pair<int,int> &left, const std::pair<int,int> &right) {
        return (left.second < right.second);
    }
};

bool l_determineIfNodeShouldBeMarked(uint32_t threshold, L_OpenABETreeNode *node)
{
  vector<pair<int, int>> list;
  uint32_t enough_nodes = threshold, cnt = 0;
  bool result;
  if (node->l_getNodeType() == GATE_TYPE_AND) {
    // mark this node as being satisfied (at first)
    result = true;
    int sum = 0;
    for(uint32_t i = 0; i < node->l_getNumSubnodes(); i++) {
      if(!node->l_getSubnode(i)->l_getMark()) {
          // mark this node as not being satisfied
          // (found at least one unmatched subnode)
          result = false;
      }
      sum += node->l_getSubnode(i)->l_getNumSatisfied();
    }

    if (result) {
      node->l_setMark(result, sum);
    } else {
      node->l_setMark(false, 0);
    }
  } else if(node->l_getNodeType() == GATE_TYPE_OR) {
    result = false;
    // build up list
    for (uint32_t i = 0; i < node->l_getNumSubnodes(); i++) {
      cnt = node->l_getSubnode(i)->l_getNumSubnodes();
      if(cnt == 0) {
        cnt++;
      }
      // only sorting nodes that are marked 'true'
      if (node->l_getSubnode(i)->l_getMark()) {
        list.push_back(std::make_pair(i, cnt));
      }
    }
    // sort the list (usually size 2)
    std::sort(list.begin(), list.end(), less_than());
    uint32_t i;
    // iterate through list in increasing order of subnodes to
    // determine satisfiability of subtree
    for (size_t k = 0; k < list.size(); k++) {
      i = list[k].first;
      // cout << "index: " << i << ", subnodes: " << list[k].second <<
      //        ", satisfied: " << (node->getSubnode(i)->getMark() ? "true": "false") << endl;
      if (node->l_getSubnode(i)->l_getMark() && enough_nodes > 0) {
        enough_nodes--;
        result = true;
      } else if(node->l_getSubnode(i)->l_getMark() && enough_nodes == 0) {
        // mark remaining nodes as false
        node->l_getSubnode(i)->l_setMark(false, 0);
      }
    }

    if (result) {
      node->l_setMark(result, list[0].second);
    } else {
      node->l_setMark(false, 0);
    }
  }
  else {
      result = false;
  }

  return result;
}

pair<bool, int> l_checkIfSatisfied(L_OpenABEPolicy *policy, L_OpenABEAttributeList *attr_list, bool reset_flags) {
    //ASSERT_NOTNULL(policy);
    //ASSERT_NOTNULL(attr_list);
    // check whether list satisfies the policy
    bool isSatisfied = l_iterativeScanTree(policy->l_getRootNode(), attr_list);
    int numNodesSatisfied = policy->l_getRootNode()->l_getNumSatisfied();
    // reset flags
    if(reset_flags) {
        l_resetFlags(policy->l_getRootNode());
    }
    // return result of check
    return make_pair(isSatisfied, numNodesSatisfied);
}


/*#ifndef OpenABE_NO_TEST_ROUTINES

//
// Used for testing only
//

ZP
OpenABELSSS::LSSStestSecretRecovery(const OpenABELSSSRowMap& coefficients, const OpenABELSSSRowMap& shares) {
    // Set 'result' to zero
    ZP result;
    this->m_Pairing->initZP(result, 0);
    
    // For each share, find the matching coefficient
    for(OpenABELSSSRowMap::const_iterator shareIt = shares.begin(); shareIt != shares.end(); ++shareIt) {
    	// First identify the coefficient that matches this share
    	OpenABELSSSRowMap::const_iterator coeffIt = coefficients.find(shareIt->first);
    	if (coeffIt == coefficients.end()) {
    		// OpenABE_LOG_AND_THROW("Could not find a matching coefficient in the list", OpenABE_ERROR_SECRET_SHARING_FAILED);
    		// Note: this condition occurs in one of two situations:
    		// 1) there is legitimately a missing coefficient in the list (due to recoveryCoefficient error)
    		// 2) we are dealing with an OR policy, in which case only 1 of the coefficients is necessary to recover secret
    		continue;
    	}

    	// Now compute result += (share * coeff)
    	result += (coeffIt->second.element() * shareIt->second.element());
    }
    
    return result;
}
//#endif
*/
//}
