#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class StudentManager {
public:
    void addStudent(sqlite3* db) {
        string name, dept;
        cout << "Name: "; cin.ignore(); getline(cin, name);
        cout << "Dept: "; getline(cin, dept);

        string sql = "INSERT INTO STUDENTS (NAME, DEPT) VALUES ('" + name + "', '" + dept + "');";
        sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
        cout << "Student Added.\n";
    }

    void viewStudents(sqlite3* db) {
        cout << "\n--- STUDENTS ---\n";
        sqlite3_exec(db, "SELECT * FROM STUDENTS;", [](void*, int, char** argv, char**) {
            cout << "ID: " << argv[0] << " | Name: " << argv[1] << " | Dept: " << argv[2] << endl;
            return 0;
        }, NULL, NULL);
    }
};

#endif