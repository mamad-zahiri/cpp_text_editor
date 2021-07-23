#include <iostream>
#include <string>
#include <fstream>

#define CMD_help "help" // show all commands. each command tells user for its own inputs when called

#define PROMPT ">> "        // prompt when get command
#define CMD_get_text "show" // show TEXT
#define CMD_insert "insert" // insert user words in user pos

#define CMD_select "select" // select from user pos as many as user len
#define CMD_move "move"     // move a string in TEXT to user pos
#define CMD_copy "copy"     // store string from user pos as many as user len in CLIPBOARD
#define CMD_paste "paste"   // paste any thing from CLIPBOARD in user pos
#define CMD_erase "erase"   // erase from user pos as many as user len

#define CMD_find "find"       // find user string
#define CMD_replace "replace" // replace a string with user string

#define CMD_open "open" // open a file to edit
#define CMD_save "save" // save TEXT in a file
#define CMD_exit "exit" // close the editor

using namespace std;

extern string CMD;       // store given command
extern string TEXT;      // store the text that user works on
extern string CLIPBOARD; // store text on calling 'find, select, copy, move, moveline, copyline'
extern string FILE_NAME; // store a file name for save or open

void help();

int TEXT_pos(int = -1);           // get "pos" from user an checks for bad input
int TEXT_len(int = -1, int = -1); // get "len" according to "pos" from user an checks for bad input
string TEXT_text(string = "");    // get "text" from user and checks for bad input

void get_text();                    // print TEXT with some information
void read_cmd();                    // get command from user and run it
void insert(string = "", int = -1); // insert given "text" to TEXT in given "pos"

void select(int = -1, int = -1); // store "len" chars to CLIPBOARD from given "pos"
void move();                     // move "len" chars from given "pos" to given "new pos"
void copy();                     // "select()" and "paste()"
void paste(int = -1);            // paste CLIPBOARD in given "pos"
void erase(int = -1, int = -1);  // erase given "len" chars from given "pos"

void find(string = ""); // find and show the position of given "text"
void replace();         // replace "find(string)" with given "text"

void open();              // open a file to edit
void save();              // save TEXT in a file
void goodbye();           // print an exit message
void command_not_found(); // print a not found command message
