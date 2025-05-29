#pragma once
#include <string>

class MeleeWeapon 
{
public:
	std::string id;
	std::string name;
	int damage;
	int accuracy;

	MeleeWeapon(std::string id, const std::string name, int damage, int accuracy) : id(id), name(name), damage(damage), accuracy(accuracy) {}

};

MeleeWeapon MeleeLoader(const std::string& filename, const std::string& IdForMelee);