#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "text_editor.hpp"

using namespace std;

string TEXT;
string CMD;
string CLIPBOARD;
string FILE_NAME;

int TEXT_pos(int pos)
{
    int l = TEXT.length();
    if (pos < 0)
    {
        cout << "pos : ";
        cin >> pos;
        cin.ignore();
    }
    return pos < 0    ? 0
           : pos == 0 ? 0
           : pos >= l ? l
                      : pos;
}

int TEXT_len(int pos, int len)
{
    int l = TEXT.length();
    if (len < 0)
    {
        cout << "len : ";
        cin >> len;
        cin.ignore();
    }
    return len < 0           ? 0
           : (len + pos) > l ? l
                             : len;
}

string TEXT_text(string text)
{
    if (text == "")
    {
        cout << "text : ";
        getline(cin, text);
    }
    return text;
}

void get_text()
{
    cout << "\n============================== START ==============================\n"
         << TEXT /*<< (TEXT[-1] == '\n' ? "" : "%\n")*/
         << "\n==============================  END  =============================="
         << "\n=== " << setw(5) << TEXT.length() << " chars " << setw(53) << " ===\n\n";
}

void read_cmd()
{
    cout << PROMPT;
    getline(cin, CMD);

    CMD == CMD_get_text  ? get_text()
    : CMD == CMD_insert  ? insert()
    : CMD == CMD_select  ? select()
    : CMD == CMD_move    ? move()
    : CMD == CMD_copy    ? copy()
    : CMD == CMD_paste   ? paste()
    : CMD == CMD_erase   ? erase()
    : CMD == CMD_find    ? find()
    : CMD == CMD_replace ? replace()
    : CMD == CMD_open    ? open()
    : CMD == CMD_save    ? save()
    : CMD == CMD_help    ? help()
    : CMD == CMD_exit    ? goodbye()
                         : command_not_found();
}

void insert(string str, int pos)
{
    str = TEXT_text(str);
    pos = TEXT_pos(pos);
    TEXT.insert(pos, str);
}

void select(int from, int len)
{
    CLIPBOARD = "";
    from = TEXT_pos(from);
    len = TEXT_len(from, len);
    for (int i = from; i < (from + len > TEXT.length() ? TEXT.length() : from + len); i++)
        CLIPBOARD += TEXT[i];
}

void move()
{
    int from = TEXT_pos();
    int len = TEXT_len(from);
    int pos = TEXT_pos();
    select(from, len);
    erase(from, len);
    paste((pos < from ? pos : pos - len));
}

void copy()
{
    select();
    paste();
}

void paste(int pos)
{
    pos = TEXT_pos(pos);
    insert(CLIPBOARD, pos);
}

void erase(int from, int len)
{
    from = TEXT_pos(from);
    len = TEXT_len(from, len);
    TEXT.erase(from, len);
}

void find(string str)
{
    CLIPBOARD = TEXT_text(str);
    int counter = 1,
        pos = TEXT.find(CLIPBOARD);

    while (pos >= 0)
    {
        cout << setw(4) << counter << " -> " << setw(4) << pos << " - `";
        for (int i = pos - 4 < 0 ? 0 : (pos - 4); i < (pos + 5 > TEXT.length() ? TEXT.length() : pos + 5); i++)
            cout << TEXT[i];
        cout << "`\n";

        pos = TEXT.find(CLIPBOARD, pos + 1);
        counter++;
    }
}

void replace()
{
    find();

    cout << "replace with\n";
    string new_str = TEXT_text();

    cout << "replace all : [y/n]\n";
    string replace_all = TEXT_text();

    if (replace_all == "Y" || replace_all == "y")
    {
        int pos = TEXT.find(CLIPBOARD);
        while (pos >= 0)
        {
            TEXT.replace(pos, CLIPBOARD.length(), new_str);
            pos = TEXT.find(CLIPBOARD, pos + 1);
        }
    }
    else
        TEXT.replace(TEXT_pos(), CLIPBOARD.length(), new_str);
}

void open()
{
    cout << "file name\n";
    FILE_NAME = TEXT_text();
    ifstream file;
    file.open(FILE_NAME);
    if (file)
        TEXT.assign((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
    else
        cout << "file not found\n";
    file.close();
}

void save()
{
    cout << "file name\n";
    FILE_NAME = TEXT_text();
    ofstream file(FILE_NAME);
    file << TEXT;
    file.close();
}

void goodbye()
{
    cout << "GoodBye...\n";
}

void command_not_found()
{
    cout << "command not found!\n";
}

void help()
{
    cout
        << setw(15) << "help" << setw(4) << ""
        << "show all commands. each command tells user for its own inputs when called\n"
        << setw(15) << "show" << setw(4) << ""
        << "show TEXT\n"
        << setw(15) << "insert" << setw(4) << ""
        << "insert user words in user pos\n"
        << setw(15) << "select" << setw(4) << ""
        << "select from user pos as many as user len\n"
        << setw(15) << "move" << setw(4) << ""
        << "move a string in TEXT to user pos\n"
        << setw(15) << "copy" << setw(4) << ""
        << "store string from user pos as many as user len in CLIPBOARD\n"
        << setw(15) << "paste" << setw(4) << ""
        << "paste any thing from CLIPBOARD in user pos\n"
        << setw(15) << "erase" << setw(4) << ""
        << "erase from user pos as many as user len\n"
        << setw(15) << "find" << setw(4) << ""
        << "find user string\n"
        << setw(15) << "replace" << setw(4) << ""
        << "replace a string with user string\n"
        << setw(15) << "open" << setw(4) << ""
        << "open a file to edit\n"
        << setw(15) << "save" << setw(4) << ""
        << "save TEXT in a file\n"
        << setw(15) << "exit" << setw(4) << ""
        << "close the editor\n";
}