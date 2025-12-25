#ifndef RESULTMANAGER_H
#define RESULTMANAGER_H

#include "sqlite3.h"
#include "Sort.h"
#include <vector>
using namespace std;

class ResultManager {
    MeritSorter sorter; 
public:
    // ADMIN ONLY
    void addResult(sqlite3* db) {
        int id; double m;
        cout << "ID: "; cin >> id;
        cout << "Marks: "; cin >> m;
        string sql = "INSERT INTO RESULTS (STUDENT_ID, MARKS) VALUES (" + to_string(id) + ", " + to_string(m) + ");";
        sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
        cout << "Saved.\n";
    }

    // ADMIN/TEACHER
    void showMeritList(sqlite3* db) {
        vector<StudentMark> results;
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, "SELECT STUDENT_ID, MARKS FROM RESULTS;", -1, &stmt, NULL) == SQLITE_OK) {
            while (sqlite3_step(stmt) == SQLITE_ROW) {
                results.push_back({
                    sqlite3_column_int(stmt, 0),
                    sqlite3_column_double(stmt, 1)
                });
            }
        }
        sqlite3_finalize(stmt);
        sorter.generateMeritList(results);
    }

    // STUDENT ONLY
    void viewMyResult(sqlite3* db, int myID) {
        cout << "\n--- MY RESULTS ---\n";
        string sql = "SELECT MARKS FROM RESULTS WHERE STUDENT_ID=" + to_string(myID) + ";";
        sqlite3_exec(db, sql.c_str(), [](void*, int, char** argv, char**) {
            cout << "Marks: " << argv[0] << endl;
            return 0;
        }, NULL, NULL);
    }
};
#endif