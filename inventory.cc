#include "inventory.h"

#include <string>
#include <vector>

#include "item.h"
void Inventory::AddItem(const std::string& itemID,
                        const std::vector<Item>& all_items) {
  Item new_item = ItemFactory(all_items, itemID);
  items_.push_back(new_item);
}

void Inventory::RemoveItem(const std::string& item_id) {
  items_.erase(std::remove_if(items_.begin(), items_.end(),
                             [&item_id](const Item& item) {
                               return item.GetID() == item_id;
                             }),
              items_.end());
}
