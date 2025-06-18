#pragma once
#include "Graphic.h"

class Page
{
protected:
	const int coordinateWindowX = 5;
	const int coordinateWindowY = 5;
	const int distanceStrFromTopInWindowY = 0;
	const int indentInfoFromLineX = 4;
	const int indentInfoFromUpY = 1;
	const int sizeOfInfo = 13;

	ButtonsControl buttons;

	map<string, map<char, unsigned int>> coordinate;

	map<string, char> keysMap = 
	{ 
		{"PutFlag", 'e'}, {"OpenCell", 'q'}, {"Up", 'w'}, {"Down", 's'},
		{"Left", 'a'}, {"Right", 'd'} 
	};

	map<string, unsigned int> colorsMap = 
	{ 
		{"GameBasic", 7}, {"GameCursor", 22}, {"GameTimer", 7}, {"GameFlags", 7}, {"GameText", 7},					
		{"WindowBasic", 7}, {"ButtonsBasic", 7}, {"ButtonsHighlighted", 2}, {"StatisticBasic", 7},							
		{"OptionBasic", 7}, {"CheckKey", 112} 
	};

	map<string, char> windowSymbolsMap = 
	{ 
		{"WallVertical", 179}, {"WallHorizontal", 196}, {"CornerLeftUp", 218}, {"CornerLeftDown", 192},
		{"CornerRightDown", 217}, {"CornerRightUp", 191}, {"CombiningRight", 180} 
	};

	map<string, char> pageSymbolsMap = 
	{ 
		{"WallVertical", 179}, {"WallHorizontal", 196}, {"CornerLeftUp", 218}, {"CornerLeftDown", 192},
		{"CornerRightUp", 191}, {"CornerRightDown", 217}, {"CombiningLeft", 195}, {"CombiningRight", 180},
		{"CombiningUp", 194}, {"CombiningDown", 193} 
	};

	map<string, char> groundSymbolsMap = 
	{ 
		{"WallVertical", 186}, {"WallHorizontal", 205}, {"CornerLeftUp", 201}, {"CornerLeftDown", 200},
		{"CornerRightUp", 187}, {"CornerRightDown", 188}, {"CombiningLeft", 204}, {"CombiningRight", 185},
		{"CombiningUp", 203}, {"CombiningDown", 202}, {"Cross", 206} 
	};


public:
	void replace_colors(const map <string, unsigned int>& _colors)
	{
		replace_map_elements_from_another_map(colorsMap, _colors);
		buttons.replace_colors(_colors);
	}

	void replace_symbols_of_page(const map <string, char>& _symbols)
	{
		replace_map_elements_from_another_map(pageSymbolsMap, _symbols);
	}

	void replace_symbols_of_ground(const map <string, char>& _symbols)
	{
		replace_map_elements_from_another_map(groundSymbolsMap, _symbols);
	}

	void replace_symbols_of_window(const map <string, char>& _symbols)
	{
		replace_map_elements_from_another_map(windowSymbolsMap, _symbols);
	}

	void replace_keys(const map <string, char>& _keys)
	{
		replace_map_elements_from_another_map(keysMap, _keys);
		buttons.replace_keys(_keys);
	}
};

class PageGame : public Page
{
private:
	const int minFieldSize = 3;
	const int maxFieldSize = 15;
	const int minSizeFieldForPlacementOfButtonsInCenterX = 9;

	const int widthOfText = 9;
	const int distanceButtonRetryFromCenterX = 2;
	const int distanceButtonExitFromCenterX = 5;

	const int widthOfInfo = 19;
	const int widthOfTimer = 5;
	const int distanceFlagsFromTimerX = 3;

	const int distanceButtonsFromSidesInWindowInputX = 1;
	const int distanceButtonsFromSidesInWindowDoubleInputX = 2;
	const int distanceButtonsFromSidesInWindowNotificationX = 8;
	const int distanceInputCellFromStrInWindowInputY = 1;
	const int maxNumberOfSymbolsInWindowInput = 15;
	const int maxNumberOfSymbolsInWindowDoubleInput = 3;


	void set_buttons(unsigned int sizeFieldX)
	{
		equal_to_no_less(sizeFieldX, minSizeFieldForPlacementOfButtonsInCenterX);

		coordinate["Text"]['X'] = coordinate["Field"]['X'] + sizeFieldX - widthOfText / 2;

		buttons.clear();

		buttons.push(Button(coordinate["Text"]['X'] - distanceButtonRetryFromCenterX, coordinate["Text"]['Y'] + 1, "Retry"));
		buttons.push(Button(coordinate["Text"]['X'] + distanceButtonExitFromCenterX, coordinate["Text"]['Y'] + 1, "Close"));

		buttons.replace_colors(colorsMap);
	}

	void add_distance_from_top_to_coordinate(const int& additionalDistanceY, const bool& startingFromFirstLineX, const bool& addToField = true)
	{
		if (startingFromFirstLineX)
		{
			if (addToField)
				coordinate["Field"]['Y'] += additionalDistanceY;

			coordinate["SecondLineX"]['Y'] += additionalDistanceY;
		}

		coordinate["Text"]['Y'] += additionalDistanceY;
		coordinate["ThirdLineX"]['Y'] += additionalDistanceY;
	}

public:
	PageGame(const unsigned int& distanceInfoFromLinesX, const unsigned int& distanceInfoFromLinesY,
		     const unsigned int& distanceFieldFromLinesX, const unsigned int& distanceFieldFromLinesY,
		     const unsigned int& distanceTextFromLinesY)
	{
		set_coordinate_info(distanceInfoFromLinesX, distanceInfoFromLinesY);
		set_coordinate_field(distanceFieldFromLinesX, distanceFieldFromLinesY);
		set_coordinate_text(distanceTextFromLinesY);
	}

	PageGame(const unsigned int& distanceInfoFromLinesX, const unsigned int& distanceInfoFromLinesY,
			 const unsigned int& distanceFieldFromLinesX, const unsigned int& distanceFieldFromLinesY)
		: PageGame(distanceInfoFromLinesX, distanceInfoFromLinesY, distanceFieldFromLinesX, distanceFieldFromLinesY, 0) {}

	PageGame(const unsigned int& distanceInfoFromLinesX, const unsigned int& distanceInfoFromLinesY)
		: PageGame(distanceInfoFromLinesX, distanceInfoFromLinesY, 3, 1, 0) {}

	PageGame()
		: PageGame(3, 1, 3, 1, 0) {}


	void set_coordinate_info(const unsigned int& distanceInfoFromLinesX, const unsigned int& distanceInfoFromLinesY)
	{
		const unsigned int additionalDistanceY = distanceInfoFromLinesY - coordinate["Info"]['Y'];
		add_distance_from_top_to_coordinate(additionalDistanceY, true);

		coordinate["Info"]['X'] = distanceInfoFromLinesX;
		coordinate["Info"]['Y'] = distanceInfoFromLinesY;
		coordinate["FirstLineX"]['Y'] = coordinate["Info"]['Y'] + distanceInfoFromLinesY + 1;
	}

	void set_coordinate_field(const unsigned int& distanceFieldFromLinesX, const unsigned int& distanceFieldFromLinesY)
	{
		const unsigned int additionalDistanceY = (coordinate["FirstLineX"]['Y'] + distanceFieldFromLinesY) - coordinate["Field"]['Y'];
		add_distance_from_top_to_coordinate(additionalDistanceY, false);

		coordinate["Field"]['X'] = distanceFieldFromLinesX;
		coordinate["Field"]['Y'] = coordinate["FirstLineX"]['Y'] + distanceFieldFromLinesY + 1;
		coordinate["SecondLineX"]['Y'] = coordinate["Field"]['Y'] + distanceFieldFromLinesY + 1;
	}

	void set_coordinate_text(const unsigned int& distanceTextFromLinesY)
	{
		coordinate["Text"]['Y'] = coordinate["SecondLineX"]['Y'] + distanceTextFromLinesY + 1;
		coordinate["ThirdLineX"]['Y'] = coordinate["Text"]['Y'] + distanceTextFromLinesY + 2;
	}

	void create_basic(const unsigned int& sizeFieldX)
	{
		unsigned int lineXLength = coordinate["Field"]['X'] * 2 + sizeFieldX * 2 + 1;
		equal_to_no_less(lineXLength, coordinate["Info"]['X'] * 2 + widthOfInfo);

		set_color_text(colorsMap["GameBasic"]);

		XLine(pageSymbolsMap["WallHorizontal"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["WallHorizontal"], 
			  lineXLength + indentInfoFromLineX * 2 + sizeOfInfo, 0, coordinate["ThirdLineX"]['Y']);

		YLine(pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], pageSymbolsMap["CombiningDown"], 
			  coordinate["ThirdLineX"]['Y'] + 1, lineXLength, 0);
		YLine(pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], pageSymbolsMap["CornerRightDown"], 
			  coordinate["ThirdLineX"]['Y'] + 1, lineXLength + indentInfoFromLineX * 2 + sizeOfInfo, 0);

		XLine(pageSymbolsMap["WallHorizontal"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"],
			  lineXLength, 0, coordinate["FirstLineX"]['Y']);
		XLine(pageSymbolsMap["WallHorizontal"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"],
			  lineXLength, 0, coordinate["SecondLineX"]['Y']);

	}

	void create_object(const Timer& timer, Ground& ground, const Flags& flags)
	{
		ground.render();

		set_color_text(colorsMap["GameTimer"]);
		set_position_console_cursor(coordinate["Info"]['X'], coordinate["Info"]['Y']);
		cout << timer;

		set_color_text(colorsMap["GameFlags"]);
		set_position_console_cursor(coordinate["Info"]['X'] + widthOfTimer + distanceFlagsFromTimerX, coordinate["Info"]['Y']);
		cout << flags;
	}

	void create_info(const unsigned int& sizeFieldX)
	{
		unsigned int lineXLength = coordinate["Field"]['X'] * 2 + sizeFieldX * 2 + 1;
		equal_to_no_less(lineXLength, coordinate["Info"]['X'] * 2 + widthOfInfo);
		unsigned int i = 0;

		set_color_text(colorsMap["GameBasic"]);

		set_position_console_cursor(lineXLength + indentInfoFromLineX + 5, indentInfoFromUpY + i++);
		cout << "INFO";

		for (const auto& key : keysMap)
		{
			set_position_console_cursor(lineXLength + indentInfoFromLineX, indentInfoFromUpY + i++);
			cout << key.second << " - " << key.first;
		}
	}

	void check_button_game(Ground& ground, Flags& flags, bool& firstOpen)
	{
		if (_kbhit())
		{
			char clickedKey = _getch();

			if (clickedKey == keysMap["Up"])
				ground.change_cursor(0, -1);
			else if (clickedKey == keysMap["Down"])
				ground.change_cursor(0, 1);
			else if (clickedKey == keysMap["Right"])
				ground.change_cursor(1, 0);
			else if (clickedKey == keysMap["Left"])
				ground.change_cursor(-1, 0);
			else if (clickedKey == keysMap["OpenCell"])
			{
				ground.open_cell_on_cursor(firstOpen);
				firstOpen = false;
			}
			else if (clickedKey == keysMap["PutFlag"])
			{
				set_position_console_cursor(coordinate["Info"]['X'] + widthOfTimer + distanceFlagsFromTimerX, coordinate["Info"]['Y']);
				set_color_text(colorsMap["GameFlags"]);
				flags.change_from_cell(ground.get_current_cell_is_flag());
				ground.put_flag();
			}
		}
	}

	Statistic start_game(const unsigned int& sizeFieldX, const unsigned int& sizeFieldY)
	{
		add_distance_from_top_to_coordinate(sizeFieldX * 2, true, false);

		Ground ground(sizeFieldX, sizeFieldY, coordinate["Field"]['X'], coordinate["Field"]['Y'], 
			          coordinate["Text"]['Y'] - (coordinate["Field"]['Y'] + sizeFieldY * 2));
		Timer timer;
		Flags flags(ground.get_number_of_mines());
		Statistic statistic;

		ground.replace_colors(colorsMap);
		ground.replace_symbols(groundSymbolsMap);

		set_buttons(sizeFieldX);
		set_color_text(colorsMap["GameBasic"]);

		WindowInputSingle windowEnterName(coordinateWindowX, coordinateWindowY, "Enter your name");

		windowEnterName.set_options(distanceStrFromTopInWindowY, distanceButtonsFromSidesInWindowInputX,
								    distanceInputCellFromStrInWindowInputY, maxNumberOfSymbolsInWindowInput);
		windowEnterName.replace_colors(colorsMap);
		windowEnterName.replace_symbols(windowSymbolsMap);

		string playerName = windowEnterName.open();

		if (!playerName.empty())
		{
			while (true)
			{
				system("cls");
				create_basic(sizeFieldX);
				create_info(sizeFieldX);
				create_object(timer, ground, flags);
				bool firstOpen = true;

				while (true)
				{
					check_button_game(ground, flags, firstOpen);

					set_position_console_cursor(coordinate["Info"]['X'], coordinate["Info"]['Y']);
					set_color_text(colorsMap["GameTimer"]);
					timer.improve();

					if (ground.is_win() || ground.is_lose()) 
						break;
				}

				statistic.add(playerName, timer, flags, ground.is_win(), sizeFieldX, sizeFieldY);

				if (buttons.check_button_click() == "Close")
					break;

				flags.reset();
				timer.clear();
			}

			system("cls");
		}

		add_distance_from_top_to_coordinate(sizeFieldX * -2, true, false);
		system("cls");
		return statistic;
	}

	map<char, unsigned int> ask_size()
	{
		WindowInputMultiply windowFieldSize(coordinateWindowX, coordinateWindowY, "Enter field size");

		windowFieldSize.set_options(distanceStrFromTopInWindowY, distanceButtonsFromSidesInWindowDoubleInputX, 
									distanceInputCellFromStrInWindowInputY, maxNumberOfSymbolsInWindowDoubleInput);
		windowFieldSize.set_str_input_cell_vector({ "X: ", "Y: " });
		windowFieldSize.replace_colors(colorsMap);
		windowFieldSize.replace_symbols(windowSymbolsMap);

		map<string, unsigned int> size = windowFieldSize.open();

		if (size.empty())
			return {};
		else
			return { { 'X', size["X: "]}, {'Y', size["Y: "]}};
	}

	bool ask_users_agree_about_changed_size() const
	{
		WindowNotification windowModifiedSize(coordinateWindowX, coordinateWindowY, "The size isn`t suitable, run the game with modified size?");

		windowModifiedSize.set_options(distanceStrFromTopInWindowY, distanceButtonsFromSidesInWindowNotificationX);
		windowModifiedSize.replace_symbols(windowSymbolsMap);
		windowModifiedSize.replace_colors(colorsMap);

		return windowModifiedSize.open();
	}

	Statistic open()
	{
		map<char, unsigned int> size = ask_size();
		bool modify = false;

		for (auto& item : size)
		{
			if (item.second < minFieldSize)
			{
				item.second = minFieldSize;
				modify = true;
			}
			else if (item.second > maxFieldSize)
			{
				item.second = maxFieldSize;
				modify = true;
			}
		}

		if (size.empty() || modify && !ask_users_agree_about_changed_size())
		{
			system("cls");
			return Statistic();
		}

		return start_game(size['X'], size['Y']);
	}
};


class PageStatistic : public Page
{
private:
	const int widthOfPage = 50;
	const int heightOfButtonsCell = 3;
	const int distanceButtonExitFromLeftSideX = 6;
	const int distanceButtonRecordFromRightSideX = 8;
	const int distanceCentralLineFromCenterX = 4;

	const int distanceButtonsFromSidesInWindowInputX = 2;
	const int distanceButtonsFromSidesInWindowNotificationX = 8;
	const int distanceInputCellFromStrInWindowInputY = 1;
	const int maxNumberOfSymbolsInWindowInput = 100;

	const map <string, int> windowOption =
	{
		{"distanceStrFromTopInWindowY", 0}
	};

	Statistic statistic;

	void set_buttons()
	{
		buttons.clear();

		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonExitFromLeftSideX + 1, coordinate["Page"]['Y'] + 1, "<- Exit"));
		buttons.push(Button(coordinate["Page"]['X'] + widthOfPage / 2 + widthOfPage / 4 - distanceButtonRecordFromRightSideX - 1,
			                coordinate["Page"]['Y'] + 1, "Record to file"));
	}

public:
	PageStatistic(const unsigned int& _coordinateStatisticX, const unsigned int& _coordinateStatisticY)
	{
		set_coordinate_statistic(_coordinateStatisticX, _coordinateStatisticY);
	}
	
	PageStatistic()
		: PageStatistic(5, 2) {}


	void set_coordinate_statistic(const unsigned int& _coordinateStatisticX, const unsigned int& _coordinateStatisticY)
	{
		coordinate["Page"]['X'] = _coordinateStatisticX;
		coordinate["Page"]['Y'] = _coordinateStatisticY;

		set_buttons();
	}

	Statistic& get_statistic()
	{
		return statistic;
	}

	void create_basic()
	{ 
		YLine(pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], 
			  statistic.get_max_number() * 2 + heightOfButtonsCell, coordinate["Page"]['X'], coordinate["Page"]['Y']);
		YLine(pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], 
			  statistic.get_max_number() * 2 + heightOfButtonsCell, coordinate["Page"]['X'] + widthOfPage, coordinate["Page"]['Y']);

		for (unsigned int i = 0; i <= statistic.get_max_number() + 1; i++)
		{
			if (i == 0)
				XLine(pageSymbolsMap["CornerLeftUp"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CornerRightUp"], 
					  widthOfPage, coordinate["Page"]['X'], coordinate["Page"]['Y'] + i * 2);
			else if (i == statistic.get_max_number() + 1)
				XLine(pageSymbolsMap["CornerLeftDown"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CornerRightDown"], 
					  widthOfPage, coordinate["Page"]['X'], coordinate["Page"]['Y'] + i * 2);
			else
				XLine(pageSymbolsMap["CombiningLeft"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"], 
					  widthOfPage, coordinate["Page"]['X'], coordinate["Page"]['Y'] + i * 2);
		}

		YLine(pageSymbolsMap["CombiningUp"], pageSymbolsMap["WallVertical"], pageSymbolsMap["CombiningDown"], heightOfButtonsCell,
			  coordinate["Page"]['X'] + widthOfPage / 2 - distanceCentralLineFromCenterX, coordinate["Page"]['Y']);
	}

	void open()
	{
		while (true)
		{
			system("cls");
			set_color_text(colorsMap["StatisticBasic"]);

			create_basic();
			buttons.print();

			set_color_text(colorsMap["StatisticBasic"]);
			statistic.show(cout, coordinate["Page"]['X'] + 2, coordinate["Page"]['Y'] + heightOfButtonsCell);

			string nameOfButton = buttons.check_button_click();
			system("cls");

			if (nameOfButton == "Record to file")
				open_record_window();
			else
				break;
		}
	}

	void record_to_file(string fileName)
	{
		ofstream file(fileName, ios_base::app);
		statistic.show(file, 0, 0);
		file.close();
	}

	void open_record_window()
	{
		WindowInputSingle windowFileName(coordinateWindowX, coordinateWindowY, "Enter a file name");

		windowFileName.set_options(distanceStrFromTopInWindowY, distanceButtonsFromSidesInWindowInputX, 
								   distanceInputCellFromStrInWindowInputY, maxNumberOfSymbolsInWindowInput);
		windowFileName.replace_symbols(windowSymbolsMap);
		windowFileName.replace_colors(colorsMap);

		string fileName = windowFileName.open();

		if (!fileName.empty())
		{
			fileName.append(".txt");
			ifstream ifFile(fileName);

			if (ifFile.is_open() == true)
			{
				ifFile.close();

				WindowNotification windowAddNewDate(coordinateWindowX, coordinateWindowY, "A file with this name already exists, add new data to it?");

				windowAddNewDate.set_options(distanceStrFromTopInWindowY, distanceButtonsFromSidesInWindowNotificationX);
				windowAddNewDate.replace_symbols(windowSymbolsMap);
				windowAddNewDate.replace_colors(colorsMap);

				if (!windowAddNewDate.open())
					return;
			}

			record_to_file(fileName);
		}
	}

	PageStatistic& operator+= (const Statistic& other)
	{
		statistic += other;
		return *this;
	}
};


class PageOption : public Page
{
private:
	const int widthOfPage = 50;
	const int heightOfPage = 23;
	const int heightOfButtonsCell = 3;
	const int maxSizeOfFileName = 193;

	const int distanceStrFormLeftSideX = 5;
	const int distanceTapeCellFormLeftSideX = 35;

	const int distanceButtonExitFromLeftSideX = 2;
	const int distanceButtonSymbolsFromLeftSideX = 13;
	const int distanceButtonColorsFromLeftSideX = 24;
	const int distanceButtonKeysFromLeftSideX = 34;
	const int distanceButtonStandardFromLeftSideX = 4;
	const int distanceButtonCloseFromLeftSideX = 18;

	const char startOfPermissibleSymbols = '0';
	const char endOfPermissibleSymbols = '~';
	const string prohibitionSymbols = "\\ / \"\'<>*|?:";

	string saveFileName = "Save";

	map<string, unsigned int> standardSettingSymbols = 
	{ 
		{"windowSymbols", 1} , {"pageSymbols", 1}, {"groundSymbols", 0} 
	};

	map<string, unsigned int> standardSettingColors = 
	{ 
		{"GameCursor", 2}, {"ButtonsHighlighted", 1}, {"CheckKey", 3} 
	};

	map<string, char> standardSettingKeys = 
	{ 
		{"PutFlag", 'e'}, {"OpenCell", 'q'}, {"Up", 'w'}, {"Down", 's'},
		{"Left", 'a'}, {"Right", 'd'} 
	};

	vector<unsigned int> colorsCollection = { 7, 2, 22, 112 };

	map<string, vector<char>> symbolsCollection = 
	{ 
		{"WallVertical",    {(char)186, (char)179}},
		{"WallHorizontal",  {(char)205, (char)196}},
		{"CornerRightDown", {(char)188, (char)217}},
		{"CornerRightUp",   {(char)187, (char)191}},
		{"CornerLeftDown",  {(char)200, (char)192}},
		{"CornerLeftUp",    {(char)201, (char)218}},
		{"CombiningLeft",   {(char)204, (char)195}},
		{"CombiningRight",  {(char)185, (char)180}},
		{"CombiningUp",     {(char)203, (char)194}},
		{"CombiningDown",   {(char)202, (char)193}},
		{"Cross",           {(char)206, (char)197}} 
	};

	void set_buttons()
	{
		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonExitFromLeftSideX, 
							coordinate["Page"]['Y'] + heightOfButtonsCell - 1, "<- Exit"));
		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonSymbolsFromLeftSideX, 
							coordinate["Page"]['Y'] + heightOfButtonsCell - 1, "Symbols"));
		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonColorsFromLeftSideX, 
							coordinate["Page"]['Y'] + heightOfButtonsCell - 1, "Colors"));
		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonKeysFromLeftSideX, 
							coordinate["Page"]['Y'] + heightOfButtonsCell - 1, "Keys"));
	}

	void set_buttons_symbols(ButtonsControl& buttonsTab)
	{
		buttonsTab.push(Button(coordinate["Page"]['X'] + distanceButtonExitFromLeftSideX, 
							   coordinate["Page"]['Y'] + heightOfButtonsCell - 1, "<- Back"));
		buttonsTab.push(Button(coordinate["Page"]['X'] + distanceButtonSymbolsFromLeftSideX, 
							   coordinate["Page"]['Y'] + heightOfButtonsCell - 1, "Ground"));
		buttonsTab.push(Button(coordinate["Page"]['X'] + distanceButtonColorsFromLeftSideX, 
							   coordinate["Page"]['Y'] + heightOfButtonsCell - 1, "Window"));
		buttonsTab.push(Button(coordinate["Page"]['X'] + distanceButtonKeysFromLeftSideX, 
							   coordinate["Page"]['Y'] + heightOfButtonsCell - 1, "Page"));
	}

	void set_buttons_tab(ButtonsControl& buttonsTab)
	{
		buttonsTab.push(Button(coordinate["Page"]['X'] + distanceButtonStandardFromLeftSideX,
							   coordinate["Page"]['Y'] + heightOfPage - 2, "Standard"));
		buttonsTab.push(Button(coordinate["Page"]['X'] + distanceButtonCloseFromLeftSideX, 
							   coordinate["Page"]['Y'] + heightOfPage - 2, "Close"));
	}

	void set_buttons_row_of_tab(ButtonsControl& buttonsTab, const unsigned int& index)
	{
		buttonsTab.push(Button(coordinate["Page"]['X'] + 2, coordinate["Page"]['Y'] + heightOfButtonsCell + index + 1, 
			                   to_string(index + 1)));
	}

	void create_row_in_tab(const vector<TapeCell>& tapeCellsVector, ButtonsControl& buttonsTab, const unsigned int& index, const string& name)
	{
		set_buttons_row_of_tab(buttonsTab, index);

		set_position_console_cursor(coordinate["Page"]['X'] + distanceStrFormLeftSideX + 1, 
			                        coordinate["Page"]['Y'] + heightOfButtonsCell + index + 1);
		set_color_text(colorsMap["OptionBasic"]);
		cout << name << ": ";

		set_position_console_cursor(coordinate["Page"]['X'] + distanceTapeCellFormLeftSideX, 
			                        coordinate["Page"]['Y'] + heightOfButtonsCell + index + 1);

		if (tapeCellsVector[index].empty())
		{
			set_color_text(colorsMap["CheckKey"]);
			cout << (char)keysMap[tapeCellsVector[index].get_name()];
		}
		else
			cout << tapeCellsVector[index];
	}

	void change_repeat_key(const char& key, const string& nameOfCharacteristics)
	{
		unsigned int index = 0;

		for (auto& opt : keysMap)
		{
			index++;

			if (nameOfCharacteristics != opt.first && key == opt.second)
				keysMap[opt.first] = keysMap[nameOfCharacteristics];

			set_position_console_cursor(coordinate["Page"]['X'] + distanceTapeCellFormLeftSideX,
				                        coordinate["Page"]['Y'] + heightOfButtonsCell + index);
			set_color_text(colorsMap["CheckKey"]);
			cout << (char)keysMap[opt.first];
		}
	}

	void get_clicked_key(const string& nameOfCharacteristics, const unsigned int& coordinateX, const unsigned int& coordinateY)
	{
		set_color_text(colorsMap["CheckKey"]);
		set_position_console_cursor(coordinateX, coordinateY);
		cout << " ";

		while (true)
		{
			if (_kbhit())
			{
				char key = _getch();

				if (key >= startOfPermissibleSymbols && key <= endOfPermissibleSymbols && prohibitionSymbols.find(key) == -1)
				{
					change_repeat_key(key, nameOfCharacteristics);

					keysMap[nameOfCharacteristics] = key;

					set_position_console_cursor(coordinateX, coordinateY);
					cout << key;

					return;
				}
			}
		}
	}

	template <typename T>
	void check_button_click_in_tab(vector<TapeCell>& tapeCellsVector, ButtonsControl& buttonsTab, map<string, T>& mapOption,
		                           const string& nameOfSetting)
	{
		while (true)
		{
			string nameOfButtonClicked = buttonsTab.check_button_click();

			if (nameOfButtonClicked == "Standard")
				make_standard_setting(nameOfSetting);

			if (nameOfButtonClicked == "Standard" || nameOfButtonClicked == "Close")
				break;

			unsigned int index = stoi(nameOfButtonClicked) - 1;
			string nameOfCharacteristics = tapeCellsVector[index].get_name();

			if (!tapeCellsVector[index].empty())
			{
				tapeCellsVector[index].check_button_input(coordinate["Page"]['X'] + distanceTapeCellFormLeftSideX,
					                                      coordinate["Page"]['Y'] + heightOfButtonsCell + index + 1);

				if (nameOfSetting == "colors")
					mapOption[nameOfCharacteristics] = tapeCellsVector[index].get_current_color();
				else
					mapOption[nameOfCharacteristics] = tapeCellsVector[index].get_current_date();

				create_basic();
				buttons.replace_colors(colorsMap);

				buttonsTab.replace_colors(colorsMap);
				buttonsTab.print();
			}
			else 
				get_clicked_key(nameOfCharacteristics, coordinate["Page"]['X'] + distanceTapeCellFormLeftSideX,
					            coordinate["Page"]['Y'] + heightOfButtonsCell + index + 1);
		}
	}

	void open_tab_colors()
	{
		vector<TapeCell> tapeCellsVector;
		ButtonsControl buttonsTab;

		unsigned index = 0;

		for (auto& opt : colorsMap)
		{
			vector<char> symbolsShow;
			index++;

			for (unsigned int i = 0; i < colorsCollection.size(); i++)
				symbolsShow.push_back('X');

			tapeCellsVector.push_back(TapeCell(opt.first, symbolsShow, colorsCollection));
			tapeCellsVector.back().put_cursor_on_color(opt.second);

			create_row_in_tab(tapeCellsVector, buttonsTab, index - 1, opt.first);
		}

		set_buttons_tab(buttonsTab);
		check_button_click_in_tab(tapeCellsVector, buttonsTab, colorsMap, "colors");
	}

	void open_section_tab_symbols(map<string, char>& mapSection, const string& nameOfSetting)
	{
		vector<TapeCell> tapeCellsVector;
		ButtonsControl buttonsTab;

		unsigned index = 0;

		for (auto& opt : mapSection)
		{
			index++;

			tapeCellsVector.push_back(TapeCell(opt.first, symbolsCollection[opt.first], { CONSOLE_COLOR, CONSOLE_COLOR }));
			tapeCellsVector.back().put_cursor_on_value(opt.second);

			create_row_in_tab(tapeCellsVector, buttonsTab, index - 1, opt.first);
		}

		set_buttons_tab(buttonsTab);
		check_button_click_in_tab(tapeCellsVector, buttonsTab, mapSection, nameOfSetting);

		if (mapSection == pageSymbolsMap)
			create_basic();
	}

	void open_tab_symbols()
	{
		ButtonsControl buttonsSection;
		set_buttons_symbols(buttonsSection);

		clear_buttons();

		while (true)
		{
			clear_tab();
			string nameOfButtonClicked = buttonsSection.check_button_click();

			if (nameOfButtonClicked == "<- Back") 
				break;

			if (nameOfButtonClicked == "Ground")
				open_section_tab_symbols(groundSymbolsMap, "groundSymbols");
			else if (nameOfButtonClicked == "Window")
				open_section_tab_symbols(windowSymbolsMap, "windowSymbols");
			else if (nameOfButtonClicked == "Page")
				open_section_tab_symbols(pageSymbolsMap, "pageSymbols");
		}
	}

	void open_tab_keys()
	{
		vector<TapeCell> tapeCellsVector;
		ButtonsControl buttonsTab;

		unsigned index = 0;

		for (auto& opt : keysMap)
		{
			index++;

			TapeCell tempTapeCell(opt.first, {}, {});
			tempTapeCell.replace_keys(keysMap);
			tapeCellsVector.push_back(tempTapeCell);

			create_row_in_tab(tapeCellsVector, buttonsTab, index - 1, opt.first);
		}

		set_buttons_tab(buttonsTab);
		check_button_click_in_tab(tapeCellsVector, buttonsTab, keysMap, "keys");
	}

public:
	PageOption(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
	{
		set_coordinate(_coordinateX, _coordinateY);
	}

	PageOption()
		: PageOption(3, 1) {}


	void set_coordinate(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
	{
		coordinate["Page"]['X'] = _coordinateX;
		coordinate["Page"]['Y'] = _coordinateY;

		set_buttons();
	}

	void set_save_file_name(const string& _saveFileName)
	{
		if (_saveFileName.size() < maxSizeOfFileName)
		{
			for (char symbol : _saveFileName)
			{
				if (symbol >= startOfPermissibleSymbols && symbol <= endOfPermissibleSymbols && prohibitionSymbols.find(symbol) == -1)
					continue;

				throw invalid_argument("The file name contains prohibition symbols;\n");
			}
		}
		else
			throw length_error("The file name is too big (maxSize =" + to_string(maxSizeOfFileName) + 
				               ", your size = " + to_string(_saveFileName.size()) + " );\n");
	}

	map<string, char>& get_symbols_map_page()   { return pageSymbolsMap; }
	map<string, char>& get_symbols_map_ground() { return groundSymbolsMap; }
	map<string, char>& get_symbols_map_window() { return windowSymbolsMap; }
	map<string, unsigned int>& get_colors_map() { return colorsMap; }
	map<string, char>& get_keys_map()           { return keysMap; }

	bool symbol_is_present_in_map(const char& symbol)
	{
		for (const auto& item : symbolsCollection)
			for (const char& elem : item.second)
				if (symbol == elem)
					return true;

		return false;
	}

	void clear_tab()
	{
		for (unsigned int i = 1; i < heightOfPage - heightOfButtonsCell; i++)
		{
			set_position_console_cursor(coordinate["Page"]['X'] + 1, coordinate["Page"]['Y'] + heightOfButtonsCell + i);
			
			for (unsigned int k = 1; k < widthOfPage; k++)
				cout << " ";
		}

		XLine(pageSymbolsMap["CombiningLeft"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + heightOfPage - heightOfButtonsCell);
		XLine(pageSymbolsMap["CornerLeftDown"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CornerRightDown"], widthOfPage,
			coordinate["Page"]['X'], coordinate["Page"]['Y'] + heightOfPage - 1);
	}

	void clear_buttons()
	{
		set_position_console_cursor(coordinate["Page"]['X'] + 1, coordinate["Page"]['Y'] + heightOfButtonsCell - 1);

		for (unsigned int i = 1; i < widthOfPage; i++)
			cout << " ";
	}

	void create_basic()
	{
		set_color_text(colorsMap["OptionBasic"]);

		YLine(pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], heightOfPage - 1,
			coordinate["Page"]['X'], coordinate["Page"]['Y']);
		YLine(pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], heightOfPage - 1,
			coordinate["Page"]['X'] + widthOfPage, coordinate["Page"]['Y']);

		XLine(pageSymbolsMap["CornerLeftUp"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CornerRightUp"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y']);
		XLine(pageSymbolsMap["CombiningLeft"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + heightOfButtonsCell);
		XLine(pageSymbolsMap["CombiningLeft"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + heightOfPage - heightOfButtonsCell);
		XLine(pageSymbolsMap["CornerLeftDown"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CornerRightDown"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + heightOfPage - 1);
	}

	void open()
	{
		system("cls");
		create_basic();
		buttons.print();

		while (true)
		{
			clear_tab();
			clear_buttons();

			string nameOfButtonClicked = buttons.check_button_click();

			if (nameOfButtonClicked == "<- Exit") 
				break;

			if (nameOfButtonClicked == "Symbols")
				open_tab_symbols();
			else if (nameOfButtonClicked == "Colors")
				open_tab_colors();
			else if (nameOfButtonClicked == "Keys")
				open_tab_keys();
		}

		system("cls");
	}

	template<typename KEY, typename VALUE>
	void save_one_map_to_file(ofstream& saveFile, const map<KEY, VALUE>& mapItem)
	{
		for (const auto& item : mapItem)
			saveFile.write((char*)&item.second, sizeof(item.second));
	}

	void save_to_file()
	{
		ofstream saveFile(saveFileName);

		save_one_map_to_file(saveFile, colorsMap);
		save_one_map_to_file(saveFile, windowSymbolsMap);
		save_one_map_to_file(saveFile, pageSymbolsMap);
		save_one_map_to_file(saveFile, groundSymbolsMap);
		save_one_map_to_file(saveFile, keysMap);

		saveFile.close();
	}

	template<typename KEY, typename VALUE>
	void read_one_map_into_file(ifstream& saveFile, map<KEY, VALUE>& mapItem,
		                        const bool& isKeys = false, const bool& isColors = false)
	{
		for (auto& item : mapItem)
		{
			VALUE valueTemp = 0;
			saveFile.read((char*)&valueTemp, sizeof(valueTemp));

			if (isKeys && (isupper(valueTemp) || islower(valueTemp) || isdigit(valueTemp)))
				item.second = valueTemp;
			else if (isColors && find(begin(colorsCollection), end(colorsCollection), valueTemp) != end(colorsCollection))
				item.second = valueTemp;
			else if (!isKeys && !isColors && symbol_is_present_in_map(valueTemp))
				item.second = valueTemp;
			else
				throw invalid_argument("Save file is damaged;\n");
		}
	}

	void read_into_file()
	{
		ifstream saveFile(saveFileName);

		if (saveFile.is_open())
		{
			read_one_map_into_file(saveFile, colorsMap, false, true);
			read_one_map_into_file(saveFile, windowSymbolsMap);
			read_one_map_into_file(saveFile, pageSymbolsMap);
			read_one_map_into_file(saveFile, groundSymbolsMap);
			read_one_map_into_file(saveFile, keysMap, true, false);

			saveFile.close();
		}
	}

	void make_colors_standard_setting()
	{
		for (auto& item : colorsMap)
			item.second = colorsCollection[standardSettingColors[item.first]];
	}

	void make_symbols_standard_setting(const string& nameOfSection, map<string, char>& mapOfSection)
	{
		for (auto& item : mapOfSection)
			item.second = symbolsCollection[item.first][standardSettingSymbols[nameOfSection]];
	}

	void make_keys_standard_setting()
	{
		for (auto& item : keysMap)
			item.second = standardSettingKeys[item.first];
	}

	void make_standard_setting(const string& nameOfSetting)
	{
		if (nameOfSetting == "colors")
			make_colors_standard_setting();
		else if (nameOfSetting == "windowSymbols")
			make_symbols_standard_setting("windowSymbols", windowSymbolsMap);
		else if (nameOfSetting == "pageSymbols")
			make_symbols_standard_setting("pageSymbols", pageSymbolsMap);
		else if (nameOfSetting == "groundSymbols")
			make_symbols_standard_setting("groundSymbols", groundSymbolsMap);
		else if (nameOfSetting == "keys")
			make_keys_standard_setting();
	}
};

class PageMenu : public Page
{
private:
	const int widthOfPage = 25;
	const int heightOfPage = 10;
	const int distanceTextFromLeftSideX = 7;

	const int distanceButtonsFromLeftSideX = 2;
	const int distanceButtonStartFromTopY = 2;
	const int distanceButtonStatisticsFromTopY = 4;
	const int distanceButtonOptionFromTopY = 6;
	const int distanceButtonExitFromTopY = 8;

	PageStatistic pageStatistic;
	PageGame pageGame;
	PageOption pageOption;

	void set_buttons()
	{
		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonsFromLeftSideX + 1,
			                coordinate["Page"]['Y'] + distanceButtonStartFromTopY + 1, "Start"));
		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonsFromLeftSideX + 1,
							coordinate["Page"]['Y'] + distanceButtonStatisticsFromTopY + 1, "Statistics"));
		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonsFromLeftSideX + 1,
							coordinate["Page"]['Y'] + distanceButtonOptionFromTopY + 1, "Option"));
		buttons.push(Button(coordinate["Page"]['X'] + distanceButtonsFromLeftSideX + 1,
							coordinate["Page"]['Y'] + distanceButtonExitFromTopY + 1, "Exit"));
	}

public:
	PageMenu(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
	{
		coordinate["Page"]['X'] = _coordinateX;
		coordinate["Page"]['Y'] = _coordinateY;
		set_buttons();
	}

	PageMenu()
		: PageMenu(5, 3) {}


	void replace_characterizations_of_pages_into_option()
	{
		replace_colors(pageOption.get_colors_map());
		replace_keys(pageOption.get_keys_map());
		replace_symbols_of_page(pageOption.get_symbols_map_page());
		replace_symbols_of_ground(pageOption.get_symbols_map_ground());
		replace_symbols_of_window(pageOption.get_symbols_map_window());

		pageGame.replace_symbols_of_page(pageSymbolsMap);
		pageGame.replace_symbols_of_ground(groundSymbolsMap);
		pageGame.replace_symbols_of_window(windowSymbolsMap);
		pageGame.replace_colors(colorsMap);
		pageGame.replace_keys(keysMap);

		pageStatistic.replace_symbols_of_page(pageSymbolsMap);
		pageStatistic.replace_symbols_of_ground(groundSymbolsMap);
		pageStatistic.replace_symbols_of_window(windowSymbolsMap);
		pageStatistic.replace_colors(colorsMap);
		pageStatistic.replace_keys(keysMap);
	}

	PageGame& get_page_game()           { return pageGame; }
	PageStatistic& get_page_statistic() { return pageStatistic; }

	void create_basic()
	{
		set_position_console_cursor(coordinate["Page"]['X'] + distanceTextFromLeftSideX, coordinate["Page"]['Y'] + 1);
		cout << "MINESWEEPER";

		YLine(pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], heightOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y']);
		YLine(pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], pageSymbolsMap["WallVertical"], heightOfPage,
			  coordinate["Page"]['X'] + widthOfPage, coordinate["Page"]['Y']);

		XLine(pageSymbolsMap["CornerLeftUp"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CornerRightUp"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y']);
		XLine(pageSymbolsMap["CombiningLeft"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + distanceButtonStartFromTopY);
		XLine(pageSymbolsMap["CombiningLeft"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + distanceButtonStatisticsFromTopY);
		XLine(pageSymbolsMap["CombiningLeft"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + distanceButtonOptionFromTopY);
		XLine(pageSymbolsMap["CombiningLeft"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CombiningRight"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + distanceButtonExitFromTopY);
		XLine(pageSymbolsMap["CornerLeftDown"], pageSymbolsMap["WallHorizontal"], pageSymbolsMap["CornerRightDown"], widthOfPage,
			  coordinate["Page"]['X'], coordinate["Page"]['Y'] + heightOfPage);
	}

	void open_menu()
	{
		string buttonName;

		pageOption.read_into_file();
		replace_characterizations_of_pages_into_option();

		while (true)
		{
			create_basic();
			buttonName = buttons.check_button_click();

			if (buttonName == "Exit")
				break;

			if (buttonName == "Start")
				pageStatistic += pageGame.open();
			else if (buttonName == "Statistics")
				pageStatistic.open();
			else if (buttonName == "Option")
			{
				pageOption.open();
				pageOption.save_to_file();
				replace_characterizations_of_pages_into_option();
			}
		}

		system("cls");
	}
};