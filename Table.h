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

void setCell(int, int, int, int a=0, double b=0, const char* c = nullptr); //add formula !!!!!

void print();

bool load(std::fstream&);
bool save(std::fstream&);
};