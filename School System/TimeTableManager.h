#ifndef TIMETABLEMANAGER_H
#define TIMETABLEMANAGER_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class TimeTableManager {
public:
    void assignClass(sqlite3* db) {
        int tid; string day, slot, sub;
        cout << "Teacher ID: "; cin >> tid;
        cout << "Day: "; cin >> day;
        cout << "Slot: "; cin >> slot;
        cout << "Subject: "; cin >> sub;

        string sql = "INSERT INTO TIMETABLE (TEACHER_ID, DAY, SLOT, SUBJECT) VALUES (" + to_string(tid) + ", '" + day + "', '" + slot + "', '" + sub + "');";
        char* errMsg;
        if(sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg) != SQLITE_OK) {
            cerr << "Conflict! Teacher already busy.\n";
        } else {
            cout << "Schedule Assigned.\n";
        }
    }
};

#endif