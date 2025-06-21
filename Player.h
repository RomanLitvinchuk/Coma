#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "gun.h"
#include "inventory.h"
#include "melee_weapon.h"
class Player {
 private:
  int health_ = 100;
  int mental_health_ = 100;
  int max_health_ = 100;
  int level_ = 1;
  int experience_ = 0;
  int level_points_ = 0;
  int melee_level_ = 1;
  int gun_level_ = 1;
  int intelligence_ = 1;
  bool is_defend_ = false;

 public:
  MeleeWeapon current_melee_;
  GunWeapon current_gun_;
  Inventory inventory_;
  Player(MeleeWeapon& melee, GunWeapon& gun);
  // Armor CurrentArmor;
  void TakeDamage(int damage);
  bool IsAlive() const;
  // bool IsDefending() const { return isDefend; }
  void SetDefending() { is_defend_ = true; }
  void StopDefending() { is_defend_ = false; }
  void GainExperience(int amount);
  int GetHealth() const { return health_; }
  int GetMaxHealth() const { return max_health_; }
  int GetMentalHealth() const { return mental_health_; }
  int GetLevel() const { return level_; }
  int GetLevelPoints() const { return level_points_; }
  void SetLevelPoints(int amount) { level_points_ = amount; }
  int GetExperience() const { return experience_; }
  int GetMeleeLevel() const { return melee_level_; }
  int GetGunLevel() const { return gun_level_; }
  int GetIntelligence() const { return intelligence_; }
  void MeleeLevelUp() { ++melee_level_; }
  void GunLevelUp() { ++gun_level_; }
  void IntelligenceUp() { ++intelligence_; }
  void MaxHealthUp() { max_health_ += 20; }
  void Heal(int amount) { health_ += amount; }
};

#endif  // PLAYER_H_
