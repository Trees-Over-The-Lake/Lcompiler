#ifndef TOKEN_CPP
#define TOKEN_CPP
 
#include "token_type.cpp"
#include "token_class.cpp"
#include "token_id.cpp"
#include <unordered_map>
#include <string>
#include <cstdint>

class Token {
    private:
        TokenID id;
        std::string lexema;
        TokenType tipo;
        TokenClass classe;
        uint8_t tamanho;
    public:
        Token(TokenID id = TokenID::ATRIBUICAO, std::string lexema = "", TokenType tipo = TokenType::NAO_DEFINIDO, TokenClass classe = TokenClass::NENHUM, uint8_t tamanho = 1);
        ~Token();

        std::string get_lexema();
        TokenType get_tipo();
        TokenClass get_classe();
        uint8_t get_tamanho();
        TokenID get_id();

        void set_lexema(std::string lexema);
        void set_tipo(TokenType tipo);
        void set_classe(TokenClass classe);
        void set_tamanho(uint8_t tamanho);
        void set_id(TokenID id);

        std::string to_string();
};

Token::Token(TokenID id, std::string lexema, TokenType tipo, TokenClass classe, uint8_t tamanho) {
    this->id = id;
    this->lexema = lexema;
    this->tipo = tipo;
    this->classe = classe;
    this->tamanho = tamanho;
}

Token::~Token()
{

}

std::string Token::get_lexema() {
    return this->lexema;
}

TokenType Token::get_tipo() {
    return this->tipo;
}

TokenClass Token::get_classe() {
    return this->classe;
}

uint8_t Token::get_tamanho() {
    return this->tamanho;
}

TokenID Token::get_id() {
    return this->id;
}

void Token::set_lexema(std::string lexema) {
    this->lexema = lexema;
}

void Token::set_tipo(TokenType tipo) {
    this->tipo = tipo;
}

void Token::set_classe(TokenClass classe) {
    this->classe = classe;
}

void Token::set_tamanho(uint8_t tamanho) {
    this->tamanho = tamanho;
}

void Token::set_id(TokenID id) {
    this->id = id;
}

std::string Token::to_string() {
    return "token_id: " + token_id_to_string(this->id) + "\t lexema: " + this->lexema + "\t tipo: " + \
            token_type_to_string(this->tipo) + "\t classe: " + token_class_to_string(this->classe) + "\t tamanho: " + std::to_string(this->tamanho);
}

#endif