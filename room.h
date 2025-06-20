#ifndef ROOM_H_
#define ROOM_H_

#include <string>
#include <vector>

enum class RoomType { kDefault, kChest, kEnemies };

class Room {
 public:
  std::string id_;
  std::string name_;
  std::string description_;
  bool is_checked_ = false;
  std::vector<std::string> connected_rooms_;
  RoomType type_;
  std::vector<std::string> enemy_ids_;

  Room(const std::string id, const std::string name, const std::string desc,
       RoomType type, std::vector<std::string> connections,
       std::vector<std::string> enemy_ids)
      : id_(id),
        name_(name),
        description_(desc),
        type_(type),
        connected_rooms_(connections),
        enemy_ids_(enemy_ids) {}
};

std::vector<Room> LoadAllRooms(const std::string& filename);
Room RoomFactory(const std::string id, const std::vector<Room>& all_rooms);
std::string GetRoomNameById(const std::string id,
                            const std::vector<Room>& all_rooms);

#endif  // ROOM_H_
