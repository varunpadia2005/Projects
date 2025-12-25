#ifndef COURSEMANAGER_H
#define COURSEMANAGER_H

#include "sqlite3.h"
#include <iostream>
#include <string>
using namespace std;

class CourseManager {
public:
    // ADMIN ONLY
    void addCourse(sqlite3* db) {
        string code, name;
        cout << "Course Code (e.g., CS101): "; cin >> code;
        cout << "Course Name: "; cin.ignore(); getline(cin, name);
        
        string sql = "INSERT INTO COURSES (CODE, NAME) VALUES ('" + code + "', '" + name + "');";
        sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
        cout << "Course Added.\n";
    }

    // OPEN TO ALL
    void viewCourses(sqlite3* db) {
        cout << "\n--- COURSE LIST ---\n";
        string sql = "SELECT * FROM COURSES;";
        sqlite3_exec(db, sql.c_str(), [](void*, int, char** argv, char**) {
            cout << "[" << argv[1] << "] " << argv[2] << endl;
            return 0;
        }, NULL, NULL);
    }
};
#endif