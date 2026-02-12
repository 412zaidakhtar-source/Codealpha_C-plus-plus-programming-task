#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

class Transaction {
public:
    string type;
    double amount;
    string details;

    Transaction(string t, double a, string d) : type(t), amount(a), details(d) {}
};

class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNo, double initialBalance = 0) : accountNumber(accNo), balance(initialBalance) {}

    int getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount, "Self Deposit"));
        cout << "Deposited $" << amount << " successfully.\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance! Cannot withdraw $" << amount << ".\n";
            return false;
        }
        balance -= amount;
        history.push_back(Transaction("Withdraw", amount, "Self Withdraw"));
        cout << "Withdrawn $" << amount << " successfully.\n";
        return true;
    }

    bool transfer(Account &to, double amount) {
        if (amount > balance) {
            cout << "Insufficient balance! Cannot transfer $" << amount << ".\n";
            return false;
        }
        balance -= amount;
        to.balance += amount;
        history.push_back(Transaction("Transfer", amount, "To Acc " + toAccountString(to)));
        to.history.push_back(Transaction("Transfer", amount, "From Acc " + toAccountString(*this)));
        cout << "Transferred $" << amount << " to Account " << to.getAccountNumber() << " successfully.\n";
        return true;
    }

    void printTransactions() {
        if (history.empty()) {
            cout << "No transactions yet.\n";
            return;
        }
        cout << "Transaction History for Account " << accountNumber << ":\n";
        cout << left << setw(12) << "Type" << setw(10) << "Amount" << "Details\n";
        cout << "--------------------------------------\n";
        for (auto &t : history) {
            cout << left << setw(12) << t.type << setw(10) << t.amount << t.details << endl;
        }
    }

    void showInfo() {
        cout << "Account Number: " << accountNumber << "\nBalance: $" << balance << endl;
    }

private:
    string toAccountString(Account &a) { return to_string(a.getAccountNumber()); }
};

class Customer {
private:
    string name;
    int customerID;
    vector<Account> accounts;

public:
    Customer(string n, int id) : name(n), customerID(id) {}

    void addAccount(int accNo, double initialBalance = 0) {
        accounts.push_back(Account(accNo, initialBalance));
        cout << "Account " << accNo << " created for " << name << ".\n";
    }

    Account* getAccount(int accNo) {
        for (auto &a : accounts) {
            if (a.getAccountNumber() == accNo) return &a;
        }
        return nullptr;
    }

    int getCustomerID() { return customerID; }

    void showCustomerInfo() {
        cout << "Customer Name: " << name << "\nCustomer ID: " << customerID << endl;
        for (auto &a : accounts) {
            a.showInfo();
            cout << endl;
        }
    }

    vector<Account>& getAccounts() { return accounts; }
};

Customer* findCustomer(vector<Customer> &customers, int customerID) {
    for (auto &c : customers) {
        if (c.getCustomerID() == customerID) return &c;
    }
    return nullptr;
}

Account* findAccount(vector<Customer> &customers, int accountNo) {
    for (auto &c : customers) {
        Account* a = c.getAccount(accountNo);
        if (a) return a;
    }
    return nullptr;
}

// Input validation helpers
int getValidatedInt(string prompt, int minVal = numeric_limits<int>::min(), int maxVal = numeric_limits<int>::max()) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= minVal && val <= maxVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        } else {
            cout << "Invalid input! Please enter a number between " << minVal << " and " << maxVal << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double getValidatedDouble(string prompt, double minVal = 0) {
    double val;
    while (true) {
        cout << prompt;
        if (cin >> val && val >= minVal) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return val;
        } else {
            cout << "Invalid input! Please enter a number greater than or equal to " << minVal << ".\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string getNonEmptyString(string prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "Input cannot be empty! Please try again.\n";
    }
}

void bankingMenu(vector<Customer> &customers) {
    int choice;
    do {
        cout << "\n--- Banking System Menu ---\n";
        cout << "1. Create Customer\n";
        cout << "2. Create Account\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Transfer\n";
        cout << "6. Show Account Info\n";
        cout << "7. Show Transaction History\n";
        cout << "0. Exit\n";

        choice = getValidatedInt("Enter choice: ", 0, 7);

        switch(choice) {
            case 1: {
                string name = getNonEmptyString("Enter Customer Name: ");
                int id = getValidatedInt("Enter Customer ID: ", 1);
                if (findCustomer(customers, id)) {
                    cout << "Customer ID already exists! Try again.\n";
                } else {
                    customers.push_back(Customer(name, id));
                    cout << "Customer created successfully.\n";
                }
                break;
            }
            case 2: {
                int id = getValidatedInt("Enter Customer ID to create account: ", 1);
                Customer* cust = findCustomer(customers, id);
                if (!cust) {
                    cout << "Customer not found! Please enter a valid Customer ID.\n";
                    break;
                }
                int accNo = getValidatedInt("Enter Account Number: ", 1);
                if (findAccount(customers, accNo)) {
                    cout << "Account Number already exists! Try again.\n";
                    break;
                }
                double initBal = getValidatedDouble("Enter Initial Balance: ", 0);
                cust->addAccount(accNo, initBal);
                break;
            }
            case 3: {
                int accNo = getValidatedInt("Enter Account Number: ", 1);
                Account* acc = findAccount(customers, accNo);
                if (!acc) {
                    cout << "Account not found! Enter a valid account number.\n";
                    break;
                }
                double amount = getValidatedDouble("Enter Amount to Deposit: ", 0.01);
                acc->deposit(amount);
                break;
            }
            case 4: {
                int accNo = getValidatedInt("Enter Account Number: ", 1);
                Account* acc = findAccount(customers, accNo);
                if (!acc) {
                    cout << "Account not found! Enter a valid account number.\n";
                    break;
                }
                double amount = getValidatedDouble("Enter Amount to Withdraw: ", 0.01);
                acc->withdraw(amount);
                break;
            }
            case 5: {
                int fromAccNo = getValidatedInt("Enter Source Account Number: ", 1);
                int toAccNo = getValidatedInt("Enter Destination Account Number: ", 1);
                double amount = getValidatedDouble("Enter Amount to Transfer: ", 0.01);

                Account* fromAcc = findAccount(customers, fromAccNo);
                Account* toAcc = findAccount(customers, toAccNo);

                if (!fromAcc) {
                    cout << "Source account not found! Please enter a valid account number.\n";
                    break;
                }
                if (!toAcc) {
                    cout << "Destination account not found! Please enter a valid account number.\n";
                    break;
                }
                fromAcc->transfer(*toAcc, amount);
                break;
            }
            case 6: {
                int accNo = getValidatedInt("Enter Account Number: ", 1);
                Account* acc = findAccount(customers, accNo);
                if (!acc) {
                    cout << "Account not found! Enter a valid account number.\n";
                    break;
                }
                acc->showInfo();
                break;
            }
            case 7: {
                int accNo = getValidatedInt("Enter Account Number: ", 1);
                Account* acc = findAccount(customers, accNo);
                if (!acc) {
                    cout << "Account not found! Enter a valid account number.\n";
                    break;
                }
                acc->printTransactions();
                break;
            }
            case 0: cout << "Exiting...\n"; break;
        }

    } while(choice != 0);
}

int main() {
    vector<Customer> customers;
    bankingMenu(customers);
    return 0;
}
