#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

bool isValidUsername(const string& username)
{
    if (username.length() < 4)
        return false;

    for (char c : username)
    {
        if (!isalnum(c))
            return false;
    }
    return true;
}

bool isValidPassword(const string& password)
{
    if (password.length() < 6)
        return false;

    bool hasDigit = false;
    for (char c : password)
    {
        if (isdigit(c))
            hasDigit = true;
    }
    return hasDigit;
}

bool userExists(const string& username)
{
    ifstream file("users.txt");
    string fileUser, filePass;

    while (file >> fileUser >> filePass)
    {
        if (fileUser == username)
            return true;
    }
    return false;
}

void registerUser()
{
    string username, password;

    while (true)
    {
        cout << "Enter username: ";
        cin >> username;

        if (!isValidUsername(username))
        {
            cout << "Invalid username. Must be at least 4 characters and contain only letters and numbers.\n";
            continue;
        }

        if (userExists(username))
        {
            cout << "Username already exists. Try another one.\n";
            continue;
        }
        break;
    }

    while (true)
    {
        cout << "Enter password: ";
        cin >> password;

        if (!isValidPassword(password))
        {
            cout << "Invalid password. Must be at least 6 characters and contain at least one digit.\n";
            continue;
        }
        break;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();

    cout << "Registration successful.\n";
}

void loginUser()
{
    string username, password;
    bool found = false;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    string fileUser, filePass;

    while (file >> fileUser >> filePass)
    {
        if (fileUser == username && filePass == password)
        {
            found = true;
            break;
        }
    }
    file.close();

    if (found)
        cout << "Login successful. Welcome " << username << ".\n";
    else
        cout << "Invalid username or password.\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n--- Login and Registration System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
