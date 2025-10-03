#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

class BankAccount {
private:
    std::string accountHolder;
    int accountNumber;
    double balance;

    // Static members
    static int totalAccounts;
    static int nextAccountNumber;

public:
    // Constructors and destructor
    BankAccount();                                    // Default: "Unknown", 0.0
    BankAccount(const std::string& name, double initialBalance);
    ~BankAccount();

    // Disable copy and move to avoid duplicate account numbers
    BankAccount(const BankAccount&) = delete;
    BankAccount& operator=(const BankAccount&) = delete;
    BankAccount(BankAccount&&) = delete;
    BankAccount& operator=(BankAccount&&) = delete;

    // Accessors
    std::string getAccountHolder() const;
    int getAccountNumber() const;
    double getBalance() const;

    // Member functions
    bool deposit(double amount);
    bool withdraw(double amount);
    void printAccountInfo() const;
    bool transfer(BankAccount& toAccount, double amount);

    // Static function
    static int getTotalAccounts();
};

#endif // BANKACCOUNT_H

