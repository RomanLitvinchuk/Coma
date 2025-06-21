#include "inventory.h"

#include <string>
#include <vector>

#include "item.h"
void Inventory::AddItem(const std::string& item_id,
                        const std::vector<Item>& all_items) {
  Item new_item = ItemFactory(all_items, item_id);
  items_.push_back(new_item);
}

void Inventory::RemoveItem(const std::string& item_id) {
  items_.erase(std::remove_if(items_.begin(), items_.end(),
                             [&item_id](const Item& item) {
                               return item.GetID() == item_id;
                             }),
              items_.end());
}

void Inventory::AddMelee(const std::string& melee_id, const std::vector<MeleeWeapon> all_melee) 
{
    MeleeWeapon new_melee = MeleeFactory(melee_id, all_melee);
    melees_.push_back(new_melee);
}
