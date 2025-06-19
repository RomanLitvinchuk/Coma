#ifndef ENEMY_H
#define ENEMY_H

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
	int GetAttack() const { return attack; }
	int GetExperience() const { return experience; }
	std::string GetName() const { return name; }
	std::string GetID() const { return id; }
	bool IsAlive() const { return health > 0; }
	void TakeDamage(int amount);
	int GetHealth() const { return health; }
};

std::vector<Enemy> LoadAllEnemies(const std::string& filename);

#endif
