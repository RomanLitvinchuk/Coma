#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <string>
#include <vector>
#include "melee_weapon.h"
#include "gun.h"

#include "item.h"

class Inventory {
 public:
  std::vector<Item> items_;
  std::vector<MeleeWeapon> melees_;
  std::vector<GunWeapon> guns_;
  void AddItem(const std::string& item_id, const std::vector<Item>& all_items);
  void RemoveItem(const std::string& item_id);
  void AddMelee(const std::string& melee_id, const std::vector<MeleeWeapon>& all_melee);
  void AddGun(const std::string& gun_id, const std::vector<GunWeapon>& all_guns);
};

#endif  // INVENTORY_H_
