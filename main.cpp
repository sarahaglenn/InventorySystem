#include <iostream>
#include <iomanip>
#include "inventory.h"
#include "item.h"
#include <vector>
#include <string>

using namespace std;

// Function prototypes
void menu(Y::Inventory& inventory);
void viewInventory(const Y::Inventory& inventory);
void addItem(Y::Inventory& inventory);
void removeItem(Y::Inventory& inventory);
void updateItem(Y::Inventory& inventory);
bool tryParseInt(string& input);
bool tryParseDouble(string& input);
void displayItemsWithIndex (vector<M::Item> items);

int main() {
    // Initialize new inventory with items in vector
    Y::Inventory myInventory;
    // Initialize items
    M::Item item1("Nike Alpha Fly", 82.99, 17);
    M::Item item2("Adidas Sprint", 105.99, 30);
    M::Item item3("Brooks Ghost", 120.99, 45);
    M::Item item4("New Balance Trek", 80.99, 20);
    // Add items to inventory
    myInventory.addItem(item1);
    myInventory.addItem(item2);
    myInventory.addItem(item3);
    myInventory.addItem(item4);

    menu(myInventory);
}

void menu(Y::Inventory& inventory) {
    bool isDisplayed = true;
    while (isDisplayed) {
        cout << "\nInventory System\n\n"
        "1. View inventory\n"
        "2. Add new item\n"
        "3. Update an item\n"
        "4. Remove an item\n"
        "5. Exit\n";
        cout << "Select an option: ";
        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1:
                viewInventory(inventory);
                break;
            case 2:
                addItem(inventory);
                break;
            case 3:
                updateItem(inventory);
                break;
            case 4:
                removeItem(inventory);
                break;
            case 5:
                isDisplayed = false;
            default:
                cout << "Please select a valid option" << endl;
        }
    }
}
void viewInventory(const Y::Inventory& inventory) {
    cout << endl;
    // Print column headers
    cout << left << setw(20) << "Name"
         << setw(10) << "Price"
         << setw(10) << "Quantity" << endl;
    // for each item in the list, call display function
    for (M::Item item : inventory.getItems()) {
        cout << item.displayDetails() << endl;
    }
    cout << "Press enter to return to the main menu."<< endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return;
}
void addItem(Y::Inventory& inventory) {
    string name;
    string price;
    string qty;
    cout << "\nAdd an item to the inventory" << endl;
    // prompt for each part of item
    cout << "\nEnter the name of the item: ";
    std::cin.ignore();
    getline(std::cin, name, '\n');
    cout << "\nEnter the price of the item: ";
    getline(std::cin, price, '\n');
    while (!tryParseDouble(price)) {
        cout << "Please enter a valid price." << endl;
        getline(std::cin, price, '\n');
    }
    double doublePrice = stod(price);
    cout << "\nEnter the quantity of the item: ";
    getline(std::cin, qty, '\n');
    while (!tryParseInt(qty)) {
        cout << "Please enter a valid quantity." << endl;
        getline(std::cin, qty, '\n');
    }
    int intQty = stoi(qty);
    // initialize new item
    M::Item newItem(name, doublePrice, intQty);
    // add the item to inventory list
    try {
        inventory.addItem(newItem);
        cout << "Item added to inventory." << endl;
    } catch (const exception& e){
        cout << "Item could not be added to inventory." <<  e.what() << endl;
    }
    return;
}
void removeItem(Y::Inventory& inventory) {
    vector<M::Item> inventoryItems = inventory.getItems();
    displayItemsWithIndex(inventoryItems);
    // ask which item to remove
    cout << "\nWhich item would you like to remove?" << endl;
    int itemNum;
    std::cin >> itemNum;
    // find and delete chosen item
    if (itemNum < inventoryItems.size()) {
        M::Item& itemToRemove = inventoryItems[itemNum];
        if (inventory.removeItem(itemToRemove)) {
             cout << "1 item removed from the inventory" << endl;
        } else {
            cout << "Item could not be removed from inventory." << endl;
        }
    } else {
        cout << "Invalid item number." << endl;
    }
}

void updateItem(Y::Inventory& inventory) {
    vector<M::Item> inventoryItems = inventory.getItems();
    displayItemsWithIndex(inventoryItems);
    // ask which item to update
    cout << "\nWhich item would you like to update? ";
    int itemNum;
    cin >> itemNum;
    // find the item
    if (itemNum < inventoryItems.size()) {
        M::Item& itemToUpdate = inventoryItems[itemNum];
        // Display it's details
        cout << "Current details: " << itemToUpdate.displayDetails() << endl;
        bool isDisplayed = true;
        while (isDisplayed) {
            // ask which attribute to update
            cout << "\nWhich aspect would you like to update?\n"
                "1. Name\n"
                "2. Price\n"
                "3. Quantity\n" << endl;
            // update item
            int choice;
            string name;
            double price;
            int qty;
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Enter the updated name: ";
                    cin.ignore();
                    getline(cin, name, '\n');
                    if (!itemToUpdate.setName(name)) {
                        cout << "Name could not be updated." << endl;
                    }
                    cout << "Name updated successfully." << endl;
                    isDisplayed = false;
                    break;
                case 2:
                    cout << "Enter the updated price: ";
                    cin >> price;
                    if (!itemToUpdate.setPrice(price)) {
                        cout << "Price could not be updated" << endl;
                    }
                    cout << "Price updated successfully." << endl;
                    isDisplayed = false;
                    break;
                case 3:
                    cout << "Enter the updated quantity: ";
                    cin >> qty;
                    if (!itemToUpdate.setQuantity(qty)) {
                        cout << "Quantity could not be updated." << endl;
                    }
                    cout << "Quantity updated successfully." << endl;
                    isDisplayed = false;
                    break;
                default:
                    cout << "Please enter a valid option." << endl;
            }
        }
    } else {
        cout << "Please enter a valid option." << endl;
    }
    // Update the inventory with the changed items
    inventory.setItems(inventoryItems);
}

void displayItemsWithIndex (vector<M::Item> items) {
    // Print column headers
    cout << endl;
    cout << left << setw(10) << "Index"
         << setw(20) << "Name"
         << setw(10) << "Price"
         << setw(10) << "Quantity" << endl;
    int i = 0;
    for (const M::Item& item : items) {
        cout << left << setw(10) << to_string(i) 
             << item.displayDetails();
        i++;
    }
}

bool tryParseInt(string& input) {
    try {
        stoi(input);
    } catch (invalid_argument) {
        return false;
    }
    return true;
}
bool tryParseDouble(string& input) {
    try {
        stod(input);
    } catch (invalid_argument) {
        return false;
    }
    return true;
}
