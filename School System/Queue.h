#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <queue>
using namespace std;

class LibraryWaitlist {
    queue<int> studentQueue;
public:
    void joinWaitlist(int studentID) {
        studentQueue.push(studentID);
        cout << "Student " << studentID << " added to waitlist.\n";
    }

    void processNext() {
        if(studentQueue.empty()) {
            cout << "No one waiting.\n";
        } else {
            cout << "Book allocated to Student ID: " << studentQueue.front() << endl;
            studentQueue.pop();
        }
    }
};
#endif