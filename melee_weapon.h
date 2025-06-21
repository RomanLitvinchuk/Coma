#ifndef MELEE_WEAPON_H_
#define MELEE_WEAPON_H_

#include <string>

class MeleeWeapon {
 private:
  std::string id_;
  std::string name_;
  int damage_;
  int accuracy_;

 public:
  MeleeWeapon(std::string id, const std::string name, int damage, int accuracy)
      : id_(id), name_(name), damage_(damage), accuracy_(accuracy) {}
  std::string GetID() const { return id_; }
  std::string GetName() const { return name_; }
  int GetDamage() const { return damage_; }
  int GetAccuracy() const { return accuracy_; }
};

std::vector<MeleeWeapon> LoadAllMelee(const std::string& filename);
MeleeWeapon MeleeFactory(const std::string& melee_id, const std::vector<MeleeWeapon> all_melee);

#endif  // MELEE_WEAPON_H_
