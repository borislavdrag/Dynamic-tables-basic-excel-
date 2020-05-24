#include "Cell.h"

#define DEFAULT_SIZE 3

class Table
{
int nRows;
int nCols;

Cell** table;

void copy(const Table&);
void free();

public:

Table(int nRows = DEFAULT_SIZE, int nCols = DEFAULT_SIZE);
Table(const Table&);
Table& operator = (const Table&);
~Table();

const int getNRows() const;
const int getNCols() const;
const Cell& getCell(int, int) const;

const int evaluate(const char* side) const;
const int evaluate(Formula&) const;

void setCell(int, int, int, int =0, double =0, const char* = nullptr, const Formula& = Formula()); //add formula !!!!!

void print();

bool load(std::fstream&);
bool save(std::fstream&);
};