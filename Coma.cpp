#include <iostream>
#include <Windows.h>
#include "TextView.h"
int main() 
{
	TextView textview;
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	bool GameIsRunning = true;
	int input;
	while (GameIsRunning)
	{
		textview.showMainMenu();
		std::cin >> input;
	}
	return 0;
}

