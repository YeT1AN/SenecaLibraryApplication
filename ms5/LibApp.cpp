/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 05 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "LibApp.h"
#include "Utils.h"

using namespace std;
namespace sdds {

    bool LibApp::confirm(const char* message) {
        Menu menu(message);
        menu << "Yes";
        return menu.run() == 1;
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
        ifstream fin(m_fileName);
        char type{};            // to store the type of publication
        for (int i = 0; fin; i++) {
            fin >> type;
            fin.ignore();
            if (fin) {          // dynamically instantiating the corresponding object
                if (type == 'B') {
                    PPA[i] = new Book;
                }
                else if (type == 'P') {
                    PPA[i] = new Publication;
                }
                if (PPA[i]) {   // into the next available PPA element
                    fin >> *PPA[i];
                    NOLP++;
                    LLRN = PPA[i]->getRef();
                }
            }
        }
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;
        ofstream fout(m_fileName);
        for (int i = 0; i < NOLP; i++) {    // loop through PPA up to NOLP
            if (PPA[i]->getRef() != 0) {    // insert all ref except deleted (0)
                fout << *PPA[i] << endl;
            }
        }
    }

    int LibApp::search(int mode) {
        PublicationSelector P("Select one of the following found matches:", 15);
        int sel, i, ret{};
        char* title = new char[256];
        bool match = false;
        if (mode == 1) {    // search all
            sel = m_publicationMenu.run();
            switch (sel) {
                case 0:
                    cout << "Aborted!\n";
                case 1:
                    cin.ignore();
                    cout << "Publication Title: ";
                    cin.getline(title, 256);
                    for (i = 0; i < NOLP; i++) {
                        if (PPA[i]->getRef() && *PPA[i]==title && PPA[i]->type() != 'P') {
                            match = true;
                            P << *PPA[i];
                        }
                    }
                    if (match) {
                        P.sort();
                        ret = P.run();
                        if (ret == 0) cout << "Aborted!\n";
                    }
                    else cout << "No matches found!\n";
                    break;
                case 2:
                    cin.ignore();
                    cout << "Publication Title: ";
                    cin.getline(title, 256);
                    for (i = 0; i < NOLP; i++) {
                        if (PPA[i]->getRef() && *PPA[i]==title && PPA[i]->type() == 'P') {
                            match = true;
                            P << *PPA[i];
                        }
                    }
                    if (match) {
                        P.sort();
                        ret = P.run();
                        if (ret == 0) cout << "Aborted!\n";
                    }
                    else cout << "No matches found!\n";
                    break;
            }
        }
        else if (mode == 2) {   // search checkout items
            sel = m_publicationMenu.run();
            switch (sel) {
                case 0:
                    cout << "Aborted!\n";
                case 1:
                    cin.ignore();
                    cout << "Publication Title: ";
                    cin.getline(title, 256);
                    for (i = 0; i < NOLP; i++) {
                        if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() != 'P' && PPA[i]->onLoan()) {
                            match = true;
                            P << *PPA[i];
                        }
                    }
                    if (match) {
                        P.sort();
                        ret = P.run();
                        if (ret == 0) cout << "Aborted!\n";
                    }
                    else cout << "No matches found!\n";
                    break;
                case 2:
                    cin.ignore();
                    cout << "Publication Title: ";
                    cin.getline(title, 256);
                    for (i = 0; i < NOLP; i++) {
                        if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() == 'P' && PPA[i]->onLoan()) {
                            match = true;
                            P << *PPA[i];
                        }
                    }
                    if (match) {
                        P.sort();
                        ret = P.run();
                        if (ret == 0) cout << "Aborted!\n";
                    }
                    else cout << "No matches found!\n";
                    break;
            }
        }
        else if (mode == 3) {   // search available items
            sel = m_publicationMenu.run();
            switch (sel) {
                case 0:
                    cout << "Aborted!\n";
                case 1:
                    cin.ignore();
                    cout << "Publication Title: ";
                    cin.getline(title, 256);
                    for (i = 0; i < NOLP; i++) {
                        if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() != 'P' && !PPA[i]->onLoan()) {
                            match = true;
                            P << *PPA[i];
                        }
                    }
                    if (match) {
                        P.sort();
                        ret = P.run();
                        if(ret == 0) cout << "Aborted!\n";
                    }
                    else cout << "No matches found!\n";
                    break;
                case 2:
                    cin.ignore();
                    cout << "Publication Title: ";
                    cin.getline(title, 256);
                    for (i = 0; i < NOLP; i++) {
                        if (PPA[i]->getRef() && *PPA[i] == title && PPA[i]->type() == 'P' && !PPA[i]->onLoan()) {
                            match = true;
                            P << *PPA[i];
                        }
                    }
                    if (match) {
                        P.sort();
                        ret = P.run();
                        if (ret == 0) cout << "Aborted!\n";
                    }
                    else cout << "No matches found!\n";
                    break;
            }
        }
        delete[] title;
        return ret;
    }

    Publication* LibApp::getPub(int libRef) {
        Publication* ret = nullptr;             // set ret
        for (int i = 0; i < NOLP; i++) {
            if (PPA[i]->getRef() == libRef) {   // if PPA matches libRef
                ret = PPA[i];                   // assign the address to ret
            }
        }
        return ret;
    }

    void LibApp::returnPub() {
        int index = -1;
        int checkout,late;
        double penalty;
        Date d;
        cout << "Return publication to the library\n";
        int ret = search(2);//Search on Loan
        if (ret > 0) {//search returns 0 by default
            for (int i = 0; i < NOLP; i++) {
                if (PPA[i]->getRef() == ret)
                    index = i;
            }
            if (index > -1) {
                cout << *PPA[index] << endl;
                if (confirm("Return Publication?")) {
                    checkout = d - PPA[index]->checkoutDate();
                    if (checkout > SDDS_MAX_LOAN_DAYS) {
                        late = checkout - SDDS_MAX_LOAN_DAYS;
                        penalty = .50 * late;
                        cout << "Please pay $";
                        cout << fixed << setprecision(2) << penalty;
                        cout.unsetf(ios::fixed);
                        cout << " penalty for being " << late << " days late!\n";
                    }
                    PPA[index]->set(0);
                    m_changed = true;
                    cout << "Publication returned\n";
                }
            }
        }
    }

    void LibApp::newPublication() {
        Publication* P{};   // set temp object for adding new publication
        if (NOLP == SDDS_LIBRARY_CAPACITY) {
            cout << "Library is at its maximum capacity!" << endl;
        }
        else {
            cout << "Adding new publication to the library" << endl;
            size_t mode = m_publicationMenu.run();
            if (mode == 1) {        // create new book
                P = new Book;
                cin >> *P;
            }
            else if(mode == 2) {    // create new publication
                Publication newPub;
                P = new Publication;
                cin >> *P;
            }
            if (mode == 0) {        // abort
                if (!cin) {
                    cin.ignore();
                }
                cout << "Aborted!" << endl;
            }
            else {
                if (confirm("Add this publication to the library?")) { // request user confirmation
                    if (P) {    // if confirmed & P is valid, record data
                        LLRN += 1;
                        P->setRef(LLRN);
                        PPA[NOLP] = P;
                        NOLP += 1;
                        m_changed = true;
                        cout << "Publication added";
                        cout << endl;
                    }
                    else {      // else remove data
                        cout << "Failed to add publication!" << endl;
                        delete P;
                    }
                }
                else {          
                    cout << "Aborted!\n";
                }
            }
        }
    }

    void LibApp::removePublication() {
        cout << "Removing publication from the library\n";
        int index = -1;
        int ret = search(1);
        if (ret > 0) {
            for (int i = 0; i < NOLP; i++) {
                if (PPA[i]->getRef() == ret)
                    index = i;
            }
            if (index > -1) {
                cout << *PPA[index] << endl;
                if (confirm("Remove this publication from the library?")) {
                    PPA[index]->setRef(0);
                    m_changed = true;
                    cout << "Publication removed\n";
                }
            }
        }
    }

    void LibApp::checkOutPub() {
        cout << "Checkout publication from the library\n";
        int num,len,index=-1;
        int ret = search(3);    // earch available items
        if (ret > 0) {          // search returns 0 by default
            for (int i = 0; i < NOLP; i++) {
                if (PPA[i]->getRef() == ret)
                    index = i;
            }
            if (index > -1) {
                cout << *PPA[index] << endl;
                if (confirm("Check out publication?")) {
                    cout << "Enter Membership number: ";
                    do {        // validate membership
                        cin >> num;
                        len = numLen(num);  // check int length
                        if (len != 5) {
                            cout << "Invalid membership number, try again: ";
                        }
                    } while (len != 5);
                    PPA[index]->set(num);
                    m_changed = true;
                    cout << "Publication checked out\n";
                }
            }
        }
    }

    LibApp::LibApp(const char* filename):m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?"), m_publicationMenu("Choose the type of publication:") {
        strcpy(m_fileName, filename);
        m_mainMenu << "Add New Publication"
                   << "Remove Publication"
                   << "Checkout publication from library"
                   << "Return publication to library";
        m_exitMenu << "Save changes and exit"
                   << "Cancel and go back to the main menu";
        m_publicationMenu << "Book" << "Publication";
        load();
    }

    LibApp::~LibApp() {
        for (int i = 0; i < NOLP; i++) {
            delete PPA[i];
        }
    }

    void LibApp::run() {
        bool done = false;      // flag for selection
        while (!done) {
            unsigned int choice = m_mainMenu.run();
            switch (choice) {   // select from menu
                case 0:
                    done = true;
                    break;
                case 1:
                    newPublication();
                    cout << endl;
                    break;
                case 2:
                    removePublication();
                    cout << endl;
                    break;
                case 3:
                    checkOutPub();
                    cout << endl;
                    break;
                case 4:
                    returnPub();
                    cout << endl;
                    break;
                default:
                    break;
            }
            if (done) {         // exit or loop back
                if (m_changed) {
                    unsigned int exitchoice = m_exitMenu.run();
                    if (exitchoice == 1) {
                        save();
                        done = true;
                    }
                    else if (exitchoice == 2) {
                        cout << endl;
                        done = false;
                    }
                    else {
                        if (confirm("This will discard all the changes are you sure?")) {
                            done = true;
                        }
                        else {
                            done = false;
                        }
                    }
                }
            }
        }
        cout << "\n-------------------------------------------\n"
             << "Thanks for using Seneca Library Application\n";
    }

}
