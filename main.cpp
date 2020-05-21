#include <iostream>
#include <string.h>
using namespace std;

#include "Table.h"

#define SIZE 1024

void copyFirtCommand(char* target, char* source)
{
    int src_len = strlen(source);
    for (int i = 0; i <= src_len; i++)
        {
            if(source[i] == ' ' || source[i] == '\0')
            {
                strncpy(target, source, i);
                target[i] = '\0';
                break;
            }
        }
}

void removeFirstCommand(char* source, char* currentCommand)
{
    if (strlen(source) == 0)
        return;
    int trg_len = strlen(source) - strlen(currentCommand);
    char* command2 = new char[trg_len+1];
    for (int i = 0; i <= trg_len; i++)
        command2[i] = source[i+strlen(currentCommand)+1];

    command2[trg_len] = '\0';

    strcpy(source, command2);
    delete [] command2;
}

void removeWhitespace(char* source)
{

}


int main()
{
    // while(true)
    // {
    //     char command[SIZE];
    //     cin.getline(command, SIZE);

    //     char command1[1000];
    //     char command2[1000];

    //     copyFirtCommand(command1, command);
    //     removeFirstCommand(command, command1);
    //     copyFirtCommand(command2, command);
    //     cout << command1 << endl;
    //     cout << command2 << endl;
    // }

    Cell cell(0, 0, 2);
    cell.setStringValue("abcdef");
    cell.print();
}