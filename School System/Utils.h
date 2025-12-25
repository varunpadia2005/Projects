#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <ctime>
using namespace std;

class Utils {
public:
    static string getCurrentDate() {
        time_t now = time(0);
        char buf[80];
        strftime(buf, sizeof(buf), "%Y-%m-%d", localtime(&now));
        return string(buf);
    }
};

#endif