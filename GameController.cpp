#include "GameController.h"
#include "TextView.h"
#include <iostream>

void GameController::handleMainMenu(int choice)
{
	switch (choice) 
	{
	case 1: //����� ����
		state->currentState = States::GAME_MENU;
		TextView::showMessage(u8"����� ���� ������!");
		break;
	//case 2: ����������
	//	std::cin.ignore();
	case 3:
		exit(0);
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"������������ ����!");
	}
}

void GameController::handleGameMenu(int choice) 
{
	switch (choice) 
	{
	//case 1: ������������

	case 2: //�����
		state->currentState = States::PLAYER_MENU;
		break;
	//case 3: �����
	//case 4: ����������
	case 5:
		state->currentState = States::MAIN_MENU;
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"������������ ����!");
	}

}

void GameController::handlePlayerMenu(int choice) 
{
	switch (choice) 
	{
	case 1:
		state->currentState = States::GAME_MENU;
		break;
	case 2:
		state->currentState = States::LEVEL_MENU;
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"������������ ����!");
	}
}

void GameController::handleLevelMenu(int choice, Player& player) 
{
	switch (choice) 
	{
	case 1:
		state->currentState = States::PLAYER_MENU;
		break;
	case 2:
		if (player.getLevelPoints() > 0) 
		{ 
			player.MaxHealthUp(); 
			player.setLevelPoints(player.getLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			TextView::showMessage(u8"�� ������� ����� �������������!");
		}
		break;
	case 3: 
		if (player.getLevelPoints() > 0) 
		{ 
			player.MeleeLevelUp(); 
			player.setLevelPoints(player.getLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			TextView::showMessage(u8"�� ������� ����� �������������!");
		}
		break;
	case 4:
		if (player.getLevelPoints() > 0) 
		{ 
			player.GunLevelUp(); 
			player.setLevelPoints(player.getLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			TextView::showMessage(u8"�� ������� ����� �������������!");
		}
		break;
	case 5:
		if (player.getLevelPoints() > 0) 
		{ 
			player.IntelligenceUp(); 
			player.setLevelPoints(player.getLevelPoints() - 1);
		}
		else {
			std::cin.ignore();
			TextView::showMessage(u8"�� ������� ����� �������������!");
		}
		break;
	default:
		std::cin.ignore();
		TextView::showMessage(u8"������������ ����!");
	}
}
