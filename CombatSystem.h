#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>
class CombatSystem 
{
    enum class CombatAction {
        ATTACK,
        DEFEND,
        USE_ITEM
    };

    struct CombatResult {
        bool playerWon;
        bool playerFled;
    };
    CombatResult executeCombat(Player& player, std::vector<Enemy>& enemies, CombatAction playerAction);
    void playerAttack(Player& player, Enemy& enemy);
    void playerDefend(Player& player);
    void enemyAttack(Enemy& enemy, Player& player);
};