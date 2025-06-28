#include "controller.h"

#include <iostream>
#include <random>

#include "view.h"

void Controller::HandleMainMenu(int choice) {
  switch (choice) {
    case 1:  // Новая игра
      state_->current_state_ = States::kGameMenu;
      View::ViewMessage(u8"Новая игра начата!");
      break;
    // case 2: Сохранение
    //	std::cin.ignore();
    case 3:
      exit(0);
      break;
    default:
      std::cin.ignore();
      View::ViewMessage(u8"Некорректный ввод!");
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
      View::ViewMessage(u8"Некорректный ввод!");
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
    case 4:
      state_->current_state_ = States::kInventoryGunMenu;
      break;
    case 5:
      state_->current_state_ = States::kInventoryItemsMenu;
      break;
    default:
      std::cin.ignore();
      View::ViewMessage(u8"Некорректный ввод!");
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
        View::ViewMessage(u8"Не хватает очков характеристик!");
      }
      break;
    case 3:
      if (player.GetLevelPoints() > 0) {
        player.MeleeLevelUp();
        player.SetLevelPoints(player.GetLevelPoints() - 1);
      } else {
        std::cin.ignore();
        View::ViewMessage(u8"Не хватает очков характеристик!");
      }
      break;
    case 4:
      if (player.GetLevelPoints() > 0) {
        player.GunLevelUp();
        player.SetLevelPoints(player.GetLevelPoints() - 1);
      } else {
        std::cin.ignore();
        View::ViewMessage(u8"Не хватает очков характеристик!");
      }
      break;
    case 5:
      if (player.GetLevelPoints() > 0) {
        player.IntelligenceUp();
        player.SetLevelPoints(player.GetLevelPoints() - 1);
      } else {
        std::cin.ignore();
        View::ViewMessage(u8"Не хватает очков характеристик!");
      }
      break;
    default:
      std::cin.ignore();
      View::ViewMessage(u8"Некорректный ввод!");
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
      View::ViewMessage(u8"Некорректный ввод!");
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
        View::ViewMessage(u8"Некорректный ввод!");
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
      View::ViewMessage(u8"Некорректный ввод!");
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
          player.Heal(player.inventory_.items_[choice - 1].GetHealAmount(),
                      player.inventory_.items_[choice - 1].GetMentalHeal());
          View::ViewMessage(
              u8"Вы использовали " +
              player.inventory_.items_[choice - 1].GetName() +
              u8", вы восстановили " +
              std::to_string(
                  player.inventory_.items_[choice - 1].GetHealAmount()));
          std::cin.ignore();
          player.inventory_.RemoveItem(
              player.inventory_.items_[choice - 1].GetID());
        } else {
          View::ViewMessage(u8"У вас уже полное здоровье");
        }
        std::cin.ignore();
      } else {
        std::cin.ignore();
        View::ViewMessage(u8"Некорректный ввод!");
      }
  }
}

void Controller::HandleInventoryMeleeMenu(int choice, Player& player) {
  switch (choice) {
    case 0:
      state_->current_state_ = States::kPlayerMenu;
      break;
    default:
      if (choice <= player.inventory_.melees_.size()) {
        player.current_melee_ = player.inventory_.melees_[choice - 1];
        View::ViewMessage(u8"Вы сменили оружие на " +
                          player.inventory_.melees_[choice - 1].GetName());
        std::cin.ignore();
      } else {
        std::cin.ignore();
        View::ViewMessage(u8"Некорректный ввод!");
      }
  }
}

void Controller::HandleInventoryGunMenu(int choice, Player& player) {
  switch (choice) {
    case 0:
      state_->current_state_ = States::kPlayerMenu;
      break;
    default:
      if (choice <= player.inventory_.guns_.size()) {
        player.current_gun_ = player.inventory_.guns_[choice - 1];
        View::ViewMessage(u8"Вы сменили оружие на " +
                          player.inventory_.guns_[choice - 1].GetName());
        std::cin.ignore();
      } else {
        std::cin.ignore();
        View::ViewMessage(u8"Некорректный ввод!");
      }
  }
}

void Controller::HandleRoomMenu(int choice, Player& player,
                                std::vector<Enemy>& all_enemies,
                                std::vector<MeleeWeapon>& all_melee,
                                std::vector<GunWeapon>& all_guns,
                                std::vector<Item> all_items) {
  switch (choice) {
    case 1:
      state_->current_state_ = States::kGameMenu;
      break;
    case 2:
      if (!state_->current_room_.is_checked_) {
        std::cin.ignore();
        switch (state_->current_room_.type_) {
          case RoomType::kDefault:
            View::ViewMessage(
                u8"Вы исследуете комнату, но не находите ничего интересного");
            break;
          case RoomType::kEnemies:
            state_->enemies_.clear();
            state_->enemies_ =
                EnemyFactory(all_enemies, state_->current_room_.enemy_ids_);
            View::ViewMessage(u8"На вас нападает противник!");
            state_->current_state_ = States::kCombatMenu;
            break;
          case RoomType::kChest:
            std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> dist1(1, 3);
            int loot_type = dist1(gen);
            std::uniform_int_distribution<int> dist2(1, 10);
            int loot_id = dist2(gen);
            std::string str_loot_id = std::to_string(loot_id);
            switch (loot_type) {
              case 1:
                player.inventory_.AddMelee(str_loot_id, all_melee);
                break;
              case 2:
                player.inventory_.AddGun(str_loot_id, all_guns);
                break;
              case 3:
                player.inventory_.AddItem(str_loot_id, all_items);
                break;
            }
        }
        state_->current_room_.is_checked_ = true;
      } else {
        std::cin.ignore();
        View::ViewMessage(u8"В этой комнате больше нет ничего интересного");
      }
      break;
    case 3:
      state_->current_state_ = States::kChooseRoomMenu;
      break;
    default:
      std::cin.ignore();
      View::ViewMessage(u8"Некорректный ввод!");
  }
}

void Controller::HandleRoomChooseMenu(int choice,
                                      std::vector<Room>& all_rooms) {
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
        View::ViewMessage(u8"Некорректный ввод!");
      }
  }
}

void Controller::HandleInventoryItemsMenu(int choice, Player& player) {
  switch (choice) {
    case 0:
      state_->current_state_ = States::kPlayerMenu;
      break;
    default:
      if (choice <= player.inventory_.items_.size()) {
        if (player.GetHealth() < player.GetMaxHealth()) {
          player.Heal(player.inventory_.items_[choice - 1].GetHealAmount(),
                      player.inventory_.items_[choice - 1].GetMentalHeal());
          View::ViewMessage(
              u8"Вы использовали " +
              player.inventory_.items_[choice - 1].GetName() +
              u8", вы восстановили " +
              std::to_string(
                  player.inventory_.items_[choice - 1].GetHealAmount()));
          std::cin.ignore();
          player.inventory_.RemoveItem(
              player.inventory_.items_[choice - 1].GetID());
        } else {
          View::ViewMessage(u8"У вас уже полное здоровье");
        }
        std::cin.ignore();
      } else {
        std::cin.ignore();
        View::ViewMessage(u8"Некорректный ввод!");
      }
  }
}
