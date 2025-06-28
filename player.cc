#include "player.h";

#include <iostream>
#include <vector>

#include "view.h"

Player::Player(MeleeWeapon& melee, GunWeapon& gun)
    : current_melee_(melee), current_gun_(gun) {}

bool Player::IsAlive() const { return (health_ > 0 and mental_health_ > 0); }

void Player::TakeDamage(int damage) {
  if (!is_defend_) {
    health_ -= damage;
  } else {
    health_ -= damage / 2;
  }
}

void Player::TakeMentalDamage(int mental_damage) 
{
    mental_health_ -= mental_damage;
}

void Player::GainExperience(int amount) {
  experience_ += amount;
  std::cout << u8"Вы получили " << amount << u8" опыта!\n";
  while (experience_ >= 100) {
    ++level_;
    std::cout << u8"Вы достигли уровня " << level_ << u8"!\n";
    ++level_points_;
    health_ = max_health_;
    experience_ -= 100;
  }
}
