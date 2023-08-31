/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 26 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */
#ifndef SDDS_BOOK_H__
#define SDDS_BOOK_H__
#include "Publication.h"

namespace sdds {
    class Book : public Publication {
        char* m_name{};
    public:
        Book();
        Book(const Book& B);
        Book& operator=(const Book& B);
        ~Book();
        
        char type()const;
        std::ostream& write(std::ostream& os)const;
        std::istream& read(std::istream& istr);
        void set(int membership);
        operator bool()const;
    };
}

#endif
