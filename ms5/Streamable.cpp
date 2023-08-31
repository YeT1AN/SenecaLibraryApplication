/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 24 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include <iostream>
#include "Streamable.h"

using namespace std;
namespace sdds {
    Streamable::~Streamable(){};

    ostream& operator<<(ostream& os, const Streamable& s) {
        if (s) {
            s.write(os);
        }
        return os;
    }

    istream& operator>>(istream& is, Streamable& s) {
        return s.read(is);
    }
}
