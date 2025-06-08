#pragma once
#include <string>
#include <vector>
class Item 
{
private:
	std::string id;
	std::string name;
	int healAmount;
public:
	Item(const std::string& id, const std::string& name, int healAmount) : id(id), name(name), healAmount(healAmount) {}
	std::string getID() const { return id; }
	std::string getName() const { return name; }
	int getHealAmount() const { return healAmount; }

};

std::vector<Item> LoadAllItems(const std::string& filename);
Item ItemFactory(const std::vector<Item>& allItems, const std::string& itemId);