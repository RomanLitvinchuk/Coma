#include "inventory.h"
#include <vector>
#include <string>
#include "item.h"
void Inventory::AddItem(const std::string& itemID, const std::vector<Item>& allItems) 
{
	Item newItem = ItemFactory(allItems, itemID);
	items.push_back(newItem);
}

void Inventory::RemoveItem(const std::string& itemID) 
{
    items.erase(
        std::remove_if(items.begin(), items.end(),
            [&itemID](const Item& item) { return item.getID() == itemID; }),
        items.end()
    );
}