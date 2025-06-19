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
	std::cout << u8"\n==========КОМА==========\n"
		<< u8"[1] Новая игра\n"
		<< u8"[2] Загрузить игру\n"
		<< u8"[3] Выход\n"
		<< u8"========================\n";
}

void View::ShowGameMenu() 
{
	std::cout << u8"\n==========МЕНЮ==========\n"
		<< u8"[1] Передвижение\n"
		<< u8"[2] Персонаж\n"
		<< u8"[3] Боёвка\n"
		<< u8"[4] Сохранить игру\n"
		<< u8"[5] Главное меню\n"
		<< u8"========================\n";
}

void View::ShowCombatMenu(const Player& player)
{
	std::cout << u8"========================\n"
		<< u8"[1] Атака\n"
		<< u8"[2] Защита\n"
		<< u8"[3] Предметы\n"
		<< u8"[4] Осмотр противников\n" 
		<< u8"Здоровье: " << player.GetHealth() << "\n"
		<< u8"========================\n";
}

void View::ShowEnemyListInCombat(const std::vector<Enemy>& enemies) 
{
	std::cout << u8"========================\n"
		<< u8"[0] Назад\n";

	for (int i = 1; i <= enemies.size(); ++i) 
	{
		std::cout << u8"[" << i << "]" << enemies[i-1].GetName() << " " << enemies[i-1].GetHealth() << "\n";
	}
	std::cout << u8"========================\n";


}

void View::ShowPlayerMenu(const Player& player)
{
	std::cout << u8"===========PLAYER===========\n"
		<< u8"Здоровье: " << player.GetHealth() << "\n"
		<< u8"Рассудок: " << player.GetMentalHealth() << "\n"
		<< u8"Уровень: " << player.GetLevel() << "\n"
		<< u8"Опыта до следующего уровня: " << 100 - player.GetExperience() << "\n"
		<< u8"Оружие: " << player.CurrentMelee.GetName() << "\n"
		<< u8"Пистолет: " << player.CurrentGun.GetName() << "\n"
		<< u8"[1] Назад\n"
		<< u8"[2] Прокачка\n";
		

}

void View::ShowLevelMenu(const Player& player) 
{
	std::cout << u8"===========ПРОКАЧКА===========\n"
		<< u8"Доступные очки характеристик: " << player.GetLevelPoints() << "\n"
		<< u8"Максимальное здоровье: " << player.GetMaxHealth() << "\n"
		<< u8"Мастерство ближнего боя: " << player.GetMeleeLevel() << "\n"
		<< u8"Мастерство дальнего боя: " << player.GetGunLevel() << "\n"
		<< u8"Интеллект: " << player.GetIntelligence() << "\n"
		<< u8"[1] Назад\n";
		std::cout << u8"[2] Прокачать макс. здоровье\n"
			<< u8"[3] Прокачать ближний бой\n"
			<< u8"[4] Прокачать дальний бой\n"
			<< u8"[5] Прокачать интеллект\n";
}

void View::ShowEnemyList(const std::vector<Enemy>& enemies) 
{
	std::cout << u8"\n============ВРАГИ============\n";
		for (const auto& curenemy : enemies) 
		{
			std::cout << u8"\n[" << curenemy.GetID() << u8"]" << curenemy.GetName() << "\n"
				<< u8"Здоровье: " << curenemy.GetHealth() << "\n"
				<< u8"Урон: " << curenemy.GetAttack();
			std::cout << "\n";
		}
		std::cout << u8"[0] Назад\n"
			<< u8"=============================\n";
}


void View::ShowMeleeStats(const MeleeWeapon& melee) 
{
	std::cout << u8"[" << melee.GetID() << u8"]" << melee.GetName() << "\n"
		<< u8"Урон: " << melee.GetDamage() << "\n"
		<< u8"Точность: " << melee.GetAccuracy() << "\n";
}


void View::ShowMessage(const std::string& str) 
{
	std::cout << u8"\n" << str << "\n";
}

void View::ShowInventoryInCombat(const Player& player)
{
	std::cout << u8"\n===============ПРЕДМЕТЫ===============\n"
		<< u8"[0] Назад\n";
	for (int i = 1; i <= player.inventory.items.size(); ++i) 
	{
		std::cout << u8"[" << i << u8"] " << player.inventory.items[i - 1].GetName() << " " << player.inventory.items[i - 1].GetHealAmount() << "\n";
	}
	std::cout << u8"======================================\n";
}