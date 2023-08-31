/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 24 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include <iostream>
#include <cstring>
#include <iomanip>
#include "Publication.h"

using namespace std;
namespace sdds {
Publication::Publication() {
    m_title = nullptr;
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    resetDate();
}

// Modifiers:
void Publication::set(int member_id) {
    m_membership = member_id;
}

void Publication::setRef(int value) {
    m_libRef = value;
}
   
void Publication::resetDate() {
    m_date = Date();
}

// Queries:
char Publication::type()const {
    return 'P';
}
   //Returns the character 'P' to identify this object as a "Publication object"
bool Publication::onLoan()const {
    return m_membership ? true : false;
}
   //Returns true is the publication is checkout (membership is non-zero)
Date Publication::checkoutDate()const {
    return m_date;
}
   //Returns the date attribute
bool Publication::operator==(const char* title)const {
    return strstr(m_title, title) != nullptr;
}
   //Returns true if the argument title appears anywhere in the title of the
   //publication. Otherwise, it returns false; (use strstr() function in <cstring>)
Publication::operator const char* ()const {
    return m_title;
}
   //Returns the title attribute
int Publication::getRef()const {
    return m_libRef;
}
   //Returns the libRef attirbute

bool Publication::conIO(ios& io)const {
    return (&io == &cin || &io == &cout);
}

ostream& Publication::printFill( const char* str, int width, char fill, ostream& ostr )const {
    int i = 0;
    for ( ; str && str[i] && i < width; i++ ) {
        ostr << str[i];
    }
    for ( ; i < width; i++) {
        ostr << fill;
    }
    return ostr;
}

ostream& Publication::write(ostream& os) const{
           
    if (conIO(os)) {
        os << "| " << m_shelfId << " | ";
        printFill(m_title, SDDS_TITLE_WIDTH, '.', os) << " | ";
        os.unsetf(std::ios::left);
        if (!m_membership) {
            os << " N/A ";
        }
        else {
            os << m_membership;
        }
        os << " | " << m_date << " |";
    }
    else {
        os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
    }
    return os;
}

istream& Publication::read(istream& istr) {
    char* title = new char[256];
    char shelfID[SDDS_SHELF_ID_LEN + 1] = { '\0' };
    int membership = 0, libRef = -1;
    Date date;
    
    m_title = nullptr;
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    resetDate();
    
    if (conIO(istr)) {
        std::cout << "Shelf No: ";
        istr >> shelfID;
        if (strlen(shelfID) != SDDS_SHELF_ID_LEN) istr.setstate(std::ios::failbit);
        else istr.ignore(1000, '\n');
        std::cout << "Title: ";
        istr.getline(title, 256, '\n');
        std::cout << "Date: ";
        istr >> date;
    }
    else {
        istr >> libRef;
        istr.ignore();
        istr.get(shelfID, SDDS_SHELF_ID_LEN + 2, '\t');
        istr.ignore();
        istr.get(title, 256, '\t');
        istr.ignore();
        istr >> membership;
        istr.ignore();
        istr >> date;
    }
    if (!date) istr.setstate(std::ios::failbit);
    if (istr) {
        if (title) {
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);
            strcpy(m_shelfId, shelfID);
            m_membership = membership;
            m_date = date;
            m_libRef = libRef;
        }
    }
    delete[] title;
    return istr;
}

Publication::operator bool()const {
    return (m_title != nullptr && m_shelfId[0] != '\0');
}

Publication::Publication(const Publication& p) {
    *this = p;
}

Publication& Publication::operator=(const Publication& p) {
    delete [] m_title;
    m_title = nullptr;
    if (p.m_title) {
        m_title = new char[strlen(p.m_title) + 1];
        strcpy(m_title, p.m_title);
    }
    strcpy(m_shelfId, p.m_shelfId);
    set(p.m_membership);
    setRef(p.m_libRef);
    m_date = p.m_date;
    return *this;
}

Publication::~Publication() {
    delete [] m_title;
}
}
