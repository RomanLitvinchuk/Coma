#include "view.h"
#include <iostream>
#include <vector>
#include "enemy.h"
#include "player.h"

void View::ClearScreen() 
{
	system("cls");
}


void View::ShowMainMenu() 
{
	std::cout << u8"\n==========����==========\n"
		<< u8"[1] ����� ����\n"
		<< u8"[2] ��������� ����\n"
		<< u8"[3] �����\n"
		<< u8"========================\n";
}

void View::ShowGameMenu() 
{
	std::cout << u8"\n==========����==========\n"
		<< u8"[1] ������������\n"
		<< u8"[2] ��������\n"
		<< u8"[3] �����\n"
		<< u8"[4] ��������� ����\n"
		<< u8"[5] ������� ����\n"
		<< u8"========================\n";
}

void View::ShowCombatMenu(const Player& player)
{
	std::cout << u8"========================\n"
		<< u8"[1] �����\n"
		<< u8"[2] ������\n"
		<< u8"[3] ��������\n"
		<< u8"[4] ������ �����������\n" 
		<< u8"��������: " << player.GetHealth() << "\n"
		<< u8"========================\n";
}

void View::ShowEnemyListInCombat(const std::vector<Enemy>& enemies) 
{
	std::cout << u8"========================\n"
		<< u8"[0] �����\n";

	for (int i = 1; i <= enemies.size(); ++i) 
	{
		std::cout << u8"[" << i << "]" << enemies[i-1].GetName() << " " << enemies[i-1].GetHealth() << "\n";
	}
	std::cout << u8"========================\n";


}

void View::ShowPlayerMenu(const Player& player)
{
	std::cout << u8"===========PLAYER===========\n"
		<< u8"��������: " << player.GetHealth() << "\n"
		<< u8"��������: " << player.GetMentalHealth() << "\n"
		<< u8"�������: " << player.GetLevel() << "\n"
		<< u8"����� �� ���������� ������: " << 100 - player.GetExperience() << "\n"
		<< u8"������: " << player.CurrentMelee.GetName() << "\n"
		<< u8"��������: " << player.CurrentGun.GetName() << "\n"
		<< u8"[1] �����\n"
		<< u8"[2] ��������\n";
		

}

void View::ShowLevelMenu(const Player& player) 
{
	std::cout << u8"===========��������===========\n"
		<< u8"��������� ���� �������������: " << player.GetLevelPoints() << "\n"
		<< u8"������������ ��������: " << player.GetMaxHealth() << "\n"
		<< u8"���������� �������� ���: " << player.GetMeleeLevel() << "\n"
		<< u8"���������� �������� ���: " << player.GetGunLevel() << "\n"
		<< u8"���������: " << player.GetIntelligence() << "\n"
		<< u8"[1] �����\n";
		std::cout << u8"[2] ��������� ����. ��������\n"
			<< u8"[3] ��������� ������� ���\n"
			<< u8"[4] ��������� ������� ���\n"
			<< u8"[5] ��������� ���������\n";
}

void View::ShowEnemyList(const std::vector<Enemy>& enemies) 
{
	std::cout << u8"\n============�����============\n";
		for (const auto& curenemy : enemies) 
		{
			std::cout << u8"\n[" << curenemy.GetID() << u8"]" << curenemy.GetName() << "\n"
				<< u8"��������: " << curenemy.GetHealth() << "\n"
				<< u8"����: " << curenemy.GetAttack();
			std::cout << "\n";
		}
		std::cout << u8"[0] �����\n"
			<< u8"=============================\n";
}


void View::ShowMeleeStats(const MeleeWeapon& melee) 
{
	std::cout << u8"[" << melee.GetID() << u8"]" << melee.GetName() << "\n"
		<< u8"����: " << melee.GetDamage() << "\n"
		<< u8"��������: " << melee.GetAccuracy() << "\n";
}


void View::ShowMessage(const std::string& str) 
{
	std::cout << u8"\n" << str << "\n";
}

void View::ShowInventoryInCombat(const Player& player)
{
	std::cout << u8"\n===============��������===============\n"
		<< u8"[0] �����\n";
	for (int i = 1; i <= player.inventory.items.size(); ++i) 
	{
		std::cout << u8"[" << i << u8"] " << player.inventory.items[i - 1].GetName() << " " << player.inventory.items[i - 1].GetHealAmount() << "\n";
	}
	std::cout << u8"======================================\n";
}