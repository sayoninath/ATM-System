#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>

class ATM {
private:
    std::unordered_map<std::string, std::pair<std::string, double>> accounts;

    bool authenticate(const std::string& username, const std::string& pin) {
        if (accounts.find(username) != accounts.end() && accounts[username].first == pin) {
            return true;
        }
        return false;
    }

public:
    ATM() {
        //some dummy accounts
        accounts["user1"] = std::make_pair("1234", 1000.0);
        accounts["user2"] = std::make_pair("5678", 2000.0);
        accounts["user3"] = std::make_pair("91011", 3000.0);
    }

    void showMenu() {
        std::cout << "1. Check Balance\n";
        std::cout << "2. Deposit\n";
        std::cout << "3. Withdraw\n";
        std::cout << "4. Exit\n";
    }

    void start() {
        std::string username;
        std::string pin;

        std::cout << "Welcome to the ATM!\n";
        std::cout << "Please enter your username: ";
        std::cin >> username;
        std::cout << "Please enter your PIN: ";
        std::cin >> pin;

        if (authenticate(username, pin)) {
            int choice;
            do {
                showMenu();
                std::cout << "Please choose an option: ";
                std::cin >> choice;

                switch (choice) {
                case 1:
                    checkBalance(username);
                    break;
                case 2:
                    deposit(username);
                    break;
                case 3:
                    withdraw(username);
                    break;
                case 4:
                    std::cout << "Thank you for using the ATM. Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            } while (choice != 4);
        } else {
            std::cout << "Authentication failed. Please try again.\n";
        }
    }

    void checkBalance(const std::string& username) {
        std::cout << "Your current balance is: $" << std::fixed << std::setprecision(2) << accounts[username].second << "\n";
    }

    void deposit(const std::string& username) {
        double amount;
        std::cout << "Enter amount to deposit: ";
        std::cin >> amount;
        if (amount > 0) {
            accounts[username].second += amount;
            std::cout << "Deposit successful. Your new balance is: $" << std::fixed << std::setprecision(2) << accounts[username].second << "\n";
        } else {
            std::cout << "Invalid amount. Please try again.\n";
        }
    }

    void withdraw(const std::string& username) {
        double amount;
        std::cout << "Enter amount to withdraw: ";
        std::cin >> amount;
        if (amount > 0 && amount <= accounts[username].second) {
            accounts[username].second -= amount;
            std::cout << "Withdrawal successful. Your new balance is: $" << std::fixed << std::setprecision(2) << accounts[username].second << "\n";
        } else {
            std::cout << "Invalid amount or insufficient funds. Please try again.\n";
        }
    }
};

int main() {
    ATM atm;
    atm.start();
    return 0;
}
