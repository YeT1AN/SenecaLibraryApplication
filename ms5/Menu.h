/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 8 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>

using namespace std;
namespace sdds {
    const unsigned int MAX_MENU_ITEMS = 20;
    class Menu;

    class MenuItem {
        friend class Menu;
        char* m_content{};
        
        MenuItem(){};
        MenuItem(const char * title);
        ~MenuItem();
        
        MenuItem(const MenuItem &) = delete;
        void operator=(const MenuItem&) = delete;
        
        operator bool()const;
        operator const char*()const;
        
        ostream& display(ostream & os = std::cout)const;
        
        void setEmpty();
    };

    class Menu{
        MenuItem m_title;
        MenuItem * m_items[MAX_MENU_ITEMS]{};
        unsigned int m_noOfItems;
        
    public:
        Menu(const char * title ="");
        ~Menu();
        
        Menu(const Menu&) = delete;
        void operator=(const Menu&) = delete;
        ostream& displayTitle(ostream& os = std::cout)const;
        ostream& display(ostream& os = std::cout)const;
        unsigned int run()const;
        unsigned int operator~()const;
        Menu& operator<<(const char* menuitemConent);
        operator int()const;
        operator unsigned int()const;
        operator bool()const;
        const char* operator[](unsigned int index)const;
    };

    ostream& operator<<(ostream& os, const Menu & menu);
}
#endif
