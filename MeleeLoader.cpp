#include "MeleeWeapon.h"
#include "TextView.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <optional>

MeleeWeapon MeleeLoader(const std::string& filename, const std::string& weaponId) 
{
    std::ifstream file(filename);

    if (!file.is_open()) {
        TextView::showMessage(u8"Failed to load file melee.txt");
        return MeleeWeapon("", "", 0, 0);
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
                    return MeleeWeapon(
                        currentId,
                        weaponData["name"],
                        std::stoi(weaponData["damage"]),
                        std::stoi(weaponData["accuracy"])
                    );
                }
                catch (const std::exception& e) {
                    TextView::showMessage(u8"Failed to parsing melee data");
                    return MeleeWeapon("", "", 0, 0);
                }
            }
            weaponData.clear();
            continue;
        }

        if (line[0] == '[' && line.back() == ']') {
            currentId = line.substr(1, line.size() - 2);
            found = (currentId == weaponId);
        }
        else if (found) {
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
            return MeleeWeapon(
                currentId,
                weaponData["name"],
                std::stoi(weaponData["damage"]),
                std::stoi(weaponData["accuracy"])
            );
        }
        catch (const std::exception& e) {
            TextView::showMessage(u8"Error to parsing melee data");
        }
    }

    TextView::showMessage(u8"Failed to found a melee ID");
    return MeleeWeapon("", "", 0, 0);
}