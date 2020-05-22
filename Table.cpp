#include "Table.h"
#include <cmath>

int numlen(int a)
{
    return trunc(log10(a)) + 1;
}

int numlen(double a)
{
    return numlen((int) a) + PRECISION;
}

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

void Table::setCell(int row, int col, int type, int intVal, double doubleVal, const char* stringVal)
{
    if (row >= this->nRows)
    {
        Cell** table2 = new Cell*[row+1];
        for (int i = 0; i <= row; i++)
        {
            if(i < this->nRows) 
                table2[i] = this->table[i];
            else
                table2[i] = new Cell[nCols];
        }

        delete [] this->table;
        this->table = table2;
        this->nRows = row+1;
    }
    else if (col >= this->nCols)
    {
        Cell** table2 = new Cell*[nRows];

        for (int i = 0; i < nRows; i++)
            table2[i] = new Cell[col+1];

        for (int i = 0; i < nRows; i++)
            for (int j = 0; j <= col; j++)
                if (j < this->nCols)
                    table2[i][j] = this->table[i][j];            
        

        delete [] this->table;
        this->table = table2;
        this->nCols = col+1;
    }
    
    
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
    
    int len = 0;
    for (int i = 0; i < nRows; i++)
        for (int j = 0; j < nCols; j++)
        {
            len = 0;
            switch (this->table[i][j].getType())
            {
            case 0:
                len = numlen(this->table[i][j].getIntValue());
                if(len > paddings[j])
                    paddings[j] = len;
                break;
            case 1:
                len = numlen(this->table[i][j].getDoubleValue());
                if(len > paddings[j])
                    paddings[j] = len;
                break;
            case 2:
                len = strlen(this->table[i][j].getStringValue());
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

    for (int i = 0; i < this->nRows; i++)
    {
        std::cout << '|';
        for (int j = 0; j < this->nCols; j++)
        {
            switch (table[i][j].getType())
            {
            case 0:
                std::cout << std::left << std::setw(paddings[j]) << table[i][j].getIntValue();
                break;
            case 1:
                std::cout << std::left << std::setw(paddings[j]) << std::setprecision(PRECISION) << table[i][j].getDoubleValue();
                break;
            case 2:
                std::cout << std::left << std::setw(paddings[j]) << table[i][j].getStringValue();
                break;
            // case 3:
            //     std::cout << std::left << std::setw(paddings[j]) << table[i][j].getIntValue();
            //     break;
            default:
                std::cout << std::left << std::setw(paddings[j]) << "";
                break;
            }
            std::cout <<'|';
        }
        std::cout << std::endl; 
    }
    std::cout << std::endl; 
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
    if(!in.good())
        return 0;

    char line[1000];
    char temp[1000];

    // in.getline(line, 1000);
    int j = 0;
    int i = 0;
    int p = 0;
    int prev = 0;

    bool intFlag = true;
    bool doubleFlag = true;
    bool formulaFlag = true;
    
    while(in.getline(line, 1000))
    {
        do
        {
            // std::cout << line[p] << std::endl;
            if (line[p] == ',' || line[p] == '\0')
            {
                // std::cout << p << std::endl;
                strncpy(temp, line+prev, p-prev);
                temp[p-prev] = '\0';
                std::cout << "Temp: " << temp << std::endl;
                if (numlen(atoi(temp)) == strlen(temp))
                {
                    // std::cout << atoi(strncpy(temp, line+prev, p-prev)) << std::endl;
                    setCell(i, j, 0, atoi(temp));
                    prev = p+1;
                }
                else if (numlen(atof(temp)) == strlen(temp))
                {
                    setCell(i, j, 1, 0, atof(temp));
                    prev = p+1;
                }
                // ADD FORMULA SUPPORT
                else
                {
                    setCell(i, j, 2, 0, 0, temp);
                    prev = p+1;
                }
                
                j++;
            }
            
        }while(line[p++] != '\0');
        i++;
        j = 0;
        prev = 0;
        p = 0;
    }

    return 1;
}
bool Table::save(std::fstream& out)
{
    if(!out.good())
        return 0;

    for (int i = 0; i < this->nRows; i++)
    {
        for (int j = 0; j < this->nCols; j++)
        {
            switch (this->table[i][j].getType())
            {
            case 0:
                out << this->table[i][j].getIntValue();
                if (j < this->nCols - 1)
                    out << ",";
                else
                    out << "\n";
                break;

                case 1:
                out << std::setprecision(PRECISION) << this->table[i][j].getDoubleValue();
                if (j < this->nCols - 1)
                    out << ",";
                else
                    out << "\n";
                break;

                case 2:
                out << this->table[i][j].getStringValue();
                if (j < this->nCols - 1)
                    out << ",";
                else
                    out << "\n";
                break;
                // case 3:
                // out << this->table[i][j].getIntValue();
                // if (j < this->nCols - 1)
                //     out << ",";
                // else
                //     out << "\n";
                // break;
            
            default:
                if (j < this->nCols - 1)
                    out << ",";
                else
                    out << "\n";
                break;
            }
        }
    }
    return 1;
}