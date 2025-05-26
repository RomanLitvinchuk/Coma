#include "TextView.h"
#include <iostream>

void TextView::ClearScreen() 
{
	system("cls");
}


void TextView::showMainMenu() 
{
	std::cout << u8"\n==========����==========\n"
		<< u8"[1] ����� ����\n"
		<< u8"[2] ��������� ����\n"
		<< u8"[3] �����\n"
		<< u8"========================\n";
}

void TextView::showGameMenu() 
{
	std::cout << u8"\n==========����==========\n"
		<< u8"[1] ������������\n"
		<< u8"[2] �����\n"
		<< u8"[3] ��������� ����\n"
		<< u8"[4] ������� ����\n"
		<< u8"========================\n";
}

void TextView::ShowCombatMenu()
{
	std::cout << u8"========================\n"
		<< u8"[1] �����\n"
		<< u8"[2] ������\n"
		<< u8"[3] ��������\n"
		<< u8"========================";
}

void TextView::showMessage(const std::string& str) 
{
	std::cout << u8" " << str << "\n";
}