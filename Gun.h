#ifndef GUN_H_
#define GUN_H_

#include <string>

class GunWeapon {
 private:
  std::string id;
  std::string name;
  int damage;
  int accuracy;
  int cooldown;

 public:
  GunWeapon(const std::string id, const std::string name, int damage,
            int accuracy, int cooldown)
      : id(id),
        name(name),
        damage(damage),
        accuracy(accuracy),
        cooldown(cooldown) {}
  std::string GetID() const { return id; }
  std::string GetName() const { return name; }
  int GetDamage() const { return damage; }
  int GetAccuracy() const { return accuracy; }
  int GetCooldown() const { return cooldown; }
};

GunWeapon GunLoader(const std::string& filename, const std::string& GunID);

#endif  // GUN_H_
