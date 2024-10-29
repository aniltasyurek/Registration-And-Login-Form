#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class temp {
    string userName, email, password;
    string searchName, searchPass, searchEmail;
    fstream file;
public:
    void login();
    void signUp();
    void forget();
};

int main() {
    char choice;
    temp obj;

    do {
        cout << "1- Login" << endl;
        cout << "2- Sign-Up" << endl;
        cout << "3- Forgot Password" << endl;
        cout << "4- Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;
        cin.ignore(); // Clear the newline left in the buffer

        switch (choice) {
        case '1':
            obj.login();
            break;

        case '2':
            obj.signUp();
            break;

        case '3':
            obj.forget();
            break;

        case '4':
            cout << "Exiting..." << endl;
            return 0;

        default:
            cout << "Invalid Selection...!" << endl;
        }
    } while (choice != '4'); // Loop until user chooses to exit

    return 0;
}

void temp::signUp() {
    cout << "Enter Your Username: " << endl;
    getline(cin, userName);
    cout << "Enter Your Email Address: " << endl;
    getline(cin, email);
    cout << "Enter Your Password: " << endl;
    getline(cin, password);

    file.open("loginData.txt", ios::out | ios::app);
    file << userName << "*" << email << "*" << password << endl;
    file.close();
}

void temp::login() {
    ifstream file;

    cout << "-----LOGIN-----" << endl;
    cout << "Enter Your Username: " << endl;
    getline(cin, searchName);
    cout << "Enter Your Password: " << endl;
    getline(cin, searchPass);

    file.open("loginData.txt", ios::in);

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    bool loginSuccess = false; // Track if login is successful

    while (getline(file, userName, '*') &&
        getline(file, email, '*') &&
        getline(file, password)) {

        if (userName == searchName && password == searchPass) {
            cout << "Account Login Successful...!" << endl;
            cout << "Username: " << userName << endl;
            cout << "Email: " << email << endl;
            loginSuccess = true;
            break; // Exit the loop upon successful login
        }
    }

    if (!loginSuccess) {
        cout << "Login failed: Incorrect username or password." << endl;
    }

    file.close();
}

void temp::forget() {
    ifstream file;

    cout << "\nEnter Your Username: ";
    getline(cin, searchName);
    cout << "Enter Your Email Address: ";
    getline(cin, searchEmail);

    file.open("loginData.txt", ios::in);

    if (!file) {
        cout << "Error opening file!" << endl;
        return;
    }

    bool accountFound = false;

    while (getline(file, userName, '*') &&
        getline(file, email, '*') &&
        getline(file, password)) {

        if (userName == searchName && email == searchEmail) {
            cout << "Account Found...!" << endl;
            cout << "Your Password: " << password << endl;
            accountFound = true;
            break; // Exit the loop upon finding the account
        }
    }

    if (!accountFound) {
        cout << "Not Found...!\n";
    }

    file.close();
}
