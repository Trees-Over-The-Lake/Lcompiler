#ifndef SEMANTIC_ANALYZER
#define SEMANTIC_ANALYZER

#include"../symbol_table/token/token.cpp"
#include"../error_manager/cerror_manager.cpp"

CErrorType verifyIfAlreadyDeclaredToken(Token* t) {

    CErrorType erro = NenhumErro;

    if (t->get_classe() == NENHUM) 
        t->set_classe(VARIAVEL);
    else 
        erro = IdentificadorJaDeclarado;

    return erro;
}

CErrorType verifyTokenCompatibility(Token* t, TokenType expected_type) {

    CErrorType erro = NenhumErro;

    if (t->get_tipo() != expected_type) {
        erro = TiposIncompativeis;
    }
}

#endif