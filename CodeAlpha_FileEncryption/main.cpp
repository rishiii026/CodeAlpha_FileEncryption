#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// ANSI Color Codes
#define RESET       "\033[0m"
#define BOLDWHITE   "\033[1;37m"
#define GREEN       "\033[0;32m"
#define RED         "\033[0;31m"
#define YELLOW      "\033[0;33m"
#define CYAN        "\033[0;36m"

// ---------------- Title Display ----------------
void showTitle() {
    cout << BOLDWHITE << "=============================================\n";
    cout << "        FILE ENCRYPTION/DECRYPTION TOOL      \n";
    cout << "               Developed by Rishi            \n";
    cout << "=============================================" << RESET << "\n\n";
}

// ---------------- Caesar Cipher Logic ----------------
string caesarEncrypt(const string& text, int shift) {
    string result = "";
    for (char c : text) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            result += (c - base + shift) % 26 + base;
        } else {
            result += c;
        }
    }
    return result;
}

string caesarDecrypt(const string& text, int shift) {
    return caesarEncrypt(text, 26 - shift);
}

// ---------------- Timestamp Generator ----------------
string getTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y%m%d_%H%M%S", ltm);
    return string(buffer);
}

// ---------------- Activity Logger ----------------
void logActivity(const string& activity, const string& filename) {
    ofstream log("activity_log.txt", ios::app);
    log << "[" << getTimestamp() << "] " << activity << ": " << filename << "\n";
    log.close();
}

// ---------------- Login System with Retry ----------------
bool login() {
    const string correctUser = "Rishi";
    const string correctPass = "Rishiii9126";
    string username, password;

    int attempts = 3;
    while (attempts--) {
        cout << CYAN << "LOGIN REQUIRED (" << (3 - attempts) << "/3)\n" << RESET;
        cout << CYAN << "Username: " << RESET;
        getline(cin, username);
        cout << CYAN << "Password: " << RESET;
        getline(cin, password);

        if (username == correctUser && password == correctPass) {
            cout << GREEN << "\nLogin successful.\n\n" << RESET;
            return true;
        } else {
            cout << RED << "Invalid credentials. " << (attempts ? "Try again.\n\n" : "No attempts left.\n") << RESET;
        }
    }
    return false;
}

// ---------------- Main Application ----------------
int main() {
    showTitle();

    if (!login()) {
        cout << RED << "Access denied. Exiting program.\n" << RESET;
        return 0;
    }

    string inputFile, outputFile, line, password;
    int choice;

    cout << CYAN << "Enter input file name (e.g., input.txt): " << RESET;
    getline(cin, inputFile);

    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << RED << "Error: Could not open input file.\n" << RESET;
        return 1;
    }

    cout << CYAN << "\nSelect Operation:\n";
    cout << "1. Encrypt File\n";
    cout << "2. Decrypt File\n";
    cout << "Enter choice (1 or 2): " << RESET;
    cin >> choice;
    cin.ignore();

    if (choice != 1 && choice != 2) {
        cerr << RED << "Invalid operation. Exiting.\n" << RESET;
        return 1;
    }

    cout << CYAN << "Enter password to generate encryption key: " << RESET;
    getline(cin, password);

    int shift = 0;
    for (char c : password) shift += c;
    shift %= 26;

    string timestamp = getTimestamp();
    outputFile = (choice == 1 ? "encrypted_" : "decrypted_") + timestamp + ".txt";
    ofstream outFile(outputFile);

    if (!outFile) {
        cerr << RED << "Error: Could not create output file.\n" << RESET;
        return 1;
    }

    cout << YELLOW << "\nProcessing file...\n" << RESET;

    int lineCount = 0;
    while (getline(inFile, line)) {
        string result = (choice == 1) ? caesarEncrypt(line, shift) : caesarDecrypt(line, shift);
        outFile << result << "\n";
        if (lineCount < 3) {
            cout << "Line " << (lineCount + 1) << ": " << result << "\n";
        }
        lineCount++;
    }

    inFile.close();
    outFile.close();

    string activity = (choice == 1) ? "Encrypted" : "Decrypted";
    logActivity(activity, outputFile);

    cout << GREEN << "\nOperation completed successfully.\n" << RESET;
    cout << GREEN << "Output saved to: " << outputFile << "\n";
    cout << GREEN << "Activity logged in: activity_log.txt\n" << RESET;

    return 0;
}


