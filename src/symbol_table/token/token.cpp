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
        uint8_t tamanho;
    public:
        Token(TokenID id = TokenID::ATRIBUICAO, std::string lexema = "", TokenType tipo = TokenType::NAO_DEFINIDO, uint8_t tamanho = 1);
        ~Token();

        std::string to_string();
};

Token::Token(TokenID id, std::string lexema, TokenType tipo, uint8_t tamanho) {
    this->id = id;
    this->lexema = lexema;
    this->tipo = tipo;
    this->tamanho = tamanho;
}

Token::~Token()
{

}

std::string Token::to_string() {
    return "token_id: " + std::to_string(this->id) + "| lexema: " + this->lexema + "| tipo: " + \
            std::to_string(this->tipo) + "| tamanho: " + std::to_string(this->tamanho);
}

#endif