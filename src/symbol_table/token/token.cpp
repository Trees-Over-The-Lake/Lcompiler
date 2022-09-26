#ifndef TOKEN_CPP
#define TOKEN_CPP
 
#include "token_type.cpp"
#include "token_class.cpp"
#include "token_id.cpp"
#include <unordered_map>
#include <string>
#include <cstdint>

class Token
{
private:
    TokenID id;
    std::string lexema;
    TokenType tipo;
    uint8_t tamanho;
public:
    Token(TokenID id, std::string lexema, TokenType tipo = TokenType::NAO_DEFINIDO, uint8_t tamanho = 1);
    ~Token();
};

Token::Token(TokenID id, std::string lexema, TokenType tipo = TokenType::NAO_DEFINIDO, uint8_t tamanho = 1)
{
    this->id = id;
    this->lexema = lexema;
    this->tipo = tipo;
    this->tamanho = tamanho;
}

Token::~Token()
{

}







#endif