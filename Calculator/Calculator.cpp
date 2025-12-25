#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

// --- Structures ---
struct CalculationRecord {
    string equation;
    double result;
};

// --- Calculator Class ---
class AdvancedCalculator {
private:
    vector<CalculationRecord> history;
    double lastResult;
    bool hasLastResult;
    const double PI = 3.14159265358979323846;

public:
    AdvancedCalculator() : lastResult(0.0), hasLastResult(false) {}

    // 1. Basic Operations
    double add(double a, double b) { return a + b; }
    double subtract(double a, double b) { return a - b; }
    double multiply(double a, double b) { return a * b; }
    
    double divide(double a, double b) {
        if (b == 0) throw runtime_error("Error: Division by zero.");
        return a / b;
    }

    // 2. Advanced Operations
    double power(double base, double exp) { return pow(base, exp); }
    
    double squareRoot(double n) {
        if (n < 0) throw runtime_error("Error: Negative input for Square Root.");
        return sqrt(n);
    }

    // Trigonometry (takes degrees, converts to radians for cmath)
    double sine(double deg) { return sin(deg * PI / 180.0); }
    double cosine(double deg) { return cos(deg * PI / 180.0); }
    double tangent(double deg) { return tan(deg * PI / 180.0); }

    // 3. Memory & History Management
    void addToHistory(string eq, double res) {
        history.push_back({eq, res});
        lastResult = res;
        hasLastResult = true;
        
        // Keep only last 10 records to save memory
        if (history.size() > 10) {
            history.erase(history.begin());
        }
    }

    void showHistory() {
        if (history.empty()) {
            cout << "\n[!] Memory is empty.\n";
            return;
        }
        cout << "\n--- Calculation History (Last " << history.size() << ") ---\n";
        for (size_t i = 0; i < history.size(); ++i) {
            cout << i + 1 << ". " << history[i].equation << " = " << history[i].result << endl;
        }
        cout << "------------------------------------------\n";
    }

    void clearHistory() {
        history.clear();
        hasLastResult = false;
        cout << "\n[!] Memory Cleared.\n";
    }

    double getLastResult() {
        return hasLastResult ? lastResult : 0.0;
    }
    
    bool hasPreviousResult() {
        return hasLastResult;
    }
};

// --- Helper for Input Validation ---
double getNumber(string prompt) {
    double num;
    while (true) {
        cout << prompt;
        if (cin >> num) {
            return num;
        } else {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// --- Main Program ---
int main() {
    AdvancedCalculator calc;
    int choice;
    double num1, num2, result;
    bool useAns = false;

    cout << "====================================\n";
    cout << "   C++ ADVANCED CALCULATOR v1.0    \n";
    cout << "====================================\n";

    do {
        cout << "\nSELECT OPERATION:\n";
        cout << "1. Addition (+)\n";
        cout << "2. Subtraction (-)\n";
        cout << "3. Multiplication (*)\n";
        cout << "4. Division (/)\n";
        cout << "5. Power (x^y)\n";
        cout << "6. Square Root (sqrt)\n";
        cout << "7. Sine (sin)\n";
        cout << "8. Cosine (cos)\n";
        cout << "9. Tangent (tan)\n";
        cout << "10. View History\n";
        cout << "11. Clear History\n";
        cout << "0. Exit\n";
        cout << "------------------------------------\n";
        
        // Show 'Ans' capability if available
        if (calc.hasPreviousResult()) {
            cout << "NOTE: Enter '99' to use previous result (" << calc.getLastResult() << ") as first number.\n";
        }
        
        cout << "Enter Choice: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 0) break;
        if (choice == 10) { calc.showHistory(); continue; }
        if (choice == 11) { calc.clearHistory(); continue; }

        try {
            // Handle "Ans" or new input for first number
            string eqString = "";
            
            // Logic to determine if we need 1 or 2 numbers
            bool needsTwoArgs = (choice >= 1 && choice <= 5);
            bool needsOneArg = (choice >= 6 && choice <= 9);

            if (needsTwoArgs || needsOneArg) {
                // Ask for first number (or use Ans)
                cout << "Enter first number (or 99 for Ans): ";
                string input;
                cin >> input;
                
                if (input == "99" && calc.hasPreviousResult()) {
                    num1 = calc.getLastResult();
                    cout << "Using Ans: " << num1 << endl;
                } else {
                    try {
                        num1 = stod(input);
                    } catch (...) {
                        cout << "Invalid number. Resetting.\n";
                        continue;
                    }
                }
            }

            // Get second number if needed
            if (needsTwoArgs) {
                num2 = getNumber("Enter second number: ");
            }

            // Perform Calculation
            switch (choice) {
                case 1:
                    result = calc.add(num1, num2);
                    eqString = to_string(num1) + " + " + to_string(num2);
                    break;
                case 2:
                    result = calc.subtract(num1, num2);
                    eqString = to_string(num1) + " - " + to_string(num2);
                    break;
                case 3:
                    result = calc.multiply(num1, num2);
                    eqString = to_string(num1) + " * " + to_string(num2);
                    break;
                case 4:
                    result = calc.divide(num1, num2);
                    eqString = to_string(num1) + " / " + to_string(num2);
                    break;
                case 5:
                    result = calc.power(num1, num2);
                    eqString = to_string(num1) + "^" + to_string(num2);
                    break;
                case 6:
                    result = calc.squareRoot(num1);
                    eqString = "sqrt(" + to_string(num1) + ")";
                    break;
                case 7:
                    result = calc.sine(num1);
                    eqString = "sin(" + to_string(num1) + ")";
                    break;
                case 8:
                    result = calc.cosine(num1);
                    eqString = "cos(" + to_string(num1) + ")";
                    break;
                case 9:
                    result = calc.tangent(num1);
                    eqString = "tan(" + to_string(num1) + ")";
                    break;
                default:
                    cout << "Invalid choice.\n";
                    continue;
            }

            // Output and Store
            cout << "\n>>> Result: " << result << "\n";
            calc.addToHistory(eqString, result);

        } catch (const exception& e) {
            cout << "\n[Error]: " << e.what() << "\n";
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}