//
//  main.cpp
//  CSet
//
//  Created by Jamie Sherman on 19/02/2014.
//  Copyright (c) 2014 Jamie Sherman. All rights reserved.
//

#include <iostream>
#include "CSet.h"

int main(int argc, const char * argv[])
{

    ABSciex_HT::CSetBinary comb(5, 3);

    do {
        std::cout << comb << std::endl;
    } while (comb.nextCombination());

    return 0;
}

