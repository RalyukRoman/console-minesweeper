#pragma once
#include "Gameplay.h"


class Ground
{
private:
    const char cellSymbolFlag = '!';
    const char cellSymbolMine = 'x';
    const char cellSymbolEmpty = ' ';

    const int maxSizeField = 15;
    const int minSizeField = 3;
    const int minSizeFieldForPlacementOfTextInCenterX = 9;
    const int widthOfText = 9;

    unsigned int distanceTextFromFieldY;
    Field field;

    map<char, unsigned int> cursorPosition;
    map<char, unsigned int> coordinate;

    map <string, unsigned int> colors = 
    { 
        { "GameBasic", 7}, { "GameCursor", 22 }, { "GameText", 7 }
    };

    map <string, char> symbols = 
    { 
        {"WallVertical", 186}, {"WallHorizontal", 205}, {"CornerRightDown", 188}, {"CornerRightUp", 187},
        {"CornerLeftDown", 200}, {"CornerLeftUp", 201}, {"CombiningLeft", 204}, {"CombiningRight", 185},
        {"CombiningUp", 203}, {"CombiningDown", 202}, {"Cross", 206}
    };


    void print_symbol_of_ground(const unsigned int& printX, const unsigned int& printY)
    {
        if (!(printX % 2 == 0 && printY % 2 == 0))
        {
            if (printX == coordinate['X'])
            {
                if (printY == coordinate['Y'])
                    cout << symbols["CornerLeftUp"];
                else if (printY == coordinate['Y'] + 2 * field.get_size('Y'))
                    cout << symbols["CornerLeftDown"];
                else if (printY % 2 == 1)
                    cout << symbols["CombiningLeft"];
                else
                    cout << symbols["WallVertical"];
            }
            else if (printX == coordinate['X'] + 2 * field.get_size('X'))
            {
                if (printY == coordinate['Y'])
                    cout << symbols["CornerRightUp"];
                else if (printY == coordinate['Y'] + 2 * field.get_size('Y'))
                    cout << symbols["CornerRightDown"];
                else if (printY % 2 == 1)
                    cout << symbols["CombiningRight"];
                else
                    cout << symbols["WallVertical"];
            }
            else if (printX % 2 == 1)
            {
                if (printY == coordinate['Y'])
                    cout << symbols["CombiningUp"];
                else if (printY == coordinate['Y'] + 2 * field.get_size('Y'))
                    cout << symbols["CombiningDown"];
                else if (printY % 2 == 0)
                    cout << symbols["WallVertical"];
                else
                    cout << symbols["Cross"];
            }
            else
                cout << symbols["WallHorizontal"];
        }
        else
            cout << cellSymbolEmpty;
    }

public:
    Ground(const unsigned int& _sizeFieldX, const unsigned int& _sizeFieldY, 
           const unsigned int& _coordinateFieldX, const unsigned int& _coordinateFieldY,
           const unsigned int& _distanceTextFromFieldY)
        : distanceTextFromFieldY{ _distanceTextFromFieldY }
    {
        set_coordinate_field(_coordinateFieldX, _coordinateFieldY);
        set_field_size(_sizeFieldX, _sizeFieldY);

        cursorPosition['X'] = 0;
        cursorPosition['Y'] = 0;
    }

    Ground(const unsigned int& _sizeX, const unsigned int& _sizeY, 
           const unsigned int& _coordinateFieldX, const unsigned int& _coordinateFieldY)
        : Ground(_sizeX, _sizeY, _coordinateFieldX, _coordinateFieldY, 4) {}

    Ground(const unsigned int& _sizeX, const unsigned int& _yMax)
        : Ground(_sizeX, _yMax, 3, 5, 4) {}

    Ground()
        : Ground(3, 3, 3, 5, 4) {}


    void set_coordinate_field(const unsigned int& _coordinateFieldX, const unsigned int& _coordinateFieldY)
    {
        coordinate['X'] = _coordinateFieldX;
        coordinate['Y'] = _coordinateFieldY;
    }

    void set_field_size(unsigned int _sizeFieldX, unsigned int _sizeFieldY)
    {
        string strExcept;

        if (_sizeFieldX < minSizeField || _sizeFieldX > maxSizeField)
        {
            strExcept.append("The value for x (" + to_string(_sizeFieldX) +
                             ") goes beyond the permissible values in the Ground;\n");

            equal_to_no_less(_sizeFieldX, minSizeField);
            equal_to_no_more(_sizeFieldX, maxSizeField);
        }

        if (_sizeFieldY < minSizeField || _sizeFieldY > maxSizeField)
        {
            strExcept.append("The value for y (" + to_string(_sizeFieldY) +
                             ") goes beyond the permissible values in the Ground;\n");

            equal_to_no_less(_sizeFieldY, minSizeField);
            equal_to_no_more(_sizeFieldY, maxSizeField);
        }

        field = Field(_sizeFieldX, _sizeFieldY);

        if (!strExcept.empty())
            throw invalid_argument(strExcept);
    }

    void set_cursor_position(const unsigned int& _cursorPositionX, const unsigned int& _cursorPositionY)
    {
        field.check_out_of_range(_cursorPositionX, _cursorPositionY);

        improve_cell(cursorPosition['X'], cursorPosition['Y'], true);

        cursorPosition['X'] = _cursorPositionX;
        cursorPosition['Y'] = _cursorPositionY;

        improve_cell(cursorPosition['X'], cursorPosition['Y'], false);
    }

    void replace_colors(const map <string, unsigned int>& _colors)
    {
        replace_map_elements_from_another_map(colors, _colors);
    }

    void replace_symbols(const map <string, char>& _symbols)
    {
        replace_map_elements_from_another_map(symbols, _symbols);
    }

    bool get_current_cell_is_flag()
    {
        return field.cell_is_flag(cursorPosition['X'], cursorPosition['Y']);
    }

    unsigned int get_number_of_mines()          
    { 
        return field.get_number_of_mines(); 
    }

    unsigned int get_field_size(const char& ch) 
    { 
        return field.get_size(ch); 
    }

    bool is_win()  { return field.is_win(); }
    bool is_lose() { return field.is_lose(); }

    void create_basic()
    {
        set_color_text(colors["GameBasic"]);

        for (unsigned int printY = coordinate['Y'];
             printY < field.get_size('Y') * 2 + 1 + coordinate['Y'];
             printY++)
        {
            for (unsigned int printX = coordinate['X'];
                 printX < field.get_size('X') * 2 + 1 + coordinate['X'];
                 printX++)
            {
                set_position_console_cursor(printX, printY);
                print_symbol_of_ground(printX, printY);
            }
        }
    }

    void render()
    {
        create_basic();
        field.clear_grid();
        set_cursor_position(0, 0);
    }

    void improve_cell(const unsigned int& x, const unsigned int& y, const bool ignoreCursor = false)
    {
        set_position_console_cursor(coordinate['X'] + x * 2 + 1,
                                    coordinate['Y'] + y * 2 + 1);

        if (!ignoreCursor && x == cursorPosition['X'] && y == cursorPosition['Y'])
            set_color_text(colors["GameCursor"]);
        else
            set_color_text(colors["GameBasic"]);

        if (field.cell_is_empty(x, y) || field.cell_is_common_mine(x, y))
            cout << cellSymbolEmpty;
        else if (field.cell_is_flag(x, y))
            cout << cellSymbolFlag;
        else if (field.cell_is_mine(x, y))
            cout << cellSymbolMine;
        else
            cout << field.get_cell(x, y);
    }

    void change_cursor(const int& addX, const int& addY)
    {
        try
        {
            set_cursor_position(cursorPosition['X'] + addX, cursorPosition['Y'] + addY);
        }
        catch (...) {}
    }

    void put_flag()
    {
        field.put_flag(cursorPosition['X'], cursorPosition['Y']);
        improve_cell(cursorPosition['X'], cursorPosition['Y']);
    }

    void open_cell(const unsigned int& x, const unsigned int& y)
    {
        if (field.cell_is_empty(x, y) || field.cell_is_common_mine(x, y))
        { 
            field.open_cell(x, y);
            improve_cell(x, y);

            if (field.get_cell(x, y) == 0)
                open_cells_in_area(x, y);

            if (is_win())
                print_result(true);
            else if (is_lose())
                print_result(false);
        }
    }

    void open_cell_on_cursor(const bool& firstOpen = false)
    {
        if (firstOpen)
            field.random_fill_mines(cursorPosition['X'], cursorPosition['Y']);

        open_cell(cursorPosition['X'], cursorPosition['Y']);
    }

    void open_cells_in_area(const unsigned int& x, const unsigned int& y)
    {
        field.check_out_of_range(x, y);

        for (int xCheck = (int)x - 1; xCheck <= (int)x + 1; xCheck++)
        {
            for (int yCheck = (int)y - 1; yCheck <= (int)y + 1; yCheck++)
            {
                if (xCheck == x && yCheck == y)
                    continue;

                try
                {
                    open_cell(xCheck, yCheck);
                }
                catch (...) {}
            }
        }
    }

    void open_field()
    {
        set_color_text(colors["GameBasic"]);

        for (unsigned int i = 0; i < field.get_size('X'); i++)
            for (unsigned int j = 0; j < field.get_size('Y'); j++)
                improve_cell(i, j);
    }

    void print_result(const bool& isWin)
    {
        if (!isWin)
            field.open_grid();

        open_field();

        unsigned int printX = field.get_size('X');
        unsigned int printY = field.get_size('Y');

        equal_to_no_less(printX, minSizeFieldForPlacementOfTextInCenterX);

        printX = coordinate['X'] + printX - widthOfText / 2;
        printY = coordinate['Y'] + printY * 2 + distanceTextFromFieldY;

        set_position_console_cursor(printX, printY);
        set_color_text(colors["GameText"]);

        if (isWin) 
            cout << "YOU WIN!";
        else       
            cout << "YOU LOSE!";

    }
};


class Button
{
private:
    string name = "Button";
    bool highlighted;

    map<char, unsigned int> coordinate;

    map<string, unsigned int> colors = 
    { 
        {"ButtonsBasic", 7}, {"ButtonsHighlighted", 2} 
    };

public:
    Button(const unsigned int& _coordinateX, const unsigned int& _coordinateY, const string& _name, const bool& _highlighted)
        : highlighted{_highlighted} 
    {
        set_coordinate(_coordinateX, _coordinateY);
        set_name(_name);
    }

    Button(const unsigned int& _coordinateX, const unsigned int& _coordinateY, const string& _name)
        : Button(_coordinateX, _coordinateY, _name, false) {}

    Button(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
        : Button(_coordinateX, _coordinateY, "Button", false) {}

    Button()
        : Button(0, 0, "Button", false) {}


    void set_coordinate(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
    {
        coordinate['X'] = _coordinateX;
        coordinate['Y'] = _coordinateY;
    }

    void set_name(const string& _name)
    {
        if (_name.empty())
            throw length_error("The name for the button is empty;\n");
        else if (!check_string(_name))
            throw invalid_argument("The name has incorrect symbol;\n");
        else 
            name = _name;
    }

    void set_highlighted(const bool& _highlighted)
    {
        highlighted = _highlighted;
    }

    void replace_colors(const map <string, unsigned int>& _colors)
    {
        replace_map_elements_from_another_map(colors, _colors);
    }

    string get_name() const 
    { 
        return name; 
    }
    bool is_highlighted() const 
    { 
        return highlighted; 
    }

    unsigned int get_coordinate(const char& ch) const
    {
        if (ch == 'X' || ch == 'Y')
            return coordinate.at(ch);
        else
            throw invalid_argument("Invalid symbol to get coordinate of the button (ch = " + to_string((char)ch) + "); \n");
    }

    void print()
    {
        if (highlighted) 
            set_color_text(colors["ButtonsHighlighted"]);
        else             
            set_color_text(colors["ButtonsBasic"]);

        set_position_console_cursor(coordinate['X'], coordinate['Y']);
        cout << name;
    }

    friend bool operator== (const Button& one, const Button& two)
    {
        return one.name == two.name;
    }
};


class ButtonsControl
{
private:
    unsigned int indexOfHighlighted = 0;

    vector<Button> buttonsVector;

    map <string, char> keys = 
    { 
        {"Up", 'w'}, {"Down", 's'}, {"Left", 'a'}, {"Right", 'd'}, {"Click", 13}
    };

public:
    void check_out_of_range(const string& buttonName, const unsigned int& _coordinateX, const unsigned int& _coordinateY)
    {
        for (Button& btn : buttonsVector)
        {
            if (btn.get_name() != buttonName &&
                btn.get_coordinate('Y') == _coordinateY &&
                _coordinateX + buttonName.size() >= btn.get_coordinate('X') &&
                _coordinateX <= btn.get_coordinate('X') + btn.get_name().size())
            {
                throw out_of_range("Buttons overlap each other;\n");
            }
        }
    }

    void set_coordinate_button(const string& buttonName, const unsigned int& _coordinateX, const unsigned int& _coordinateY)
    {
        check_out_of_range(buttonName, _coordinateX, _coordinateY);

        unsigned int index = (unsigned int) (find_button(buttonName) - begin(buttonsVector));
        buttonsVector[index].set_coordinate(_coordinateX, _coordinateY);
    }

    void set_name_of_button(const string& oldButtonName, string newButtonName)
    {
        unsigned int index = (unsigned int) (find_button(oldButtonName) - begin(buttonsVector));
        buttonsVector[index].set_name(newButtonName);
    }

    void replace_colors(const map <string, unsigned int>& _colors)
    {
        for (Button& btn : buttonsVector)
            btn.replace_colors(_colors);
    }

    void replace_keys(const map <string, char>& _keys)
    {
        replace_map_elements_from_another_map(keys, _keys);
    }

    void push(const Button& btn)
    {
        check_out_of_range(btn.get_name(), btn.get_coordinate('X'), btn.get_coordinate('Y'));

        buttonsVector.push_back(btn);

        if ((unsigned int) buttonsVector.size() == 1)
            buttonsVector.front().set_highlighted(true);
    }

    void pop()
    {
        if (buttonsVector.empty())
            return;

        if (buttonsVector.size() > 1 && buttonsVector.back().is_highlighted())
        {
            indexOfHighlighted -= 1;
            buttonsVector[indexOfHighlighted].set_highlighted(true);
        }

        buttonsVector.pop_back();
    }

    void highlight(const unsigned int& index = 0)
    {
        if (index >= buttonsVector.size())
            throw out_of_range("Invalid value for the button, maximum value: " + to_string(buttonsVector.size() - 1) +
                               ", but index = " + to_string(index) + ";\n");

        if (index != indexOfHighlighted)
        {
            buttonsVector[indexOfHighlighted].set_highlighted(false);
            indexOfHighlighted = index;
            buttonsVector[indexOfHighlighted].set_highlighted(true);
        }
    }

    vector<Button>::iterator find_button(const string& buttonName)
    {
        Button btn(0, 0, buttonName);
        auto it = find(begin(buttonsVector), end(buttonsVector), btn);

        if (it == end(buttonsVector))
            throw invalid_argument("The button under the name of the " + buttonName + " isn`t founded;\n");

        return it;
    }

    void print()
    {
        for (Button& elem : buttonsVector)
        {
            elem.print();
            set_color_text(CONSOLE_COLOR);
        }
    }

    void clear()
    {
        buttonsVector.clear();
    }

    string check_button_click()
    {
        print();

        while (true)
        {
            if (_kbhit())
            {
                char symbol = _getch();

                if (symbol == keys["Click"])
                    return buttonsVector[indexOfHighlighted].get_name();

                if (symbol == keys["Down"] || symbol == keys["Right"])
                {
                    if (indexOfHighlighted == (unsigned int) buttonsVector.size() - 1)
                        highlight(0);
                    else
                        highlight(indexOfHighlighted + 1);
                }
                else if (symbol == keys["Up"] || symbol == keys["Left"])
                {
                    if (indexOfHighlighted == 0)
                        highlight((unsigned int) buttonsVector.size() - 1);
                    else
                        highlight(indexOfHighlighted - 1);
                }

                print();
            }
        }
    }

    ButtonsControl& operator= (const ButtonsControl& other)
    {
        if (this != &other)
            buttonsVector = other.buttonsVector;

        return *this;
    }
};


class InputCell
{
private:
    const char startOfPermissibleSymbols = ';';
    const char endOfPermissibleSymbols = '~';
    const string prohibitionSymbols = "\\<>|?";

    unsigned int color = 112;
    unsigned int length = 1;
    unsigned int maxNumberOfSymbols;
    string date;

    map <string, char> keys = 
    { 
        {"Click", 13}, {"Delete", 8} 
    };

public:
    InputCell(const unsigned int& _length, const unsigned int& _maxNumberOfSymbols)
    {
        set_length(_length);
        set_max_number_of_symbols(_maxNumberOfSymbols);
    }

    InputCell(const unsigned int& _length)
        : InputCell(_length, 100) {}

    InputCell()
        : InputCell(5, 100) {}


    void set_length(const unsigned int& _length)
    {
        if (_length == 0)
            throw invalid_argument("Length cannot equal zero;\n");
        else
            length = _length;
    }

    void set_max_number_of_symbols(const unsigned int& _maxNumberOfSymbols)
    {
         if (_maxNumberOfSymbols == 0)
             throw invalid_argument("Maximum number of symbols cannot equal zero;\n");
         else
             maxNumberOfSymbols = _maxNumberOfSymbols;
    }

    void set_color(const unsigned int& _color)
    {
        color = _color;
    }

    void replace_keys(const map <string, char>& _keys)
    {
        replace_map_elements_from_another_map(keys, _keys);
    }

    string get_date()
    {
        return date;
    }

    bool empty() const
    {
        return date.empty();
    }

    void check_input(const unsigned int& coordinateX, const unsigned int& coordinateY, const bool& only_digits = false)
    {
        set_color_text(color);
        set_position_console_cursor(coordinateX, coordinateY);
        cout << *this;

        while (true)
        {
            if (_kbhit())
            {
                char symbol = _getch();

                if (symbol == keys["Click"])
                    break;

                if (symbol == keys["Delete"] && !date.empty())
                    date.pop_back();
                else if (maxNumberOfSymbols <= date.size())
                    continue;
                else if (isdigit(symbol))
                    date.push_back(symbol);
                else if (symbol >= startOfPermissibleSymbols && symbol <= endOfPermissibleSymbols && 
                         !only_digits && prohibitionSymbols.find(symbol) == -1)
                    date.push_back(symbol);

                set_position_console_cursor(coordinateX, coordinateY);
                cout << *this;
            }
        }
    }

    friend ostream& operator<< (ostream& OUTStream, const InputCell& other)
    {
        if (other.date.size() <= other.length)
        {
            OUTStream << other.date;

            for (unsigned int i = (unsigned int) other.date.size(); i < other.length; i++)
                OUTStream << " ";
        }
        else
        {
            string tempDate = other.date.substr(other.date.size() - other.length, other.date.size());
            OUTStream << tempDate;
        }

        return OUTStream;
    }
};


class TapeCell
{
private:
    string name = "TapeCell";
    unsigned int colorBasic = 7;
    unsigned int currentPositionIndex = 0;

    vector<char> date;
    vector<unsigned int> dateColors;

    map <string, char> keys = 
    { 
        {"Click", 13}, {"Up", 'w'}, {"Down", 's'}, {"Left", 'a'}, {"Right", 'd'} 
    };


    void check_correct_current_position_index()
    {
        if (currentPositionIndex >= date.size())
        {
            if (date.empty())
                currentPositionIndex = 0;
            else
                currentPositionIndex = (unsigned int)date.size() - 1;
        } 
    }

public:
    TapeCell(const string& _name, const vector<char>& _date, const vector<unsigned int>& _dateColors,
             const unsigned int& _currentPositionIndex)
    {
        set_date_and_colors(_date, _dateColors);
        set_name(_name);
        put_cursor(_currentPositionIndex);
    }

    TapeCell(const string& _name, const vector<char>& _date, const vector<unsigned int>& _dateColors)
        : TapeCell(_name, _date, _dateColors, 0) {}

    TapeCell(const string& _name)
        : TapeCell(_name, {}, {}, 0) {}
    
    TapeCell()
        : TapeCell("TapeCell", {}, {}, 0) {}


    void set_date_and_colors(const vector<char>& _date, const vector<unsigned int>& _dateColors)
    {
        if (_date.size() != _dateColors.size())
            throw length_error("The vectors aren`t equal;\n");

        date = _date;
        dateColors = _dateColors;

        check_correct_current_position_index();
    }

    void set_name(const string& _name)
    {
        if (_name.empty())
            throw length_error("The name is empty;\n");
        else if (!check_string(_name))
            throw invalid_argument("The str has incorrect symbol;\n");
        else
            name = _name;
    }

    void set_color(const unsigned int& _colorBasic)
    {
        colorBasic = _colorBasic;
    }

    void replace_keys(const map <string, char>& _keys)
    {
        replace_map_elements_from_another_map(keys, _keys);
    }

    char get_current_date() const
    {
        if (empty()) 
            return 0;

        return date[currentPositionIndex];
    }

    unsigned int get_current_color() const
    {
        if (empty()) 
            return 0;

        return dateColors[currentPositionIndex];
    }

    unsigned int get_current_position() const
    {
        return currentPositionIndex;
    }

    string get_name() const
    {
        return name;
    }

    bool empty() const
    {
        return date.empty();
    }

    void push(const char& _dateItem, const unsigned int& _color)
    {
        date.push_back(_dateItem);
        dateColors.push_back(_color);
    }

    void pop()
    {
        if (empty()) 
            return;

        date.pop_back();
        dateColors.pop_back();

        check_correct_current_position_index();
    }

    void check_button_input(const unsigned int& coordinateX, const unsigned int& coordinateY)
    {
        if (empty()) 
            return;

        set_position_console_cursor(coordinateX, coordinateY);
        cout << *this;

        while (true)
        {
            if (_kbhit())
            {
                char symbol = _getch();

                if (symbol == keys["Click"])
                    break;

                if (symbol == keys["Right"] || symbol == keys["Up"])
                {
                    if (currentPositionIndex + 1 >= (unsigned int) date.size())
                        currentPositionIndex = 0;
                    else
                        currentPositionIndex++;
                }
                else if (symbol == keys["Left"] || symbol == keys["Down"])
                {
                    if (currentPositionIndex == 0)
                        currentPositionIndex = (unsigned int) date.size() - 1;
                    else
                        currentPositionIndex--;
                }

                set_position_console_cursor(coordinateX, coordinateY);
                cout << *this;
            }
        }
    }

    void put_cursor_on_value(const char& value)
    {
        auto it = find(begin(date), end(date), value);

        if (it == end(date))
            throw invalid_argument("Element with this value doesn`t exist (value = " + to_string(value) +");\n");
        else
            currentPositionIndex = (unsigned int)(it - begin(date));
    }

    void put_cursor_on_color(const unsigned int& color)
    {
        auto it = find(begin(dateColors), end(dateColors), color);

        if (it == end(dateColors))
            throw invalid_argument("Element with this color doesn`t exist (color = " + to_string(color) + ");\n");
        else
            currentPositionIndex = (unsigned int) (it - begin(dateColors));
    }

    void put_cursor(const unsigned int& _currentPositionIndex)
    {
        if (currentPositionIndex >= date.size() && currentPositionIndex != 0)
            throw out_of_range("Index of current position of larger size of vector elements (" + to_string(date.size()) + ") ;\n");
        else
            currentPositionIndex = _currentPositionIndex;
    }

    friend ostream& operator<< (ostream& OUTStream, const TapeCell& other)
    {
        if (other.empty()) 
            return OUTStream;

        set_color_text(other.colorBasic);
        cout << "< ";

        set_color_text(other.dateColors[other.currentPositionIndex]);
        cout << other.date[other.currentPositionIndex];

        set_color_text(other.colorBasic);
        cout << " >";

        return OUTStream;
    }

    friend bool operator== (const TapeCell& first, const TapeCell& second)
    {
        return first.name == second.name;
    }
};


class Window
{
protected:
    const int distanceStrFromSideX = 1;
    const int widthOfButtonOk = 2;
    const int widthOfButtonCloseX = 5;
    const int distanceBetweenButtonsX = 3;

    unsigned int distanceStrFromTopY = 0;
    unsigned int distanceButtonsFromSidesX = 1;

    string str;
    ButtonsControl buttons;

    map<char, unsigned int> size;
    map<char, unsigned int> coordinate;

    map<string, unsigned int> colors = 
    { 
        {"WindowBasic", 7}, {"CheckKey", 112} 
    };

    map <string, char> symbols = 
    { 
        {"WallVertical", 179}, {"WallHorizontal", 196}, {"CornerLeftUp", 218}, {"CornerLeftDown", 192}, 
        {"CornerRightUp", 191}, {"CornerRightDown", 217} 
    };


    void create_buttons()
    {
        equal_to_no_less(size['X'], distanceButtonsFromSidesX * 2 + widthOfButtonOk + widthOfButtonCloseX + distanceBetweenButtonsX);

        unsigned int coordinateButtonsY = coordinate['Y'] + size['Y'] - 1;
        unsigned int coordinateButtonCloseX = coordinate['X'] + distanceButtonsFromSidesX + 1;
        unsigned int coordinateButtonOkX = coordinate['X'] + size['X'] - widthOfButtonOk - distanceButtonsFromSidesX;

        buttons.clear();

        buttons.push(Button(coordinateButtonCloseX, coordinateButtonsY, "Close"));
        buttons.push(Button(coordinateButtonOkX, coordinateButtonsY, "Ok"));
    }

    void create_basic()
    {
        set_color_text(colors["WindowBasic"]);

        YLine(symbols["WallVertical"], symbols["WallVertical"], symbols["WallVertical"], size['Y'],
              coordinate['X'], coordinate['Y']);
        YLine(symbols["WallVertical"], symbols["WallVertical"], symbols["WallVertical"], size['Y'],
              coordinate['X'] + size['X'], coordinate['Y']);

        XLine(symbols["CornerLeftUp"], symbols["WallHorizontal"], symbols["CornerRightUp"], size['X'],
              coordinate['X'], coordinate['Y']);
        XLine(symbols["CornerLeftDown"], symbols["WallHorizontal"], symbols["CornerRightDown"], size['X'],
              coordinate['X'], coordinate['Y'] + size['Y']);
    }

    void create()
    {
        system("cls");
        set_color_text(colors["WindowBasic"]);

        set_position_console_cursor(coordinate['X'] + distanceStrFromSideX + 1, coordinate['Y'] + distanceStrFromTopY + 1);
        cout << str;

        equal_to_no_less(size['X'], (unsigned int)str.size() + distanceStrFromSideX * 2 + 2);
        
        create_buttons();
        buttons.print();

        create_basic();
    }

public:
    Window(const unsigned int& _coordinateX, const unsigned int& _coordinateY, const string& _str)
    {
        set_coordinate(_coordinateX, _coordinateY);
        set_str(_str);
    }

    Window(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
        : Window(_coordinateX, _coordinateY, " ") {}

    Window()
        : Window(5, 5, " ") {}


    void set_coordinate(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
    {
        coordinate['X'] = _coordinateX;
        coordinate['Y'] = _coordinateY;
    }

    void set_str(const string& _str)
    {
        if (!check_string(_str))
            throw invalid_argument("The str has incorrect symbol;\n");
        else
            str = _str;
    }

    void set_distance_str_from_top_Y(const unsigned int& _distanceStrFromTopY)
    {
        distanceStrFromTopY = _distanceStrFromTopY;
    }

    void set_distance_buttons_from_sides_X(const unsigned int& _distanceButtonsFromSidesX)
    {
        distanceButtonsFromSidesX = _distanceButtonsFromSidesX;
    }

    void replace_symbols(const map <string, char>& _symbols)
    {
        replace_map_elements_from_another_map(symbols, _symbols);
    }

    void replace_colors(const map <string, unsigned int>& _colors)
    {
        buttons.replace_colors(_colors);

        replace_map_elements_from_another_map(colors, _colors);
    }
};


class WindowNotification : public Window
{
private:
    const int sizeOfWindowY = 4;

public:
    WindowNotification(const unsigned int& _coordinateX, const unsigned int& _coordinateY, const string& _str)
        : Window(_coordinateX, _coordinateY, _str) {}

    WindowNotification(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
        : Window(_coordinateX, _coordinateY) {}

    WindowNotification()
        : Window() {}


    void set_options(const unsigned int& _distanceStrFromTopY = 0, const unsigned int& _distanceButtonsFromSidesX = 1)
    {
        set_distance_str_from_top_Y(_distanceStrFromTopY);
        set_distance_buttons_from_sides_X(_distanceButtonsFromSidesX);
    }

    bool open()
    {
        size['X'] = 0;
        size['Y'] = distanceStrFromTopY + sizeOfWindowY;

        create();

        return buttons.check_button_click() == "Ok";
    }
};


class WindowInput : public Window
{
protected:
    const int sizeOfWindowY = 5;
    const int minSizeOfInputCell = 3;

    unsigned int distanceInputCellFromStrY = 1;
    unsigned int maxNumberOfSymbols = 100;

public:
    WindowInput(const unsigned int& _coordinateX, const unsigned int& _coordinateY, const string& _str)
        : Window(_coordinateX, _coordinateY, _str) {}

    WindowInput(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
        : Window(_coordinateX, _coordinateY) {}

    WindowInput()
        : Window() {}


    void set_distance_input_cell_from_str_Y(const unsigned int& _distanceInputCellFromStrY)
    {
        distanceInputCellFromStrY = _distanceInputCellFromStrY;
    }

    void set_max_number_of_symbol(const unsigned int& _maxNumberOfSymbols)
    {
        if (_maxNumberOfSymbols > 0)
            maxNumberOfSymbols = _maxNumberOfSymbols;
        else
            throw length_error("Max number of symbols in input cell cannot equal to zero;\n");
    }

    void set_options(const unsigned int& _distanceStrFromTopY = 0, const unsigned int& _distanceButtonsFromSidesX = 1,
                     const unsigned int& _distanceInputCellFromStrY = 1, const unsigned int& _maxNumberOfSymbols = 100)
    {
        set_distance_str_from_top_Y(_distanceStrFromTopY);
        set_distance_buttons_from_sides_X(_distanceButtonsFromSidesX);
        set_distance_input_cell_from_str_Y(_distanceInputCellFromStrY);
        set_max_number_of_symbol(_maxNumberOfSymbols);
    }
};


class WindowInputSingle : public WindowInput
{
public:
    WindowInputSingle(const unsigned int& _coordinateX, const unsigned int& _coordinateY, const string& _str)
        : WindowInput(_coordinateX, _coordinateY, _str) {}

    WindowInputSingle(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
        : WindowInput(_coordinateX, _coordinateY) {}

    WindowInputSingle()
        : WindowInput() {}


    string open()
    {
        size['X'] = 0;
        size['Y'] = distanceStrFromTopY + distanceInputCellFromStrY + sizeOfWindowY;

        create();

        if (size['X'] - 4 < minSizeOfInputCell)
            size['X'] = minSizeOfInputCell + 4;

        InputCell inputCell(size['X'] - 3, maxNumberOfSymbols);
        inputCell.set_color(colors["CheckKey"]);
        inputCell.check_input(coordinate['X'] + 2, coordinate['Y'] + distanceStrFromTopY + distanceInputCellFromStrY + 2);

        if (buttons.check_button_click() == "Ok")
            return inputCell.get_date();
        else
            return "";
    }
};


class WindowInputMultiply : public WindowInput
{
private:
    vector<string> strInputCellVector;


    void print_str_input_cell(const unsigned int& i)
    {
        unsigned int coordinateStrInputCellY = coordinate['Y'] + distanceStrFromTopY + distanceInputCellFromStrY + i * 2 + 2;

        set_color_text(colors["WindowBasic"]);
        set_position_console_cursor(coordinate['X'] + 2, coordinateStrInputCellY);
        cout << strInputCellVector[i];
    }

    void push_and_print_input_cell(vector<InputCell>& inputCellVector, const unsigned int& i, const unsigned int& maxLengthOfStr)
    {
        unsigned int coordinateInputCellY = coordinate['Y'] + distanceStrFromTopY + distanceInputCellFromStrY + i * 2 + 2;

        inputCellVector.push_back(InputCell(size['X'] - maxLengthOfStr - 4, maxNumberOfSymbols));
        inputCellVector[i].set_color(colors["CheckKey"]);
        inputCellVector[i].check_input(coordinate['X'] + maxLengthOfStr + 3, coordinateInputCellY, true);
    }

public:
    WindowInputMultiply(const unsigned int& _coordinateX, const unsigned int& _coordinateY, const string& _str)
        : WindowInput(_coordinateX, _coordinateY, _str) {}

    WindowInputMultiply(const unsigned int& _coordinateX, const unsigned int& _coordinateY)
        : WindowInput(_coordinateX, _coordinateY) {}

    WindowInputMultiply()
        : WindowInput() {}


    void set_str_input_cell_vector(const vector<string>& _strInputCellVector)
    {
        strInputCellVector = _strInputCellVector;
    }

    void push(const string& _str)
    {
        if (_str.empty())
            throw length_error("The str is empty;\n");
        else
            strInputCellVector.push_back(_str);
    }

    void pop()
    {
        if (!strInputCellVector.empty())
            strInputCellVector.pop_back();
    }

    unsigned int find_maximum_length_of_str_in_vector(const vector<string>& strInputCellVector)
    {
        unsigned int maxLengthOfStr = 0;

        for (const string& item : strInputCellVector)
            if ((unsigned int)item.size() > maxLengthOfStr)
                maxLengthOfStr = (unsigned int)item.size();

        return maxLengthOfStr;
    }

    void calculate_size()
    {
        size['X'] = find_maximum_length_of_str_in_vector(strInputCellVector) + minSizeOfInputCell + 4;
        size['Y'] = sizeOfWindowY + distanceStrFromTopY + distanceInputCellFromStrY + (unsigned int)strInputCellVector.size();
    }

    map<string, unsigned int> open()
    {
        if (strInputCellVector.empty())
            throw length_error("Vector of string of input cell is empty;\n");

        calculate_size();

        unsigned int maxLengthOfStr = find_maximum_length_of_str_in_vector(strInputCellVector);
        vector<InputCell> inputCellVector;
        map<string, unsigned int> result;

        create();

        for (int i = 0; i < strInputCellVector.size(); i++)
        {
            print_str_input_cell(i);
            push_and_print_input_cell(inputCellVector, i, maxLengthOfStr);

            if (!inputCellVector[i].empty())
                result[strInputCellVector[i]] = stoi(inputCellVector[i].get_date());
        }

        if (buttons.check_button_click() == "Ok")
            return result;
        else
            return {};
    }
};