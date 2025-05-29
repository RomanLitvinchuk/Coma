#pragma once
#include <string>

class GunWeapon
{
public:
	std::string id;
	std::string name;
	int damage;
	int acuracy;
	int cooldown;

	GunWeapon(const std::string id, const std::string name, int damage, int accuracy, int cooldown) : id(id), name(name), damage(damage), cooldown(cooldown) {}
};

GunWeapon GunLoader(const std::string& filename, const std::string& GunID);