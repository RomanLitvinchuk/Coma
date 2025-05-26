#pragma once
#include <string>

class Enemy 
{
private:
	int id;
	int health;
	int attack;
	int experience;
	std::string name;
public:
	Enemy(int id, const std::string& name, int health, int attack, int experience);
	int getAttack();
	int getExperience();
	std::string getName();
	bool isAlive();
	void takeDamage(int amount);
};