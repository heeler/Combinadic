//
//  CSet.cpp
//  CSet
//
//  Created by Jamie Sherman on 19/02/2014.
//  Copyright (c) 2014 Jamie Sherman. All rights reserved.
//

#include <sstream>
#include <algorithm>
#include "CSet.h"


namespace ABSciex_HT {
    
    
    CSetBinary::CSetBinary(CSBType N, CSBType K): m_n(N), m_k(K), m_combination(), m_last() {
        m_combination = firstCombination();
        m_last = endCombination(m_combination);

    }
    
    bool CSetBinary::nextCombination(CSBType &x) // assume x has form x'01^a10^b in binary
    {
        if ( x > m_last ) return false;
        CSBType u = x & -x; // extract rightmost bit 1; u =  0'00^a10^b
        CSBType v = u + x; // set last non-trailing bit 0, and clear to the right; v=x'10^a00^b
        if (v==0) // then overflow in v, or x==0
            return false; // signal that next k-combination cannot be represented
        x = v +(((v^x)/u)>>2); // v^x = 0'11^a10^b, (v^x)/u = 0'0^b1^{a+2}, and x ← x'100^b1^a
        return !(x > m_last); // successful completion
    }
    
    CSetBinary::CSBType CSetBinary::firstCombination(void) const {
        const CSBType shift = CSBTypeSize - m_k;
        
        if( m_n > CSBTypeSize ) // Check N
            throw CSetBinaryExcetpion( m_n );
        
        if( m_n < m_k ) // Check K
            throw CSetBinaryExcetpion( m_k, "CSetBinrary:  K > N !" );
        
        CSBType tmp = ~0; // 1111111111
        return (tmp >> shift);
    }
    
    CSetBinary::CSBType CSetBinary::endCombination(void) const {
        return endCombination(firstCombination());
    }

    CSetBinary::CSBType CSetBinary::endCombination(CSBType start) const {
        const CSBType shift = this->n() - this->k();        
        return (start << shift);
    }

    CSetBinary::CSBType
    CSetBinary::combinadicFromCombination(CSBType x){
        Math::IDXVecPtr idxs(new Math::IDXVec());
        std::cout << CSBTypeSize << ": " << std::bitset<CSBTypeSize>(x) << std::endl;
        CSBType xtmp = x;
        for (CSBType i = 0, j=0 ; i < CSBTypeSize ; i++, j++){
            if (!(i%32) && i != 0) { // this is here because the bitshift operator only can shift 32 bits max
                xtmp = xtmp >> 32;
                j = 0;
            }
            if( xtmp & (1 << j) )
                idxs->push_back( i );

        }
        return Math::combinadicFromIndexList(idxs.get());
    }
    
    CSetBinary::CSBType
    CSetBinary::combinationFromCombinadic(CSBType idx){
        CSBType ans = 0;
        Math::IDXVecPtr listp = Math::indexListFromCombinadic(idx, m_n, m_k);
        std::for_each(listp->begin(), listp->end(), [&ans](Math::IDXVec::value_type val)->void{
            ans |= 1 << val;
        });
        return ans;
    }
    
    CSetBinary::CSBType
    CSetBinary::smartShift(CSBType x, CSBType shift){
        if (shift <= SHIFTMAX) return (x << shift);
            
        CSBType ans = x, i = 0;
        while ( i++ < (shift / SHIFTMAX) ) ans = ans << SHIFTMAX;
        ans = ans << (shift%SHIFTMAX);
        return ans;
    }
    
    
    std::string CSetBinary::str(void) const {
        std::stringstream sstr;
        sstr << std::bitset<CSBTypeSize>(this->combination());
        std::string asString(sstr.str());
        return std::string(asString.begin()+(CSBTypeSize - this->n()), asString.end());
    }
    
    std::ostream &operator<<(std::ostream &os, const CSetBinary &csb){
        return os << csb.str(); // << "   int: " << csb.combination();
    }
    
}


