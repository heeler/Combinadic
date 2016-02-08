//
//  main.cpp
//  CSetUnitTests
//
//  Created by Jamie Sherman on 19/02/2014.
//  Copyright (c) 2014 Jamie Sherman. All rights reserved.
//

#include <iostream>
#include "gtest/gtest.h"

int main(int argc, char * argv[])
{
    testing::InitGoogleTest(&argc, argv);

    // insert code here...
    std::cout << "Running Tests!\n";
    return RUN_ALL_TESTS();
}

