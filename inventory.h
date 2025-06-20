#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <string>
#include <vector>

#include "item.h"

class Inventory {
 public:
  std::vector<Item> items_;
  void AddItem(const std::string& item_id, const std::vector<Item>& all_items);
  void RemoveItem(const std::string& item_id);
};

#endif  // INVENTORY_H_
