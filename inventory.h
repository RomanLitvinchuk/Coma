#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <string>
#include <vector>

#include "item.h"

class Inventory {
 public:
  std::vector<Item> items;
  void AddItem(const std::string& itemID, const std::vector<Item>& allItems);
  void RemoveItem(const std::string& itemID);
};

#endif  // INVENTORY_H_
