#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <iostream>
#include "sqlite3.h" 
#include <string>
using namespace std;

class DatabaseManager {
    sqlite3* DB;
public:
    DatabaseManager() {
        if (sqlite3_open("SchoolSystem_Final.db", &DB)) {
            cerr << "DB Error: " << sqlite3_errmsg(DB) << endl;
        } else {
            initializeTables();
        }
    }
    ~DatabaseManager() { sqlite3_close(DB); }

    void initializeTables() {
        const char* sql = R"(
            CREATE TABLE IF NOT EXISTS STUDENTS(ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME TEXT, DEPT TEXT);
            CREATE TABLE IF NOT EXISTS USERS(USERNAME TEXT PRIMARY KEY, PASSWORD TEXT, ROLE TEXT);
            CREATE TABLE IF NOT EXISTS RESULTS(ID INTEGER PRIMARY KEY AUTOINCREMENT, STUDENT_ID INTEGER, MARKS REAL);
            CREATE TABLE IF NOT EXISTS ATTENDANCE(ID INTEGER PRIMARY KEY, STUDENT_ID INTEGER, DATE TEXT, STATUS TEXT);
            CREATE TABLE IF NOT EXISTS COURSES(ID INTEGER PRIMARY KEY AUTOINCREMENT, CODE TEXT, NAME TEXT);
            INSERT OR IGNORE INTO USERS VALUES ('admin', 'admin123', 'ADMIN');
            INSERT OR IGNORE INTO USERS VALUES ('student', 'student123', 'STUDENT');
            INSERT OR IGNORE INTO USERS VALUES ('teacher', 'teacher123', 'TEACHER');
        )";
        sqlite3_exec(DB, sql, NULL, 0, NULL);
    }
    sqlite3* getDB() { return DB; }
};
#endif