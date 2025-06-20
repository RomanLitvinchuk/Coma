#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "gun.h"
#include "inventory.h"
#include "melee_weapon.h"
class Player {
 private:
  std::string name = "";
  int health = 100;
  int MentalHealth = 100;
  int MaxHealth = 100;
  int level = 1;
  int experience = 0;
  int LevelPoints = 0;
  int MeleeLevel = 1;
  int GunLevel = 1;
  int intelligence = 1;
  bool isDefend = false;

 public:
  MeleeWeapon CurrentMelee;
  GunWeapon CurrentGun;
  Inventory inventory;
  Player(MeleeWeapon& melee, GunWeapon& gun);
  // Armor CurrentArmor;
  void TakeDamage(int damage);
  bool IsAlive() const;
  // bool IsDefending() const { return isDefend; }
  void SetDefending() { isDefend = true; }
  void StopDefending() { isDefend = false; }
  void GainExperience(int amount);
  int GetHealth() const { return health; }
  int GetMaxHealth() const { return MaxHealth; }
  int GetMentalHealth() const { return MentalHealth; }
  int GetLevel() const { return level; }
  int GetLevelPoints() const { return LevelPoints; }
  void SetLevelPoints(int amount) { LevelPoints = amount; }
  int GetExperience() const { return experience; }
  std::string GetPlayerName() const { return name; }
  void SetPlayerName(const std::string& NewName) { name = NewName; }
  int GetMeleeLevel() const { return MeleeLevel; }
  int GetGunLevel() const { return GunLevel; }
  int GetIntelligence() const { return intelligence; }
  void MeleeLevelUp() { ++MeleeLevel; }
  void GunLevelUp() { ++GunLevel; }
  void IntelligenceUp() { ++intelligence; }
  void MaxHealthUp() { MaxHealth += 20; }
  void Heal(int amount) { health += amount; }
};

#endif  // PLAYER_H_
