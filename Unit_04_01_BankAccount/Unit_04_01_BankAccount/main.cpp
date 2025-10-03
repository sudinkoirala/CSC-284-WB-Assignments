#include <iostream>
#include "BankAccount.h"

int main() {
    std::cout << "Creating accounts...\n\n";

    BankAccount alice("Alice", 1000.0);
    BankAccount bob("Bob", 500.0);

    std::cout << "Initial account info:\n";
    alice.printAccountInfo();
    bob.printAccountInfo();

    std::cout << "Alice deposits $200\n";
    alice.deposit(200.0);

    std::cout << "Bob withdraws $100\n";
    bob.withdraw(100.0);

    std::cout << "\nUpdated account info:\n";
    alice.printAccountInfo();
    bob.printAccountInfo();

    std::cout << "Total active accounts: " << BankAccount::getTotalAccounts() << "\n\n";

    std::cout << "Entering block scope...\n";
    {
        BankAccount temp("Charlie", 50.0);
        std::cout << "Total active accounts: " << BankAccount::getTotalAccounts() << "\n";
    }
    std::cout << "Leaving block scope...\n";
    std::cout << "Total active accounts after block: " << BankAccount::getTotalAccounts() << "\n\n";

    std::cout << "Alice transfers $250 to Bob...\n";
    alice.transfer(bob, 250.0);

    std::cout << "\nFinal account info:\n";
    alice.printAccountInfo();
    bob.printAccountInfo();

    std::cout << "Exiting program...\n";
    return 0;
}

