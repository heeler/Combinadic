//
//  FactorialChoosePiUnit.cpp
//  CSet
//
//  Created by Jamie Sherman on 20/02/2014.
//  Copyright (c) 2014 Jamie Sherman. All rights reserved.
//

#include <memory>
#include <vector>
#include "CSet.h"
#include "FactorialChoosePiOperators.h"
#include "gtest/gtest.h"



TEST(FactorialTest, TwelveFactorial) {
    EXPECT_EQ(ABSciex_HT::Math::factorial(12), 479001600);
}

TEST(FactorialTest, OneFactorial) {
    EXPECT_EQ(ABSciex_HT::Math::factorial(1), 1);
}

TEST(FactorialTest, ZeroFactorial) {
    EXPECT_EQ(ABSciex_HT::Math::factorial(0), 1);
}


TEST(ChooseTest, ThreeCHZeroTest) {
    EXPECT_EQ(ABSciex_HT::Math::choose(0, 3), 0);
}

TEST(ChooseTest, ThreeCHOneTest) {
    EXPECT_EQ(ABSciex_HT::Math::choose(1, 3), 0);
}

TEST(ChooseTest, ThreeCHThreeTest) {
    EXPECT_EQ(ABSciex_HT::Math::choose(3, 3), 1);
}

TEST(ChooseTest, FourCHThreeTest) {
    EXPECT_EQ(ABSciex_HT::Math::choose(4, 3), 4);
}

TEST(ChooseTest, TenCHFiveTest) {
    EXPECT_EQ(ABSciex_HT::Math::choose(10, 5), 252);
}

TEST(ChooseTest, ThrowTest) {
    EXPECT_THROW(ABSciex_HT::Math::choose(64, 32), ABSciex_HT::Math::FactorialException );
}


class MathCombinadicTest : public testing::Test {
protected:
    
    ABSciex_HT::Math::uBigI m_index = 72;
    ABSciex_HT::Math::uBigI m_N = 10;
    ABSciex_HT::Math::uBigI m_K = 5;
    ABSciex_HT::Math::IDXVecPtr m_ansp =
        ABSciex_HT::Math::IDXVecPtr(new ABSciex_HT::Math::IDXVec({0, 1, 3, 6, 8}));

};


TEST_F(MathCombinadicTest, ListFromIndex){
    using namespace ABSciex_HT;
    Math::IDXVecPtr listp = Math::indexListFromCombinadic( m_index, m_N, m_K);
    for (int i = 0; i < m_K; i++) {
        EXPECT_TRUE( (*listp)[i] == (*m_ansp)[i] );
    }
}

TEST_F(MathCombinadicTest, IndexFromList){
    using namespace ABSciex_HT;
    Math::uBigI index = Math::combinadicFromIndexList(m_ansp.get());
    EXPECT_EQ( index, m_index );
}
