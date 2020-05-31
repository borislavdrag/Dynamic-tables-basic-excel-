#include "Table.h"
#include <cmath>

// Helper functions

int numlen(int a)
{
    if (a == 0)
        return 1;
    return trunc(log10(a)) + 1;
}

int numlen(double a)
{
    return numlen((int) a) + PRECISION + 1;
}

//Clears space at beginning and end of line and also around commas
void clearInputWhitespace(char* line)
{
    int len = strlen(line);
    for (int i = 0, p = 0; i < len; i++, p++)
    {
        if(line[i] == ' ')
        {
            p--;
        }
    }
}

// Constructors & such

Table::Table(int nRows, int nCols)
{
    this->nRows = nRows;
    this->nCols = nCols;

    this->table = new Cell*[nRows];
    for (int i = 0; i < nRows; i++)
        table[i] = new Cell[nCols];

    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            table[i][j].setRow(i);
            table[i][j].setCol(j);
        }
    };
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

void Table::setCell(int row, int col, int type, int intVal, double doubleVal, const char* stringVal, const Formula& formulaVal)
{   
    if (row >= this->nRows || col >= this->nCols)
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
        if (col >= this->nCols)
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
    case 3:
        table[row][col].setFormulaValue(formulaVal); 
        break;
    default:
        std::cout << "Invalid type" << std::endl;
        break;
    }
}

//Evaluators

const double Table::evaluate(const char* side) const
{
    int len = strlen(side);

    bool doubleFlag = true;
    bool point = false;
    bool formulaFlag = true;
    bool intFlag = true;
    bool cellFlag = false;


    if (side[0] == 'R' && side[2] == 'C' && strlen(side) == 4 && side[1] >= '0'
        && side[1] <= '9' && side[3] >= '0' && side[3] <= '9' && (side[1] - '0') < nRows && (side[3]-'0') < nCols)
        cellFlag = true;

    // check if it's a double
    for (int i = 0; i < len; i++)
    {   
        if (side[i] == '.')
        {
            if(!point)
                point = true;
            else
            {
                    doubleFlag = false;
                    break;
            }   
        }
        else if(side[i] > '9' || side[i] < '0')
        {
            doubleFlag = false;
            break;
        }
    }

    // check if it's int
    for (int i = 0; i < len; i++)
    {
        if (side[i] > '9' || side[i] < '0')
        {
            intFlag = false;
            break;
        }
    }
    
    if (len == 0) // handle empty cells
        return 0;
    else if (cellFlag)
    {
        Cell c = table[side[1] - '0'][side[3] - '0'];

        switch (c.getType())
        {
        case 0:
             return c.getIntValue();
        case 1:
            return c.getDoubleValue();
        case 2:
            return 0;
        case 3:
            return evaluate(c.getFormulaValue());
        default:
            return 0;
        }
        
    }
    else if (intFlag)
        return atoi(side);
    else if (doubleFlag)
        return std::round(atof(side)*std::pow(10.0, PRECISION))/std::pow(10.0, PRECISION);
    else
        return 0;
            
}

const double Table::evaluate(const Formula& f) const
{
    switch (f.getOperation())
    {
    case '+':
        return (evaluate(f.getLHS()) + evaluate(f.getRHS()));
        break;
    case '-':
        return (evaluate(f.getLHS()) - evaluate(f.getRHS()));
        break;
    case '*':
        return (evaluate(f.getLHS()) * evaluate(f.getRHS()));
        break;
    case '/':
        if(evaluate(f.getRHS()) == 0)
        {
            std::cout << "ERROR: Division by 0" << std::endl;
            return 0;
        }
        return (evaluate(f.getLHS()) / evaluate(f.getRHS()));
        break;
    case '^':
        return pow(evaluate(f.getLHS()), evaluate(f.getRHS()));
        break;
    default:
        std::cout << "ERROR: Unknown operation" << std::endl;
        break;
    }

    return 0;
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
             case 3:
                 len = numlen(evaluate(this->table[i][j].getFormulaValue()));
                 if(len > paddings[j])
                     paddings[j] = len;
                 break;
           
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
                std::cout << std::left << std::setw(paddings[j]) << std::fixed << std::setprecision(PRECISION) << table[i][j].getDoubleValue();
                break;
            case 2:
                std::cout << std::left << std::setw(paddings[j]) << table[i][j].getStringValue();
                break;
             case 3:
                 std::cout << std::left << std::setw(paddings[j]) << evaluate(table[i][j].getFormulaValue());
                 break;
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

    char line[CELL_SIZE];
    char temp[CELL_SIZE];

    int j = 0;
    int i = 0;
    int p = 0;
    int prev = 0;

    bool doubleFlag = true;
    bool point = false;
    bool formulaFlag = true;
    bool intFlag = true;
    
    while(in.getline(line, CELL_SIZE))
    {
        do
        {
            if (line[p] == ',' || line[p] == '\0')
            {
                strncpy(temp, line+prev, p-prev);
                temp[p-prev] = '\0';

                // check if it's a formula
                if (temp[0] != '=')
                    formulaFlag = false;

                // check if it's a double
                for (int i = 0; i < p-prev; i++)
                {   
                    if (temp[i] == '.')
                    {
                        if(!point)
                            point = true;
                        else
                        {
                             doubleFlag = false;
                             break;
                        }
                        
                    }
                    else if(temp[i] > '9' || temp[i] < '0')
                    {
                        doubleFlag = false;
                        break;
                    }
                }

                // check if it's int
                for (int i = 0; i < p-prev; i++)
                {
                    if (temp[i] > '9' || temp[i] < '0')
                    {
                        intFlag = false;
                        break;
                    }
                }
                
                if (p - prev == 0){} // handle empty cells
                else if (intFlag)
                    setCell(i, j, 0, atoi(temp));
                else if (doubleFlag)
                    setCell(i, j, 1, 0, std::round(atof(temp)*std::pow(10.0, PRECISION))/std::pow(10.0, PRECISION));
                else if (formulaFlag)
                {
                    int len = strlen(temp);
                    char dump1[CELL_SIZE];
                    char dump2[CELL_SIZE];
                    for (int q = 1, endOfLHS = 1; q < len; q++, endOfLHS++)
                    {
                        if (temp[q] == '+' || temp[q] == '-' || temp[q] == '/' || temp[q] == '*' || temp[q] == '^')
                        {
                            char* newLHS = strncpy(dump1, temp + 1, endOfLHS - 1);
                            newLHS[endOfLHS - 1] = '\0';
                            char* newRHS = strncpy(dump2, temp + endOfLHS + 1, len - endOfLHS - 1);
                            newRHS[len - endOfLHS - 1] = '\0';
                            setCell(i, j, 3, 0, 0, "", Formula(newLHS, newRHS, temp[q]));
                            break;
                        }
                        else if (endOfLHS == len-2)
                        {
                            std::cout << "Wrong formula" << std::endl;
                        }
                    }
                }
                else
                    setCell(i, j, 2, 0, 0, temp);

                prev = p+1;
                j++;

                doubleFlag = true;
                formulaFlag = true;
                intFlag = true;
                point = false;
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
    Formula f;
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
                out << std::fixed << std::setprecision(PRECISION) << this->table[i][j].getDoubleValue();
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
                case 3:
                 f = table[i][j].getFormulaValue();
                 out << "=" << f.getLHS() << f.getOperation() << f.getRHS();
                 if (j < this->nCols - 1)
                     out << ",";
                 else
                     out << "\n";
                 break;
            
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