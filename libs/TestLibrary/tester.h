//Header file for testlibrary

#ifndef TESTER_H
#define TESTER_H

#include <iostream>

//Function to test values/functions/...
//:param a: Bool-value
//:return bool: Returns the bool-value
void test (bool a) {
    if (!a) {
        std::cerr << "Test failed!" << std::endl;
        //exit(-1);
    }
}

#endif //TESTER_H
