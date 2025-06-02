#pragma once
#include <string>

class MeleeWeapon 
{
private:
	std::string id;
	std::string name;
	int damage;
	int accuracy;
public:
	MeleeWeapon(std::string id, const std::string name, int damage, int accuracy) : id(id), name(name), damage(damage), accuracy(accuracy) {}
	std::string getID() const { return id; }
	std::string getName() const { return name; }
	int getDamage() const { return damage; }
	int getAccuracy() const { return accuracy; }
};

MeleeWeapon MeleeLoader(const std::string& filename, const std::string& IdForMelee);