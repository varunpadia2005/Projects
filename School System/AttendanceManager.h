#ifndef ATTENDANCEMANAGER_H
#define ATTENDANCEMANAGER_H

#include "sqlite3.h"
#include "Utils.h"
#include "NotificationService.h" // <--- Essential include
#include <iostream>
#include <string>

using namespace std;

class AttendanceManager {
public:
    void mark(sqlite3* db) {
        int id; 
        string status;
        
        cout << "Enter Student ID: "; cin >> id; 
        cout << "Enter Status (P/A): "; cin >> status;

        string date = Utils::getCurrentDate();
        string sql = "INSERT INTO ATTENDANCE VALUES (" + to_string(id) + ", " + to_string(id) + ", '" + date + "', '" + status + "');";
        
        sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
        cout << "Attendance Marked.\n";

        // Logic to trigger the alert if Absent
        if (status == "A" || status == "a") {
            NotificationService::sendAlert("Parent (ID: " + to_string(id) + ")", "Your child is ABSENT today.");
        }
    }
};
#endif