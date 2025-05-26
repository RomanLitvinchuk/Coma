#include "TextView.h"
#include <iostream>

void TextView::ClearScreen() 
{
	system("cls");
}


void TextView::showMainMenu() 
{
	std::cout << u8"\n==========КОМА==========\n"
		<< u8"[1] Новая игра\n"
		<< u8"[2] Загрузить игру\n"
		<< u8"[3] Выход\n"
		<< u8"========================\n";
}

void TextView::showGameMenu() 
{
	std::cout << u8"\n==========МЕНЮ==========\n"
		<< u8"[1] Передвижение\n"
		<< u8"[2] Боёвка\n"
		<< u8"[3] Сохранить игру\n"
		<< u8"[4] Главное меню\n"
		<< u8"========================\n";
}

void TextView::ShowCombatMenu()
{
	std::cout << u8"========================\n"
		<< u8"[1] Атака\n"
		<< u8"[2] Защита\n"
		<< u8"[3] Предметы\n"
		<< u8"========================";
}

void TextView::showMessage(const std::string& str) 
{
	std::cout << u8" " << str << "\n";
}