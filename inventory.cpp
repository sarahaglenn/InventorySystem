#include "inventory.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <sstream>

namespace Y {
        // Constructors
        Inventory::Inventory() {}
        Inventory::Inventory(std::vector<M::Item>& i)
            :items(i) {}
        // Setter
        void Inventory::setItems(const std::vector<M::Item>& i) {
            items = i;
        }
        // Getter
        const std::vector<M::Item>& Inventory::getItems() const{
            return items;
        }
        // Class methods
        void Inventory::addItem(const M::Item& newItem) {
            items.push_back(newItem);
        }
        bool Inventory::removeItem(const M::Item& itemToRemove) {
            for (size_t i = 0; i < items.size(); i++) {
                if (items[i] == itemToRemove) {
                    std::swap(items[i], items.back());
                    items.pop_back();
                    return true;
                }
            }
            return false;
        }
};