//
//  FactorialChoosePiOperators.h
//  CSet
//
//  Created by Jamie Sherman on 20/02/2014.
//  Copyright (c) 2014 Jamie Sherman. All rights reserved.
//

#ifndef __CSet__FactorialChoosePiOperators__
#define __CSet__FactorialChoosePiOperators__

#include <iostream>
#include <exception>
#include <vector>
#include <memory>
#include <sstream>


namespace ABSciex_HT {
    struct Math {
        //typedef unsigned long uBigI;
        typedef unsigned long long int uBigI; //Big Int Type
        typedef long long int BigI;
        //typedef std::vector<uint_fast16_t> IDXVec;
        typedef std::vector<uBigI> IDXVec;
        typedef std::unique_ptr<IDXVec> IDXVecPtr;
        
        static IDXVec pyIndexListFromCombinadic(uBigI cbx, uBigI N, uBigI K);
        static uBigI pyCombinadicFromIndexList(IDXVec &vec);

        
        static uBigI choose(uBigI N, uBigI K);
        static uBigI factorial(uBigI N);
        
        static BigI SequenceProduct(BigI i, BigI M); // math: \Pi_i^m
        
        
        static IDXVecPtr indexListFromCombinadic(uBigI cbx, uBigI N, uBigI K);
        
        static uBigI combinadicFromIndexList(IDXVec *vecp);
        
        //abstract base class
        class MathException : public std::exception{
        protected:
            const char *m_func;
        public:
            MathException(const char*f): m_func(f) {}
            virtual const char* what(void) const throw() { return "message"; }
        };

        
        class FactorialException : public MathException
        {
            uBigI m_N;
        public:
            FactorialException(uBigI N, const char* funcName): MathException(funcName), m_N(N) {}
            const char* what() const throw ();
        };
        
        class SequenceOrderException : public MathException
        {
            BigI m_i, m_M;
        public:
            SequenceOrderException(uBigI i, uBigI M, const char* func)
                : MathException(func), m_i(i), m_M(M) {}
            const char* what(void) const throw ();
        };
        
    private:
        static BigI SequenceProduct(BigI i, BigI M, unsigned long int depth); // math: \Pi_i^m
        static uBigI factorialp(uBigI N, unsigned long depth);
        static uBigI indexFromInteger(BigI &x, uBigI n, uBigI k);
    };
}




#endif /* defined(__CSet__FactorialChoosePiOperators__) */
