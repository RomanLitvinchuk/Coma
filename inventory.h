#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
#include "item.h"

class Inventory 
{
public:
	std::vector<Item> items;
	void AddItem(const std::string& itemID, const std::vector<Item>& allItems);
	void RemoveItem(const std::string& itemID);
};

#endif