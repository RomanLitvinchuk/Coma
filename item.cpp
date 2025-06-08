#include "item.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
std::vector<Item> LoadAllItems(const std::string& filename) 
{
    std::vector<Item> items;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        // ��������� ������ �������� �����
        return items;
    }

    std::string line;
    std::unordered_map<std::string, std::string> currentItemData;
    int currentId = -1;

    while (std::getline(file, line))
    {
        // ���������� ����������� � ������ ������
        if (line.empty() || line.find("//") == 0) continue;

        if (line[0] == '[' && line.back() == ']')
        {
            // ���� ��� ���� ������ � ���������� ��������, ��������� ��
            if (currentId != -1 && !currentItemData.empty())
            {
                try
                {
                    items.emplace_back(
                        std::to_string(currentId),
                        currentItemData["name"],
                        std::stoi(currentItemData["healAmount"])
                    );
                }
                catch (const std::exception& e)
                {
                    // ��������� ������ �������� ������
                }

                currentItemData.clear();
            }

            // �������� ����� ID
            try
            {
                currentId = std::stoi(line.substr(1, line.size() - 2));
            }
            catch (const std::exception& e)
            {
                // ��������� ��������� ������� ID
                currentId = -1;
            }
        }
        else
        {
            // ������ ��������� ���� key=value
            size_t delimiterPos = line.find('=');
            if (delimiterPos != std::string::npos)
            {
                std::string key = line.substr(0, delimiterPos);
                std::string value = line.substr(delimiterPos + 1);
                currentItemData[key] = value;
            }
        }
    }

    // ��������� ��������� �������
    if (currentId != -1 && !currentItemData.empty())
    {
        try
        {
            items.emplace_back(
                std::to_string(currentId),
                currentItemData["name"],
                std::stoi(currentItemData["healAmount"])
            );
        }
        catch (const std::exception& e)
        {
            // ��������� ������ �������� ������
        }
    }

    return items;

}


Item ItemFactory(const std::vector<Item>& allItems, const std::string& itemId)
{
    Item item("", "", 0);
    bool found = false;

    // ���� ������ ����� � ������ ID
    for (const auto& templ : allItems) {
        if (templ.getID() == itemId) {
            item = templ;
            return item;
        }
    //if (!found)
    }
}

