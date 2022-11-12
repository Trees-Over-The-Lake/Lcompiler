#ifndef SYMBOLS_TABLE_CPP
#define SYMBOLS_TABLE_CPP

#include<unordered_map>
#include<string>
#include<stdexcept>
#include<algorithm>
#include<memory>

#include"token/token.cpp"
#include"lexeme.cpp"
#include"../utils/string_utils.cpp"
#include<locale>

typedef std::shared_ptr<Token> Token_pointer;

class SymbolTable {
    private:

        static std::unordered_map<std::string,Token_pointer> table;
        static bool table_initialized;

        void initiate_symbol_table();

    public:
        SymbolTable();
        ~SymbolTable();

        Token_pointer add_id(std::string lexeme);
        Token_pointer find_by_lexeme(std::string lexeme);
        std::string to_string();

        bool is_character_valid(const char c);
};

bool SymbolTable::table_initialized = false;
std::unordered_map<std::string,Token_pointer> SymbolTable::table;

SymbolTable::SymbolTable(){

    if (!table_initialized)
        initiate_symbol_table();
}

SymbolTable::~SymbolTable(){}

void SymbolTable::initiate_symbol_table() {
    
    for(auto iter = LEXEMES.begin(); iter != LEXEMES.end(); ++iter) {
        TokenID id = iter->first;
        std::string lexeme = iter->second;

        auto token = std::make_shared<Token>(id,lexeme);

        SymbolTable::table.insert({lexeme, token});
    }
}

Token_pointer SymbolTable::add_id(std::string lexeme) {

    auto lowered_lexeme = to_lower(lexeme);

    Token_pointer token = find_by_lexeme(lexeme);

    if (token == nullptr) {

        this->table.insert(std::make_pair(lowered_lexeme, 
                            std::make_shared<Token>(IDENTIFICADOR, lowered_lexeme)));
        token = this->table.find(lowered_lexeme)->second;
    }

    return token;
}

Token_pointer SymbolTable::find_by_lexeme(std::string lexeme) {
    
    Token_pointer token = nullptr;

    if (this->table.find(lexeme) != this->table.end())
        token = this->table.at(lexeme);
    
    return token;
}

bool SymbolTable::is_character_valid(const char c) {
    return std::isalnum(c) ||
           std::find(VALID_CHARACTERS.begin(), VALID_CHARACTERS.end(), c) != VALID_CHARACTERS.end();
}

std::string SymbolTable::to_string() {

    std::string result = "";

    for(auto iter = SymbolTable::table.begin(); iter != SymbolTable::table.end(); ++iter) {
        std::string lexeme = iter->first;
        auto token = iter->second;

        if (token != nullptr)
            result += "lexeme: " + lexeme + "\ttoken: \n" + token->to_string() + "\n\n" ;
        else 
            result += "ERROR! Found null token\n\n";
    }

    return result;
}

#endif