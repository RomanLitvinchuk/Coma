#ifndef MELEE_WEAPON_H
#define MELEE_WEAPON_H

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
	std::string GetID() const { return id; }
	std::string GetName() const { return name; }
	int GetDamage() const { return damage; }
	int GetAccuracy() const { return accuracy; }
};

MeleeWeapon MeleeLoader(const std::string& filename, const std::string& IdForMelee);

#endif