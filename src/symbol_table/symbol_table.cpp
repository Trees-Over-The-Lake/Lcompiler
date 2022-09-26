#ifndef SYMBOLS_TABLE_CPP
#define SYMBOLS_TABLE_CPP

#include<unordered_map>
#include"token/token.cpp"
#include<string>

class SymbolTable
{
private:
    static std::unordered_map<std::string,Token> table;
    bool table_initialized = false;

public:
    SymbolTable(/* args */);
    ~SymbolTable();
};

SymbolTable::SymbolTable(/* args */)
{
}

SymbolTable::~SymbolTable()
{
}


#endif