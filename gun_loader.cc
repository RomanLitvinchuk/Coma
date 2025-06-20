#include <fstream>
#include <optional>
#include <string>
#include <unordered_map>

#include "gun.h"
#include "view.h"

GunWeapon GunLoader(const std::string& filename, const std::string& weapon_id) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    View::ShowMessage(u8"Failed to load file guns.txt");
    return GunWeapon("", "", 0, 0, 0);
  }

  std::string line;
  std::unordered_map<std::string, std::string> weapon_data;
  std::string current_id;
  bool found = false;

  while (std::getline(file, line)) {
    if (line.empty()) {
      // ѕровер€ем, нашли ли нужное оружие перед пустой строкой
      if (found && current_id == weapon_id && !weapon_data.empty()) {
        try {
          return GunWeapon(current_id, weapon_data["name"],
                           std::stoi(weapon_data["damage"]),
                           std::stoi(weapon_data["accuracy"]),
                           std::stoi(weapon_data["cooldown"]));
        } catch (const std::exception& e) {
          View::ShowMessage(u8"Failed to parsing gun data");
          return GunWeapon("", "", 0, 0, 0);
        }
      }
      weapon_data.clear();
      continue;
    }

    if (line[0] == '[' && line.back() == ']') {
      current_id = line.substr(1, line.size() - 2);
      found = (current_id == weapon_id);
    } else if (found) {
      size_t delimeter_pos = line.find('=');
      if (delimeter_pos != std::string::npos) {
        std::string key = line.substr(0, delimeter_pos);
        std::string value = line.substr(delimeter_pos + 1);
        weapon_data[key] = value;
      }
    }
  }

  // ѕровер€ем последнее оружие в файле (если нет пустой строки в конце)
  if (found && current_id == weapon_id && !weapon_data.empty()) {
    try {
      return GunWeapon(
          current_id, weapon_data["name"], std::stoi(weapon_data["damage"]),
          std::stoi(weapon_data["accuracy"]), std::stoi(weapon_data["cooldown"]));
    } catch (const std::exception& e) {
      View::ShowMessage(u8"Error to parsing gun data");
    }
  }

  View::ShowMessage(u8"Failed to found a gun ID");
  return GunWeapon("", "", 0, 0, 0);
}
