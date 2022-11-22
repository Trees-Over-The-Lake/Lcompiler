#ifndef ANALYZERS_SEMANTIC_ANALYZER
#define ANALYZERS_SEMANTIC_ANALYZER

#include"../symbol_table/symbol_table.cpp"
#include"../error_manager/cerror_manager.cpp"

CErrorType verify_token_identification(Token_pointer& t, TokenClass new_token_class) {

    CErrorType erro = NenhumErro;

    if (t->get_classe() == NENHUM) 
        t->set_classe(new_token_class);

    else 
        erro = IdentificadorJaDeclarado;

    return erro;
}

CErrorType verify_if_token_already_initialized(Token_pointer& t) {

    CErrorType erro = NenhumErro;

    if (t->get_classe() == NENHUM) 
        erro = IdentificadorNaoDeclarado;

    return erro;
}

CErrorType verify_type_compatibility(Token_pointer& t, TokenType expected_type) {

    CErrorType erro = NenhumErro;

    if (t->get_tipo() != expected_type)
        erro = TiposIncompativeis;

    return erro;
}

CErrorType verify_type_incompatibility(Token_pointer& t, TokenType not_expected_type) {

    CErrorType erro = NenhumErro;

    if (t->get_tipo() == not_expected_type)
        erro = TiposIncompativeis;

    return erro;
}

CErrorType verify_class_compatibility(Token_pointer& t, TokenClass expected_type) {

    CErrorType erro = NenhumErro;

    if (t->get_classe() != expected_type)
        erro = ClasseDeIdentificadorIncompativel;

    return erro;
}

void atribute_new_type(Token_pointer& t, TokenType new_type) {
    t->set_tipo(new_type);
}

CErrorType verify_token_is_number(Token_pointer& t) {

    CErrorType erro = NenhumErro;

    if (t->get_tipo() != INTEIRO && t->get_tipo() != REAL)
        erro = TiposIncompativeis;

    return erro;
}

CErrorType compare_tokens(Token_pointer& t, Token_pointer& t1) {
    CErrorType erro = NenhumErro;

    if(t->get_tipo() != t1->get_tipo()) {

        if(t->get_tipo() == REAL && t1->get_tipo() == INTEIRO) {

        } else {
            erro = TiposIncompativeis;
        }

    } 

    return erro;
}

#endif