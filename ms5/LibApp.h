/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 05 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Publication.h"
#include "Book.h"
#include "Lib.h"
#include "PublicationSelector.h"

namespace sdds {

    class LibApp {
        char m_fileName[256]{};
        Publication* PPA[SDDS_LIBRARY_CAPACITY]{};
        int NOLP{}; // Number Of Loaded Publications
        int LLRN{}; // Last Library Reference Number
        bool m_changed;
        Menu m_mainMenu;
        Menu m_exitMenu;
        Menu m_publicationMenu;
        bool confirm(const char* message);
        void load();
        void save();
        int search(int mode);
        Publication* getPub(int libRef);
        void returnPub();
        void newPublication();
        void removePublication();
        void checkOutPub();
    public:
        LibApp(const char* filename);
        ~LibApp();
        void run();
    };

}
#endif
