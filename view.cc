#include "view.h"

#include <conio.h>

#include <iostream>
#include <vector>

#include "enemy.h"
#include "player.h"
#include "room.h"

void View::ClearScreen() { std::cout << "\033[2J\033[1;1H"; }

void View::ShowMainMenu() {
  std::cout << u8"╔═════════КОМА═════════╗\n"
            << u8"║ › [1] Новая игра     ║\n"
            << u8"║ › [2] Загрузить игру ║\n"
            << u8"║ › [3] Выход          ║\n"
            << u8"╚══════════════════════╝\n";
}

void View::ShowGameMenu() {
  std::cout << u8"╔══════════МЕНЮ═════════╗\n"
            << u8"║ › [1] Передвижение    ║\n"
            << u8"║ › [2] Персонаж        ║\n"
            << u8"║ › [3] Сохранить игру  ║\n"
            << u8"║ › [4] Главное меню    ║\n"
            << u8"╚═══════════════════════╝\n";
}

void View::ShowCombatMenu(const Player& player) {
  std::cout << u8"╔═══════════════════════════╗\n"
            << u8"║ › [1] Атака               ║\n"
            << u8"║ › [2] Защита              ║\n"
            << u8"║ › [3] Предметы            ║\n"
            << u8"║ › [4] Осмотр противников  ║\n"
            << u8"╚═══════════════════════════╝\n"
            << u8"HP: " << player.GetHealth() << "\n";
}

void View::ShowEnemyListInCombat(const std::vector<Enemy>& enemies) {
  std::cout << u8"╔═══════════════════════════╗\n" << u8"║ › [0] Назад\n";

  for (int i = 1; i <= enemies.size(); ++i) {
    std::cout << u8"║ › [" << i << "]" << enemies[i - 1].GetName() << " "
              << enemies[i - 1].GetHealth() << "\n";
  }
  std::cout << u8"╚═══════════════════════════╝\n";
}

void View::ShowPlayerMenu(const Player& player) {
  std::cout << u8"╔══════════════PLAYER═════════════╗\n"
            << u8"║ Здоровье: " << player.GetHealth()
            << u8"                   \n"
            << u8"║ Рассудок: " << player.GetMentalHealth()
            << u8"                   \n"
            << u8"║ Уровень: " << player.GetLevel()
            << u8"                      \n"
            << u8"║ Опыта до следующего уровня: "
            << 100 - player.GetExperience() << u8" \n"
            << u8"║ Оружие: " << player.current_melee_.GetName()
            << u8"                   \n"
            << u8"║ Пистолет: " << player.current_gun_.GetName()
            << u8"                    \n"
            << u8"║═════════════════════════════════║\n"
            << u8"║ › [1] Назад                     ║\n"
            << u8"║ › [2] Прокачка                  ║\n"
            << u8"║ › [3] Поменять оружие (ближнее) ║\n"  
            << u8"║ › [4] Поменять оружие (дальнее) ║\n"
            << u8"║ › [5] Предметы                  ║\n"
            << u8"╚═════════════════════════════════╝\n";
}

void View::ShowLevelMenu(const Player& player) {
  std::cout << u8"╔══════════════ПРОКАЧКА══════════════╗\n"
            << u8"║ Доступные очки характеристик: " << player.GetLevelPoints()
            << u8"    \n"
            << u8"║ Максимальное здоровье: " << player.GetMaxHealth()
            << u8"         \n"
            << u8"║ Мастерство ближнего боя: " << player.GetMeleeLevel()
            << u8"         \n"
            << u8"║ Мастерство дальнего боя: " << player.GetGunLevel()
            << u8"         \n"
            << u8"║ Интеллект: " << player.GetIntelligence()
            << u8"                       \n"
            << u8"║════════════════════════════════════║\n"
            << u8"║ › [1] Назад                        ║\n"
            << u8"║ › [2] Прокачать макс. здоровье     ║\n"
            << u8"║ › [3] Прокачать ближний бой        ║\n"
            << u8"║ › [4] Прокачать дальний бой        ║\n"
            << u8"║ › [5] Прокачать интеллект          ║\n"
            << u8"╚════════════════════════════════════╝\n";
}

void View::ShowEnemyList(const std::vector<Enemy>& enemies) {
  std::cout << u8"\n╔═════════════ВРАГИ════════════╗\n";
  for (const auto& curenemy : enemies) {
    std::cout << u8"║ [" << curenemy.GetID() << u8"]" << curenemy.GetName()
              << "\n"
              << u8"║ Здоровье: " << curenemy.GetHealth() << "\n"
              << u8"║ Урон: " << curenemy.GetAttack() << "\n"
              << u8"║══════════════════════════════║\n";
  }
  std::cout << u8"║ › [0] Назад                  ║\n"
            << u8"╚══════════════════════════════╝\n";
}

void View::ShowMeleeStats(const MeleeWeapon& melee) {
  std::cout << u8"[" << melee.GetID() << u8"]" << melee.GetName() << "\n"
            << u8"Урон: " << melee.GetDamage() << "\n"
            << u8"Точность: " << melee.GetAccuracy() << "\n";
}

void View::ShowMessage(const std::string& str) {
  std::cout << u8"\n" << str << "\n";
}

void View::ShowInventoryItemsMenu(const Player& player) {
  std::cout << u8"╔══════════════ПРЕДМЕТЫ══════════════╗\n";
  for (int i = 1; i <= player.inventory_.items_.size(); ++i) {
    std::cout << u8"║ › [" << i << u8"] "
              << player.inventory_.items_[i - 1].GetName() << " "
              << player.inventory_.items_[i - 1].GetHealAmount() << "\n";
  }
  std::cout << u8"║════════════════════════════════════║\n"
            << u8"║ › [0] Назад                        ║\n"
            << u8"╚════════════════════════════════════╝\n";
}

void View::ShowRoomMenu(const GameState& state) {
  std::cout << u8"╔═════════════════════════════════╗\n"
            << u8"║ " << state.current_room_.name_ << "\n"
            << u8"║ " << state.current_room_.description_ << "\n"
            << u8"║ › [1] Назад\n"
            << u8"║ › [2] Исследовать\n"
            << u8"║ › [3] Перейти в другие комнаты\n"
            << u8"╚═════════════════════════════════╝\n";
}

void View::ShowRoomChooseMenu(const GameState& state,
                              const std::vector<Room>& all_rooms) {
  std::cout << u8"╔═══════════════════════════════════╗\n";
  if (!state.current_room_.connected_rooms_.empty()) {
    for (int i = 1; i <= state.current_room_.connected_rooms_.size(); ++i) {
      std::cout << u8"║ › [" << i << u8"] "
                << GetRoomNameById(state.current_room_.connected_rooms_[i - 1],
                                   all_rooms)
                << "\n";
    }
  }
  std::cout << u8"║═══════════════════════════════════║\n"
            << u8"║ › [0] Назад                       ║\n"
            << u8"╚═══════════════════════════════════╝\n";
}

void View::ShowInventoryMeleeMenu(const Player& player) 
{
    std::cout << u8"╔═════════════════════════════════╗\n";
    for (int i = 1; i <= player.inventory_.melees_.size(); ++i) 
    {
        std::cout << u8"║ › [" << i << u8"] "
            << player.inventory_.melees_[i - 1].GetName() << "\n";
    }
	std::cout << u8"║════════════════════════════════════║\n"
		      << u8"║ › [0] Назад                        ║\n"
		      << u8"╚════════════════════════════════════╝\n";
}
