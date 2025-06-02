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
		<< u8"Здоровье: " << player.getHealth() << "\n"
		<< u8"Рассудок: " << player.getMentalHealth() << "\n"
		<< u8"Уровень: " << player.getLevel() << "\n"
		<< u8"Опыта до следующего уровня: " << 100 - player.getExperience() << "\n"
		<< u8"Оружие: " << player.CurrentMelee.getName() << "\n"
		<< u8"Пистолет: " << player.CurrentGun.getName() << "\n"
		<< u8"[1] Назад\n"
		<< u8"[2] Прокачка\n";
		

}

void TextView::showLevelMenu(const Player& player) 
{
	std::cout << u8"===========ПРОКАЧКА===========\n"
		<< u8"Доступные очки характеристик: " << player.getLevelPoints() << "\n"
		<< u8"Максимальное здоровье: " << player.getMaxHealth() << "\n"
		<< u8"Мастерство ближнего боя: " << player.getMeleeLevel() << "\n"
		<< u8"Мастерство дальнего боя: " << player.getGunLevel() << "\n"
		<< u8"Интеллект: " << player.getIntelligence() << "\n"
		<< u8"[1] Назад\n";
		std::cout << u8"[2] Прокачать макс. здоровье\n"
			<< u8"[3] Прокачать ближний бой\n"
			<< u8"[4] Прокачать дальний бой\n"
			<< u8"[5] Прокачать интеллект\n";
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
	std::cout << u8"[" << melee.getID() << u8"]" << melee.getName() << "\n"
		<< u8"Урон: " << melee.getDamage() << "\n"
		<< u8"Точность: " << melee.getAccuracy() << "\n";
}


void TextView::showMessage(const std::string& str) 
{
	std::cout << u8"\n" << str << "\n";
}