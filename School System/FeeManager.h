#ifndef FEEMANAGER_H
#define FEEMANAGER_H

#include <iostream>
#include "sqlite3.h"

using namespace std;

class FeeManager {
public:
    void setFee(sqlite3* db) {
        int id; double total;
        cout << "Student ID: "; cin >> id;
        cout << "Total Fee: "; cin >> total;
        
        string sql = "INSERT OR REPLACE INTO FEES (STUDENT_ID, TOTAL_FEE, PAID_AMOUNT, BALANCE) VALUES (" + to_string(id) + ", " + to_string(total) + ", 0, " + to_string(total) + ");";
        sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
        cout << "Fee Structure Set.\n";
    }

    void payInstallment(sqlite3* db) {
        int id; double amount;
        cout << "Student ID: "; cin >> id;
        cout << "Amount Paying: "; cin >> amount;

        string sql = "UPDATE FEES SET PAID_AMOUNT = PAID_AMOUNT + " + to_string(amount) + ", BALANCE = BALANCE - " + to_string(amount) + " WHERE STUDENT_ID=" + to_string(id) + ";";
        sqlite3_exec(db, sql.c_str(), NULL, 0, NULL);
        
        string viewSql = "SELECT BALANCE FROM FEES WHERE STUDENT_ID=" + to_string(id);
        sqlite3_exec(db, viewSql.c_str(), [](void*, int, char** argv, char**) { 
            cout << "Remaining Balance: " << argv[0] << endl; return 0; 
        }, NULL, NULL);
    }
};

#endif