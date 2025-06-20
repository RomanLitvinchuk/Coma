#include <fstream>
#include <optional>
#include <string>
#include <unordered_map>

#include "gun.h"
#include "view.h"

GunWeapon GunLoader(const std::string& filename, const std::string& weaponId) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    View::ShowMessage(u8"Failed to load file guns.txt");
    return GunWeapon("", "", 0, 0, 0);
  }

  std::string line;
  std::unordered_map<std::string, std::string> weaponData;
  std::string currentId;
  bool found = false;

  while (std::getline(file, line)) {
    if (line.empty()) {
      // ѕровер€ем, нашли ли нужное оружие перед пустой строкой
      if (found && currentId == weaponId && !weaponData.empty()) {
        try {
          return GunWeapon(currentId, weaponData["name"],
                           std::stoi(weaponData["damage"]),
                           std::stoi(weaponData["accuracy"]),
                           std::stoi(weaponData["cooldown"]));
        } catch (const std::exception& e) {
          View::ShowMessage(u8"Failed to parsing gun data");
          return GunWeapon("", "", 0, 0, 0);
        }
      }
      weaponData.clear();
      continue;
    }

    if (line[0] == '[' && line.back() == ']') {
      currentId = line.substr(1, line.size() - 2);
      found = (currentId == weaponId);
    } else if (found) {
      size_t delimiterPos = line.find('=');
      if (delimiterPos != std::string::npos) {
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        weaponData[key] = value;
      }
    }
  }

  // ѕровер€ем последнее оружие в файле (если нет пустой строки в конце)
  if (found && currentId == weaponId && !weaponData.empty()) {
    try {
      return GunWeapon(
          currentId, weaponData["name"], std::stoi(weaponData["damage"]),
          std::stoi(weaponData["accuracy"]), std::stoi(weaponData["cooldown"]));
    } catch (const std::exception& e) {
      View::ShowMessage(u8"Error to parsing gun data");
    }
  }

  View::ShowMessage(u8"Failed to found a gun ID");
  return GunWeapon("", "", 0, 0, 0);
}
