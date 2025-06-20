#ifndef ENEMY_FACTORY_H_
#define ENEMY_FACTORY_H_

#include <string>
#include <vector>

#include "enemy.h"

inline std::vector<Enemy> EnemyFactory(
    const std::vector<Enemy> all_enemies,
    const std::vector<std::string>& enemy_ids) {
  std::vector<Enemy> enemies;

  for (const auto& enemy_id : enemy_ids) {
    bool found = false;

    // Ищем шаблон врага с нужным ID
    for (const auto& templ : all_enemies) {
      if (templ.GetID() == enemy_id) {
        enemies.push_back(templ);
        found = true;
        break;
      }
    }

    // Если враг не найден - бросаем исключение
    if (!found) {
      // throw std::runtime_error("Enemy template '" + enemyId + "' not found");
    }
  }

  return enemies;
}

#endif  // ENEMY_FACTORY_H_
