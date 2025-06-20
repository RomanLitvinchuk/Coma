#ifndef GUN_H_
#define GUN_H_

#include <string>

class GunWeapon {
 private:
  std::string id_;
  std::string name_;
  int damage_;
  int accuracy_;
  int cooldown_;

 public:
  GunWeapon(const std::string id, const std::string name, int damage,
            int accuracy, int cooldown)
      : id_(id),
        name_(name),
        damage_(damage),
        accuracy_(accuracy),
        cooldown_(cooldown) {}
  std::string GetID() const { return id_; }
  std::string GetName() const { return name_; }
  int GetDamage() const { return damage_; }
  int GetAccuracy() const { return accuracy_; }
  int GetCooldown() const { return cooldown_; }
};

GunWeapon GunLoader(const std::string& filename, const std::string& gun_id);

#endif  // GUN_H_
