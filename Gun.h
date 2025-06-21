#ifndef GUN_H_
#define GUN_H_

#include <string>

class GunWeapon {
 private:
  std::string id_;
  std::string name_;
  int damage_;
  int accuracy_;
  int current_cooldown_;
  //int max_cooldown;

 public:
  GunWeapon(const std::string id, const std::string name, int damage,
            int accuracy, int cur_cooldown)
      : id_(id),
        name_(name),
        damage_(damage),
        accuracy_(accuracy),
        current_cooldown_(cur_cooldown){}
  std::string GetID() const { return id_; }
  std::string GetName() const { return name_; }
  int GetDamage() const { return damage_; }
  int GetAccuracy() const { return accuracy_; }
  int GetCurrentCooldown() const { return current_cooldown_; }
};

GunWeapon GunLoader(const std::string& filename, const std::string& gun_id);

#endif  // GUN_H_
