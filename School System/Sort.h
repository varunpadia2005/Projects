#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct StudentMark {
    int id;
    double marks;
};

class MeritSorter {
    int partition(vector<StudentMark>& arr, int low, int high) {
        double pivot = arr[high].marks;
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j].marks > pivot) { // Descending Order
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    void quickSort(vector<StudentMark>& arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

public:
    void generateMeritList(vector<StudentMark>& data) {
        if (data.empty()) { cout << "No data to sort.\n"; return; }
        
        quickSort(data, 0, data.size() - 1);

        cout << "\n--- MERIT LIST (QuickSort) ---\n";
        cout << "Rank | ID | Marks\n";
        for (size_t i = 0; i < data.size(); i++) {
            cout << "  " << (i + 1) << "  | " << data[i].id << " | " << data[i].marks << endl;
        }
    }
};
#endif