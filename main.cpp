#include <iostream>
#include <string.h>
using namespace std;

#include "Table.h"

#define STARTING_COMMAND_LENGTH 10
#define DEFAULT_RESIZE_VALUE 10
#define MAX_FUNCTION_LENGTH 15
#define PRECISION 2
#define CELL_SIZE 1000

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
//	Table t;
//
//	fstream in;
//	in.open("table1.csv", fstream::in);
//	in.seekg(0, fstream::beg);
//	t.load(in);
//	//t.setCell(0, 1, 1, 0, 5.989);
//	t.print();
//
	Table table;
	bool opened = false;
	char* filename = nullptr;

     while(true)
     {
		 char* command = new char[STARTING_COMMAND_LENGTH + 1];
		 command[0] = '\0';
		 char symbol;

		 unsigned int lengthBoundary = STARTING_COMMAND_LENGTH;
		 unsigned int commandLength = 0;

		 do
		 {
			 cin.get(symbol);
			 // cout << symbol;

			 if (commandLength == lengthBoundary)
			 {
				 lengthBoundary += DEFAULT_RESIZE_VALUE;

				 char* temp = new char[lengthBoundary + 1];
				 strcpy(temp, command);

				 delete[] command;
				 command = temp;
			 }
			 // strcat(command, &symbol);
			 command[commandLength] = symbol;

			 // cout << "2 " << command << endl;
			 commandLength++;
			 command[commandLength] = '\0';


		 } while (symbol != '\n');

		 command[commandLength - 1] = '\0';
		 // cout << "1 " << command << endl;

		 // extracting the first word (the function)
		 char currentCommand[MAX_FUNCTION_LENGTH];

		 copyFirtCommand(currentCommand, command);

		 removeFirstCommand(command, currentCommand);

		 // cout << currentCommand << endl;        
		 // cout << command << endl;

		 // check the functionality
		 if (strcmp("help", currentCommand) == 0)
		 {
			 cout << "Help" << endl;
		 }
		 else if (strcmp("exit", currentCommand) == 0)
		 {
			 cout << "Sorry to see you go :(" << endl;
			 return 0;
		 }
		 else if (strcmp("open", currentCommand) == 0)
		 {
			 char* name = new char[strlen(command) + 1];
			 copyFirtCommand(name, command);

			 if (filename != nullptr)
				 delete[] filename;
			 filename = new char[strlen(name) + 1];
			 strcpy(filename, name);

			 fstream in;
			 in.open(name, fstream::in);
			 in.seekg(0, fstream::beg);
			 table.load(in);

			 cout << "Loaded " << name << endl;
			 opened = true;
			 delete[] name;
			 in.close();
		 }
		 else if (strcmp("close", currentCommand) == 0)
		 {
			 if (!opened)
				 cout << "Open a file first" << endl;
			 else
			 {
				 opened = false;
				 Table table2;
				 table = table2;
				 cout << "Closed the file" << endl;
			 }
		 }
		 else if (strcmp("save", currentCommand) == 0)
		 {
			 if (!opened)
				 cout << "Open a file first" << endl;
			 else
			 {
				 fstream out;
				 if (filename == nullptr)
				 {
					 out.open("hotel1.data", fstream::out | fstream::trunc);
					 filename = new char[strlen("hotel1.data") + 1];
					 strcpy(filename, "hotel1.data");
					 table.save(out);
				 }
				 else
				 {
					 out.open(filename, fstream::out | fstream::trunc);
					 table.save(out);
				 }
				 cout << "Saved " << filename << endl;
				 out.close();
			 }
		 }
		 else if (strcmp("saveas", currentCommand) == 0)
		 {
			 if (!opened)
				 cout << "Open a file first" << endl;
			 else
			 {
				 char* name = new char[strlen(command) + 1];
				 copyFirtCommand(name, command);

				 fstream out;
				 out.open(name, fstream::out | fstream::trunc);
				 table.save(out);

				 cout << "Saving as " << name << endl;
				 delete[] name;
				 out.close();
			 }
		 }
		 else if (strcmp("edit", currentCommand) == 0)
		 {
			 if (!opened)
				 cout << "Open a file first" << endl;
			 else
			 {
				 char* r = new char[strlen(command) + 1];
				 copyFirtCommand(r, command);
				 removeFirstCommand(command, r);

				 char* c = new char[strlen(command) + 1];
				 copyFirtCommand(c, command);
				 removeFirstCommand(command, c);

				 int len = strlen(command);

				 bool doubleFlag = true;
				 bool point = false;
				 bool formulaFlag = true;
				 bool intFlag = true;

				 // check if it's a double
				 for (int i = 0; i < len; i++)
				 {
					 if (command[i] == '.')
					 {
						 if (!point)
							 point = true;
						 else
						 {
							 doubleFlag = false;
							 break;
						 }
					 }
					 else if (command[i] > '9' || command[i] < '0')
					 {
						 doubleFlag = false;
						 break;
					 }
				 }

				 // check if it's int
				 for (int i = 0; i < len; i++)
				 {
					 if (command[i] > '9' || command[i] < '0')
					 {
						 intFlag = false;
						 break;
					 }
				 }

				 if (command[0] != '=')
					 formulaFlag = false;

				 if (len == 0) {}// handle empty cells
				 else if (intFlag)
					 table.setCell(atoi(r), atoi(c), 0, atoi(command));
				 else if (doubleFlag)
					 table.setCell(atoi(r), atoi(c), 1, 0, round(atof(command) * pow(10.0, PRECISION)) / pow(10.0, PRECISION));
				 else if (formulaFlag)
				 {
					 char dump1[CELL_SIZE];
					 char dump2[CELL_SIZE];
					 for (int q = 1, endOfLHS = 1; q < len; q++, endOfLHS++)
					 {
						 if (command[q] == '+' || command[q] == '-' || command[q] == '/' || command[q] == '*' || command[q] == '^')
						 {
							 char* newLHS = strncpy(dump1, command + 1, endOfLHS - 1);
							 newLHS[endOfLHS - 1] = '\0';
							 char* newRHS = strncpy(dump2, command + endOfLHS + 1, len - endOfLHS - 1);
							 newRHS[len - endOfLHS - 1] = '\0';
							 table.setCell(atoi(r), atoi(c), 3, 0, 0, "", Formula(newLHS, newRHS, command[q]));
							 table.evaluate(Formula(newLHS, newRHS, command[q]));
							 break;
						 }
						 else if (endOfLHS == len - 2)
						 {
							 std::cout << "Wrong formula" << std::endl;
						 }
					 }
				 }
				 else
					 table.setCell(atoi(r), atoi(c), 2, 0, 0, command);
			 }
		 }
		 else if (strcmp("print", currentCommand) == 0)
		 {
			 if (!opened)
				 cout << "Open a file first" << endl;
			 else
			 {
				 table.print();
			 }
		 }
		 else
		 {
			 cout << "Command not recognised, type \'help\' for a guide." << endl;
		 }
     }

    /*Table t;
    Cell cell(0, 0, 1);
    cell.setDoubleValue(1.9885);
    cell.print();

     t.setCell(0, 0, 0, 5);
     t.setCell(1, 0, 0, 177);
     t.setCell(1, 2, 2, 0, 0, "abcd");
     t.print();*/

	//Table t;
 //    t.setCell(3, 1, 0, 66666);
 //    t.print();
 //    t.setCell(0, 4, 2, 0, 0, "66666");
 //    t.print();
 //    t.setCell(10, 10, 2, 0, 0, "bobby is weird");
 //    t.setCell(11, 11, 0, 42, 0, "bobby is weird");
 //    t.print();


 //   fstream in;
 //   in.open("test1.csv", fstream::in);
 //   in.seekg(0, fstream::beg);
 //   t.load(in);
 //   t.setCell(0, 1, 1, 0, 5.989);
 //   t.print();

 //   Formula f("3", "566", '*');
 //   t.setCell(0, 1, 3, 0, 0, "", f);
 //   t.print();

 //   fstream out;
 //   out.open("test2.csv", fstream::out | fstream::trunc);
 //   t.save(out);
 //   out.close();

 //   Table t2;
 //   fstream in2;
 //   in2.open("test2.csv", fstream::in);
 //   in2.seekg(0, fstream::beg);
 //   t2.load(in2);
 //   //t.setCell(0, 1, 1, 0, 5.989);
 //   t2.print();
}