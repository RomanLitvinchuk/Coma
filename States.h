#pragma once


enum class States {
    MAIN_MENU,
    GAME_MENU,
    COMBAT_MENU,
    PLAYER_MENU
};




class GameState 
{
    States currentState = States::MAIN_MENU;
};