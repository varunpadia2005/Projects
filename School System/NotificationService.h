#ifndef NOTIFICATIONSERVICE_H
#define NOTIFICATIONSERVICE_H

#include <iostream>
#include <string>
#include "LinkedList.h" // Ensure you have this file for the Notice Board
using namespace std;

class NotificationService {
    LiveNoticeBoard board; 
public:
    // --- THIS IS THE MISSING FUNCTION ---
    static void sendAlert(string recipient, string msg) {
        cout << "\n[>>> ALERT >>>] ---------------------\n";
        cout << "To: " << recipient << "\n";
        cout << "Message: " << msg << "\n";
        cout << "------------------------------------\n";
    }

    // Existing Notice Board functions
    void postNotice() {
        string msg;
        cout << "Enter Notice: "; cin.ignore(); getline(cin, msg);
        board.addNotice(msg);
        cout << "Posted to Live Board.\n";
    }

    void viewBoard() {
        board.viewNotices();
    }
};
#endif