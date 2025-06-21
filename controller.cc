#include "controller.h"

#include <iostream>

#include "view.h"

void Controller::HandleMainMenu(int choice) {
  switch (choice) {
    case 1:  // Новая игра
      state_->current_state_ = States::kGameMenu;
      View::ShowMessage(u8"Новая игра начата!");
      break;
    // case 2: Сохранение
    //	std::cin.ignore();
    case 3:
      exit(0);
      break;
    default:
      std::cin.ignore();
      View::ShowMessage(u8"Некорректный ввод!");
  }
}

void Controller::HandleGameMenu(int choice) {
  switch (choice) {
    case 1:  // Комнаты
      state_->current_state_ = States::kRoomMenu;
      break;
    case 2:  // Игрок
      state_->current_state_ = States::kPlayerMenu;
      break;
    // case 3: Сохранение
    case 4:
      state_->current_state_ = States::kMainMenu;
      break;
    default:
      std::cin.ignore();
      View::ShowMessage(u8"Некорректный ввод!");
  }
}

void Controller::HandlePlayerMenu(int choice) {
  switch (choice) {
    case 1:
      state_->current_state_ = States::kGameMenu;
      break;
    case 2:
      state_->current_state_ = States::kLevelMenu;
      break;
    case 3:
        state_->current_state_ = States::kInventoryMeleeMenu;
        break;
    //case 4: //Guns

    case 5:
        state_->current_state_ = States::kInventoryItemsMenu;
        break;
    default:
      std::cin.ignore();
      View::ShowMessage(u8"Некорректный ввод!");
  }
}

void Controller::HandleLevelMenu(int choice, Player& player) {
  switch (choice) {
    case 1:
      state_->current_state_ = States::kPlayerMenu;
      break;
    case 2:
      if (player.GetLevelPoints() > 0) {
        player.MaxHealthUp();
        player.SetLevelPoints(player.GetLevelPoints() - 1);
      } else {
        std::cin.ignore();
        View::ShowMessage(u8"Не хватает очков характеристик!");
      }
      break;
    case 3:
      if (player.GetLevelPoints() > 0) {
        player.MeleeLevelUp();
        player.SetLevelPoints(player.GetLevelPoints() - 1);
      } else {
        std::cin.ignore();
        View::ShowMessage(u8"Не хватает очков характеристик!");
      }
      break;
    case 4:
      if (player.GetLevelPoints() > 0) {
        player.GunLevelUp();
        player.SetLevelPoints(player.GetLevelPoints() - 1);
      } else {
        std::cin.ignore();
        View::ShowMessage(u8"Не хватает очков характеристик!");
      }
      break;
    case 5:
      if (player.GetLevelPoints() > 0) {
        player.IntelligenceUp();
        player.SetLevelPoints(player.GetLevelPoints() - 1);
      } else {
        std::cin.ignore();
        View::ShowMessage(u8"Не хватает очков характеристик!");
      }
      break;
    default:
      std::cin.ignore();
      View::ShowMessage(u8"Некорректный ввод!");
  }
}

CombatSystem::CombatState Controller::HandleCombatMenu(
    int choice, Player& player, std::vector<Enemy>& enemies) {
  switch (choice) {
    case 1:
      state_->current_state_ = States::kChooseEnemiesMenu;
      break;
    case 2:
      player.SetDefending();
      CombatSystem::EnemyTurn(player, enemies);
      player.StopDefending();
      if (!player.IsAlive()) {
        return CombatSystem::kEnemyWin;
      } else {
        return CombatSystem::kContinue;
      }
      break;
    case 3:
      state_->current_state_ = States::kInventoryInCombatMenu;
      break;
    case 4:
      state_->current_state_ = States::kEnemyListMenu;
      return CombatSystem::kContinue;
      break;
    default:
      std::cin.ignore();
      View::ShowMessage(u8"Некорректный ввод!");
      return CombatSystem::kContinue;
  }
}

CombatSystem::CombatState Controller::HandleChooseEnemyMenu(
    int choice, Player& player, std::vector<Enemy>& enemies) {
  switch (choice) {
    case 0:
      state_->current_state_ = States::kCombatMenu;
      return CombatSystem::kContinue;
      break;
    default:
      if (choice <= enemies.size()) {
        CombatSystem::PlayerAttack(enemies[choice - 1], player);
        CombatSystem::EnemyTurn(player, enemies);
        state_->current_state_ = States::kCombatMenu;
        if (!player.IsAlive()) {
          return CombatSystem::kEnemyWin;
        }
        bool AllFalse = true;
        for (auto& currentEnemy : enemies) {
          if (currentEnemy.IsAlive()) {
            AllFalse = false;
            break;
          }
        }
        if (AllFalse) {
          return CombatSystem::kPlayerWin;
        } else {
          return CombatSystem::kContinue;
          state_->current_state_ = States::kCombatMenu;
        }
      } else {
        std::cin.ignore();
        View::ShowMessage(u8"Некорректный ввод!");
        return CombatSystem::kContinue;
      }
      break;
  }
}

void Controller::HandleEnemyListMenu(int choice) {
  switch (choice) {
    case 0:
      state_->current_state_ = States::kCombatMenu;
      break;
    default:
      std::cin.ignore();
      View::ShowMessage(u8"Некорректный ввод!");
  }
}

void Controller::HandleInventoryInCombatMenu(int choice, Player& player) {
  switch (choice) {
    case 0:
      state_->current_state_ = States::kCombatMenu;
      break;
    default:
      if (choice <= player.inventory_.items_.size()) {
        if (player.GetHealth() < player.GetMaxHealth()) {
          player.Heal(player.inventory_.items_[choice - 1].GetHealAmount());
          View::ShowMessage(
              u8"Вы использовали " +
              player.inventory_.items_[choice - 1].GetName() +
              u8", вы восстановили " +
              std::to_string(
                  player.inventory_.items_[choice - 1].GetHealAmount()));
          std::cin.ignore();
          player.inventory_.RemoveItem(
              player.inventory_.items_[choice - 1].GetID());
        } else {
          View::ShowMessage(u8"У вас уже полное здоровье");
        }
        std::cin.ignore();
      } else {
        std::cin.ignore();
        View::ShowMessage(u8"Некорректный ввод!");
      }
  }
}

void Controller::HandleInventoryMeleeMenu(int choice, Player& player) 
{
    switch (choice) 
    {
    case 0:
        state_->current_state_ = States::kPlayerMenu;
        break;
    default:
        if (choice <= player.inventory_.melees_.size()) 
        {
            player.current_melee_ = player.inventory_.melees_[choice - 1];
            View::ShowMessage(u8"Вы сменили оружие на " + player.inventory_.melees_[choice - 1].GetName());
            std::cin.ignore();
        }
        else 
        {
			std::cin.ignore();
			View::ShowMessage(u8"Некорректный ввод!");
        }
    }
}

void Controller::HandleRoomMenu(int choice, std::vector<Enemy>& all_enemies) {
  switch (choice) {
    case 1:
      state_->current_state_ = States::kGameMenu;
      break;
    case 2:
      if (!state_->current_room_.is_checked_) {
        std::cin.ignore();
        switch (state_->current_room_.type_) {
          case RoomType::kDefault:
            View::ShowMessage(
                u8"Вы исследуете комнату, но не находите ничего интересного");
            break;
          case RoomType::kEnemies:
            state_->enemies_.clear();
            state_->enemies_ =
                EnemyFactory(all_enemies, state_->current_room_.enemy_ids_);
            View::ShowMessage(u8"На вас нападает противник!");
            state_->current_state_ = States::kCombatMenu;
            break;
        }
        state_->current_room_.is_checked_ = true;
      } else {
        std::cin.ignore();
        View::ShowMessage(u8"В этой комнате больше нет ничего интересного");
      }
      break;
    case 3:
      state_->current_state_ = States::kChooseRoomMenu;
      break;
    default:
      std::cin.ignore();
      View::ShowMessage(u8"Некорректный ввод!");
  }
}

void Controller::HandleRoomChooseMenu(int choice, std::vector<Room>& all_rooms) {
  switch (choice) {
    case 0:
      state_->current_state_ = States::kRoomMenu;
      break;
    default:
      if (choice <= state_->current_room_.connected_rooms_.size()) {
        state_->current_room_ = RoomFactory(
            state_->current_room_.connected_rooms_[choice - 1], all_rooms);
        state_->current_state_ = States::kRoomMenu;
        break;
      } else {
        std::cin.ignore();
        View::ShowMessage(u8"Некорректный ввод!");
      }
  }
}

void Controller::HandleInventoryItemsMenu(int choice, Player& player) 
{
	switch (choice) {
	case 0:
		state_->current_state_ = States::kPlayerMenu;
		break;
	default:
		if (choice <= player.inventory_.items_.size()) {
			if (player.GetHealth() < player.GetMaxHealth()) {
				player.Heal(player.inventory_.items_[choice - 1].GetHealAmount());
				View::ShowMessage(
					u8"Вы использовали " +
					player.inventory_.items_[choice - 1].GetName() +
					u8", вы восстановили " +
					std::to_string(
						player.inventory_.items_[choice - 1].GetHealAmount()));
				std::cin.ignore();
				player.inventory_.RemoveItem(
					player.inventory_.items_[choice - 1].GetID());
			}
			else {
				View::ShowMessage(u8"У вас уже полное здоровье");
			}
			std::cin.ignore();
		}
		else {
			std::cin.ignore();
			View::ShowMessage(u8"Некорректный ввод!");
		}
	}
}
