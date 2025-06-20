#ifndef ROOM_H_
#define ROOM_H_

#include <string>
#include <vector>

enum class RoomType { DEFAULT, CHEST, ENEMIES };

class Room {
 public:
  std::string id;
  std::string name;
  std::string description;
  bool IsChecked = false;
  std::vector<std::string> connectedRooms;
  RoomType type;
  std::vector<std::string> enemyIds;

  Room(const std::string id, const std::string name, const std::string desc,
       RoomType type, std::vector<std::string> connections,
       std::vector<std::string> enemyIds)
      : id(id),
        name(name),
        description(desc),
        type(type),
        connectedRooms(connections),
        enemyIds(enemyIds) {}
};

std::vector<Room> LoadAllRooms(const std::string& filename);
Room RoomFactory(const std::string id, const std::vector<Room>& AllRooms);
std::string GetRoomNameById(const std::string id,
                            const std::vector<Room>& AllRooms);

#endif  // ROOM_H_
