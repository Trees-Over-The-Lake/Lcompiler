#ifndef SYMBOLS_TABLE_CPP
#define SYMBOLS_TABLE_CPP

#include<map>
#include<unordered_map>
#include<string>
#include<stdexcept>
#include<algorithm>

#include"token/token.cpp"
#include"lexeme.cpp"
#include"../utils/string_utils.cpp"
#include<locale>

class SymbolTable {
    private:

        static std::unordered_map<std::string,Token> table;
        static bool table_initialized;

        void initiate_symbol_table();

    public:
        SymbolTable();
        ~SymbolTable();

        Token* add_id(std::string lexeme);
        Token* find_lexeme(std::string lexeme);
        std::string to_string();

        bool is_character_valid(const char c);
};

bool SymbolTable::table_initialized = false;
std::unordered_map<std::string,Token> SymbolTable::table;

SymbolTable::SymbolTable(){

    if (!table_initialized)
        initiate_symbol_table();
}

void SymbolTable::initiate_symbol_table() {
    for(auto iter = LEXEMES.begin(); iter != LEXEMES.end(); ++iter) {
        TokenID id = iter->first;
        std::string lexeme = iter->second;

        SymbolTable::table.insert({lexeme, Token(id,lexeme)});
    }
}

SymbolTable::~SymbolTable(){}

Token* SymbolTable::add_id(std::string lexeme) {

    auto lowered_lexeme = to_lower(lexeme);
    Token* token = NULL;

    try {
        token = &(this->table[lowered_lexeme]);
        if (token->get_lexema().empty() && token->get_id() != FIM_DE_ARQUIVO) {
            token = new Token(TokenID::IDENTIFICADOR, lowered_lexeme);
            this->table.insert({lowered_lexeme, *token});
        }
    
    } catch(std::exception e ) {

        token = new Token(TokenID::IDENTIFICADOR, lowered_lexeme);
        this->table.insert({lowered_lexeme, *token});

    } 

    return token;
}

Token* SymbolTable::find_lexeme(std::string lexeme) {
    
    Token* token = NULL;

    try {
        token = &(this->table[lexeme]);

    } catch(std::exception e ) {} 

    return token;
}

/**
 * Dado um certo caractere, verificar se o mesmo eh valido na linguagem
 */
bool SymbolTable::is_character_valid(const char c) {
    return std::isalnum(c) ||
           std::find(VALID_CHARACTERS.begin(), VALID_CHARACTERS.end(), c) != VALID_CHARACTERS.end();
}

std::string SymbolTable::to_string() {

    std::string result = "";

    for(auto iter = SymbolTable::table.begin(); iter != SymbolTable::table.end(); ++iter) {
        std::string lexeme = iter->first;
        Token token = iter->second;

        result += "lexeme: " + lexeme + "\ttoken: \n" + token.to_string() + "\n\n" ;
    }

    return result;
}

#endif