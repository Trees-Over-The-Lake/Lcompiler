#ifndef SYMBOL_TABLE_TOKEN_CLASS_CPP
#define SYMBOL_TABLE_TOKEN_CLASS_CPP

enum TokenClass
{
    VARIAVEL,
    CONSTANTE,
    NENHUM,
};

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