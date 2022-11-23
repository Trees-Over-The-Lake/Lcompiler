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
#include"../generator/bin_constants.hpp"
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
        token_size get_token_type_size(TokenType t,std::string lexeme);
        std::string to_string();

        bool is_character_valid(const char c);
};

bool SymbolTable::table_initialized = false;
std::unordered_map<std::string,Token_pointer> SymbolTable::table;

/**
 * 
 * @brief Constructor of symbol table that verifies if an instance of it exists.
 *  
*/
SymbolTable::SymbolTable(){

    if (!table_initialized)
        initiate_symbol_table();
}

// Desconstrutor da classe Tabela de Simbolo 
SymbolTable::~SymbolTable(){}

/**
 * 
 * @brief Adds all reserved words in the symbol table.
 *  
*/
void SymbolTable::initiate_symbol_table() {
    
    for(auto iter = LEXEMES.begin(); iter != LEXEMES.end(); ++iter) {
        TokenID id = iter->first;
        std::string lexeme = iter->second;

        auto token = std::make_shared<Token>(id,lexeme);

        SymbolTable::table.insert({lexeme, token});
    }
}

/**
 * 
 * @brief Adds a new lexeme in the symbol table.
 * @param lexeme string to be added.
 *  
*/
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

/**
 * 
 * @brief Finds a token in the symbol table, based on a lexeme
 * @param lexeme string to be added
 * 
*/
Token_pointer SymbolTable::find_by_lexeme(std::string lexeme) {
    
    Token_pointer token = nullptr;

    if (this->table.find(lexeme) != this->table.end())
        token = this->table.at(lexeme);
    
    return token;
}

/**
 * 
 * @brief Verifies if a certain character is valid
 * @param c char to be verified
 *  
*/
bool SymbolTable::is_character_valid(const char c) {
    return std::isalnum(c) ||
           std::find(VALID_CHARACTERS.begin(), VALID_CHARACTERS.end(), c) != VALID_CHARACTERS.end();
}

/**
 * 
 * @brief Returns the lexeme and token as a string 
 *  
*/
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

/**
 * 
 * @brief Returns the size of determined token type
 * @param t token type selected
 * @param lexeme string necessary to calculate if token type is a string 
 *  
*/
token_size SymbolTable::get_token_type_size(TokenType t,std::string lexeme) {

    token_size size = 0;

    switch (t) {

        case INTEIRO:
            size = L_NUMBER_SIZE;
            break;
        case TEXTO:
            size = (lexeme.length() - 2) + 1; // Remover as aspas e adicionar o \0
            break;
        case REAL: 
            size = L_NUMBER_SIZE;
            break;
        case LOGICO:
            size = L_BOOLEAN_SIZE;
            break;
        case CARACTERE:
            size = L_CHAR_SIZE;
            break;
        default:
            size = 0;
            break;
    }

    return size;
}

#endif