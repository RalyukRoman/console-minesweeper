#pragma once

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <string>
using namespace std;

#define CONSOLE_COLOR 7

const HANDLE windowConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void set_color_text(const unsigned int& color)
{
    SetConsoleTextAttribute(windowConsole, color);
}

void set_position_console_cursor(const short& xPos, const short& yPos)
{
    SetConsoleCursorPosition(windowConsole, { xPos, yPos });
}

void XLine(const char& firstSymbol, const char& symbol, const char& lastSymbol, const unsigned int& length, 
	       const unsigned int& coordinateX, const unsigned int& coordinateY)
{
	set_position_console_cursor(coordinateX, coordinateY);

	for (unsigned int i = coordinateX; i < coordinateX + length + 1; i++)
	{
		if (i == coordinateX + length)
			cout << lastSymbol;
		else if (i == coordinateX)
			cout << firstSymbol;
		else
			cout << symbol;
	}
}

void YLine(const char& firstSymbol, const char& symbol, const char& lastSymbol, const unsigned int& length,
	       const unsigned int& coordinateX, const unsigned int& coordinateY)
{
	for (unsigned int i = coordinateY; i < coordinateY + length; i++)
	{
		set_position_console_cursor(coordinateX, i);

		if (i == coordinateY + length - 1)
			cout << lastSymbol;
		else if (i == coordinateY)
			cout << firstSymbol;
		else
			cout << symbol;
	}
}

template<typename T>
void replace_map_elements_from_another_map (map<string, T>& replacement, const map<string, T>& source)
{
	for (auto& elem : source)
	{
		auto it = replacement.find(elem.first);

		if (it != end(replacement))
			replacement[elem.first] = elem.second;
	}
}

template<typename T>
int equal_to_no_less(T& value, const int& number)
{
	if (value < (T)number)
		value = (T)number;

	return value;
}

template<typename T>
int equal_to_no_more(T& value, const int& number)
{
	if (value > (T)number)
		value = (T)number;

	return value;
}

bool check_string(const string& str)
{
	for (const char& a : str)
	{
		if (a >= 0 && a <= 31 || a == 127)
			return false;
	}

	return true;
}