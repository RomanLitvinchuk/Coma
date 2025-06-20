#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#include "room.h"
#include "view.h"

// Вспомогательная функция для парсинга списков вида {a,b,c}
std::vector<std::string> ParseStringList(const std::string& s) {
  std::vector<std::string> result;
  if (s.empty() || s == "{}") return result;

  std::string content = s.substr(1, s.size() - 2);
  std::stringstream ss(content);
  std::string item;

  while (std::getline(ss, item, ',')) {
    item.erase(std::remove_if(item.begin(), item.end(), ::isspace), item.end());
    if (!item.empty()) {
      result.push_back(item);
    }
  }

  return result;
}

std::vector<Room> LoadAllRooms(const std::string& filename) {
  std::vector<Room> rooms;
  std::ifstream file(filename);

  if (!file.is_open()) {
    View::ShowMessage(u8"Failed to load file rooms.txt");
    return rooms;
  }

  std::string line;
  std::unordered_map<std::string, std::string> current_room_data;
  std::string current_id;

  while (std::getline(file, line)) {
    // Пропускаем пустые строки и комментарии
    if (line.empty() || line.find("//") == 0) continue;

    if (line[0] == '[' && line.back() == ']') {
      // Если есть данные о предыдущей комнате, добавляем её в вектор
      if (!current_id.empty() && !current_room_data.empty()) {
        try {
          RoomType type = RoomType::kDefault;
          if (current_room_data["type"] == "CHEST")
            type = RoomType::kChest;
          else if (current_room_data["type"] == "ENEMIES")
            type = RoomType::kEnemies;

          rooms.emplace_back(current_id, current_room_data["name"],
                             current_room_data["description"], type,
                             ParseStringList(current_room_data["connections"]),
                             ParseStringList(current_room_data["enemyIds"]));
        } catch (const std::exception& e) {
          View::ShowMessage(u8"Failed to parse room data");
        }

        current_room_data.clear();
      }

      // Устанавливаем новый ID комнаты
      current_id = line.substr(1, line.size() - 2);
    } else {
      // Парсим пары key=value
      size_t delimiter_pos = line.find('=');
      if (delimiter_pos != std::string::npos) {
        std::string key = line.substr(0, delimiter_pos);
        std::string value = line.substr(delimiter_pos + 1);
        current_room_data[key] = value;
      }
    }
  }

  // Добавляем последнюю комнату (если есть)
  if (!current_id.empty() && !current_room_data.empty()) {
    try {
      RoomType type = RoomType::kDefault;
      if (current_room_data["type"] == "CHEST")
        type = RoomType::kChest;
      else if (current_room_data["type"] == "ENEMIES")
        type = RoomType::kEnemies;

      rooms.emplace_back(current_id, current_room_data["name"],
                         current_room_data["description"], type,
                         ParseStringList(current_room_data["connections"]),
                         ParseStringList(current_room_data["enemyIds"]));
    } catch (const std::exception& e) {
      View::ShowMessage(u8"Failed to parse room data");
    }
  }

  return rooms;
}

Room RoomFactory(const std::string id, const std::vector<Room>& all_rooms) {
  bool is_found = false;
  for (const auto& templ : all_rooms) {
    if (templ.id_ == id) {
      is_found = true;
      return templ;
    }
  }

  if (!is_found) {
    View::ShowMessage(u8"Failed to find room");
  }
}

std::string GetRoomNameById(const std::string id,
                            const std::vector<Room>& all_rooms) {
  bool is_found = false;
  for (const auto& templ : all_rooms) {
    if (templ.id_ == id) {
      return templ.name_;
    }
  }

  if (!is_found) {
    View::ShowMessage(u8"Failed to find room");
  }
}
