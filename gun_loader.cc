#include <algorithm>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "gun.h"
#include "view.h"

std::vector<GunWeapon> LoadAllGuns(const std::string& filename) {
	std::vector<GunWeapon> weapons;
	std::ifstream file(filename);

	if (!file.is_open()) {
		View::ViewMessage(u8"Failed to load file guns.txt");
		return weapons;
	}

	std::string line;
	std::unordered_map<std::string, std::string> current_weapon_data;
	std::string current_id;

	while (std::getline(file, line)) {
		// ���������� ����������� � ������ ������
		if (line.empty() || line.find("//") == 0) continue;

		if (line[0] == '[' && line.back() == ']') {
			// ���� ��� ���� ������ � ���������� ������, ��������� ��
			if (!current_id.empty() && !current_weapon_data.empty()) {
				try {
					weapons.emplace_back(current_id, current_weapon_data["name"],
						std::stoi(current_weapon_data["damage"]),
						std::stoi(current_weapon_data["accuracy"]),
						std::stoi(current_weapon_data["cur_cooldown"]));
				}
				catch (const std::exception& e) {
					View::ViewMessage(u8"Failed to parse gun weapon data");
				}

				current_weapon_data.clear();
			}

			// �������� ����� ID
			current_id = line.substr(1, line.size() - 2);
		}
		else {
			// ������ ��������� ���� key=value
			size_t delimeter_pos = line.find('=');
			if (delimeter_pos != std::string::npos) {
				std::string key = line.substr(0, delimeter_pos);
				std::string value = line.substr(delimeter_pos + 1);
				current_weapon_data[key] = value;
			}
		}
	}

	// ��������� ��������� ������
	if (!current_id.empty() && !current_weapon_data.empty()) {
		try {
			weapons.emplace_back(current_id, current_weapon_data["name"],
				std::stoi(current_weapon_data["damage"]),
				std::stoi(current_weapon_data["accuracy"]),
				std::stoi(current_weapon_data["cooldown"]));
		}
		catch (const std::exception& e) {
			View::ViewMessage(u8"Failed to parse gun weapon data");
		}
	}

	return weapons;
}

GunWeapon GunFactory(const std::string& gun_id, const std::vector<GunWeapon>& all_guns) {
	for (const auto& templ : all_guns) {
		if (templ.GetID() == gun_id) {
			return templ;
		}
	}
	View::ViewMessage(u8"Failed to find a gun ID");
	return GunWeapon("", "", 0, 0, 0);
}