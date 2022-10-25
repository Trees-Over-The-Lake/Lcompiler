#ifndef SYMBOLS_TABLE_CPP
#define SYMBOLS_TABLE_CPP

#include<map>
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
        Token_pointer find_lexeme(std::string lexeme);
        std::string to_string();

        bool is_character_valid(const char c);
};

bool SymbolTable::table_initialized = false;
std::unordered_map<std::string,Token_pointer> SymbolTable::table;

SymbolTable::SymbolTable(){

    if (!table_initialized)
        initiate_symbol_table();
}

void SymbolTable::initiate_symbol_table() {
    for(auto iter = LEXEMES.begin(); iter != LEXEMES.end(); ++iter) {
        TokenID id = iter->first;
        std::string lexeme = iter->second;

        Token_pointer token = std::make_shared<Token>(id,lexeme);

        SymbolTable::table.insert({lexeme, token});
    }
}

SymbolTable::~SymbolTable(){}

Token_pointer SymbolTable::add_id(std::string lexeme) {

    auto lowered_lexeme = to_lower(lexeme);
    Token_pointer token = std::make_shared<Token>();

    try {
        token = this->table[lowered_lexeme];
        if (token == nullptr || (token->get_lexema().empty() && token->get_id() != FIM_DE_ARQUIVO)) {
            token = std::make_shared<Token>(IDENTIFICADOR, lowered_lexeme);
            this->table.insert({lowered_lexeme, token});
        }
    
    } catch(std::exception e ) {

        token = std::make_shared<Token>(IDENTIFICADOR, lowered_lexeme);
        this->table.insert({lowered_lexeme, token});

    } 

    return token;
}

Token_pointer SymbolTable::find_lexeme(std::string lexeme) {
    
    Token_pointer token = std::make_shared<Token>();

    try {
        token = this->table[lexeme];

    } catch(std::exception e ) {} 

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
        Token_pointer token = iter->second;

        result += "lexeme: " + lexeme + "\ttoken: \n" + token->to_string() + "\n\n" ;
    }

    return result;
}

#endif