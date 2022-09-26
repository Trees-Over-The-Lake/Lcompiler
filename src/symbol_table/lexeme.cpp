#ifndef LEXEME_CPP
#define LEXEME_CPP

#include<map>
#include<string>
#include"token/token_id.cpp"

static const std::map<TokenID,std::string> LEXEMES = {
    {TokenID::ABRE_CHAVES, "{"}
};

#endif