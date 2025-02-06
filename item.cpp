#include "item.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <sstream>

namespace M {

    // Constructors
    Item::Item() : name(""), price(0), quantity(0) {}
    Item::Item(std::string n, double p, int q)
        :name(n), price(round(p * 100)), quantity(q) {}
    // Setters
    bool Item::setName(std::string n) {
        name = n;
        return true;
    }
    bool Item::setPrice(double p) {
        if (p >= 0) {
            price = round(p * 100);
            return true;
        }
        std::cout << "Price cannot be negative." << std::endl;
        return false;
    }
    bool Item::setQuantity(int q) {
        if (q >= 0) {
            quantity = q;
            return true;
        }
        std::cout << "Quantity cannot be negative." << std::endl;
        return false;
    }
    // Getters
    std::string Item::getName() const {
        return name;
    }
    double Item::getPrice() const {
        return price / 100.0;
    }
    int Item::getQuantity() const {
        return quantity;
    }
    // Class Methods
    std::string Item::displayDetails() const {
        std::ostringstream oss;
        oss << std::left << std::setw(20) << name
            << std::setw(1) << "$"
            << std::setw(10) << std::fixed << std::setprecision(2) << getPrice()
            << std::setw(10) << quantity << std::endl;
        return oss.str();
    }
    bool Item::operator==(const Item& other) const {
        return ((name == other.name) && (price == other.price) && (quantity == other.quantity));
    }
}