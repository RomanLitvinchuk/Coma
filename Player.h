#pragma once
#include <string>
#include "MeleeWeapon.h"
#include "Gun.h"
class Player 
{
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
public:
	MeleeWeapon CurrentMelee;
	GunWeapon CurrentGun;
	bool defend = 0;
	Player(MeleeWeapon& melee, GunWeapon& gun);
	//Armor CurrentArmor;
	void takeDamage(int damage);
	bool isAlive();
	void GainExperience(int amount);
	int getHealth() const { return health; }
	int getMaxHealth() const { return MaxHealth; }
	int getMentalHealth() const { return MentalHealth; }
	int getLevel() const { return level; }
	int getLevelPoints() const { return LevelPoints; }
	void setLevelPoints(int amount) { LevelPoints = amount; }
	int getExperience() const { return experience; }
	std::string getPlayerName() const { return name; }
	void setPlayerName(const std::string& NewName) { name = NewName; }
	int getMeleeLevel() const { return MeleeLevel; }
	int getGunLevel() const { return GunLevel; }
	int getIntelligence() const { return intelligence; }
	void MeleeLevelUp() { ++MeleeLevel; }
	void GunLevelUp() { ++GunLevel; }
	void IntelligenceUp() { ++intelligence; }
	void MaxHealthUp() { MaxHealth += 20; }
};