#include "Formula.h"

class Cell
{
    int idRow;
    int idCol;

    int type;

    int intValue;
    double doubleValue;
    char* stringValue;
    Formula formulaValue;

    void copy(const Cell&);
    void free();

public:

    Cell(int row=-1, int col=-1, int type=-1);
    Cell(const Cell&);
    Cell& operator = (const Cell&);
    ~Cell();

    const int getRow() const;
    const int getCol() const;
    const int getType() const;

    const int getIntValue() const;
    const double getDoubleValue() const;
    const char* getStringValue() const;
    const Formula& getFormulaValue() const;

    void setType(int);
    void setRow(int);
    void setCol(int);
    void setIntValue(int);
    void setDoubleValue(double);
    void setStringValue(const char*);
    void setFormulaValue(const Formula&);

    void print();
    void printVal();
};