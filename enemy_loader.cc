#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "enemy.h"
#include "view.h"

std::vector<Enemy> LoadAllEnemies(const std::string& filename) {
  std::vector<Enemy> enemies;
  std::ifstream file(filename);

  if (!file.is_open()) {
    View::ViewMessage(u8"Failed to load file enemies.txt");
    return enemies;
  }

  std::string line;
  std::unordered_map<std::string, std::string> current_enemy_data;
  int current_id = -1;

  while (std::getline(file, line)) {
    if (line.empty() || line.find("//") == 0) continue;

    if (line[0] == '[' && line.back() == ']') {
      // Если уже есть данные о предыдущем враге, сохраняем их
      if (current_id != -1 && !current_enemy_data.empty()) {
        try {
          enemies.emplace_back(std::to_string(current_id),
                               current_enemy_data["name"],
                               std::stoi(current_enemy_data["health"]),
                               std::stoi(current_enemy_data["attack"]),
                               std::stoi(current_enemy_data["mental_attack"]),
                               std::stoi(current_enemy_data["experience"]));
        } catch (const std::exception& e) {
          View::ViewMessage(u8"Failed to parsing enemy data");
        }

        current_enemy_data.clear();
      }

      // Получаем новый ID
      try {
        current_id = std::stoi(line.substr(1, line.size() - 2));
      } catch (const std::exception& e) {
        View::ViewMessage(u8"Invalid ID format");
        current_id = -1;
      }
    } else {
      // Парсим параметры вида key=value
      size_t delimeter_pos = line.find('=');
      if (delimeter_pos != std::string::npos) {
        std::string key = line.substr(0, delimeter_pos);
        std::string value = line.substr(delimeter_pos + 1);
        current_enemy_data[key] = value;
      }
    }
  }

  // Добавляем последнего врага
  if (current_id != -1 && !current_enemy_data.empty()) {
    try {
      enemies.emplace_back(std::to_string(current_id), current_enemy_data["name"],
                           std::stoi(current_enemy_data["health"]),
                           std::stoi(current_enemy_data["attack"]),
                           std::stoi(current_enemy_data["mental_attack"]),
                           std::stoi(current_enemy_data["experience"]));
    } catch (const std::exception& e) {
      View::ViewMessage(u8"Failed to parsing enemy data");
    }
  }

  return enemies;
}

std::vector<Enemy> EnemyFactory(const std::vector<Enemy>& all_enemies, const std::vector<std::string>& enemy_ids)
{
	std::vector<Enemy> enemies;

	for (const auto& enemy_id : enemy_ids) {
		bool found = false;

		for (const auto& templ : all_enemies) {
			if (templ.GetID() == enemy_id) {
				enemies.push_back(templ);
				found = true;
				break;
			}
		}

		if (!found) {
            View::ViewMessage(u8"Not found enemy template");
		}
	}

	return enemies;
}
