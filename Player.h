#pragma once
#include <string>
#include "MeleeWeapon.h"
#include "Gun.h"
class Player 
{
public:
	std::string name = "";
	int health = 100;
	int MaxHealth = 100;
	int MentalHealth = 100;
	int level = 1;
	int experience = 0;
	int attack = 0;
	bool defend = 0;
	MeleeWeapon CurrentMelee;
	GunWeapon CurrentGun;
	Player(MeleeWeapon& melee, GunWeapon& gun);
	//Armor CurrentArmor;
	void takeDamage(int damage);
	//void heal(int amount);
	bool isAlive();
	/*void setDefend();
	void endDefend();
	bool isDefend();*/
	void GainExperience(int amount);
};