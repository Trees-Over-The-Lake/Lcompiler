#ifndef SYMBOL_TABLE_TOKEN_CLASS_CPP
#define SYMBOL_TABLE_TOKEN_CLASS_CPP

/**
 * 
 * @brief All TokenClasses accepted by the language and enumerations 
 *  
*/
enum TokenClass
{
    VARIAVEL,
    CONSTANTE,
    NENHUM,
};

/**
 * 
 * @brief Transforms the selected TokenClass into a string
 * @param tclass TokenClass to be converted
 *  
*/
std::string token_class_to_string(TokenClass tclass) {

    switch (tclass)
    {
    case VARIAVEL:
        return "VARIAVEL";
    case CONSTANTE:
        return "CONSTANTE";
    case NENHUM:
        return "NENHUM";
    default:
        return "NULL"; 
    }

    return "NULL";
}

#endif