#include "Menu.h"

int main()
{
	srand((unsigned int) time(0));

	SetConsoleTitle(L"MineSweeper");
	PageMenu game;
	game.open_menu();

	set_position_console_cursor(0, 0);
}