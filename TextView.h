#pragma once


class TextView 
{
public:
	void ClearScreen();
	void showMainMenu();
	void showGameMenu();
	void ShowCombatMenu();
	void showMessage(const std::string& str);
};