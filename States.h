#pragma once
#include "Player.h"
#include "Enemy.h"
#include <vector>
enum class States {
    MAIN_MENU,
    GAME_MENU,
    COMBAT_MENU,
    CHOOSE_ENEMIES_MENU,
    ENEMY_LIST_MENU,
    PLAYER_MENU,
    LEVEL_MENU,
    INVENTORY_IN_COMBAT_MENU
};




class GameState 
{ 
public:
    Player& player;
    std::vector<Enemy> enemies;
    States currentState = States::MAIN_MENU;
    GameState(Player& player, std::vector<Enemy>& enemies) : player(player), enemies(enemies) {}
};