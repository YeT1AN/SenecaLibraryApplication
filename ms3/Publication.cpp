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

ostream& Publication::write(ostream& os)const {
    if (conIO(os)) {
        os << "| " << m_shelfId << " | ";
        os.width(30);
        os.setf(ios::left);
        os.fill('.');
        os << m_title;      
        os << " | ";
        onLoan() ? os << m_membership : os << " N/A ";
        os << " | " << m_date << " |";
    }
    else {
        os << type() << '\t' << '\t' << m_libRef << '\t' << m_shelfId << '\t' << m_title << '\t';
        onLoan() ? os << m_membership : os << " N/A ";
        os << '\t' << m_date;
    }
    return os;
}

istream& Publication::read(istream& istr) {
    delete [] m_title;
    m_title = nullptr;
    m_shelfId[0] = '\0';
    m_membership = 0;
    m_libRef = -1;
    resetDate();
    
    char temp_title[SDDS_TITLE_WIDTH + 1]{};
    char temp_shelfId[SDDS_SHELF_ID_LEN + 1]{};
    int temp_membership = 0;
    int temp_libRef = -1;
    Date temp_date;
    
    if (conIO(istr)) {
        cout << "Shelf No: ";
        istr.getline(temp_shelfId, SDDS_SHELF_ID_LEN + 1);
        if (strlen(temp_shelfId) != SDDS_SHELF_ID_LEN) {
            istr.setstate(ios::failbit);
        }
        
        cout << "Title: ";
        istr.getline(temp_title, SDDS_TITLE_WIDTH + 1);
        
        cout << "Date: ";
        istr >> temp_date;
    }
    else {
        istr >> temp_libRef;
        istr.ignore();
        
        istr.getline(temp_shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
        
        istr.getline(temp_title, SDDS_TITLE_WIDTH, '\t');
        
        istr >> temp_membership;
        istr.ignore(); //
        
        istr >> temp_date;
    }
    if (!temp_date) {
        istr.setstate(ios::failbit);    //set to fail when date is invalid
    }
    if (istr) {
        m_title = new char[strlen(temp_title) + 1];
        strcpy(m_title, temp_title);
        strcpy(m_shelfId, temp_shelfId);
        m_membership = temp_membership;
        m_libRef = temp_libRef;
        m_date = temp_date;
    }
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
