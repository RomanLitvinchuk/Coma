#ifndef ITEM_H_
#define ITEM_H_

#include <string>
#include <vector>
class Item {
 private:
  std::string id;
  std::string name;
  int healAmount;

 public:
  Item(const std::string& id, const std::string& name, int healAmount)
      : id(id), name(name), healAmount(healAmount) {}
  std::string GetID() const { return id; }
  std::string GetName() const { return name; }
  int GetHealAmount() const { return healAmount; }
};

std::vector<Item> LoadAllItems(const std::string& filename);
Item ItemFactory(const std::vector<Item>& allItems, const std::string& itemId);

#endif  // ITEM_H_
