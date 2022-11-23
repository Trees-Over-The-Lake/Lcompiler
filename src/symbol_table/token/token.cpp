#ifndef SYMBOL_TABLE_TOKEN_CPP
#define SYMBOL_TABLE_TOKEN_CPP
 
#include "token_type.cpp"
#include "token_class.cpp"
#include "token_id.cpp"
#include <unordered_map>
#include <string>
#include <cstdint>

typedef size_t token_size;

class Token {
private:
    TokenID id;
    std::string lexema;
    TokenType tipo;
    TokenClass classe;
    token_size tamanho;
    long endereco;

public:
    Token(TokenID id = ID_NULO, std::string lexema = "", TokenType tipo = TokenType::NAO_DEFINIDO, TokenClass classe = TokenClass::NENHUM, token_size tamanho = 1, long endereco = 0x0);
    ~Token();

    std::string get_lexema();
    TokenType get_tipo();
    TokenClass get_classe();
    token_size get_tamanho();
    TokenID get_id();
    long get_endereco();

    Token clone();

    void set_lexema(std::string lexema);
    void set_tipo(TokenType tipo);
    void set_classe(TokenClass classe);
    void set_tamanho(token_size tamanho);
    void set_id(TokenID id);
    void set_endereco(long endereco);

    std::string to_string();
};

/**
 * 
 * @brief Constructor of Token
 * @param id TokenID
 * @param lexema string
 * @param tipo TokenType
 * @param classe TokenClass
 * @param tamanho size_t
 * @param endereco long
 *  
*/
Token::Token(TokenID id, std::string lexema, TokenType tipo, TokenClass classe, token_size tamanho, long endereco) {
    this->id = id;
    this->lexema = lexema;
    this->tipo = tipo;
    this->classe = classe;
    this->tamanho = tamanho;
    this->endereco = endereco;
}

/**
 * 
 * @brief Destructor of Token
 *  
*/
Token::~Token()
{

}

/**
 * 
 * @brief Returns the lexema of the Token
 *  
*/
std::string Token::get_lexema() {
    return this->lexema;
}

/**
 * 
 * @brief Returns the type of the Token
 *  
*/
TokenType Token::get_tipo() {
    return this->tipo;
}

/**
 * 
 * @brief Returns the class of the Token
 *  
*/
TokenClass Token::get_classe() {
    return this->classe;
}

/**
 * 
 * @brief Returns the size of the Token
 *  
*/
token_size Token::get_tamanho() {
    return this->tamanho;
}

/**
 * 
 * @brief Returns the id of the Token
 *  
*/
TokenID Token::get_id() {
    return this->id;
}

/**
 * 
 * @brief Returns the address of the Token
 *  
*/
long Token::get_endereco() {
    return this->endereco;
}

/**
 * 
 * @brief Set a new lexema for the Token
 * @param lexema string to be set
 *  
*/
void Token::set_lexema(std::string lexema) {
    this->lexema = lexema;
}

/**
 * 
 * @brief Destructor of Token
 *  
*/
void Token::set_tipo(TokenType tipo) {
    this->tipo = tipo;
}

/**
 * 
 * @brief Set a new class for the Token
 * @param classe TokenClass to be set
 *  
*/
void Token::set_classe(TokenClass classe) {
    this->classe = classe;
}

/**
 * 
 * @brief Set a new size for the Token
 * @param tamanho size_t to be set
 *  
*/
void Token::set_tamanho(token_size tamanho) {
    this->tamanho = tamanho;
}

/**
 * 
 * @brief Set a new id for the Token
 * @param id TokenID to be set
 *  
*/
void Token::set_id(TokenID id) {
    this->id = id;
}

/**
 * 
 * @brief Set a new address for the Token
 * @param endereco long to be set
 *  
*/
void Token::set_endereco(long endereco) {
    this->endereco = endereco;
}

/**
 * 
 * @brief Clone the class Token 
 *  
*/
Token Token::clone() {
    Token c;
    c.classe = this->classe;
    c.id = this->id;
    c.lexema = this->lexema;
    c.tipo = this->tipo;
    c.tamanho = this->tamanho;

    return c;
}

/**
 * 
 * @brief Returns the Token variables as a string 
 *  
*/
std::string Token::to_string() {
    return "token_id: " + token_id_to_string(this->id) + "\t lexema: " + this->lexema + "\t tipo: " + \
            token_type_to_string(this->tipo) + "\t classe: " + token_class_to_string(this->classe) + "\t tamanho: " + std::to_string(this->tamanho);
}

#endif