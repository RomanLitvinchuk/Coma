#pragma once
#include <string>
#include <vector>
class Enemy 
{
private:
	std::string id;
	int health;
	int attack;
	int experience;
	std::string name;
public:
	Enemy(std::string id, const std::string& name, int health, int attack, int experience);
	int getAttack() const { return attack; }
	int getExperience() const { return experience; }
	std::string getName() const { return name; }
	std::string getID() const { return id; }
	bool isAlive() const { return health > 0; }
	void takeDamage(int amount);
	int getHealth() const { return health; }
};

std::vector<Enemy> EnemyLoader(const std::string& filename, const std::vector<int>& idsToLoad);
