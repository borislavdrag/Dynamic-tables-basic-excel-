#include "Formula.h"

//Constructors & sonstige
Formula::Formula(const char* LHS, const char* RHS, const char op)
{

   
        int len1 = strlen(LHS);
       
        this->LHS = new char[len1+1];
        strcpy(this->LHS, LHS);
    
        int len2 = strlen(RHS);
        this->RHS = new char[len2+1];
        strcpy(this->RHS, RHS);

    
   
     std::cout << 41 << std::endl; 
    // std::cout << 34 << std::endl;
    this->operation = op;
}

Formula::~Formula()
{
    print();
    delete[] this->LHS;
    std::cout << 40 << this << std::endl; 
    delete[] this->RHS;
}

Formula::Formula(const Formula& other)
{
    std::cout << 401 << std::endl;
    copy(other);
}

Formula& Formula::operator=(const Formula& other)
{
    std::cout << 401 << std::endl; 

    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

//Getters
const char* Formula::getLHS() const
{
    return LHS;
}
const char* Formula::getRHS() const
{
    return RHS;
}
const char Formula::getOperation() const
{
    return operation;
}

//Setters
void Formula::setLHS(const char* LHS)
{
    strcpy(this->LHS, LHS);
}
void Formula::setRHS(const char* RHS)
{
    strcpy(this->RHS, RHS);
}
void Formula::setOperation(const char op)
{
    this->operation = op;
}

//Other functions
void Formula::print()
{
    std::cout << "=" << LHS << operation << RHS << std::endl;
}

void Formula::copy(const Formula& other)
{
    strcpy(this->LHS, other.getLHS());
    strcpy(this->RHS, other.getRHS());
    this->operation = other.operation;
}

void Formula::free()
{
    delete[] LHS;
    delete[] RHS;

    //LHS = nullptr;
    //RHS = nullptr;
    operation = '+';
}