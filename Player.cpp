#include "Player.h";
#include <iostream>

Player::Player(const std::string& name) : name(name), health(100), MentalHealth(100), MaxHealth(100), experience(0), level(1), defend(false) {}

int Player::getHealth() { return health; }
int Player::getMentalHealth(){ return MentalHealth; }
bool Player::isAlive() { return (health > 0 and MentalHealth > 0); }
void Player::takeDamage(int damage) 
{
	health -= damage;
	isAlive();
}

void Player::GainExperience(int amount) 
{
	experience += amount;
	std::cout << u8"Вы получили " << amount << " опыта!\n";
	if (experience >= 100) 
	{
		++level;
		std::cout << u8"Вы достигли уровня " << level << "!\n";
		MaxHealth += 10;
		health = MaxHealth;
	}
}

int Player::getAttack() { return attack; }
void Player::setDefend() { defend = true; }
void Player::endDefend() { defend = false; }
bool Player::isDefend() { return defend; }