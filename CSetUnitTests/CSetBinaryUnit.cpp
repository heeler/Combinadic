//
//  CSetBinaryUnit.cpp
//  CSet
//
//  Created by Jamie Sherman on 20/02/2014.
//  Copyright (c) 2014 Jamie Sherman. All rights reserved.
//

#include <memory>
#include <vector>
#include "CSet.h"
#include "gtest/gtest.h"

// To use a test fixture, derive a class from testing::Test.

class SmallCSetBinaryTest : public testing::Test {
protected:  // You should make the members protected s.t. they can be
    // accessed from sub-classes.
    
    // virtual void SetUp() will be called before each test is run.  You
    // should define it if you need to initialize the varaibles.
    // Otherwise, this can be skipped.
    virtual void SetUp() {
        comb_p = std::unique_ptr<ABSciex_HT::CSetBinary>(new ABSciex_HT::CSetBinary( 5 , 3));
    }
    
    // virtual void TearDown() will be called after each test is run.
    // You should define it if there is cleanup work to do.  Otherwise,
    // you don't have to provide it.
    //
    // virtual void TearDown() {
    // }

    std::unique_ptr<ABSciex_HT::CSetBinary> comb_p;
    const ABSciex_HT::CSetBinary::CSBType FiveChooseThree = 10;
    std::vector<ABSciex_HT::CSetBinary::CSBType> answers = {
        0b000111, 0b001011, 0b001101, 0b001110, 0b010011,
        0b010101, 0b010110, 0b011001, 0b011010, 0b011100
    };
    
    
};

TEST_F(SmallCSetBinaryTest, ConstructorTest) {
    EXPECT_EQ(comb_p->size(), FiveChooseThree); // Choose(5,3) = 10
}

TEST_F(SmallCSetBinaryTest, ConstructorFirstComb) {
    EXPECT_EQ(comb_p->combination(), answers[0]);
}

TEST_F(SmallCSetBinaryTest, ConstructorLastComb) {
    EXPECT_EQ(comb_p->last(), answers[9]);
}

TEST_F(SmallCSetBinaryTest, CombinationTest) {
    std::vector<ABSciex_HT::CSetBinary::CSBType>::iterator ansItt = answers.begin();
    do {
//        std::cout << *comb_p << "  =?= " << std::bitset<5>(*ansItt) << std::endl;
        EXPECT_EQ( *comb_p, *ansItt);
        ansItt++;
    } while (comb_p->nextCombination());
}

class CSetBinaryCombinadicTest : public testing::Test {
protected:
    virtual void SetUp() {
        comb_p = std::unique_ptr<ABSciex_HT::CSetBinary>(new ABSciex_HT::CSetBinary( 10 , 5));
    }

    std::unique_ptr<ABSciex_HT::CSetBinary> comb_p;
    const ABSciex_HT::CSetBinary::CSBType m_index = 72;
    const ABSciex_HT::CSetBinary::CSBType SeventySecondCombination = 0b00101001011;
};


TEST_F(CSetBinaryCombinadicTest, combinationFromCombinadic){
    ABSciex_HT::CSetBinary::CSBType ans = comb_p->combinationFromCombinadic(m_index);
    EXPECT_TRUE( (ans & SeventySecondCombination) == (ans | SeventySecondCombination)  );
    EXPECT_EQ(SeventySecondCombination, ans);
}

TEST_F(CSetBinaryCombinadicTest, combinadicFromCombination){
    ABSciex_HT::CSetBinary::CSBType ans = comb_p->combinadicFromCombination(SeventySecondCombination);
    std::cout << ans << " =?= " << m_index << std::endl;
    EXPECT_EQ(m_index, ans);
}


