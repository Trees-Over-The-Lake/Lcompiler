#ifndef SYMBOL_TABLE_TOKEN_TYPE_CPP
#define SYMBOL_TABLE_TOKEN_TYPE_CPP

enum TokenType 
{
    INTEIRO,
    LOGICO,
    TEXTO,
    REAL,
    CARACTERE,
    HEXADECIMAL,
    NAO_DEFINIDO,
};

std::string token_type_to_string(TokenType type) {

    switch (type)
    {
    case CARACTERE:
        return "CARACTERE"; 
    case REAL:
        return "REAL"; 
    case INTEIRO:
        return "INTEIRO"; 
    case LOGICO:
        return "LOGICO"; 
    case TEXTO:
        return "TEXTO"; 
    case HEXADECIMAL:
        return "HEXADECIMAL"; 
    case NAO_DEFINIDO:
        return "NAO_DEFINIDO"; 
    default:
        return "NULL"; 
    }

    return "NULL";
}

#endif