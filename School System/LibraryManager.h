#ifndef LIBRARYMANAGER_H
#define LIBRARYMANAGER_H

#include "sqlite3.h"
#include "Queue.h" // Changed from DSA_Queue.h
using namespace std;

class LibraryManager {
    LibraryWaitlist waitlist; 
public:
    void menu() {
        int ch;
        cout << "\n[LIBRARY]\n1. Join Waitlist\n2. Process Next Student\nChoice: ";
        cin >> ch;
        if(ch == 1) {
            int id; cout << "Enter Student ID: "; cin >> id;
            waitlist.joinWaitlist(id);
        } else if(ch == 2) {
            waitlist.processNext();
        }
    }
};
#endif