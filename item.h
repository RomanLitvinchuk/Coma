#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>
class Item {
 private:
  std::string id_;
  std::string name_;
  int heal_amount_;
  int mental_heal_;

 public:
  Item(const std::string& id, const std::string& name, int heal_amount_, int mental_heal)
      : id_(id), name_(name), heal_amount_(heal_amount_), mental_heal_(mental_heal) {}
  std::string GetID() const { return id_; }
  std::string GetName() const { return name_; }
  int GetHealAmount() const { return heal_amount_; }
  int GetMentalHeal() const { return mental_heal_; }
};

std::vector<Item> LoadAllItems(const std::string& filename);
Item ItemFactory(const std::vector<Item>& all_items, const std::string& item_id);

#endif  // ITEM_H_
