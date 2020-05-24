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

    std::cout << 1 << std::endl;
    Table t;
    Cell cell(0, 0, 1);
    cell.setDoubleValue(1.9885);
    cell.print();

    // t.setCell(0, 0, 0, 5);
    // t.setCell(1, 0, 0, 177);
    // t.setCell(1, 2, 2, 0, 0, "abcd");
    // t.print();

    // t.setCell(3, 1, 0, 66666);
    // t.print();
    // t.setCell(0, 4, 2, 0, 0, "66666");
    // t.print();
    // t.setCell(10, 10, 2, 0, 0, "bobby is weird");
    // t.setCell(11, 11, 0, 42, 0, "bobby is weird");
    // t.print();

    // fstream out;
    // out.open("test1.csv", fstream::out | fstream::trunc);
    // t.save(out);

    fstream in;
    in.open("test1.csv", fstream::in);
    in.seekg(0, fstream::beg);
    std::cout << 66 << std::endl;
    t.load(in);
    std::cout << 67 << std::endl;
    t.setCell(0, 1, 1, 0, 5.989);
    std::cout << 68 << std::endl;
    t.print();
    std::cout << 69 << std::endl;

    Formula f("1", "2", '+');
    std::cout << 70 << std::endl;
    t.setCell(0, 1, 3, 0, 0, "", f);
    std::cout << 71 << std::endl;
    t.print();
}