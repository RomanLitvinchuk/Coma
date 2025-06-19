#ifndef ENEMY_FACTORY_H
#define ENEMY_FACTORY_H

#include <vector>
#include <string>
#include "enemy.h"

std::vector<Enemy> EnemyFactory(const std::vector<Enemy> allEnemies, const std::vector<std::string>& enemyIds) {
    std::vector<Enemy> enemies;

    for (const auto& enemyId : enemyIds) {
        bool found = false;

        // ���� ������ ����� � ������ ID
        for (const auto& templ : allEnemies) {
            if (templ.GetID() == enemyId) {
                enemies.push_back(templ);
                found = true;
                break;
            }
        }

        // ���� ���� �� ������ - ������� ����������
        if (!found) {
            //throw std::runtime_error("Enemy template '" + enemyId + "' not found");
        }
    }

    return enemies;
}

#endif