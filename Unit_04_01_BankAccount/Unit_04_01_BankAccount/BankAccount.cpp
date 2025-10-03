#include "BankAccount.h"
#include <iostream>
#include <iomanip>

// Initialize static members
int BankAccount::totalAccounts = 0;
int BankAccount::nextAccountNumber = 1001;

// Default constructor
BankAccount::BankAccount()
    : accountHolder("Unknown"), accountNumber(nextAccountNumber++), balance(0.0) {
    ++totalAccounts;
}

// Parameterized constructor
BankAccount::BankAccount(const std::string& name, double initialBalance)
    : accountHolder(name), accountNumber(nextAccountNumber++), balance(0.0) {
    if (initialBalance < 0.0) {
        std::cout << "Initial balance cannot be negative. Setting to 0.0\n";
        balance = 0.0;
    } else {
        balance = initialBalance;
    }
    ++totalAccounts;
}

// Destructor
BankAccount::~BankAccount() {
    --totalAccounts;
    std::cout << "Destructor called for account " << accountNumber << "\n";
}

// Accessors
std::string BankAccount::getAccountHolder() const { return accountHolder; }
int BankAccount::getAccountNumber() const { return accountNumber; }
double BankAccount::getBalance() const { return balance; }

// deposit
bool BankAccount::deposit(double amount) {
    if (amount <= 0.0) {
        std::cout << "Deposit amount must be positive.\n";
        return false;
    }
    balance += amount;
    return true;
}

// withdraw
bool BankAccount::withdraw(double amount) {
    if (amount <= 0.0) {
        std::cout << "Withdrawal amount must be positive.\n";
        return false;
    }
    if (amount > balance) {
        std::cout << "Insufficient funds. Withdrawal denied.\n";
        return false;
    }
    balance -= amount;
    return true;
}

// printAccountInfo
void BankAccount::printAccountInfo() const {
    std::cout << "Account Holder: " << accountHolder << "\n"
              << "Account Number: " << accountNumber << "\n"
              << "Balance: $" << std::fixed << std::setprecision(2) << balance << "\n\n";
}

// transfer
bool BankAccount::transfer(BankAccount& toAccount, double amount) {
    if (this == &toAccount) {
        std::cout << "Cannot transfer to the same account.\n";
        return false;
    }
    if (amount <= 0.0) {
        std::cout << "Transfer amount must be positive.\n";
        return false;
    }
    if (amount > balance) {
        std::cout << "Insufficient funds. Transfer denied.\n";
        return false;
    }

    // Perform transfer
    balance -= amount;
    toAccount.balance += amount;

    std::cout << "Transferred $" << std::fixed << std::setprecision(2)
              << amount << " from " << accountHolder
              << " to " << toAccount.accountHolder << "\n";
    return true;
}

// static
int BankAccount::getTotalAccounts() {
    return totalAccounts;
}

