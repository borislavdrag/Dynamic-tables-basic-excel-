#include "Cell.h"


Cell::Cell(int row, int col, int type)
{
    this->idRow = row;
    this->idCol = col;
    this->type = type;

    this->intValue = 0;
    this->doubleValue = 0;
    this->stringValue = nullptr;
    //this->formulaValue = nullptr;
}

Cell::~Cell()
{
    delete [] this->stringValue;
}

Cell::Cell(const Cell& other)
{
    copy(other);
}

Cell& Cell::operator=(const Cell& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

// Getters

const int Cell::getRow() const
{
    return this->idRow;
}
const int Cell::getCol() const
{
    return this->idCol;
}
const int Cell::getType() const
{
    return this->type;
}
const int Cell::getIntValue() const
{
    return this->intValue;
}
const double Cell::getDoubleValue() const
{
    return this->doubleValue;
}
const char* Cell::getStringValue() const
{
    return this->stringValue;
}
const Formula& Cell::getFormulaValue() const
{
    return this->formulaValue;
}

// Setters

void Cell::setType(int type)
{
    this->type = type;
}
void Cell::setRow(int row)
{
    this->idRow = row;
}
void Cell::setCol(int col)
{
    this->idCol = col;
}
void Cell::setIntValue(int val)
{
    this->type = 0;
    this->intValue = val;
}
void Cell::setDoubleValue(double val)
{
    this->type = 1;
    this->doubleValue = val;
}
void Cell::setStringValue(const char* val)
{
    this->type = 2;
    if (this->stringValue != nullptr)
    {
    delete[] this->stringValue;
    }
    this->stringValue = new char[strlen(val) + 1];
    strcpy(this->stringValue, val);
}
void Cell::setFormulaValue(const Formula& val)
{
    this->type = 3;
    this->formulaValue = val;
}

// Other functions

void Cell::print()
{
    std::cout << "R" << this->idRow << "C" << this->idCol << ": ";
    printVal();
    std::cout << std::endl;
}

void Cell::printVal()
{
    switch (type)
    {
    case 0:
        std::cout << getIntValue();
        break;
    case 1:
        std::cout << std::fixed << std::setprecision(PRECISION) << getDoubleValue();
        break;
    case 2:
        std::cout << getStringValue();
        break;
     case 3:
         std::cout << "=" << getFormulaValue().getLHS() << getFormulaValue().getOperation() << getFormulaValue().getRHS() << std::endl;
         break;
    
    default:
        break;
    }
}

void Cell::free()
{
    this->type = -1;

    this->intValue = 0;
    this->doubleValue = 0;

    delete [] this->stringValue;
    /*this->stringValue = nullptr;*/

    this->formulaValue.free();
}

void Cell::copy(const Cell& other)
{
    this->type = other.type;

    this->intValue = other.intValue;
    this->doubleValue = other.doubleValue;

    if (other.stringValue)
    {
        this->stringValue = new char[strlen(other.stringValue) + 1];
        strcpy(this->stringValue, other.stringValue);
    }

    this->formulaValue.copy(other.getFormulaValue());
}