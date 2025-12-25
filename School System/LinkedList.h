#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

struct NoticeNode {
    string msg;
    NoticeNode* next;
    NoticeNode(string m) : msg(m), next(nullptr) {}
};

class LiveNoticeBoard {
    NoticeNode* head;
public:
    LiveNoticeBoard() : head(nullptr) {}

    void addNotice(string msg) {
        NoticeNode* newNode = new NoticeNode(msg);
        newNode->next = head;
        head = newNode; // Insert at front (LIFO behavior for notices)
    }

    void viewNotices() {
        cout << "\n--- LIVE NOTICES (Linked List) ---\n";
        NoticeNode* temp = head;
        while(temp) {
            cout << ">> " << temp->msg << endl;
            temp = temp->next;
        }
    }
};
#endif