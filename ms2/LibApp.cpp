/*
 Ye Tian
 ytian62@myseneca.ca
 142003227
 11 JUL 2023
 I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
 */

#include "LibApp.h"

using namespace std;
namespace sdds {

    bool LibApp::confirm(const char* message) {
        Menu menu(message);
        menu << "Yes";
        return menu.run() == 1;
    }

    void LibApp::load() {
        cout << "Loading Data" << endl;
    }

    void LibApp::save() {
        cout << "Saving Data" << endl;
    }

    void LibApp::search() {
        cout << "Searching for publication" << endl;
    }

    void LibApp::returnPub() {
        search();
        cout << "Returning publication" << endl
             << "Publication returned" << endl;
        m_changed = true;
    }

    void LibApp::newPublication() {
        cout << "Adding new publication to library" << endl;
        if (confirm("Add this publication to library?")) {
            m_changed = true;
            cout << "Publication added" << endl;
        }
    }

    void LibApp::removePublication() {
        cout << "Removing publication from library" << endl;
        search();
        if (confirm("Remove this publication from the library?")) {
            m_changed = true;
            cout << "Publication removed" << endl;
        }
    }

    void LibApp::checkOutPub() {
        search();
        if (confirm("Check out publication?")) {
            m_changed = true;
            cout << "Publication checked out" << endl;
        }
    }

    LibApp::LibApp():m_mainMenu("Seneca Library Application"), m_exitMenu("Changes have been made to the data, what would you like to do?") {
        m_mainMenu << "Add New Publication"
                   << "Remove Publication"
                   << "Checkout publication from library"
                   << "Return publication to library";
        m_exitMenu << "Save changes and exit"
                   << "Cancel and go back to the main menu";
        load();
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
