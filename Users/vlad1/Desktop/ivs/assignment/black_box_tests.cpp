//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     VLADISLAV PASTUSHENKO <xpastu04@stud.fit.vutbr.cz>
// $Date:       $2020-02-15
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author VLADISLAV PASTUSHENKO
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"



TEST(EmptyTree, InsertNode){

    // Creating of new object b1_ of BinacryTree class. Insert node with key "1" 
    BinaryTree b1_;
    std::pair<bool, Node_t *> InsertNodeResult = b1_.InsertNode(1);
  
    
    ASSERT_TRUE(InsertNodeResult.first);
    ASSERT_TRUE(NULL != InsertNodeResult.second);
    
    ASSERT_EQ(1, InsertNodeResult.second->key);
    // Color of inserted node has to be BLACK
    ASSERT_EQ(1, InsertNodeResult.second->color);
    // It has to have no parents
    ASSERT_EQ(NULL, InsertNodeResult.second->pParent);
    
    // Testing of children
    ASSERT_TRUE(NULL != InsertNodeResult.second->pLeft);
    ASSERT_TRUE(NULL != InsertNodeResult.second->pRight);
    ASSERT_EQ(1, InsertNodeResult.second->pLeft->color);
    ASSERT_EQ(1, InsertNodeResult.second->pRight->color);
    ASSERT_TRUE(NULL != InsertNodeResult.second->pLeft->pParent);
    ASSERT_TRUE(NULL != InsertNodeResult.second->pRight->pParent);
    ASSERT_EQ(NULL, InsertNodeResult.second->pLeft->pLeft);
    ASSERT_EQ(NULL, InsertNodeResult.second->pRight->pRight);
    
    // Inserting of new node with key "2"
    std::pair<bool, Node_t *> InsertNodeResult_2 = b1_.InsertNode(2);
    
    ASSERT_TRUE(InsertNodeResult_2.first);
    ASSERT_TRUE(NULL != InsertNodeResult_2.second);
    
    ASSERT_EQ(2, InsertNodeResult_2.second->key);
    // New node has to contain RED color
    ASSERT_EQ(0, InsertNodeResult_2.second->color);
    
    // New node has to contain parent
    ASSERT_TRUE(NULL != InsertNodeResult_2.second->pParent);
    
    // Testing of children
    ASSERT_TRUE(NULL != InsertNodeResult_2.second->pLeft);
    ASSERT_TRUE(NULL != InsertNodeResult_2.second->pRight);
    ASSERT_EQ(1, InsertNodeResult_2.second->pLeft->color);
    ASSERT_EQ(1, InsertNodeResult_2.second->pRight->color);
    ASSERT_TRUE(NULL != InsertNodeResult_2.second->pLeft->pParent);
    ASSERT_TRUE(NULL != InsertNodeResult_2.second->pRight->pParent);
    ASSERT_EQ(NULL, InsertNodeResult_2.second->pLeft->pLeft);
    ASSERT_EQ(NULL, InsertNodeResult_2.second->pRight->pRight);
    ASSERT_EQ(2, InsertNodeResult_2.second->pLeft->pParent->key);
    ASSERT_EQ(2, InsertNodeResult_2.second->pRight->pParent->key);
    
    ASSERT_TRUE(NULL != InsertNodeResult.second->pRight);
    ASSERT_EQ(2, InsertNodeResult.second->pRight->key);    
    
    // Trying to insert new node with same key
    std::pair<bool, Node_t *> InsertNodeResultDublicate = b1_.InsertNode(1);
    
    ASSERT_FALSE(InsertNodeResultDublicate.first);
    ASSERT_EQ(1, InsertNodeResultDublicate.second->key);
}



TEST(EmptyTree, FindNode){
    
    // Creating of new object b1_ of BinacryTree class. Insert node with key "1" 
    BinaryTree b1_;
    b1_.InsertNode(1);
    
    ASSERT_EQ(NULL, b1_.FindNode(2));
    
    // It hasn't to find node with not existing key
    ASSERT_NE(b1_.FindNode(2), b1_.FindNode(1));
    if (NULL != b1_.FindNode(1)){
        ASSERT_EQ(1, b1_.FindNode(1)->key);
    }
}


TEST(EmptyTree, DeleteNode){
    // Creating of new object b1_ of BinacryTree class.
    BinaryTree b1_;
    
    ASSERT_FALSE(b1_.DeleteNode(1));
    ASSERT_FALSE(b1_.DeleteNode(-1));
    ASSERT_FALSE(b1_.DeleteNode(0));
    
    // Insert node with key "1" 
    b1_.InsertNode(1);
    
    ASSERT_TRUE(b1_.DeleteNode(1));
    ASSERT_EQ(NULL, b1_.FindNode(1));
    ASSERT_FALSE(b1_.DeleteNode(1));
    
}

// New testing-class. Object b2_ will contain few nodes (from 1 to 9)
class NonEmptyTree : public ::testing::Test {
    protected: 
        void SetUp()
        {
            b2_.InsertNode(1);
            b2_.InsertNode(2);
            b2_.InsertNode(3);
            b2_.InsertNode(4);
            b2_.InsertNode(5);
            b2_.InsertNode(6);
            b2_.InsertNode(7);
            b2_.InsertNode(8);
            b2_.InsertNode(9);
        }
    
        BinaryTree b2_;
};


TEST_F(NonEmptyTree, InsertNode){
    
    // Inserting new node with key "10"
    std::pair<bool, Node_t *> InsertNodeResult = b2_.InsertNode(10);
    
    ASSERT_TRUE(InsertNodeResult.first);
    ASSERT_EQ(10, InsertNodeResult.second->key);
    
    // Trying to insert node with existing key
    std::pair<bool, Node_t *> InsertNodeResult_2 = b2_.InsertNode(1);
    
    ASSERT_FALSE(InsertNodeResult_2.first);
    ASSERT_EQ(1, InsertNodeResult_2.second->key);
}

TEST_F(NonEmptyTree, FindNode){
    
    // Trying to find not existing node
    ASSERT_EQ(NULL, b2_.FindNode(10));
    
    ASSERT_NE(b2_.FindNode(10), b2_.FindNode(1));
    if (NULL != b2_.FindNode(1)){
        ASSERT_EQ(1, b2_.FindNode(1)->key);
    }
}

TEST_F(NonEmptyTree, DeleteNode){
    ASSERT_TRUE(b2_.DeleteNode(1));
    ASSERT_EQ(NULL, b2_.FindNode(1));
    ASSERT_FALSE(b2_.DeleteNode(1));
}


// New testing class. Object b3_ will contain 12 nodes (with keys from 1 to 12)
class TreeAxioms : public ::testing::Test {
    protected: 
        void SetUp()
        {
            b3_.InsertNode(1);
            b3_.InsertNode(2);
            b3_.InsertNode(3);
            b3_.InsertNode(4);
            b3_.InsertNode(5);
            b3_.InsertNode(6);
            b3_.InsertNode(7);
            b3_.InsertNode(8);
            b3_.InsertNode(9);
            b3_.InsertNode(10);
            b3_.InsertNode(11);
            b3_.InsertNode(12);
        }
    
        BinaryTree b3_;
};


TEST_F(TreeAxioms, Axiom1){
    std::vector<Node_t *> leafNodes;
    //Getting all leaves 
    b3_.GetLeafNodes(leafNodes);
    
    bool result = true;
    
    // Passing each leaf
    for(unsigned i = 0; i < leafNodes.size(); i++) {
        // Every leaf has to be black.
        if (leafNodes[i]->color == 0)
            result = false;
        }
    
    ASSERT_TRUE(result);
}

TEST_F(TreeAxioms, Axiom2){
    std::vector<Node_t *> NonleafNodes;
    b3_.GetNonLeafNodes(NonleafNodes);
    
    bool result = true;
    
    // Passing each nonLeaf node 
    for(unsigned i = 0; i < NonleafNodes.size(); i++) {
        
        // If node is black, both children have to be red
        if (NonleafNodes[i]->color == 0) {
            
            if(NonleafNodes[i]->pLeft != NULL) {
                if(NonleafNodes[i]->pLeft->color == 0)
                    result = false;     
            }
            
            if(NonleafNodes[i]->pRight != NULL) {
                if(NonleafNodes[i]->pRight->color == 0)
                    result = false;     
            }
        }
    }
    
    ASSERT_TRUE(result);
}


TEST_F(TreeAxioms, Axiom3){
    std::vector<Node_t *> leafNodes;
    b3_.GetLeafNodes(leafNodes);
    Node_t * rootNode = b3_.GetRoot();
    
    bool result = true;
    
    // Integer lenght of blacks will contain quantity of all black nodes from leaf to parent
    int lenghtOfBlacks = 0;
    
    // Passing each leaf
    for(unsigned i = 0; i < leafNodes.size(); i++) {
        
        // Integer counterOfBlacks will contain quantity of all black nodes from current leaf to parent.
        int counterOfBlacks = 0;
        
        Node_t* leafNode = leafNodes[i];
            while(leafNode != rootNode) {
                if(leafNode->color == 1)
                    counterOfBlacks++;
                
                leafNode = leafNode->pParent;
            }
        
        // If it was first iteration set the lenghtOfBlack 
        if (lenghtOfBlacks == 0)
            lenghtOfBlacks = counterOfBlacks;
        
        // If it wasn't first iteration compare current quantity and proper quantity
        if (counterOfBlacks != lenghtOfBlacks)
            result = false;
    }
    
    ASSERT_TRUE(result);
}

/*** Konec souboru black_box_tests.cpp ***/
