#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "text_editor.hpp"

using namespace std;

string CMD;
string FILE_NAME = "";
string TEXT[MAX_LINE_COUNT];
int LINE_COUNT = 1;
string CLIPBOARD;

int TEXT_line(int line, string msg)
{
    if (line < 0)
    {
        cout << msg;
        cin >> line;
        cin.ignore();
    }
    return line < 0             ? 0
           : line >= LINE_COUNT ? LINE_COUNT - 1
                                : line;
}

int TEXT_pos(int line, int pos, string msg)
{
    int l = TEXT[line].length();
    if (pos < 0)
    {
        cout << msg;
        cin >> pos;
        cin.ignore();
    }
    return pos < 0    ? 0
           : pos >= l ? l
                      : pos;
}

int TEXT_len(int line, int pos, int len, string msg)
{
    int l = TEXT[line].length();
    if (len < 0)
    {
        cout << msg;
        cin >> len;
        cin.ignore();
    }
    return len < 0           ? 0
           : (len + pos) > l ? l
                             : len;
}

string TEXT_text(string text, string msg)
{
    if (text == "")
    {
        cout << msg;
        getline(cin, text);
    }
    return text;
}

void show_text()
{
    int c, total_len = 0;
    cout << "\n-------------------------------------------------------------------\n";
    for (int line = 0; line < LINE_COUNT; line++)
    {
        cout << "|" << setw(2) << line << " | ";
        for (c = 0; c < TEXT[line].length(); c++)
            if (c > 0 && c % 59 == 0)
                cout << " |\n|     " << TEXT[line][c];
            else
                cout << TEXT[line][c];
        cout << setw((c < 60 ? 61 : 60) - c % 60) << "|" << endl;

        total_len += TEXT[line].length();
    }
    cout << "-------------------------------------------------------------------"
         << "\n| "
         << setw(5) << total_len << " chars "
         << setw(5) << LINE_COUNT << " lines "
         << setw(41) << " |"
         << "\n-------------------------------------------------------------------\n\n";
}

void read_cmd()
{
    cout << PROMPT;
    getline(cin, CMD);

    CMD == CMD_show_text ? show_text()
    : CMD == CMD_insert  ? insert()

    : CMD == CMD_select ? select()
    : CMD == CMD_move   ? move()
    : CMD == CMD_copy   ? copy()
    : CMD == CMD_paste  ? paste()
    : CMD == CMD_erase  ? erase()

    : CMD == CMD_clear ? clear()

    : CMD == CMD_find    ? find()
    : CMD == CMD_replace ? replace()

    : CMD == CMD_add_line     ? add_line()
    : CMD == CMD_move_line    ? move_line()
    : CMD == CMD_copy_line    ? copy_line()
    : CMD == CMD_clear_line   ? clear_line()
    : CMD == CMD_remove_line  ? remove_line()
    : CMD == CMD_remove_lines ? remove_lines()

    : CMD == CMD_open ? open()
    : CMD == CMD_save ? save()

    : CMD == CMD_help ? help()

    : CMD == CMD_exit ? goodbye()
                      : command_not_found();
}

void insert(string str, int line, int pos)
{
    str = TEXT_text(str, "text : ");
    line = TEXT_line(line, "to line : ");
    pos = TEXT_pos(line, pos, "at pos : ");
    TEXT[line].insert(pos, str);
}

void select(int line, int from, int len)
{
    CLIPBOARD = "";
    line = TEXT_line(line, "at line : ");
    from = TEXT_pos(line, from, "from pos : ");
    len = TEXT_len(line, from, len, "len : ");
    for (int i = from; i < (from + len > TEXT[line].length() ? TEXT[line].length() : from + len); i++)
        CLIPBOARD += TEXT[line][i];
}

void move()
{
    int from_line = TEXT_line(-1, "from line : "),
        from_pos = TEXT_pos(from_line, -1, "from pos : "),
        len = TEXT_len(from_line, from_pos, -1, "len : "),
        to_line = TEXT_line(-1, "to line : "),
        to_pos = TEXT_pos(to_line, -1, "at pos : ");
    select(from_line, from_pos, len);
    erase(from_line, from_pos, len);
    paste(to_line, (to_pos > from_line && from_line == to_line ? to_pos - len : to_pos));
}

void copy()
{
    select();
    paste();
}

void paste(int line, int pos)
{
    line = TEXT_line(line, "to line : ");
    pos = TEXT_pos(line, pos, "paste to : ");
    insert(CLIPBOARD, line, pos);
}

void erase(int line, int from, int len)
{
    line = TEXT_line(line, "at line : ");
    from = TEXT_pos(line, from, "erase from : ");
    len = TEXT_len(line, from, len, "len : ");
    TEXT[line].erase(from, len);
}

void clear()
{
    for (int line = 0; line < LINE_COUNT; line++)
        TEXT[line] = "";
    LINE_COUNT = 1;
}

void find(string str)
{
    CLIPBOARD = TEXT_text(str, "find what : ");

    for (int line = 0; line < LINE_COUNT; line++)
    {
        int pos = TEXT[line].find(CLIPBOARD),
            C_len = CLIPBOARD.length();
        if (pos >= 0)
        {
            cout << "\n   line " << line << endl;
            while (pos >= 0)
            {
                cout << setw(4) << pos << " - `";
                for (int i = pos; i < (pos + C_len + 5 <= TEXT[line].length() ? pos + C_len + 5 : TEXT[line].length()); i++)
                    cout << TEXT[line][i];
                cout << "`" << endl;

                pos = TEXT[line].find(CLIPBOARD, pos + 1);
            }
        }
    }
}

void replace()
{
    find();

    string new_text = TEXT_text("", "replace with : "),
           replace_all = TEXT_text("", "replace all : [y/n] ");

    if (replace_all == "Y" || replace_all == "y")
    {
        for (int line = 0; line < LINE_COUNT; line++)
        {
            int pos = TEXT[line].find(CLIPBOARD);
            while (pos >= 0)
            {
                TEXT[line].replace(pos, CLIPBOARD.length(), new_text);
                pos = TEXT[line].find(CLIPBOARD, pos + 1);
            }
        }
    }
    else
    {
        int line = TEXT_line(-1, "which line : "),
            pos = TEXT_pos(line, -1, "on pos : ");
        TEXT[line].replace(pos, CLIPBOARD.length(), new_text);
    }
}

void add_line(int at_line, string text)
{
    if (at_line < 0 || at_line > LINE_COUNT)
    {
        cout << "at line : ";
        cin >> at_line;
        cin.ignore();
        at_line = at_line < 0            ? 0
                  : at_line > LINE_COUNT ? LINE_COUNT
                                         : at_line;
    }
    text = TEXT_text(text, "text : ");

    for (int line = LINE_COUNT; line >= at_line; line--)
        TEXT[line] = TEXT[line - 1];

    TEXT[at_line] = text;
    ++LINE_COUNT;
}

void move_line(int from, int to)
{
    from = TEXT_line(from, "from : ");
    to = TEXT_line(to, "to : ");

    string tmp = TEXT[from];

    remove_line(from);
    add_line(to > from ? to - 1 : to, tmp);
}

void copy_line(int from, int to)
{
    add_line(to, TEXT[TEXT_line(from, "from : ")]);
    ++LINE_COUNT;
}

void clear_line(int line)
{
    line = TEXT_line(line, "which line : ");
    TEXT[line] = "";
}

void remove_lines(int from, int len)
{
    from = TEXT_line(from, "at : ");
    // checks for remove_line()
    len = len != 1 ? TEXT_line(-1, "to : ") - from + 1 : 1;

    if (len > 0)
    {
        if (from + len >= LINE_COUNT)
            for (; from < LINE_COUNT;)
                TEXT[from++] = "";
        else
            // shift next lines backward
            for (int l = from + len; l < LINE_COUNT; l++, from++)
                TEXT[from] = TEXT[l];

        LINE_COUNT -= len;
    }
}

void remove_line(int line)
{
    remove_lines(line, 1);
}

void goodbye()
{
    cout << "GoodBye...\n";
}

void command_not_found()
{
    cout << "command not found!\n";
}

void open()
{
    string name = TEXT_text("", "enter a file name to open : ");
    ifstream file;
    file.open(name);
    if (file)
        for (int line = 0; line < MAX_LINE_COUNT && getline(file, TEXT[line++]); LINE_COUNT++)
            ;
    else
        cout << "file \"" << name << "\" not found\n";
    file.close();
}

void save()
{
    string name = TEXT_text("", "enter a file name to save : ");
    ofstream file;
    file.open(name);
    if (file.is_open())
        for (int line = 0; line < LINE_COUNT; line++)
            if (line < LINE_COUNT - 1)
                file << TEXT[line] << "\n";
            else
                file << TEXT[line];
    file.close();
}

void help()
{
    cout
        << setw(12) << "open"
        << "    open the given \"file\" and store it into TEXT"
        << "\n"
        << setw(12) << "save"
        << "    save TEXT into given \"file\""
        << "\n"
        << setw(12) << "show"
        << "    show TEXT"
        << "\n"
        << setw(12) << "insert"
        << "    insert user words in user pos"
        << "\n"
        << setw(12) << "select"
        << "    select from user pos as many as user len"
        << "\n"
        << setw(12) << "move"
        << "    move a string in TEXT to user pos"
        << "\n"
        << setw(12) << "copy"
        << "    store string from user pos as many as user len in CLIPBOARD"
        << "\n"
        << setw(12) << "paste"
        << "    paste any thing from CLIPBOARD in user pos"
        << "\n"
        << setw(12) << "erase"
        << "    erase from user pos as many as user len"
        << "\n"
        << setw(12) << "clear"
        << "    truncate TEXT"
        << "\n"
        << setw(12) << "find"
        << "    find user string"
        << "\n"
        << setw(12) << "replace"
        << "    replace a string with user string"
        << "\n"
        << setw(12) << "addline"
        << "    add new line ad given \"pos\""
        << "\n"
        << setw(12) << "moveline"
        << "    move a line to given \"pos\""
        << "\n"
        << setw(12) << "copyline"
        << "    copy given \"line\" a paste into given \"pos\""
        << "\n"
        << setw(12) << "clearline"
        << "    truncate given \"line\""
        << "\n"
        << setw(12) << "rmlines"
        << "    remove a bunch of \"lines\" from given \"pos\""
        << "\n"
        << setw(12) << "rmline"
        << "    remove given \"line\""
        << "\n"
        << setw(12) << "exit"
        << "    close the editor\n";
}
