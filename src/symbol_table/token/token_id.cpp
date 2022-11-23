#ifndef SYMBOL_TABLE_TOKEN_ID_CPP
#define SYMBOL_TABLE_TOKEN_ID_CPP

#include<string>

enum TokenID
{
    CONST,              // const
    IDENTIFICADOR,      // nome da variavel
    INT,                // int
    FLOAT,              // float
    CHAR,               // char
    STRING,             // String 
    BOOLEAN,            // bool
    TRUE,               // true
    FALSE,              // false
    IF,                 // if
    ELSE,               // else
    WHILE,              // While
    MOD,                // mod
    DIV,                // div
    WRITE,              // write
    WRITELN,            // writeln
    READLN,             // readln
    NEGACAO,            // !
    IGUAL,              // = || ==
    WALRUS,             // :=
    MAIOR,              // >
    MENOR,              // <
    MAIOR_IGUAL,        // >=
    MENOR_IGUAL,        // <=
    DIFERENTE,          // !=
    VIRGULA,            // ,
    SOMA,               // +
    SUBTRACAO,          // -      
    MULTIPLICACAO,      // *
    DIVISAO,            // /
    PORCENTAGEM,        // %
    PONTO_VIRGULA,      // ;
    ABRE_PARANTESES,    // (
    FECHA_PARANTESES,   // )
    ABRE_CHAVES,        // {
    FECHA_CHAVES,       // }
    ABRE_COLCHETES,     // [
    FECHA_COLCHETES,    // ]
    AND,                // &&
    OR,                 // ||
    FIM_DE_ARQUIVO,     // \0
    ID_NULO,            // nulo
};

std::string token_id_to_string(TokenID id) {

    switch (id)
    {
    case CONST:       
        return "CONST";   
    case IDENTIFICADOR:  
        return "IDENTIFICADOR";    
    case INT:           
        return "INT";     
    case FLOAT:         
        return "FLOAT";      
    case CHAR:          
        return "CHAR";      
    case STRING:        
        return "STRING";      
    case BOOLEAN:       
        return "BOOLEAN";      
    case TRUE:          
        return "TRUE";      
    case FALSE:         
        return "FALSE";      
    case IF:            
        return "IF";      
    case ELSE:          
        return "ELSE";     
    case WHILE:         
        return "WHILE";     
    case MOD:           
        return "MOD";      
    case WRITE:         
        return "WRITE";      
    case WRITELN:       
        return "WRITELN";      
    case READLN:        
        return "READLN";      
    case NEGACAO:       
        return "NEGACAO";     
    case IGUAL:    
        return "IGUAL";          
    case WALRUS:            
        return "WALRUS";      
    case MAIOR:         
        return "MAIOR";      
    case MENOR:         
        return "MENOR";     
    case MAIOR_IGUAL:   
        return "MAIOR_IGUAL";     
    case MENOR_IGUAL:   
        return "MENOR_IGUAL";      
    case DIFERENTE:     
        return "DIFERENTE";      
    case VIRGULA:       
        return "VIRGULA";      
    case SOMA:          
        return "SOMA";     
    case SUBTRACAO:     
        return "SUBTRACAO";          
    case MULTIPLICACAO: 
        return "MULTIPLICACAO";    
    case DIVISAO:       
        return "DIVISAO";      
    case PONTO_VIRGULA: 
        return "PONTO_VIRGULA";     
    case ABRE_PARANTESES:    
        return "ABRE_PARANTESES"; 
    case FECHA_PARANTESES:  
        return "FECHA_PARANTESES"; 
    case ABRE_CHAVES:        
        return "ABRE_CHAVES"; 
    case FECHA_CHAVES:  
        return "FECHA_CHAVES";      
    case ABRE_COLCHETES:
        return "ABRE_COLCHETES";      
    case FECHA_COLCHETES:
        return "FECHA_COLCHETES";    
    case AND:           
        return "AND";     
    case OR:
        return "OR"; 
    case FIM_DE_ARQUIVO:
        return "FIM_DE_ARQUIVO";
    default:
        return "NULL"; 
    }

    return "NULL";
}

#endif