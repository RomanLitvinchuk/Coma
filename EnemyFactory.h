#pragma once
#include <vector>
#include <string>
#include "Enemy.h"

std::vector<Enemy> EnemyFactory(const std::vector<Enemy> allEnemies, const std::vector<std::string>& enemyIds) {
    std::vector<Enemy> enemies;

    for (const auto& enemyId : enemyIds) {
        bool found = false;

        // Ищем шаблон врага с нужным ID
        for (const auto& templ : allEnemies) {
            if (templ.getID() == enemyId) {
                enemies.push_back(templ);
                found = true;
                break;
            }
        }

        // Если враг не найден - бросаем исключение
        if (!found) {
            //throw std::runtime_error("Enemy template '" + enemyId + "' not found");
        }
    }

    return enemies;
}