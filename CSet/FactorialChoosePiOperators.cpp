//
//  FactorialChoosePiOperators.cpp
//  CSet
//
//  Created by Jamie Sherman on 20/02/2014.
//  Copyright (c) 2014 Jamie Sherman. All rights reserved.
//

#include <cstdlib>
#include <numeric>
#include "FactorialChoosePiOperators.h"


namespace ABSciex_HT {

    Math::uBigI
    Math::factorial(Math::uBigI N) {
        return factorial(N, 0);
    }
    
    Math::uBigI
    Math::factorial(Math::uBigI N, unsigned long depth) {
        uBigI tmp = ((N<2) ? 1 : factorial(N-1, ++depth)*N);
        if (depth > 0 && std::numeric_limits<uBigI>::max()/tmp <= (N+1))
            throw FactorialException(N+1, "ABSciex_HT::Math::factorial");
        return tmp;
    }


    Math::uBigI
    Math::choose(Math::uBigI N, Math::uBigI K) {
        if (N < K) return 0;
        if (N == K) return 1;
        uBigI larger, smaller;
        uBigI numerator = 1, denominator;
        if (K > N-K){
            larger = K;
            smaller = N-K;
        } else {
            larger = N-K;
            smaller = K;
        }
        numerator = SequenceProduct(larger+1, N);
//        for (uBigI i = N ; i > larger ; i--) numerator *= i;
        denominator = factorial( smaller );
        return numerator/denominator;
    }
    
    Math::BigI
    Math::SequenceProduct(BigI i, BigI M){
        if (i>M) throw SequenceOrderException(i, M, "ABSciex_HT::Math::SequenceProduct(,)");
        return SequenceProduct(i, M, 0);
    }
    
    Math::BigI
    Math::SequenceProduct(BigI i, BigI M, unsigned long depth){
        BigI tmp = ((i > M) ? 1 : SequenceProduct(i+1, M, ++depth)*i);
        BigI absTmp = ( tmp < 0 ? -tmp : tmp); //tried to use abs but compiler complained
        if (depth > 0 && std::numeric_limits<BigI>::max()/absTmp <= (i-1))
            throw FactorialException(i-1, "ABSciex_HT::Math::SequenceProduct(,,)");
        return tmp;

    }

    Math::IDXVecPtr
    Math::indexListFromCombinadic(uBigI cbx, uBigI N, uBigI K){
        IDXVecPtr list = IDXVecPtr(new IDXVec(K));
        IDXVec::iterator pp = list->end()-1;
        BigI remainder = cbx;
        uBigI idx = N;
        
        for (uint i = (uint)K; i > 0 ; i--, pp--) {
            idx = indexFromInteger(remainder, idx - 1, i);
            *pp = idx;
        }
        return list;
    }
    
    Math::uBigI
    Math::indexFromInteger(BigI &x, uBigI n, uBigI k){
        uBigI comb(0);
        for ( ; (comb = choose(n, k)) > x ; n--);
        x -= comb;
        return n;
    }
    
    Math::uBigI
    Math::combinadicFromIndexList(IDXVec *vecp){
        uBigI ans = 0;
        try {
            for (int i = 0; i < vecp->size(); i++)
                ans += choose((*vecp)[i], i+1);
            
        } catch (const MathException &ex) {
            throw FactorialException(vecp->back(), "ABSciex_HT::uBigI combinadicFromIndexList");
        }
        
        return ans;
    }
    
    const char *
    Math::FactorialException::what(void) const throw(){
        std::stringstream str;
        str << "FactorialException: product would be larger than type allows."
        << "   [" << m_N << "!] > "
        << std::numeric_limits<uBigI>::max() << std::endl;
        str << "Error thrown in: " << m_func << std::endl;
        return str.str().c_str();
    }

    const char*
    Math::SequenceOrderException::what() const throw() {
        std::stringstream str;
        str << "SequenceOrderExcetpion: Product from i to M requires i <= M which was violated."
        << "   [" << m_i << " > " << m_M << " ]" << std::endl;
        return str.str().c_str();
    }
    
}