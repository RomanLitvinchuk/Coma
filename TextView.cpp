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
		<< u8"[2] Персонаж\n"
		<< u8"[3] Боёвка\n"
		<< u8"[4] Сохранить игру\n"
		<< u8"[5] Главное меню\n"
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

void TextView::showPlayerMenu(const Player& player)
{
	std::cout << u8"===========PLAYER===========\n"
		<< u8"Здоровье: " << player.health << "\n"
		<< u8"Рассудок: " << player.MentalHealth << "\n"
		<< u8"Уровень: " << player.level << "\n"
		<< u8"Опыта до следующего уровня: " << 100 - player.experience << "\n"
		<< u8"Оружие: " << player.CurrentMelee.name << "\n"
		<< u8"Пистолет: " << player.CurrentGun.name << "\n"
		<< u8"[1] Назад\n";
}

void TextView::showEnemyList(const std::vector<Enemy>& enemies) 
{
	std::cout << u8"\n============ВРАГИ============\n";
		for (const auto& curenemy : enemies) 
		{
			std::cout << u8"\n[" << curenemy.id << u8"]" << curenemy.name << "\n"
				<< u8"Здоровье: " << curenemy.health << "\n"
				<< u8"Урон: " << curenemy.attack;
			std::cout << "\n";
		}
}

void TextView::showMeleeStats(const MeleeWeapon& melee) 
{
	std::cout << u8"[" << melee.id << u8"]" << melee.name << "\n"
		<< u8"Урон: " << melee.damage << "\n"
		<< u8"Точность: " << melee.accuracy << "\n";
}


void TextView::showMessage(const std::string& str) 
{
	std::cout << u8"\n" << str << "\n";
}