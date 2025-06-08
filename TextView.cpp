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

void TextView::ShowCombatMenu(const Player& player)
{
	std::cout << u8"========================\n"
		<< u8"[1] �����\n"
		<< u8"[2] ������\n"
		<< u8"[3] ��������\n"
		<< u8"[4] ������ �����������\n" 
		<< u8"��������: " << player.getHealth() << "\n"
		<< u8"========================\n";
}

void TextView::ShowEnemyListInCombat(const std::vector<Enemy>& enemies) 
{
	std::cout << u8"========================\n"
		<< u8"[0] �����\n";

	for (int i = 1; i <= enemies.size(); ++i) 
	{
		std::cout << u8"[" << i << "]" << enemies[i-1].getName() << " " << enemies[i-1].getHealth() << "\n";
	}
	std::cout << u8"========================\n";


}

void TextView::showPlayerMenu(const Player& player)
{
	std::cout << u8"===========PLAYER===========\n"
		<< u8"��������: " << player.getHealth() << "\n"
		<< u8"��������: " << player.getMentalHealth() << "\n"
		<< u8"�������: " << player.getLevel() << "\n"
		<< u8"����� �� ���������� ������: " << 100 - player.getExperience() << "\n"
		<< u8"������: " << player.CurrentMelee.getName() << "\n"
		<< u8"��������: " << player.CurrentGun.getName() << "\n"
		<< u8"[1] �����\n"
		<< u8"[2] ��������\n";
		

}

void TextView::showLevelMenu(const Player& player) 
{
	std::cout << u8"===========��������===========\n"
		<< u8"��������� ���� �������������: " << player.getLevelPoints() << "\n"
		<< u8"������������ ��������: " << player.getMaxHealth() << "\n"
		<< u8"���������� �������� ���: " << player.getMeleeLevel() << "\n"
		<< u8"���������� �������� ���: " << player.getGunLevel() << "\n"
		<< u8"���������: " << player.getIntelligence() << "\n"
		<< u8"[1] �����\n";
		std::cout << u8"[2] ��������� ����. ��������\n"
			<< u8"[3] ��������� ������� ���\n"
			<< u8"[4] ��������� ������� ���\n"
			<< u8"[5] ��������� ���������\n";
}

void TextView::showEnemyList(const std::vector<Enemy>& enemies) 
{
	std::cout << u8"\n============�����============\n";
		for (const auto& curenemy : enemies) 
		{
			std::cout << u8"\n[" << curenemy.getID() << u8"]" << curenemy.getName() << "\n"
				<< u8"��������: " << curenemy.getHealth() << "\n"
				<< u8"����: " << curenemy.getAttack();
			std::cout << "\n";
		}
		std::cout << u8"[0] �����\n"
			<< u8"=============================\n";
}


void TextView::showMeleeStats(const MeleeWeapon& melee) 
{
	std::cout << u8"[" << melee.getID() << u8"]" << melee.getName() << "\n"
		<< u8"����: " << melee.getDamage() << "\n"
		<< u8"��������: " << melee.getAccuracy() << "\n";
}


void TextView::showMessage(const std::string& str) 
{
	std::cout << u8"\n" << str << "\n";
}

void TextView::ShowInventoryInCombat(const Player& player)
{
	std::cout << u8"\n===============��������===============\n"
		<< u8"[0] �����\n";
	for (int i = 1; i <= player.inventory.items.size(); ++i) 
	{
		std::cout << u8"[" << i << u8"] " << player.inventory.items[i - 1].getName() << " " << player.inventory.items[i - 1].getHealAmount() << "\n";
	}
	std::cout << u8"======================================\n";
}