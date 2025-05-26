#pragma once
#include <string>
class Player 
{
private:
	std::string name;
	int health;
	int MaxHealth;
	int MentalHealth;
	int level;
	int experience;
	int attack;
	bool defend;
	//Melee CurrentMelee;
	//Gun CurrentGun;
	//Armor CurrentArmor;
public:
	Player(const std::string& name);
	void takeDamage(int damage);
	int getAttack();
	//void heal(int amount);
	//void defend();
	void setHealth(int amount);
	int getHealth();
	void setMentalHealth(int amount);
	int getMentalHealth();
	bool isAlive();
	void setDefend();
	void endDefend();
	bool isDefend();
	void GainExperience(int amount);

};