#include <iostream>
#include <string>
#include <fstream>
#include "text_editor.hpp"

using namespace std;

int main()
{
    while (CMD != CMD_exit)
        read_cmd();
}
