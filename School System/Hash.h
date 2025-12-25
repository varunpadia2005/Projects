#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

class AuthCache {
    unordered_map<string, string> userMap;
public:
    void cacheUser(string user, string pass) {
        userMap[user] = pass;
    }

    bool quickLogin(string user, string pass) {
        if(userMap.find(user) != userMap.end()) {
            return userMap[user] == pass;
        }
        return false;
    }
};
#endif