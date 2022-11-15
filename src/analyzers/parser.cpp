#ifndef ANALYZERS_PARSER_CPP
#define ANALYZERS_PARSER_CPP

#include"../symbol_table/symbol_table.cpp"
#include"../error_manager/cerror_manager.cpp"
#include"lexical_analyzer.cpp"
#include"semantic_analyzer.cpp"

class Parser
{
private:
    SymbolTable symbol_table;
    Token_pointer curr_token;
    TokenID curr_token_id;
    TokenClass curr_class;

    bool token_error;
    CErrorType cerror_type;
    std::string error_information;
    std::string curr_line;
    
    Token prev_token;

    LexicalAnalyzer* la;
public:
    Parser(LexicalAnalyzer* la);
    ~Parser();
    void set_curr_token(Token_pointer curr_token, int curr_line);
    void casa_token(TokenID token_id);
    bool tokens_are_a_match(const TokenID* token_id);
    void producaoS();
    void producaoA();
    void producaoB();
    void producaoC();
    void producaoD();
    void producaoE();
    void producaoF();
    void producaoG();
    void producaoH();
    void producaoI();
    void producaoJ();
    void producaoK();
    void producaoL();
    void producaoM(Token_pointer& index);
    void producaoN(Token_pointer& index);
    void producaoO(Token_pointer& index);
    void producaoP(Token_pointer& index);
    void producaoQ(Token_pointer& index);
    void producaoR(Token_pointer& index);
};

Parser::Parser(LexicalAnalyzer* la)
{
    this->la = la;
    this->symbol_table = SymbolTable();
    this->token_error = false;
    this->prev_token = Token();
}

Parser::~Parser()
{

}

void Parser::casa_token(TokenID token_id) {

    if (tokens_are_a_match(&token_id))
    {
        if(curr_class == VARIAVEL || curr_class == CONSTANTE) {
            prev_token = curr_token->clone();
        }
        
        if(token_error) {
            throw_compiler_error(cerror_type,{curr_line, error_information});
        }

        Token_pointer t = la->get_next_token();
        set_curr_token(t,la->get_curr_line_number());
    }
    else {

        if(curr_token->get_id() == FIM_DE_ARQUIVO) 
            throw_compiler_error(FimDeArquivoNaoEsperado, 
                            {curr_line});
        else 
            throw_compiler_error(TokenNaoEsperado,
                                {curr_line, curr_token->get_lexema()});
    }
    
}

bool Parser::tokens_are_a_match(const TokenID* token_id) {
    return *token_id == curr_token_id || (*token_id == CONST && (curr_token_id == TRUE || curr_token_id == FALSE));
}

void Parser::set_curr_token(Token_pointer curr_token, int curr_line) {
    this->curr_token = curr_token;
    this->curr_class = this->curr_token->get_classe();
    this->curr_token_id = this->curr_token->get_id();
    this->curr_line = std::to_string(curr_line);
}

void Parser::producaoS() {

    while(curr_token_id != FIM_DE_ARQUIVO) {

        switch (curr_token_id)
        {
            case INT:
            case FLOAT:
            case CHAR:
            case STRING:
            case BOOLEAN:
            case CONST:
                producaoA();
                break;
        
            default:
                producaoE();
                break;
        }

    }

    casa_token(FIM_DE_ARQUIVO);

}

void Parser::producaoA() {
    switch (curr_token_id)
    {
        case CONST:
            producaoD();
        break;

        default:
            producaoB();
        break;
    }

}

void Parser::producaoB() {

    CErrorType error = NenhumErro;

    producaoC();

    error = SemanticAnalyzer_verify_token_identification(curr_token,VARIAVEL);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,curr_token->get_lexema()});

    casa_token(IDENTIFICADOR);

    if(curr_token_id == ATRIBUICAO || curr_token_id == WALRUS) {

        casa_token(curr_token_id);

        if(curr_token_id == SUBTRACAO) {
            
            casa_token(curr_token_id);
            
            error = SemanticAnalyzer_atribute_compatibility(curr_token);

            if(error != NenhumErro){
                throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
            }

        }

        casa_token(CONST);
    }

    while ( curr_token_id == VIRGULA) {

        casa_token(VIRGULA);

        error = SemanticAnalyzer_verify_token_identification(curr_token,VARIAVEL);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
            
        casa_token(IDENTIFICADOR);

        if(curr_token_id == ATRIBUICAO || curr_token_id == WALRUS) {

            casa_token(curr_token_id);

            if(curr_token_id == SUBTRACAO) {
                
                casa_token(curr_token_id);
                
                error = SemanticAnalyzer_atribute_compatibility(curr_token);

                if(error != NenhumErro){
                    throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
                }

            }

            casa_token(CONST);
        }
    }

    casa_token(PONTO_VIRGULA);
}

void Parser::producaoC() {

    switch (curr_token_id)
    {
        case INT:
            casa_token(INT);
            SemanticAnalyzer_atribute_new_type(curr_token,INTEIRO);
            break;
        case FLOAT:
            casa_token(FLOAT);
            SemanticAnalyzer_atribute_new_type(curr_token,REAL);
            break;
        case CHAR:
            casa_token(CHAR);
            SemanticAnalyzer_atribute_new_type(curr_token,CARACTERE);
            break;
        case STRING:
            casa_token(STRING);
            SemanticAnalyzer_atribute_new_type(curr_token,TEXTO);
            break;
        case BOOLEAN:
            casa_token(BOOLEAN);
            SemanticAnalyzer_atribute_new_type(curr_token,LOGICO);
            break;
        default:
            break;
    }

}

void Parser::producaoD() {

    CErrorType error = NenhumErro;

    casa_token(CONST);
    
    error = SemanticAnalyzer_verify_token_identification(curr_token,CONSTANTE);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,curr_token->get_lexema()});

    casa_token(IDENTIFICADOR);

    casa_token(ATRIBUICAO);

    if(curr_token_id == SUBTRACAO) {
                
        casa_token(curr_token_id);
        
        error = SemanticAnalyzer_atribute_compatibility(curr_token);

        if(error != NenhumErro){
            throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
        }

    }

    casa_token(CONST);
    casa_token(PONTO_VIRGULA);
}

void Parser::producaoE() {


    if (curr_token_id == PONTO_VIRGULA) {
        casa_token(curr_token_id);
    }
    else 
        switch (curr_token_id)
        {
            case WHILE:
                producaoG();
                break;
            case IF:
                producaoI();
                break;
            case READLN:
                producaoK();
                break;
            case WRITE:           
            case WRITELN:
                producaoL();        
                break;

            default:
                producaoF();
                break;
        }

}

void Parser::producaoF(){

    Token_pointer index = std::make_shared <Token>();
    CErrorType error = NenhumErro;

    error = SemanticAnalyzer_verify_if_token_already_initialized(curr_token);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,curr_token->get_lexema()});

    error = SemanticAnalyzer_verify_class_Compatibility(curr_token, VARIAVEL);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,curr_token->get_lexema()});

    error = SemanticAnalyzer_verify_type_compatibility(curr_token, TEXTO);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,curr_token->get_lexema()});

    casa_token(IDENTIFICADOR);

    if(curr_token_id == ABRE_COLCHETES) {
        
        casa_token(curr_token_id);

        producaoM(index);

        error = SemanticAnalyzer_verify_type_compatibility(index, INTEIRO);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,index->get_lexema()});

        casa_token(FECHA_COLCHETES);
    }

    casa_token(WALRUS);

    producaoM(index);

    /*
    error = SemanticAnalyzer_verify_type_compatibility(index, INTEIRO);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,index->get_lexema()});
    */

    casa_token(PONTO_VIRGULA);
}
void Parser::producaoG(){
    Token_pointer index = std::make_shared <Token>();

    casa_token(WHILE);

    producaoM(index);

    producaoH();

}
void Parser::producaoH(){

    if (curr_token_id == ABRE_CHAVES) {
        casa_token(curr_token_id);

        while(curr_token_id != FECHA_CHAVES) {
            producaoE();
        }

        casa_token(FECHA_CHAVES);
    } else {

        producaoE();
    }

}
void Parser::producaoI(){
    Token_pointer index = std::make_shared <Token>();

    casa_token(IF);

    casa_token(ABRE_PARANTESES);

    producaoM(index);
    
    casa_token(FECHA_PARANTESES);

    producaoJ();

    if (curr_token_id == ELSE) {
        casa_token(ELSE);
        producaoJ();
    }
}
void Parser::producaoJ(){
    if (curr_token_id == ABRE_CHAVES) {
        
        casa_token(ABRE_CHAVES);

        while (curr_token_id != FECHA_CHAVES) 
            producaoE();
    
        casa_token(FECHA_CHAVES);
    } else 
        producaoE();
    
}
void Parser::producaoK(){

    casa_token(READLN);

    casa_token(ABRE_PARANTESES);

    casa_token(IDENTIFICADOR);

    casa_token(FECHA_PARANTESES);

    casa_token(PONTO_VIRGULA);
}
void Parser::producaoL(){
    Token_pointer index = std::make_shared <Token>();

    if (curr_token_id == WRITE) {
        casa_token(curr_token_id);
    } else {
        casa_token(WRITELN);
    }

    casa_token(ABRE_PARANTESES);

    producaoM(index);

    while(curr_token_id == VIRGULA) {
        casa_token(curr_token_id);

        producaoM(index);
    }

    casa_token(FECHA_PARANTESES);
    casa_token(PONTO_VIRGULA);
}
void Parser::producaoM(Token_pointer& index){

    producaoN(index);

    while(curr_token_id == IGUAL || curr_token_id == DIFERENTE || curr_token_id == MENOR || curr_token_id == MENOR_IGUAL || curr_token_id == MAIOR || curr_token_id == MAIOR_IGUAL) {

        casa_token(curr_token_id);
        
        producaoN(index);
    }

}
void Parser::producaoN(Token_pointer& index){

    if(curr_token_id == SOMA || curr_token_id == SUBTRACAO) {
        casa_token(curr_token_id);
    }

    producaoO(index);

    while(curr_token_id == SOMA || curr_token_id == SUBTRACAO || curr_token_id == OR) {

        casa_token(curr_token_id);
        producaoO(index);
    }

}
void Parser::producaoO(Token_pointer& index){

    producaoP(index);

    while(curr_token_id == MULTIPLICACAO || curr_token_id == DIVISAO || curr_token_id == MOD || curr_token_id == DIVISAO || curr_token_id == DIV) {

        casa_token(curr_token_id);

        producaoP(index);
    }

}
void Parser::producaoP(Token_pointer& index){

    if (curr_token_id == NEGACAO) {
        casa_token(curr_token_id);
    } 

    producaoQ(index);
}
void Parser::producaoQ(Token_pointer& index){

    if (curr_token_id == FLOAT || curr_token_id == INT) {

        casa_token(curr_token_id);
        casa_token(ABRE_PARANTESES);

        producaoM(index);

        casa_token(FECHA_PARANTESES);
    } else {

        producaoR(index);
    }
}
void Parser::producaoR(Token_pointer& index){

    if (curr_token_id == ABRE_PARANTESES) {
        
        casa_token(curr_token_id);

        producaoM(index);

        casa_token(FECHA_PARANTESES);
    } else if( curr_token_id == CONST) {
        //index = curr_token;
        
        casa_token(curr_token_id);

    } else {

        casa_token(IDENTIFICADOR);

        if (curr_token_id == ABRE_COLCHETES) {

            casa_token(curr_token_id);

            //index = curr_token;

            producaoM(index);

            casa_token(FECHA_COLCHETES);
        }
    }
}

#endif