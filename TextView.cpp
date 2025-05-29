#include "TextView.h"
#include <iostream>
#include <vector>
#include "Enemy.h"
#include "Player.h"

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
		<< u8"[2] ��������\n"
		<< u8"[3] �����\n"
		<< u8"[4] ��������� ����\n"
		<< u8"[5] ������� ����\n"
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

void TextView::showPlayerMenu(const Player& player)
{
	std::cout << u8"===========PLAYER===========\n"
		<< u8"��������: " << player.health << "\n"
		<< u8"��������: " << player.MentalHealth << "\n"
		<< u8"�������: " << player.level << "\n"
		<< u8"����� �� ���������� ������: " << 100 - player.experience << "\n"
		<< u8"������: " << player.CurrentMelee.name << "\n"
		<< u8"��������: " << player.CurrentGun.name << "\n"
		<< u8"[1] �����\n";
}

void TextView::showEnemyList(const std::vector<Enemy>& enemies) 
{
	std::cout << u8"\n============�����============\n";
		for (const auto& curenemy : enemies) 
		{
			std::cout << u8"\n[" << curenemy.id << u8"]" << curenemy.name << "\n"
				<< u8"��������: " << curenemy.health << "\n"
				<< u8"����: " << curenemy.attack;
			std::cout << "\n";
		}
}

void TextView::showMeleeStats(const MeleeWeapon& melee) 
{
	std::cout << u8"[" << melee.id << u8"]" << melee.name << "\n"
		<< u8"����: " << melee.damage << "\n"
		<< u8"��������: " << melee.accuracy << "\n";
}


void TextView::showMessage(const std::string& str) 
{
	std::cout << u8"\n" << str << "\n";
}