#include "Cell.h"


Cell::Cell(int row, int col, int type)
{
    this->idRow = row;
    this->idCol = col;
    this->type = type;

    this->intValue = 0;
    this->doubleValue = 0;
    this->stringValue = new char[0];
    // this->formulaValue = ;
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
const Formula Cell::getFormulaValue() const
{
    return this->formulaValue;
}

// Setters

void Cell::setType(int type)
{
    this->type = type;
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
    // delete [] this->stringValue; ?????????
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
}

void Cell::printVal()
{
    switch (type)
    {
    case 0:
        std::cout << getIntValue() << std::endl;
        break;
    case 1:
        std::cout << getDoubleValue() << std::endl;
        break;
    case 2:
        std::cout << getStringValue() << std::endl;
        break;
    // case 3:
    //     std::cout << getFormulaValue() << std::endl;
    //     break;
    
    default:
        std::cout << std::endl;
        break;
    }
}

void Cell::free()
{
    this->type = -1;

    this->intValue = 0;
    this->doubleValue = 0;

    delete [] this->stringValue;
    this->stringValue = new char[0];

    // Delete formula !!!!!
}

void Cell::copy(const Cell& other)
{
    this->type = other.type;

    this->intValue = other.intValue;
    this->doubleValue = other.doubleValue;

    this->stringValue = new char[strlen(other.stringValue) + 1];
    strcpy(this->stringValue, other.stringValue);

    // Copy the formula !!!!!
}