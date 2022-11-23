#ifndef SYMBOL_TABLE_TOKEN_TYPE_CPP
#define SYMBOL_TABLE_TOKEN_TYPE_CPP

/**
 * 
 * @brief All TokenTypes accepted by the language and enumerations 
 *  
*/
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

/**
 * 
 * @brief Transforms the selected TokenType into a string
 * @param type TokenType to be converted
 *  
*/
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