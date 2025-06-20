#include "item.h"

#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "view.h"
std::vector<Item> LoadAllItems(const std::string& filename) {
  std::vector<Item> items;
  std::ifstream file(filename);

  if (!file.is_open()) {
    View::ShowMessage(u8"Failed to load file items.txt");
    return items;
  }

  std::string line;
  std::unordered_map<std::string, std::string> current_item_data;
  int current_id = -1;

  while (std::getline(file, line)) {
    // Пропускаем комментарии и пустые строки
    if (line.empty() || line.find("//") == 0) continue;

    if (line[0] == '[' && line.back() == ']') {
      // Если уже есть данные о предыдущем предмете, сохраняем их
      if (current_id != -1 && !current_item_data.empty()) {
        try {
          items.emplace_back(std::to_string(current_id), current_item_data["name"],
                             std::stoi(current_item_data["healAmount"]));
        } catch (const std::exception& e) {
          View::ShowMessage(u8"Failed to parsing item data");
        }

        current_item_data.clear();
      }

      // Получаем новый ID
      try {
        current_id = std::stoi(line.substr(1, line.size() - 2));
      } catch (const std::exception& e) {
        View::ShowMessage(u8"Invalid ID format");
        current_id = -1;
      }
    } else {
      // Парсим параметры вида key=value
      size_t delimeter_pos = line.find('=');
      if (delimeter_pos != std::string::npos) {
        std::string key = line.substr(0, delimeter_pos);
        std::string value = line.substr(delimeter_pos + 1);
        current_item_data[key] = value;
      }
    }
  }

  // Добавляем последний предмет
  if (current_id != -1 && !current_item_data.empty()) {
    try {
      items.emplace_back(std::to_string(current_id), current_item_data["name"],
                         std::stoi(current_item_data["healAmount"]));
    } catch (const std::exception& e) {
      View::ShowMessage(u8"Failed to parsing item data");
    }
  }

  return items;
}

Item ItemFactory(const std::vector<Item>& all_items, const std::string& item_id) {
  Item item("", "", 0);
  bool found = false;

  // Ищем шаблон предмета с нужным ID
  for (const auto& templ : all_items) {
    if (templ.GetID() == item_id) {
      item = templ;
      return item;
    }
    // if (!found)
  }
}
