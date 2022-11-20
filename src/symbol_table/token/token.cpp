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
    Token(TokenID id = TokenID::ATRIBUICAO, std::string lexema = "", TokenType tipo = TokenType::NAO_DEFINIDO, TokenClass classe = TokenClass::NENHUM, token_size tamanho = 1, long endereco = 0x0);
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

Token::Token(TokenID id, std::string lexema, TokenType tipo, TokenClass classe, token_size tamanho, long endereco) {
    this->id = id;
    this->lexema = lexema;
    this->tipo = tipo;
    this->classe = classe;
    this->tamanho = tamanho;
    this->endereco = endereco;
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

token_size Token::get_tamanho() {
    return this->tamanho;
}

TokenID Token::get_id() {
    return this->id;
}

long Token::get_endereco() {
    return this->endereco;
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

void Token::set_tamanho(token_size tamanho) {
    this->tamanho = tamanho;
}

void Token::set_id(TokenID id) {
    this->id = id;
}

void Token::set_endereco(long endereco) {
    this->endereco = endereco;
}

Token Token::clone() {
    Token c;
    c.classe = this->classe;
    c.id = this->id;
    c.lexema = this->lexema;
    c.tipo = this->tipo;
    c.tamanho = this->tamanho;

    return c;
}

std::string Token::to_string() {
    return "token_id: " + token_id_to_string(this->id) + "\t lexema: " + this->lexema + "\t tipo: " + \
            token_type_to_string(this->tipo) + "\t classe: " + token_class_to_string(this->classe) + "\t tamanho: " + std::to_string(this->tamanho);
}

#endif