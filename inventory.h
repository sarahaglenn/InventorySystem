#pragma once

#include <vector>
#include <string>
#include "item.h"

namespace Y {
    class Inventory {
        private:
            std::vector<M::Item> items;
        public:
            Inventory();
            Inventory(std::vector<M::Item>& i);
            const std::vector<M::Item>& getItems() const;
            void setItems(const std::vector<M::Item>& i);
            void addItem(const M::Item& newItem);
            bool removeItem(const M::Item& itemToRemove);
    };
}