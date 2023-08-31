/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 8 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include <iostream>
#include <cstring>
#include <iomanip>
#include "Menu.h"
#include "Utils.h"

using namespace std;

namespace sdds {
    MenuItem::MenuItem(const char* title) {
        if (title) {
            m_content = new char[strlen(title) + 1];
            strcpy(m_content, title);
        }
        else {
            m_content = nullptr;
        }
    }

    MenuItem::~MenuItem() {
        delete [] m_content;
    }

    MenuItem::operator bool()const {
        return m_content[0] != '\0' && m_content != nullptr;
    }

    MenuItem::operator const char *()const {
        return m_content;
    }

    ostream& MenuItem::display(ostream & os)const {
        if (m_content != nullptr) {
            os << m_content;
        }
        return os;
    }

    Menu::Menu(const char * title) {
        m_title.m_content = new char[strlen(title) + 1];
        strcpy(m_title.m_content, title);
        m_noOfItems = 0;
    }

    Menu::~Menu() {
        for (unsigned int i = 0; i < m_noOfItems; i++) {
            delete m_items[i];
        }
    }

    ostream& Menu::displayTitle(ostream& os)const {
        m_title.display(os);
        return os;
    }

    ostream& Menu::display(ostream& os)const {
        displayTitle(os);
        if (m_title){
            os << ":\n";
        }
        for (unsigned int i = 0; i < m_noOfItems; i++) {
            os << setw(2) << i+1 << "- ";
            m_items[i]->display() << endl;
        }
        os << " 0- Exit\n> ";
        return os;
    }

    unsigned int Menu::run()const {
        display();
        unsigned int usrSel = getIntMM(0, m_noOfItems);
        return usrSel;
    }

    unsigned int Menu::operator~()const {
        display();
        unsigned int usrSel = getIntMM(0, m_noOfItems);
        return usrSel;
    }

    Menu& Menu::operator<<(const char* menuitemConent) {
        if (m_noOfItems < MAX_MENU_ITEMS) {
            m_items[m_noOfItems] = new MenuItem(menuitemConent);
            m_noOfItems++;
        }
        return *this;
    }

    Menu::operator int()const {
        return m_noOfItems;
    }

    Menu::operator unsigned int()const {
        return m_noOfItems;
    }

    Menu::operator bool()const {
        return m_noOfItems >= 1;
    }

    const char* Menu::operator[](unsigned int index)const {
        return index > m_noOfItems ? m_items[index % m_noOfItems]->m_content : m_items[index]->m_content;
    }

    ostream& operator<<(ostream& os, const Menu & menu) {
        return menu.displayTitle(os);
    }
}
