#include "Player.h";
#include <iostream>

Player::Player(MeleeWeapon& melee, GunWeapon& gun) : CurrentMelee(melee), CurrentGun(gun) {}

bool Player::isAlive() { return (health > 0 and MentalHealth > 0); }
void Player::takeDamage(int damage) 
{
	health -= damage;
	isAlive();
}

void Player::GainExperience(int amount) 
{
	experience += amount;
	std::cout << u8"�� �������� " << amount << " �����!\n";
	while (experience >= 100) 
	{
		++level;
		std::cout << u8"�� �������� ������ " << level << "!\n";
		health = MaxHealth;
		experience -= 100;
	}
}