#include "Player.h";
#include "TextView.h"
#include <iostream>

Player::Player(MeleeWeapon& melee, GunWeapon& gun) : CurrentMelee(melee), CurrentGun(gun) {}

bool Player::isAlive() const { return (health > 0 and MentalHealth > 0); }
void Player::takeDamage(int damage) 
{
	if (!isDefend) 
	{
		health -= damage;
	}
	else 
	{
		health -= damage/2;
	}
	
}

void Player::GainExperience(int amount) 
{
	experience += amount;
	std::cout << u8"Вы получили " << amount << " опыта!\n";
	while (experience >= 100) 
	{
		++level;
		std::cout << u8"Вы достигли уровня " << level << "!\n";
		++LevelPoints;
		health = MaxHealth;
		experience -= 100;
	}
}