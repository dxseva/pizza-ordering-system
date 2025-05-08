#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Pizza {
    string name;
    double price;
};

struct Customer {
    string firstName;
    string lastName;
    string address;
    string phoneNumber;
};

string phoneNumberChecker() {
    const string code = "+998";
    string input;
    bool isValid;

    do {
        isValid = true;
        cout << "Please, enter the phone number: \n";
        cout << code;
        cin >> input;

        if (input.length() != 9) {
            cout << "Reenter the phone number! It must consist of 9 digits!" << endl;
            isValid = false;
            continue;
        }

        for (int i = 0; i < input.length(); i++) {
            if (input[i] < '0' || input[i] > '9') {
                cout << "Phone number must contain only digits!" << endl;
                isValid = false;
                break;
            }
        }
    } while (!isValid);

    return code + input;
}

class PizzaOrder {
private:
    vector<Customer> customerDatabase;
    Customer customer;
    vector<Pizza> cart;

    vector<pair<string, double>> menu = {
        {"Pepperoni", 100000},
        {"Four Cheese", 90000},
        {"Meat", 120000},
        {"Combo", 130000}
    };

    double calculateTotal() {
        double total = 0;
        for (const auto& pizza : cart) {
            total += pizza.price;
        }
        return total;
    }

    double calculateCashback(double total) {
        return total * 0.03;
    }

    void showCart() {
        cout << "\nCurrent Cart:\n";
        if (cart.empty()) {
            cout << "Cart is empty.\n";
            return;
        }
        double total = calculateTotal();
        double cashback = calculateCashback(total);
        for (size_t i = 0; i < cart.size(); ++i) {
            cout << i + 1 << ". " << cart[i].name << " - " << fixed << setprecision(2)
                << cart[i].price << " so'm\n";
        }
        cout << "Total: " << fixed << setprecision(2) << total << " so'm\n";
        cout << "Cashback: " << fixed << setprecision(2) << cashback << " so'm\n";
    }

    Customer* findCustomerByPhoneNumber(const string& phoneNumber) {
        for (auto& c : customerDatabase) {
            if (c.phoneNumber == phoneNumber) {
                return &c;
            }
        }
        return nullptr;
    }

    bool loadCustomerFromFile(const string& phoneNumber) {
        ifstream orderFile("order.txt");
        if (!orderFile.is_open()) {
            cout << "No saved orders found.\n";
            return false;
        }

        string line, savedPhone, firstName, lastName, address;
        while (getline(orderFile, line)) {
            if (line.find("Phone Number:") != string::npos) {
                savedPhone = line.substr(line.find(":") + 2);
                if (savedPhone == phoneNumber) {
                    getline(orderFile, line); 
                    firstName = line.substr(line.find(":") + 2);
                    getline(orderFile, line);
                    lastName = line.substr(line.find(":") + 2);
                    getline(orderFile, line);
                    address = line.substr(line.find(":") + 2);

                    customer = { firstName, lastName, address, savedPhone };
                    customerDatabase.push_back(customer);
                    cout << "Welcome back, " << firstName << "!\n";
                    return true;
                }
            }
        }

        orderFile.close();
        return false;
    }

    void saveCustomerToFile() {
        ofstream orderFile("order.txt");
        if (!orderFile) {
            cerr << "Error saving customer to file.\n";
            return;
        }

        orderFile << "Customer Information:\n";
        orderFile << "Phone Number: " << customer.phoneNumber << "\n";
        orderFile << "First Name: " << customer.firstName << "\n";
        orderFile << "Last Name: " << customer.lastName << "\n";
        orderFile << "Address: " << customer.address << "\n";

        orderFile.close();
        cout << "Customer information saved to 'order.txt'.\n";
    }

public:
    void getCustomerInfo() {
        string phoneNumber = phoneNumberChecker();

        if (loadCustomerFromFile(phoneNumber)) {
            cout << "Login successful using saved data.\n";
            return;
        }

        Customer* existingCustomer = findCustomerByPhoneNumber(phoneNumber);
        if (existingCustomer) {
            cout << "Welcome back, " << existingCustomer->firstName << "!\n";
            customer = *existingCustomer;
        }
        else {
            cout << "Phone number not found. Please register as a new customer.\n";

            customer.phoneNumber = phoneNumber;

            cout << "Enter first name: ";
            cin >> customer.firstName;
            cout << "Enter last name: ";
            cin >> customer.lastName;
            cout << "Enter address: ";
            cin.ignore();
            getline(cin, customer.address);

            customerDatabase.push_back(customer);

            saveCustomerToFile();
        }

        cout << "\nRegistration/Login successful! Proceed to Pizza Menu.\n";
        showMenu();
    }

    void showMenu() {
        cout << "\nPizza Menu:\n";
        int index = 1;
        for (const auto& item : menu) {
            cout << index++ << ". " << item.first << " - " << item.second << " so'm\n";
        }
    }

    void addToCart() {
        showMenu();
        cout << "\nEnter the number of the pizza to add to cart: ";
        int choice;
        cin >> choice;
        if (choice > 0 && choice <= menu.size()) {
            cart.push_back({ menu[choice - 1].first, menu[choice - 1].second });
            cout << menu[choice - 1].first << " added to cart.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    void removeFromCart() {
        showCart();
        if (cart.empty()) return;

        cout << "\nEnter the number of the pizza to remove from cart: ";
        int choice;
        cin >> choice;

        if (choice > 0 && choice <= cart.size()) {
            cout << cart[choice - 1].name << " removed from cart.\n";
            cart.erase(cart.begin() + choice - 1);
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    void updateCustomerInfo() {
        cout << "\nUpdate customer information:\n";
        cout << "Enter first name: ";
        cin >> customer.firstName;
        cout << "Enter last name: ";
        cin >> customer.lastName;
        cout << "Enter address: ";
        cin.ignore();
        getline(cin, customer.address);

        saveCustomerToFile();
        cout << "Customer information updated successfully.\n";
    }

    void saveOrder() {
        ofstream orderFile("order.txt");
        if (!orderFile) {
            cerr << "Error saving order to file.\n";
            return;
        }

        orderFile << "Customer Information:\n";
        orderFile << "Phone Number: " << customer.phoneNumber << "\n";
        orderFile << "First Name: " << customer.firstName << "\n";
        orderFile << "Last Name: " << customer.lastName << "\n";
        orderFile << "Address: " << customer.address << "\n\n";

        orderFile << "Order:\n";
        double total = 0;
        for (const auto& pizza : cart) {
            orderFile << pizza.name << " - " << fixed << setprecision(2)
                << pizza.price << " so'm\n";
            total += pizza.price;
        }

        double cashback = calculateCashback(total);

        orderFile << "Total: " << total << " so'm\n";
        orderFile << "Cashback: " << cashback << " so'm\n";

        orderFile.close();

        cout << "Order saved to 'order.txt'\n";
    }

    void mainMenu() {
        while (true) {
            cout << "\nMain Menu:\n";
            cout << "1. Add pizza to cart\n";
            cout << "2. Remove pizza from cart\n";
            cout << "3. Show cart and total\n";
            cout << "4. Update customer information\n";
            cout << "5. Save order and exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;

            switch (choice) {
            case 1:
                addToCart();
                break;
            case 2:
                removeFromCart();
                break;
            case 3:
                showCart();
                break;
            case 4:
                updateCustomerInfo();
                break;
            case 5:
                saveOrder();
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main() {
    PizzaOrder order;

    order.getCustomerInfo();
    order.mainMenu();

    return 0;
}

