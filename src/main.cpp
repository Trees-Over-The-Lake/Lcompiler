#include<iostream>
#include"symbol_table/symbol_table.cpp"

int main(int argc, char* argv[]) {

    SymbolTable st = SymbolTable();

    std::cout << st.to_string() << std::endl;
    return 0;
}