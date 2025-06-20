#include "enemy.h"

#include <iostream>

Enemy::Enemy(std::string id, const std::string& name, int health, int attack,
             int experience)
    : id_(id),
      name_(name),
      health_(health),
      attack_(attack),
      experience_(experience) {}

void Enemy::TakeDamage(int amount) {
  health_ -= amount;
  if (health_ < 0) {
    health_ = 0;
  }
}
