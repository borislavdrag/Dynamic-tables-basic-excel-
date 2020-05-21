#include "Table.h"

Table::Table(int nRows, int nCols)
{
    this->nRows = nRows;
    this->nCols = nCols;

    this->table = new Cell*[nRows];
    for (int i = 0; i < nRows; i++)
        table[i] = new Cell[nCols];
}

Table::~Table()
{
    for (int i = 0; i < this->nRows; i++)
        delete [] this->table[i];
    delete [] this->table;
}

Table::Table(const Table& other)
{
    copy(other);
}

Table& Table::operator=(const Table& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

//Getters

const int Table::getNRows() const
{
    return this->nRows;
}
const int Table::getNCols() const
{
    return this->nCols;
}
const Cell& Table::getCell(int row, int col) const
{
    return this->table[row][col];
}

//Setter

void Table::setCell(int row, int col, int type, int intVal, double doubleVal, char* stringVal)
{
    switch (type)
    {
    case 0:
        table[row][col].setIntValue(intVal); 
        break;
    case 1:
        table[row][col].setDoubleValue(doubleVal); 
        break;
    case 2:
        table[row][col].setStringValue(stringVal); 
        break;
    // case 3:
    //     table[row][col].setFormulaValue(); 
    //     break;
    default:
        std::cout << "Invalid type" << std::endl;
        break;
    }
}
//Other functions

void Table::print()
{
    int* paddings = new int[nCols];
    for (int i = 0; i < nCols; i++)
        paddings[i] = 0;
    
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
        {
            switch (this->table[i][j].getType())
            {
            case 0:
                int len = strlen(itoa(this->table[i][j].getIntValue()));
                if(len > paddings[j])
                    paddings[j] = len;
                break;
            case 1:
                int len = strlen(itoa(this->table[i][j].getDoubleValue()));
                if(len > paddings[j])
                    paddings[j] = len;
                break;
            case 2:
                int len = strlen(this->table[i][j].getStringValue());
                if(len > paddings[j])
                    paddings[j] = len;
                break;
            // case 3:
            //     int len = strlen(itoa(this->table[i][j].getIntValue());
            //     if(len > paddings[j])
            //         paddings[j] = len;
            //     break;
           
            default:
                break;
            }
        }
        
    

    delete [] paddings;
}

void Table::free()
{
    for (int i = 0; i < this->nRows; i++)
        delete [] this->table[i];
    delete [] this->table;

    this->nRows = 0;
    this->nCols = 0;
}

void Table::copy(const Table& other)
{
    this->nRows = other.nRows;
    this->nCols = other.nCols;

    this->table = new Cell*[nRows];
    for (int i = 0; i < nRows; i++)
        table[i] = new Cell[nCols];

    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
            this->table[i][j] = other.table[i][j];
}

bool Table::load(std::fstream& in)
{

}

bool Table::save(std::fstream& out)
{

}