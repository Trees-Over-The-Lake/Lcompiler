#ifndef LEXEME_CPP
#define LEXEME_CPP

#include<map>
#include<string>
#include"token/token_id.cpp"

static const std::map<TokenID,std::string> LEXEMES = {
    {TokenID::CONST, "const"},
    {TokenID::INT, "int"},
    {TokenID::FLOAT, "float"},
    {TokenID::CHAR, "char"},
    {TokenID::STRING, "string"},
    {TokenID::BOOLEAN, "boolean"},
    {TokenID::TRUE, "true"},
    {TokenID::FALSE, "false"},
    {TokenID::IF, "if"},
    {TokenID::ELSE, "else"},
    {TokenID::WHILE, "while"},
    {TokenID::MOD, "mod"},
    {TokenID::WRITE, "write"},
    {TokenID::WRITELN, "writeln"},
    {TokenID::READLN, "readln"},
    {TokenID::DIV, "/"},
    {TokenID::NEGACAO, "!"},
    {TokenID::ATRIBUICAO, "="},
    {TokenID::IGUAL, "=="},
    {TokenID::WALRUS, ":="},
    {TokenID::MAIOR, ">"},
    {TokenID::MENOR, "<"},
    {TokenID::MAIOR_IGUAL, ">="},
    {TokenID::MENOR_IGUAL, "<="},
    {TokenID::DIFERENTE, "!="},
    {TokenID::VIRGULA, ","},
    {TokenID::SOMA, "+"},
    {TokenID::SUBTRACAO, "-"},
    {TokenID::MULTIPLICACAO, "*"},
    {TokenID::DIVISAO, "/"},
    {TokenID::PONTO_VIRGULA, ";"},
    {TokenID::ABRE_PARANTESES, "("},
    {TokenID::FECHA_PARANTESES, ")"},
    {TokenID::ABRE_CHAVES, "{"},
    {TokenID::FECHA_CHAVES, "}"},
    {TokenID::ABRE_COLCHETES, "["},
    {TokenID::FECHA_COLCHETES, "]"},
    {TokenID::AND, "&&"},
    {TokenID::OR, "||"},

};

#endif