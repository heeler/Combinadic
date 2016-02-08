//
//  CSet.h
//  CSet
//
//  Created by Jamie Sherman on 19/02/2014.
//  Copyright (c) 2014 Jamie Sherman. All rights reserved.
//

#ifndef __CSet__CSet__
#define __CSet__CSet__

#include <iostream>
#include <ostream>
#include <bitset>
#include <sstream>
#include <vector>
#include <exception>
#include "FactorialChoosePiOperators.h"


namespace ABSciex_HT {
    
    class CSBType {
        
    };
    
    // This class generates combinations up to 
    class CSetBinary{
    public:
        typedef unsigned long long int CSBType;
        #define CSBTypeSize 8*sizeof(CSBType)
        
        CSetBinary(CSBType N, CSBType K);
        bool nextCombination(void) { return nextCombination(m_combination); }
        CSBType combinadicFromCombination(CSBType x);
        CSBType combinationFromCombinadic(CSBType idx);
        bool nextCombination(CSBType &x);
        void reset(void) { m_combination = firstCombination(); }
        CSBType combination(void) const { return m_combination; }
        CSBType n(void) const { return m_n; }
        CSBType k(void) const { return m_k; }

        CSBType size(void) const { return Math::choose(m_n, m_k); }
        CSBType last(void) const { return endCombination(); };
        bool operator==(const CSBType other) const { return m_combination == other; }
        bool operator==(const CSetBinary oth) const { return m_combination == oth.m_combination; }
        std::string str(void) const;
        

        
    private:
        
        
        CSBType m_n, m_k, m_size;
        CSBType m_combination, m_last;
        #define SHIFTMAX 32
        
        CSBType firstCombination(void) const;
        CSBType endCombination(void) const;
        CSBType endCombination(CSBType first) const;
        CSBType smartShift(CSBType x, CSBType shift);
        
    };
    
    
    class CSetBinaryExcetpion : public std::exception
    {
        CSetBinary::CSBType m_N;
        const char *m_message;
        
    public:
        CSetBinaryExcetpion(CSetBinary::CSBType N, const char *msg = "CSetBinaryException: N too large to represent in CSetBinary."): m_N(N), m_message(msg) {}
        
        const char * what () const throw ()
        {
            std::stringstream str;
            str << m_message << "   [" << m_N << " bits] > "
            << std::numeric_limits<CSetBinary::CSBType>::max() << std::endl;
            return str.str().c_str();
        }
    };
    
    
    std::ostream &operator<<(std::ostream &os, const CSetBinary &csb);
    
}


#endif /* defined(__CSet__CSet__) */
