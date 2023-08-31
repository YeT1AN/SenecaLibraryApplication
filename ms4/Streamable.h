/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 24 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#ifndef SDDS_STREAMABLE_H__
#define SDDS_STREAMABLE_H__
#include <iostream>

using namespace std;
namespace sdds {
    class Streamable {
    public:
        virtual ostream& write(ostream& os)const = 0;
        virtual istream& read(istream& is) = 0;
        virtual bool conIO(ios& io)const = 0;
        virtual operator bool()const = 0;
        virtual ~Streamable() = 0;
    };
    ostream& operator<<(ostream& os, const Streamable& s);
    istream& operator>>(istream& is, Streamable& s);
}

#endif
