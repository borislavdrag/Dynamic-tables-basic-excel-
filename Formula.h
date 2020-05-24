#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cmath>

#define PRECISION 2
#define CELL_SIZE 1000

class Formula
{
    char* LHS;
    char* RHS;
    char operation;

public:

    Formula(const char* LHS = "", const char* RHS = "", const char op = '+');
    ~Formula();
    Formula(const Formula&);
    Formula& operator=(const Formula&);

    const char* getLHS() const;
    const char* getRHS() const;
    const char getOperation() const;

    void setLHS(const char*);
    void setRHS(const char*);
    void setOperation(const char);

    void free();
    void copy(const Formula&);
    void print();
};