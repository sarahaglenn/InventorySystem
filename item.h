#pragma once
#include <string>

namespace M {
    class Item {
    private:
        std::string name;
        int price;
        int quantity;
    public:
        Item();
        Item(std::string n, double p, int q);
        bool setName(std::string n);
        bool setPrice(double p);
        bool setQuantity(int q);
        std::string getName() const;
        double getPrice() const;
        int getQuantity() const;
        std::string displayDetails() const;
        bool operator==(const Item& other) const;
    };
}