/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 26 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include <iostream>
#include <cstring>
#include <iomanip>
#include "Book.h"
#include "Lib.h"

namespace sdds {
Book::Book() : Publication(), m_name(nullptr){}

Book::Book(const Book& B) : Publication(B), m_name(nullptr) {
    if (B.m_name) {
        m_name = new char[strlen(B.m_name) + 1];
        strcpy(m_name, B.m_name);
    }
}

Book& Book::operator=(const Book& B) {
    if (this != &B) {
        Publication::operator=(B);
        delete [] m_name;
        if (B.m_name) {
            m_name = new char[strlen(B.m_name) + 1];
            strcpy(m_name, B.m_name);
        }
        else {
            m_name = nullptr;
        }
    }
    return *this;
}

Book::~Book() {
    delete [] m_name;
}

char Book::type()const {
    return 'B';
}

std::ostream& Book::write(std::ostream& os)const {
    Publication::write(os);
    if (conIO(os)) {
        os << ' ';
        if (strlen(m_name) > SDDS_AUTHOR_WIDTH) {
            for (int i = 0; i < SDDS_AUTHOR_WIDTH; i++) {
                os << m_name[i];
            }
        }
        else{
            os.width(SDDS_AUTHOR_WIDTH);
            os.setf(std::ios::left);
            os.fill(' ');
            os << m_name;
            os.unsetf(std::ios::left);
        }
        os << " |";
    }
    else {
        os << '\t' << m_name;
    }
    return os;
}

std::istream& Book::read(std::istream& istr) {
    char* temp_name = new char[257]{};
    Publication::read(istr);

    if (conIO(istr)) {
        istr.ignore(1000, '\n');
        std::cout << "Author: ";
        istr.get(temp_name, 257, '\n');
    }
    else {
        istr.ignore(1000, '\t');
        istr.get(temp_name, 257, '\n');
    }
    if (istr) {
        delete [] m_name;
        m_name = nullptr;
            m_name = new char[strlen(temp_name) + 1];
            strcpy(m_name, temp_name);
    }
    delete [] temp_name;
    return istr;
}

void Book::set(int membership) {
    Publication::set(membership);
    resetDate();
}

Book::operator bool()const {
    return (m_name != nullptr && m_name[0] != '\0' && Publication::operator bool());
}
}
