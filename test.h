//Header file for test
#ifndef TEST_H
#define TEST_H

#include "libs/TestLibrary/tester.h"
#include "headers/HelperFunctions.h"

//Function to launch all tests
void LaunchTest () {
    //HelperFunctions test
    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    std::string s1 = "123,wfew";

    //test(contains(0, v1) == false);
    //test(contains(2, v1) == true);
    test(contains('1', s1) == true);
    test(contains(',', s1) == true);
    test(contains('w', s1) == true);
    test(contains('x', s1) == false);
    
}

#endif //TEST_H

