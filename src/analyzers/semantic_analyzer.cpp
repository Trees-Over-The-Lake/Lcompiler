#ifndef ANALYZERS_SEMANTIC_ANALYZER
#define ANALYZERS_SEMANTIC_ANALYZER

#include"../symbol_table/symbol_table.cpp"
#include"../error_manager/cerror_manager.cpp"

/**
 * @brief Verifies if id is a basicConstant
 * @param id const TokenID 
 * @return boolean
*/
bool id_is_basic_const(const TokenID id) {
    return (id == TRUE || id == FALSE);
}

/**
 * @brief Verifies with a identifier already exist 
 * @param t Token_pointer& that is being verified
 * @param new_token_class TokenClass that is being attributed for t
 * @return CErrorType that represent wich error happend
*/
CErrorType verify_token_identification(Token_pointer& t, TokenClass new_token_class) {

    CErrorType erro = NenhumErro;

    if (t->get_classe() == NENHUM) 
        t->set_classe(new_token_class);

    else 
        erro = IdentificadorJaDeclarado;

    return erro;
}

/**
 * @brief Verifies with a identifier wasn't initialized  
 * @param t Token_pointer& that is being verified
 * @return CErrorType that represent wich error happend
*/
CErrorType verify_if_token_already_initialized(Token_pointer& t) {

    CErrorType erro = NenhumErro;

    if (t->get_classe() == NENHUM) 
        erro = IdentificadorNaoDeclarado;

    return erro;
}

/**
 * @brief Verifies if a token is compatible with a certain type
 * @param t Token_pointer& that is being verified
 * @return CErrorType that represent wich error happend
*/
CErrorType verify_type_compatibility(Token_pointer& t, TokenType expected_type) {

    CErrorType erro = NenhumErro;

    if (t->get_tipo() != expected_type)
        erro = TiposIncompativeis;

    return erro;
}

/**
 * @brief Verifies if a token is incompatible with a certain type
 * @param t Token_pointer& that is being verified
 * @param not_expected_type TokenType not expected for t
 * @return CErrorType that represent wich error happend
*/
CErrorType verify_type_incompatibility(Token_pointer& t, TokenType not_expected_type) {

    CErrorType erro = NenhumErro;

    if (t->get_tipo() == not_expected_type)
        erro = TiposIncompativeis;

    return erro;
}

/**
 * @brief Verifies if a token is compatible with a certain class
 * @param t Token_pointer& that is being verified
 * @param expected_type TokenType expected for t
 * @return CErrorType that represent wich error happend
*/
CErrorType verify_class_compatibility(Token_pointer& t, TokenClass expected_type) {

    CErrorType erro = NenhumErro;

    if (t->get_classe() != expected_type)
        erro = ClasseDeIdentificadorIncompativel;

    return erro;
}

/**
 * @brief Sets a new type for the token
 * @param t Token_pointer& that is being selected
 * @param new_type TokenType for t
*/
void atribute_new_type(Token_pointer& t, TokenType new_type) {
    t->set_tipo(new_type);
}

/**
 * @brief Verifies if a token is a number
 * @param t Token_pointer& that is being verified
 * @return CErrorType that represent wich error happend
*/
CErrorType verify_token_is_number(Token_pointer& t) {

    CErrorType erro = NenhumErro;

    if (t->get_tipo() != INTEIRO && t->get_tipo() != REAL)
        erro = TiposIncompativeis;

    return erro;
}

/**
 * @brief Compare two tokens based on their types
 * @param t Token_pointer& that is being verified
 * @param t1 Token_pointer& that is being verified
 * @return CErrorType that represent wich error happend
*/
CErrorType compare_tokens(Token_pointer& t, Token_pointer& t1) {
    CErrorType erro = NenhumErro;
    
    if(t->get_tipo() != t1->get_tipo()) {
        if(!(t->get_tipo() == REAL && t1->get_tipo() == INTEIRO) 
        && !(t->get_tipo() == LOGICO && id_is_basic_const(t1->get_id()))
        && !(t->get_tipo() == CARACTERE && t1->get_tipo() == HEXADECIMAL) ) {
            erro = TiposIncompativeis;
        }
    } 

    return erro;
}

/**
 * @brief Function that changes the value of destination for source
 * @param destination Token_pointer& that is going to be changed
 * @param source Token_pointer& that is going to be the source 
*/
void attribute_tokens(Token_pointer& destination, Token_pointer& source) {
    destination->set_tipo(source->get_tipo());
    destination->set_endereco(source->get_endereco());
    destination->set_id(source->get_id());
}

#endif