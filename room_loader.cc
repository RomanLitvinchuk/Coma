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
  std::unordered_map<std::string, std::string> currentRoomData;
  std::string currentId;

  while (std::getline(file, line)) {
    // Пропускаем пустые строки и комментарии
    if (line.empty() || line.find("//") == 0) continue;

    if (line[0] == '[' && line.back() == ']') {
      // Если есть данные о предыдущей комнате, добавляем её в вектор
      if (!currentId.empty() && !currentRoomData.empty()) {
        try {
          RoomType type = RoomType::DEFAULT;
          if (currentRoomData["type"] == "CHEST")
            type = RoomType::CHEST;
          else if (currentRoomData["type"] == "ENEMIES")
            type = RoomType::ENEMIES;

          rooms.emplace_back(currentId, currentRoomData["name"],
                             currentRoomData["description"], type,
                             ParseStringList(currentRoomData["connections"]),
                             ParseStringList(currentRoomData["enemyIds"]));
        } catch (const std::exception& e) {
          View::ShowMessage(u8"Failed to parse room data");
        }

        currentRoomData.clear();
      }

      // Устанавливаем новый ID комнаты
      currentId = line.substr(1, line.size() - 2);
    } else {
      // Парсим пары key=value
      size_t delimiterPos = line.find('=');
      if (delimiterPos != std::string::npos) {
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);
        currentRoomData[key] = value;
      }
    }
  }

  // Добавляем последнюю комнату (если есть)
  if (!currentId.empty() && !currentRoomData.empty()) {
    try {
      RoomType type = RoomType::DEFAULT;
      if (currentRoomData["type"] == "CHEST")
        type = RoomType::CHEST;
      else if (currentRoomData["type"] == "ENEMIES")
        type = RoomType::ENEMIES;

      rooms.emplace_back(currentId, currentRoomData["name"],
                         currentRoomData["description"], type,
                         ParseStringList(currentRoomData["connections"]),
                         ParseStringList(currentRoomData["enemyIds"]));
    } catch (const std::exception& e) {
      View::ShowMessage(u8"Failed to parse room data");
    }
  }

  return rooms;
}

Room RoomFactory(const std::string id, const std::vector<Room>& AllRooms) {
  bool Isfound = false;
  for (const auto& templ : AllRooms) {
    if (templ.id == id) {
      Isfound = true;
      return templ;
    }
  }

  if (!Isfound) {
    View::ShowMessage(u8"Failed to find room");
  }
}

std::string GetRoomNameById(const std::string id,
                            const std::vector<Room>& AllRooms) {
  bool Isfound = false;
  for (const auto& templ : AllRooms) {
    if (templ.id == id) {
      return templ.name;
    }
  }

  if (!Isfound) {
    View::ShowMessage(u8"Failed to find room");
  }
}
