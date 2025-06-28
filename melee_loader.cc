#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include "melee_weapon.h"
#include "view.h"

std::vector<MeleeWeapon> LoadAllMelee(const std::string& filename) {
  std::vector<MeleeWeapon> weapons;
  std::ifstream file(filename);

  if (!file.is_open()) {
    View::ViewMessage(u8"Failed to load file melee.txt");
    return weapons;
  }

  std::string line;
  std::unordered_map<std::string, std::string> current_weapon_data;
  std::string current_id;

  while (std::getline(file, line)) {
    // Пропускаем комментарии и пустые строки
    if (line.empty() || line.find("//") == 0) continue;

    if (line[0] == '[' && line.back() == ']') {
      // Если уже есть данные о предыдущем оружии, сохраняем их
      if (!current_id.empty() && !current_weapon_data.empty()) {
        try {
          weapons.emplace_back(current_id, current_weapon_data["name"],
                               std::stoi(current_weapon_data["damage"]),
                               std::stoi(current_weapon_data["accuracy"]));
        } catch (const std::exception& e) {
          View::ViewMessage(u8"Failed to parse melee weapon data");
        }

        current_weapon_data.clear();
      }

      // Получаем новый ID
      current_id = line.substr(1, line.size() - 2);
    } else {
      // Парсим параметры вида key=value
      size_t delimeter_pos = line.find('=');
      if (delimeter_pos != std::string::npos) {
        std::string key = line.substr(0, delimeter_pos);
        std::string value = line.substr(delimeter_pos + 1);
        current_weapon_data[key] = value;
      }
    }
  }

  // Добавляем последнее оружие
  if (!current_id.empty() && !current_weapon_data.empty()) {
    try {
      weapons.emplace_back(current_id, current_weapon_data["name"],
                           std::stoi(current_weapon_data["damage"]),
                           std::stoi(current_weapon_data["accuracy"]));
    } catch (const std::exception& e) {
      View::ViewMessage(u8"Failed to parse melee weapon data");
    }
  }

  return weapons;
}


MeleeWeapon MeleeFactory(const std::string& melee_id, const std::vector<MeleeWeapon> all_melee)
{
    for (const auto& templ : all_melee) 
    {
        if (templ.GetID() == melee_id) {
            return templ;
        }
    }
}
