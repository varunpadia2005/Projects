#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include <fstream>
#include "sqlite3.h"

using namespace std;

class ReportManager {
public:
    void exportCSV(sqlite3* db) {
        ofstream file("SchoolData.csv");
        file << "ID, Name, Dept\n";
        
        sqlite3_stmt* stmt;
        sqlite3_prepare_v2(db, "SELECT * FROM STUDENTS;", -1, &stmt, NULL);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            file << sqlite3_column_text(stmt, 0) << "," << sqlite3_column_text(stmt, 1) << "," << sqlite3_column_text(stmt, 2) << "\n";
        }
        sqlite3_finalize(stmt);
        file.close();
        cout << "Exported to SchoolData.csv\n";
    }
};

#endif