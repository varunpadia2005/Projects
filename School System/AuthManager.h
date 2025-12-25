#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "sqlite3.h"
#include "Hash.h" // Ensures we keep the DSA Hashing
#include <string>
#include <iostream>
using namespace std;

class AuthManager {
    AuthCache cache; 
public:
    AuthManager() {
        cache.cacheUser("admin", "admin123"); 
    }

    string login(sqlite3* db) {
        string u, p;
        cout << "\n=== LOGIN ===\nUser: "; cin >> u;
        cout << "Pass: "; cin >> p;

        // 1. Check Cache
        if(cache.quickLogin(u, p)) return "ADMIN"; 

        // 2. Check Database
        string role = "INVALID";
        string sql = "SELECT ROLE FROM USERS WHERE USERNAME='" + u + "' AND PASSWORD='" + p + "';";
        sqlite3_stmt* stmt;
        if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
            if (sqlite3_step(stmt) == SQLITE_ROW) {
                role = string((const char*)sqlite3_column_text(stmt, 0));
                cache.cacheUser(u, p); // Add to cache for next time
            }
        }
        sqlite3_finalize(stmt);
        return role;
    }

    // --- ADDED THIS FUNCTION BACK ---
    void registerUser(sqlite3* db) {
        string u, p, r;
        cout << "\n--- REGISTER NEW USER ---\n";
        cout << "New Username: "; cin >> u;
        cout << "New Password: "; cin >> p;
        cout << "Role (ADMIN/TEACHER/STUDENT): "; cin >> r;
        
        string sql = "INSERT INTO USERS (USERNAME, PASSWORD, ROLE) VALUES ('" + u + "', '" + p + "', '" + r + "');";
        char* errMsg;
        if(sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg) == SQLITE_OK) {
            cout << "User '" << u << "' Registered Successfully!\n";
        } else {
            cout << "Error: " << errMsg << " (Username might be taken)\n";
        }
    }
};
#endif