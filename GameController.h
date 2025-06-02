#pragma once
#include "States.h"
#include "Player.h"

class GameController 
{
private:
	GameState* state;
public:
	GameController(GameState* state) : state(state) {}

	void handleMainMenu(int choice);
	void handleGameMenu(int choice);
	void handlePlayerMenu(int choice);
	void handleLevelMenu(int choice, Player& player);
};