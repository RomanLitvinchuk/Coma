#pragma once
#include <string>
#include <vector>
class Enemy 
{
public:
	std::string id;
	int health;
	int attack;
	int experience;
	std::string name;
	Enemy(std::string id, const std::string& name, int health, int attack, int experience);
	int getAttack();
	int getExperience();
	std::string getName();
	bool isAlive();
	void takeDamage(int amount);
};

std::vector<Enemy> EnemyLoader(const std::string& filename, const std::vector<int>& idsToLoad);
