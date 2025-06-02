#pragma once
#include <string>

class GunWeapon
{
private:
	std::string id;
	std::string name;
	int damage;
	int accuracy;
	int cooldown;
public:
	GunWeapon(const std::string id, const std::string name, int damage, int accuracy, int cooldown) : id(id), name(name), damage(damage), accuracy(accuracy), cooldown(cooldown) {}
	std::string getID() const { return id; }
	std::string getName() const { return name; }
	int getDamage() const { return damage; }
	int getAccuracy() const { return accuracy; }
	int getCooldown() const { return cooldown; }

};

GunWeapon GunLoader(const std::string& filename, const std::string& GunID);