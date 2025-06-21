#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <string>
#include <vector>
#include "melee_weapon.h"

#include "item.h"

class Inventory {
 public:
  std::vector<Item> items_;
  std::vector<MeleeWeapon> melees_;
  void AddItem(const std::string& item_id, const std::vector<Item>& all_items);
  void RemoveItem(const std::string& item_id);
  void AddMelee(const std::string& melee_id, const std::vector<MeleeWeapon> all_melee);
};

#endif  // INVENTORY_H_
