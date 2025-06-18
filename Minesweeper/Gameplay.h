#pragma once
#include "Basic.h"


class Field
{
private:
	const int cellMine = 10;
	const int cellOpenedMine = 12;
	const int cellFlag = 9;
	const int cellMineWithFlag = 11;
	const int cellEmpty = -1;

	const int minSizeField = 3;
	const int sizeAtWhichFirstClickOpensAreaOfCells = 5;
	const int chanceToMine = 3;

	map<char, unsigned int> size;
	int** masField = nullptr;

public:
	Field(const unsigned int& _sizeX, const unsigned int& _sizeY)
	{
		set_size(_sizeX, _sizeY);
		clear_grid();
	}

	Field()
		: Field(3, 3) {}

	~Field()
	{
		for (unsigned int i = 0; i < size['X']; i++)
			delete[] masField[i];

		delete[] masField;
	}


	void check_out_of_range(const unsigned int& _x, const unsigned int& _y = 0)
	{
		string strExcept;

		if (_x >= size['X'])
			strExcept.append("Invalid value for x, maximum value x = " + to_string(size['X'] - 1) + 
				             ", but x = " + to_string(_x) + ";\n");

		if (_y >= size['Y'])
			strExcept.append("Invalid value for y, maximum value y = " + to_string(size['Y'] - 1) + 
				             ", but y = " + to_string(_y) + ";\n");

		if (!strExcept.empty())
			throw out_of_range(strExcept);
	}

	void set_size(unsigned int sizeX, unsigned int sizeY)
	{
		if (size['X'] == sizeX && size['Y'] == sizeY)
			return;

		string strExcept;

		if (sizeX < minSizeField)
		{
			strExcept.append("Too small value for x (" + to_string(sizeX) + ") in the Field;\n");
			sizeX = minSizeField;
		}

		if (sizeY < minSizeField)
		{
			strExcept.append("Too small value for y (" + to_string(sizeY) + ") in the Field;\n");
			sizeY = minSizeField;
		}

		if (masField != nullptr)
		{
			for (unsigned int i = 0; i < size['X']; i++)
				delete[] masField[i];

			delete[] masField;
		}

		size['X'] = sizeX;
		size['Y'] = sizeY;

		masField = new int* [sizeX];

		for (unsigned int i = 0; i < sizeX; i++)
			masField[i] = new int[sizeY] {};

		if (!strExcept.empty())
			throw invalid_argument(strExcept);
	}

	unsigned int get_size(const char& ch)
	{
		if (ch != 'X' && ch != 'Y')
			throw invalid_argument("Invalid symbol to get size (ch = " + to_string((char)ch) + ");\n");

		return size[ch];
	}

	unsigned int get_number_of_mines()
	{
		return (size['X'] * size['Y']) / chanceToMine;
	}

	unsigned int get_number_of_flags()
	{
		unsigned int numberOfFlags = 0;

		for (unsigned int x = 0; x < size['X']; x++)
			for (unsigned int y = 0; y < size['Y']; y++)
				if (masField[x][y] == cellFlag)
					numberOfFlags++;

		return numberOfFlags;
	}

	int get_cell(const unsigned int& _x, const unsigned int& _y)
	{
		check_out_of_range(_x, _y);

		return masField[_x][_y];
	}

	bool cell_is_empty(const unsigned int& x, const unsigned int& y)
	{
		check_out_of_range(x, y);

		return masField[x][y] == cellEmpty;
	}

	bool cell_is_mine(const unsigned int& x, const unsigned int& y)
	{
		check_out_of_range(x, y);

		return masField[x][y] == cellMine || masField[x][y] == cellOpenedMine ||
			   masField[x][y] == cellMineWithFlag;
	}

	bool cell_is_common_mine(const unsigned int& x, const unsigned int& y)
	{
		check_out_of_range(x, y);

		return masField[x][y] == cellMine;
	}

	bool cell_is_flag(const unsigned int& x, const unsigned int& y)
	{
		check_out_of_range(x, y);

		return masField[x][y] == cellFlag || masField[x][y] == cellMineWithFlag;
	}

	bool is_win()
	{
		if (is_lose())
			return false;

		for (unsigned int i = 0; i < size['X']; i++)
			for (unsigned int j = 0; j < size['Y']; j++)
				if (masField[i][j] == cellEmpty)
					return false;

		return true;
	}

	bool is_lose()
	{
		for (unsigned int i = 0; i < size['X']; i++)
			for (unsigned int j = 0; j < size['Y']; j++)
				if (masField[i][j] == cellOpenedMine)
					return true;

		return false;
	}

	void clear_grid()
	{
		for (unsigned int i = 0; i < size['X']; i++)
			for (unsigned int k = 0; k < size['Y']; k++)
				masField[i][k] = cellEmpty;
	}

	void random_fill_mines(const unsigned int& openedCellX = 0, const unsigned int& openedCellY = 0)
	{
		check_out_of_range(openedCellX, openedCellY);

		int mines = (size['X'] * size['Y']) / chanceToMine;

		for (unsigned int i = 0; mines > 0; i++)
		{
			for (unsigned int k = 0; mines > 0 && k < size['Y']; k++)
			{
				if (masField[i][k] == cellEmpty && rand() % chanceToMine == 0)
				{
					if (size['X'] >= sizeAtWhichFirstClickOpensAreaOfCells && 
						size['Y'] >= sizeAtWhichFirstClickOpensAreaOfCells)
					{
						bool cont = false;

						for (int iOpen = (int)openedCellX - 1; iOpen <= (int)openedCellX + 1; iOpen++)
							for (int kOpen = (int)openedCellY - 1; kOpen <= (int)openedCellY + 1; kOpen++)
								if (iOpen == i && kOpen == k)
									cont = true;

						if (cont) continue;
					}
					else if (openedCellX == i && openedCellY == k)
						continue;

					masField[i][k] = cellMine;
					mines--;
				}
			}

			if (i >= size['X'] - 1) 
				i = 0;
		}
	}

	void open_cell(const unsigned int& x, const unsigned int& y)
	{
		check_out_of_range(x, y);

		if (masField[x][y] == cellEmpty)
		{
			unsigned int mines = 0;

			for (int xCheck = (int)x - 1; xCheck <= (int)x + 1; xCheck++)
			{
				for (int yCheck = (int)y - 1; yCheck <= (int)y + 1; yCheck++)
				{
					if (xCheck == x && yCheck == y)
						continue;

					try
					{
						if (cell_is_mine(xCheck, yCheck))
							mines++;
					}
					catch (...) {}
				}
			}

			masField[x][y] = mines;
		}
		else if (cell_is_mine(x, y))
		{
			masField[x][y] = cellOpenedMine;
		}
	}

	void put_flag(const unsigned int& x, const unsigned int& y)
	{
		check_out_of_range(x, y);

		if (masField[x][y] == cellEmpty)
			masField[x][y] = cellFlag;
		else if (masField[x][y] == cellMine)
			masField[x][y] = cellMineWithFlag;
		else if (masField[x][y] == cellFlag)
			masField[x][y] = cellEmpty;
		else if (masField[x][y] == cellMineWithFlag)
			masField[x][y] = cellMine;
	}

	void open_grid()
	{
		for (unsigned int i = 0; i < size['X']; i++)
		{
			for (unsigned int k = 0; k < size['Y']; k++)
			{
				if (masField[i][k] == cellFlag || masField[i][k] == cellMineWithFlag)
					put_flag(i, k);

				if (masField[i][k] == cellEmpty)
					open_cell(i, k);
				else if (masField[i][k] == cellMine)
					masField[i][k] = cellOpenedMine;
			}
		}
	}

	Field& operator= (const Field& other)
	{
		map<char, unsigned int> _size = other.size;

		set_size(_size['X'], _size['Y']);
		clear_grid();

		return *this;
	}

	int* operator[](unsigned int _x)
	{
		check_out_of_range(_x);

		return masField[_x];
	}
};


class Flags
{
private:
	unsigned int flagsAll;
	unsigned int flagsNow;

public:
	Flags(const unsigned int& _flagsAll)
		: flagsAll{ _flagsAll }, flagsNow{ _flagsAll } {}

	Flags()
		: Flags(0) {}


	void change_from_cell(const bool& isFlag)
	{
		if (isFlag)
			add();
		else
			substract();

		cout << *this << "  ";
	}

	void add(const unsigned int& number = 1)       { flagsNow += number; }
	void substract(const unsigned int& number = 1) { flagsNow -= number; }
	void reset()                                   { flagsNow = flagsAll; }

	friend ostream& operator<< (ostream& OUTStream, const Flags& other)
	{
		OUTStream << "Flags: " << other.flagsNow;

		return OUTStream;
	}
};


class Timer
{
private:
	const unsigned int secondsInMinute = 60;

	unsigned int minute = 0;
	unsigned int second = 0;
	time_t timeNow = time(0);

public:
	void add_seconds(const unsigned int& addSeconds = 1)
	{
		second += addSeconds;

		while (second >= secondsInMinute)
		{
			minute++;
			second -= secondsInMinute;
		}
	}

	void add_minutes(const unsigned int& addMinutes = 1)
	{
		minute += addMinutes;
	}

	void improve()
	{
		if ((unsigned int)(time(0) - timeNow) > 0)
		{
			add_seconds(time(0) - timeNow);
			cout << *this;
			timeNow = time(0);
		}
	}

	void clear()
	{
		minute = 0;
		second = 0;
		timeNow = time(0);
	}

	friend ostream& operator<< (ostream& OUTStream, const Timer& other)
	{
		if (other.minute < 10)
			OUTStream << "0";

		OUTStream << other.minute << ":";

		if (other.second < 10)
			OUTStream << "0";

		OUTStream << other.second;

		return OUTStream;
	}

	Timer& operator= (const Timer& other)
	{
		minute = other.minute;
		second = other.second;

		return *this;
	}
};


class Statistic
{
private:
	unsigned int maxNumber;

	vector<string> vectorPlayerName;
	vector<Timer> vectorTime;
	vector<Flags> vectorFlags;
	vector<bool> vectorIsWin;
	vector<map<char, unsigned int>> vectorSize;

public:
	Statistic(const unsigned int& _maxNumber)
	{
		set_max_number(_maxNumber);
	}

	Statistic()
		: Statistic(10) {}


	void set_max_number(const unsigned int& _maxNumber)
	{
		maxNumber = _maxNumber;

		while (vectorSize.size() >= maxNumber)
			delete_first_element();
	}

	unsigned int get_max_number() const
	{
		return maxNumber;
	}

	void add(const string& playerName, const Timer& time, const Flags& flags, const bool& isWin, 
		     const unsigned int& sizeX, const unsigned int& sizeY)
	{
		if (maxNumber == 0)
			return;

		if (vectorSize.size() >= maxNumber)
			delete_first_element();

		vectorPlayerName.push_back(playerName);
		vectorTime.push_back(time);
		vectorFlags.push_back(flags);
		vectorIsWin.push_back(isWin);
		vectorSize.push_back({ { 'X', sizeX }, { 'Y', sizeY } });
	}

	void delete_first_element()
	{
		vectorPlayerName.erase(begin(vectorPlayerName));
		vectorTime.erase(begin(vectorTime));
		vectorFlags.erase(begin(vectorFlags));
		vectorIsWin.erase(begin(vectorIsWin));
		vectorSize.erase(begin(vectorSize));
	}

	ostream& show(ostream& outStream, const unsigned int& coordinateX = 0, const unsigned int& coordinateY = 0)
	{
		set_position_console_cursor(coordinateX, coordinateY);

		if (vectorSize.size() > 0)
		{
			for (unsigned int i = 0; i < vectorSize.size() && i < maxNumber; i++)
			{
				unsigned int positionMove = (unsigned int) vectorSize.size() - i - 1;
				set_position_console_cursor(coordinateX, coordinateY + positionMove * 2);

				outStream << vectorPlayerName[i];
				outStream << ", " << vectorSize[i]['X'] << "x" << vectorSize[i]['Y'];
				outStream << ", " << vectorTime[i];
				outStream << ", " << vectorFlags[i];

				if (vectorIsWin[i])
					outStream << ", WIN" << endl;
				else
					outStream << ", LOSE" << endl;
			}
		}
		else
			outStream << "No statistics!" << endl;

		return outStream;
	}

	Statistic& operator+= (const Statistic& other)
	{
		for (int i = 0; i < other.vectorSize.size(); i++)
		{
			if (vectorSize.size() >= maxNumber)
				delete_first_element();

			map<char, unsigned int> size = other.vectorSize[i];

			add(other.vectorPlayerName[i], other.vectorTime[i], other.vectorFlags[i], other.vectorIsWin[i], 
			    size['X'], size['Y']);
		}

		return *this;
	}
};