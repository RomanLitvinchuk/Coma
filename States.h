#pragma once
#include "Player.h"

enum class States {
    MAIN_MENU,
    GAME_MENU,
    COMBAT_MENU,
    PLAYER_MENU,
    LEVEL_MENU
};




class GameState 
{
public:
    States currentState = States::MAIN_MENU;
    //Player player;
};