#include "enemy.h"
#include <iostream>

Enemy::Enemy(std::string id, const std::string& name, int health, int attack, int experience)
	: id(id), name(name), health(health), attack(attack), experience(experience) {}


void Enemy::TakeDamage(int amount) 
{
	health -= amount;
	if (health < 0) { health = 0; }
}