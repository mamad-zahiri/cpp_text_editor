#include <iostream>
#include <string>
#include <fstream>

using namespace std; // are you really read this comment?! :))

#define CMD_help "help" // show all commands

#define PROMPT ">> " // prompt when get command

extern string FILE_NAME; // store file for open or save
#define CMD_open "open"  // open the given "file" and store it into TEXT
#define CMD_save "save"  // save TEXT into given "file"

#define CMD_show_text "show" // show TEXT
#define CMD_insert "insert"  // insert user words in user pos

#define CMD_select "select" // select from user pos as many as user len
#define CMD_move "move"     // move a string in TEXT to user pos
#define CMD_copy "copy"     // store string from user pos as many as user len in CLIPBOARD
#define CMD_paste "paste"   // paste any thing from CLIPBOARD in user pos
#define CMD_erase "erase"   // erase from user pos as many as user len
#define CMD_clear "clear"   // truncate TEXT

#define CMD_find "find"       // find user string
#define CMD_replace "replace" // replace a string with user string

#define CMD_add_line "addline"     // add new line ad given "pos"
#define CMD_move_line "moveline"   // move a line to given "pos"
#define CMD_copy_line "copyline"   // copy given "line" a paste into given "pos"
#define CMD_clear_line "clearline" // truncate given "line"
#define CMD_remove_lines "rmlines" // remove a bunch of "lines" from given "pos"
#define CMD_remove_line "rmline"   // remove given "line"

#define CMD_exit "exit" // close the editor

extern string CMD; // store given command

#define MAX_LINE_COUNT 100          // maximum lines count
extern string TEXT[MAX_LINE_COUNT]; // store the text that user works on
extern int LINE_COUNT;              // biggest used line

extern string CLIPBOARD; // store text on calling 'find, select, copy, move'

void help(); // show all commands

void open(); // open the given "file" and store it into TEXT
void save(); // save TEXT into given "file"

// check the user inputs for "line", "pos", "len", "text"
int TEXT_line(int = -1, string = " : ");                    // get "line" form user and checks for bad input
int TEXT_pos(int = -1, int = -1, string = " : ");           // get "pos" according to "line" from user and checks for bad input
int TEXT_len(int = -1, int = -1, int = -1, string = " : "); // get "len" according to "pos" and "line" from user and checks for bad input
string TEXT_text(string = "", string = " : ");              // get "text" from user and checks for bad input

void show_text(); // print TEXT with some information
void read_cmd();  // get command from user and run it

void insert(string = "", int = -1, int = -1); // insert given "text" to TEXT in given "pos"

void select(int = -1, int = -1, int = -1); // store "len" chars to CLIPBOARD from given "pos"
void move();                               // move "len" chars from given "pos" to given "new pos"
void copy();                               // "select()" and "paste()"
void paste(int = -1, int = -1);            // paste CLIPBOARD in given "pos"
void erase(int = -1, int = -1, int = -1);  // erase given "len" chars from given "pos"
void clear();                              // truncate all TEXT

void find(string = ""); // find and show the position of given "text"
void replace();         // replace "find(string)" with given "text"

void add_line(int = -1, string = "");  // add new line at given "line"
void move_line(int = -1, int = -1);    // move given "line" to given "pos"
void copy_line(int = -1, int = -1);    // copy and paste a "line" to "pos"
void clear_line(int = -1);             // truncate given "line"
void remove_lines(int = -1, int = -1); // remove lines from "pos" to "pos"
void remove_line(int = -1);            // it is just "remove_lines()" with given "pos" and len 1

void goodbye();           // print an exit message
void command_not_found(); // print a not found command message
