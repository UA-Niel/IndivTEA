//Header file for HelperFunctions

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include "State.h"
#include "../libs/TestLibrary/tester.h"

//Checks if element is in object
//:param element: Element to check if it's in object v
//:param v: The object which should/should not contain element
//:return bool: Returns true if it's in there
template<typename T>
bool contains(T element, std::vector<T> v) {
    for (auto e : v) {
        if (e == element) return true;
    }

    return false;
}
bool contains(char element, std::string v) {
    for (auto e : v) {
        if (e == element) return true;
    }

    return false;
}


#endif //HELPERFUNCTIONS_H
