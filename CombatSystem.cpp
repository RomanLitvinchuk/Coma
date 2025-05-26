#include "CombatSystem.h"
#include <iostream>

void CombatSystem::playerAttack(Player& player, Enemy& enemy) {
    int damage = player.getAttack();
    enemy.takeDamage(damage);
}

void CombatSystem::enemyAttack(Enemy& enemy, Player& player) {
    int damage = enemy.getAttack();
    if (player.isDefend()) {
        damage /= 2; // ������ ��������� ����
    }
    player.takeDamage(damage);
    std::cout << enemy.getName() << " ������� " << damage << " �����" << std::endl;
}



CombatSystem::CombatResult CombatSystem::executeCombat(
    Player& player, std::vector<Enemy>& enemies, CombatAction playerAction)
{
    CombatResult result{ false, false };
    // ��� ������
    switch (playerAction)
    {
    case CombatAction::ATTACK:
        if (!enemies.empty())
        {
            playerAttack(player, enemies[0]);
        }
        break;
    case CombatAction::DEFEND:
        player.setDefend();
        break;

        /*case CombatAction::USE_ITEM:
            player.usePotion();
            break;
        }*/
    }
    // �������� �� ������
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](Enemy& e) { return !e.isAlive(); }),
        enemies.end());

    if (enemies.empty()) {
        result.playerWon = true;
        player.endDefend();
        return result;
    }

    // ��� ������
    for (auto& enemy : enemies) {
        enemyAttack(enemy, player);
        if (!player.isAlive()) break;
    }

    //player.endDefense();
    return result;
}