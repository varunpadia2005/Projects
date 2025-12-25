#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ActionStack {
    vector<string> stack; // Vector acting as Stack
public:
    void push(string action) {
        stack.push_back(action);
    }

    void viewHistory() {
        cout << "\n--- SESSION HISTORY (Stack LIFO) ---\n";
        if(stack.empty()) { cout << "No actions yet.\n"; return; }
        
        for(int i = stack.size()-1; i >= 0; i--) {
            cout << "Action: " << stack[i] << endl;
        }
    }
};
#endif