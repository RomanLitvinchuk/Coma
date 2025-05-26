#pragma once
#include "States.h"

class GameController 
{
private:
	GameState* state;
public:
	GameController(GameState* state) : state(state) {}

	void handleMainMenu(int choice);
	void handleGameMenu(int choice);
};