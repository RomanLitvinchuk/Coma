#include "Enemy.h"
#include <iostream>

Enemy::Enemy(int id, const std::string& name, int health, int attack, int experience)
	: id(id), name(name), health(health), attack(attack), experience(experience) {}

int Enemy::getAttack() { return attack; }
int Enemy::getExperience() { return experience; }
std::string Enemy::getName(){ return name; }
bool Enemy::isAlive() { return health > 0; }
void Enemy::takeDamage(int amount) 
{
	health -= amount;
	isAlive();
}