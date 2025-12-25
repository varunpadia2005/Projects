#include <iostream>
#include <limits>
#include "sqlite3.h"

// Components
#include "DatabaseManager.h"
#include "AuthManager.h"
#include "StudentManager.h"
#include "ResultManager.h"
#include "LibraryManager.h"
#include "NotificationService.h"
#include "AttendanceManager.h"
#include "CourseManager.h"
#include "Stack.h"

using namespace std;

// Helper to prevent infinite loops on bad input
int getChoice() {
    int x; cin >> x;
    if(cin.fail()) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return -1;
    }
    return x;
}

int main() {
    // 1. Initialize System
    DatabaseManager dbManager;
    AuthManager auth;
    StudentManager sm;
    ResultManager rm;
    LibraryManager lm;
    NotificationService ns;
    AttendanceManager am;
    CourseManager cm;
    ActionStack history;

    // 2. Main Loop (Handles Switch User)
    while(true) { 
        cout << "\n================================\n";
        cout << "   SCHOOL MANAGEMENT SYSTEM     \n";
        cout << "================================\n";
        
        // LOGIN SCREEN
        string role = auth.login(dbManager.getDB());

        // ---------------- ADMIN DASHBOARD ----------------
        if(role == "ADMIN") {
            history.push("Admin Login");
            while(true) {
                cout << "\n[ADMIN DASHBOARD]\n";
                cout << "1. Manage Students (Add)\n";
                cout << "2. Manage Results\n";
                cout << "3. Manage Courses\n";
                cout << "4. Library System\n";
                cout << "5. Post Notice\n";
                cout << "6. Register New User (Add User)\n"; // <--- ADDED BACK
                cout << "7. Switch User / Logout\n";           // <--- SWITCH USER
                cout << "Choice: ";
                
                int ch = getChoice();

                if(ch == 1) { sm.addStudent(dbManager.getDB()); history.push("Added Student"); }
                else if(ch == 2) { 
                    cout << "1. Add Result  2. Merit List: ";
                    int sub; cin >> sub;
                    if(sub==1) rm.addResult(dbManager.getDB());
                    else rm.showMeritList(dbManager.getDB());
                }
                else if(ch == 3) { cm.addCourse(dbManager.getDB()); }
                else if(ch == 4) { lm.menu(); }
                else if(ch == 5) { ns.postNotice(); }
                else if(ch == 6) { auth.registerUser(dbManager.getDB()); history.push("Registered User"); } // <--- CALLED HERE
                else if(ch == 7) break; // Breaks inner loop -> Goes back to Login (Switch User)
            }
        } 
        // ---------------- TEACHER DASHBOARD ----------------
        else if(role == "TEACHER") {
            history.push("Teacher Login");
            while(true) {
                cout << "\n[TEACHER DASHBOARD]\n";
                cout << "1. Mark Attendance\n";
                cout << "2. View Merit List\n";
                cout << "3. View Notices\n";
                cout << "4. Switch User / Logout\n";
                cout << "Choice: ";

                int ch = getChoice();
                if(ch == 1) am.mark(dbManager.getDB());
                else if(ch == 2) rm.showMeritList(dbManager.getDB());
                else if(ch == 3) ns.viewBoard();
                else if(ch == 4) break; // Switch User
            }
        }
        // ---------------- STUDENT DASHBOARD ----------------
        else if(role == "STUDENT") {
            history.push("Student Login");
            int myID;
            cout << "Enter your Student ID: "; cin >> myID;

            while(true) {
                cout << "\n[STUDENT DASHBOARD]\n";
                cout << "1. View My Results\n";
                cout << "2. View Notices\n";
                cout << "3. View Courses\n";
                cout << "4. Switch User / Logout\n";
                cout << "Choice: ";

                int ch = getChoice();
                if(ch == 1) rm.viewMyResult(dbManager.getDB(), myID);
                else if(ch == 2) ns.viewBoard();
                else if(ch == 3) cm.viewCourses(dbManager.getDB());
                else if(ch == 4) break; // Switch User
            }
        }
        else {
            cout << "Invalid Login! Try: admin / admin123\n";
        }
    }
    return 0;
}