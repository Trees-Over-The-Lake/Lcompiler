#ifndef SYMBOL_TABLE_LEXEME_CPP
#define SYMBOL_TABLE_LEXEME_CPP

#include<map>
#include<string>
#include<vector>
#include"token/token_id.cpp"

const std::vector<char> VALID_CHARACTERS{
        ' ',
        '|',
        '!', 
        '"', 
        '%', 
        '@',
        '?',
        '&', 
        '(', 
        ')', 
        '{', 
        '}', 
        '[', 
        ']', 
        '*', 
        '+', 
        '-', 
        '/', 
        ',', 
        '.', 
        ':', 
        ';', 
        '<', 
        '>', 
        '=', 
        '_', 
        '\'',
        '\\', 
        '\r',
        '\t',
        '\n',
        '\0'
};

const std::vector<char> VALID_HEXA_SYMBOLS{
        'A', 
        'B', 
        'C', 
        'D', 
        'E', 
        'F', 
        'a', 
        'b', 
        'c', 
        'd', 
        'e', 
        'f'
};

const std::map<TokenID,std::string> LEXEMES = {
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
    {TokenID::DIV, "div"},
    {TokenID::WRITE, "write"},
    {TokenID::WRITELN, "writeln"},
    {TokenID::READLN, "readln"},
    {TokenID::NEGACAO, "!"},
    {TokenID::IGUAL, "="},
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
    {TokenID::FIM_DE_ARQUIVO, "\0"}
};

#endif