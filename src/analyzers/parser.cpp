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
    bool is_basic_const(const TokenID* id);
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
    Token_pointer producaoM();
    Token_pointer producaoN();
    Token_pointer producaoO();
    Token_pointer producaoP();
    Token_pointer producaoQ();
    Token_pointer producaoR();
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
    return *token_id == curr_token_id || (*token_id == CONST && is_basic_const(&curr_token_id));
}

bool Parser::is_basic_const(const TokenID* id) {
    return (*id == TRUE || *id == FALSE);
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

    Token_pointer identification = curr_token;

    casa_token(IDENTIFICADOR);

    error = verify_token_identification(identification,VARIAVEL);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identification->get_lexema()});

    if(curr_token_id == ATRIBUICAO || curr_token_id == WALRUS) {

        casa_token(curr_token_id);

        Token_pointer constant = std::make_shared <Token>();

        if(curr_token_id == SUBTRACAO) {
            
            casa_token(curr_token_id);

            constant = curr_token;
            
            error = verify_atribute_compatibility(constant);
            if(error != NenhumErro){
                throw_compiler_error(error,{curr_line,constant->get_lexema()});
            }
        }

        constant = curr_token;

        casa_token(CONST);

        error = compare_tokens(identification,constant);
        if(error != NenhumErro){
            throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
        }
    }

    while ( curr_token_id == VIRGULA) {

        casa_token(VIRGULA);

        identification = curr_token;
            
        casa_token(IDENTIFICADOR);

        error = verify_token_identification(identification,VARIAVEL);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,identification->get_lexema()});

        if(curr_token_id == ATRIBUICAO || curr_token_id == WALRUS) {

            casa_token(curr_token_id);

            Token_pointer constant = std::make_shared <Token>();

            if(curr_token_id == SUBTRACAO) {
                
                casa_token(curr_token_id);
                
                constant = curr_token;
                
                error = verify_atribute_compatibility(constant);
                if(error != NenhumErro){
                    throw_compiler_error(error,{curr_line,constant->get_lexema()});
                }

            }

            constant = curr_token;

            casa_token(CONST);

            error = compare_tokens(identification,constant);
            if(error != NenhumErro){
                throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
            }
        }
    }

    casa_token(PONTO_VIRGULA);
}

void Parser::producaoC() {

    switch (curr_token_id)
    {
        case INT:
            casa_token(INT);
            atribute_new_type(curr_token,INTEIRO);
            break;
        case FLOAT:
            casa_token(FLOAT);
            atribute_new_type(curr_token,REAL);
            break;
        case CHAR:
            casa_token(CHAR);
            atribute_new_type(curr_token,CARACTERE);
            break;
        case STRING:
            casa_token(STRING);
            atribute_new_type(curr_token,TEXTO);
            break;
        case BOOLEAN:
            casa_token(BOOLEAN);
            atribute_new_type(curr_token,LOGICO);
            break;
        default:
            break;
    }

}

void Parser::producaoD() {

    CErrorType error = NenhumErro;

    casa_token(CONST);

    Token_pointer identifier = curr_token;

    casa_token(IDENTIFICADOR);

    error = verify_token_identification(identifier,CONSTANTE);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    casa_token(ATRIBUICAO);

    Token_pointer constant = std::make_shared <Token>();

    if(curr_token_id == SUBTRACAO) {
                
        casa_token(curr_token_id);

        constant = curr_token;
        
        error = verify_atribute_compatibility(constant);
        if(error != NenhumErro){
            throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
        }
    }

    constant = curr_token;

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

    Token_pointer f_token = std::make_shared <Token>();
    Token_pointer f1_token = std::make_shared <Token>();
    CErrorType error = NenhumErro;
    bool identifier_is_string = false;

    Token_pointer identifier = curr_token;

    casa_token(IDENTIFICADOR);

    error = verify_if_token_already_initialized(identifier);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    error = verify_class_compatibility(identifier, VARIAVEL);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    if(curr_token_id == ABRE_COLCHETES) {
        
        casa_token(curr_token_id);

        error = verify_type_compatibility(identifier, TEXTO);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,identifier->get_lexema()});
        
        else 
            identifier_is_string = true;
        

        f_token = producaoM();

        error = verify_type_compatibility(f_token, INTEIRO);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,f_token->get_lexema()});

        casa_token(FECHA_COLCHETES);
    }

    casa_token(ATRIBUICAO);

    f1_token = producaoM();

    if (identifier_is_string) {

        error = verify_type_compatibility(f1_token, CARACTERE);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,f1_token->get_lexema()});
    
    } else {

        error = compare_tokens(identifier,f1_token);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,f_token->get_lexema()});
    }

    casa_token(PONTO_VIRGULA);
}
void Parser::producaoG(){

    CErrorType error = NenhumErro;
    Token_pointer g_token = std::make_shared <Token>();

    casa_token(WHILE);

    g_token = producaoM();

    producaoH();

    error = verify_type_compatibility(g_token, LOGICO);
    if (error != NenhumErro) {
        throw_compiler_error(error,{curr_line,g_token->get_lexema()});
    }

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

    CErrorType error = NenhumErro;
    Token_pointer i_token = std::make_shared <Token>();

    casa_token(IF);

    casa_token(ABRE_PARANTESES);

    i_token = producaoM();

    error = verify_type_compatibility(i_token, LOGICO);
    if (error != NenhumErro) {
        throw_compiler_error(error,{curr_line,i_token->get_lexema()});
    }
    
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

    CErrorType error = NenhumErro;

    casa_token(READLN);

    casa_token(ABRE_PARANTESES);

    Token_pointer identifier = curr_token;

    casa_token(IDENTIFICADOR);

    error = verify_if_token_already_initialized(identifier);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    error = verify_class_compatibility(identifier, VARIAVEL);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    error = verify_type_compatibility(identifier, LOGICO);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    casa_token(FECHA_PARANTESES);

    casa_token(PONTO_VIRGULA);
}
void Parser::producaoL(){

    CErrorType error = NenhumErro;
    Token_pointer l_token = std::make_shared <Token>();

    if (curr_token_id == WRITE) 
        casa_token(curr_token_id);

    else 
        casa_token(WRITELN);


    casa_token(ABRE_PARANTESES);

    l_token = producaoM();

    error = verify_type_compatibility(l_token, LOGICO);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,l_token->get_lexema()});

    while(curr_token_id == VIRGULA) {

        casa_token(curr_token_id);

        l_token = producaoM();

        error = verify_type_compatibility(l_token, LOGICO);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,l_token->get_lexema()});

    }

    casa_token(FECHA_PARANTESES);
    casa_token(PONTO_VIRGULA);
}
Token_pointer Parser::producaoM(){

    Token_pointer m_token = std::make_shared <Token>();
    Token_pointer n_token = std::make_shared <Token>();

    TokenID operation;

    m_token = producaoN();

    while(curr_token_id == IGUAL || curr_token_id == DIFERENTE || curr_token_id == MENOR || curr_token_id == MENOR_IGUAL || curr_token_id == MAIOR || curr_token_id == MAIOR_IGUAL) {

        operation = curr_token->get_id();

        casa_token(curr_token_id);
        
        n_token = producaoN();

        if (operation == IGUAL && m_token->get_tipo() == TEXTO && n_token->get_tipo() == TEXTO) {

            m_token->set_tipo(LOGICO);
        } else if (m_token->get_tipo() == CARACTERE && n_token->get_tipo() == CARACTERE) {

            m_token->set_tipo(LOGICO);
        } else if ((m_token->get_tipo() == REAL || m_token->get_tipo() == INTEIRO) && 
        (n_token->get_tipo() == REAL || n_token->get_tipo() == INTEIRO)) {

            m_token->set_tipo(LOGICO);
        } else {

            throw_compiler_error(TiposIncompativeis,{curr_line});
        }

    }

    return m_token;
}
Token_pointer Parser::producaoN(){

    Token_pointer n_token = std::make_shared <Token>();
    Token_pointer n1_token = std::make_shared <Token>();
    CErrorType error = NenhumErro;
    bool n_flag = false;
    TokenID operation;
    
    if(curr_token_id == SOMA || curr_token_id == SUBTRACAO) {
        casa_token(curr_token_id);
        n_flag = true;
    }

    n_token = producaoO();

    if (n_flag) {

        error = verify_atribute_compatibility(n_token);
        if (error != NenhumErro) {
            throw_compiler_error(TiposIncompativeis,{curr_line});

        } if (n_token->get_tipo() == REAL) {

        } else {

        }
    }

    while(curr_token_id == SOMA || curr_token_id == SUBTRACAO || curr_token_id == OR) {

        operation = curr_token->get_id();

        casa_token(curr_token_id);
        n1_token = producaoO();

        if (operation == OR) {
            if (n_token->get_tipo() != LOGICO || n1_token->get_tipo() != LOGICO) {
                throw_compiler_error(TiposIncompativeis,{curr_line});
            } else {

                if ((n_token->get_tipo() != REAL && n_token->get_tipo() != INTEIRO) 
                || (n1_token->get_tipo() != REAL && n1_token->get_tipo() != INTEIRO)) {
                    throw_compiler_error(TiposIncompativeis,{curr_line});
                }
            }
        }
    }

    return n_token;
}
Token_pointer Parser::producaoO(){

    Token_pointer o_token = std::make_shared <Token>();
    Token_pointer o1_token = std::make_shared <Token>();
    CErrorType error = NenhumErro;
    TokenID operation;

    o_token = producaoP();

    while(curr_token_id == MULTIPLICACAO || curr_token_id == DIVISAO || curr_token_id == MOD || curr_token_id == DIVISAO || curr_token_id == DIV) {

        operation = curr_token_id;

        casa_token(curr_token_id);

        o1_token = producaoP();

        if (operation == AND) {
            if (o_token->get_tipo() != LOGICO || o1_token->get_tipo() != LOGICO) {
                throw_compiler_error(TiposIncompativeis,{curr_line});
            }
        } else if (operation == MULTIPLICACAO || operation == DIVISAO) {
            if((o_token->get_tipo() != REAL && o_token->get_tipo() != INTEIRO) 
            || (o1_token->get_tipo() != REAL && o1_token->get_tipo() != INTEIRO)) {
                throw_compiler_error(TiposIncompativeis,{curr_line});
            } else {
                if (o_token->get_tipo() != o1_token->get_tipo()) {
                    o_token->set_tipo(REAL);

                    if (operation == MULTIPLICACAO) {
                        
                        if(o1_token->get_tipo() == REAL) {

                        } else {

                        }
                    } else {

                    }
                } else {
                    if( o_token->get_tipo() == INTEIRO && operation == DIVISAO) {
                        throw_compiler_error(TiposIncompativeis,{curr_line});
                    }
                }
            }
        } else {
            if (o_token->get_tipo() != INTEIRO || o1_token->get_tipo() != INTEIRO ) {
                throw_compiler_error(TiposIncompativeis,{curr_line});
            }
        }
    }

    return o_token;
}
Token_pointer Parser::producaoP(){

    CErrorType error = NenhumErro;
    Token_pointer p_token = std::make_shared <Token>();

    if (curr_token_id == NEGACAO) {
        casa_token(curr_token_id);

        p_token = producaoQ();

        error = verify_type_compatibility(p_token,LOGICO);
        if (error != NenhumErro) {
            throw_compiler_error(error,{curr_line});
        } else {

        }
    } else {
        p_token = producaoQ();
    }

    return p_token;
}
Token_pointer Parser::producaoQ(){

    Token_pointer q_token = std::make_shared <Token>();

    if (curr_token_id == FLOAT) {

        casa_token(FLOAT);
        casa_token(ABRE_PARANTESES);

        q_token = producaoM();

        if(q_token->get_tipo() != REAL && q_token->get_tipo() != INTEIRO) {
            throw_compiler_error(TiposIncompativeis,{curr_line});
        } else {

            if (q_token->get_tipo() == INTEIRO) {
                // geracao de codigo
            }

            q_token->set_tipo(REAL);
        }

        casa_token(FECHA_PARANTESES);
    } if (curr_token_id == INT) {

        casa_token(INT);
        casa_token(ABRE_PARANTESES);

        q_token = producaoM();

        if(q_token->get_tipo() != REAL && q_token->get_tipo() != INTEIRO) {
            throw_compiler_error(TiposIncompativeis,{curr_line});
        } else {

            if (q_token->get_tipo() == REAL) {
                // geracao de codigo
            }

            q_token->set_tipo(INTEIRO);
        }

        casa_token(FECHA_PARANTESES);
    }  
    else {

        q_token = producaoR();
    }

    return q_token;
}
Token_pointer Parser::producaoR(){

    CErrorType error = NenhumErro;
    Token_pointer r_token = std::make_shared <Token>();
    Token_pointer constante = std::make_shared <Token>();

    if (curr_token_id == ABRE_PARANTESES) {
        
        casa_token(curr_token_id);

        r_token = producaoM();

        casa_token(FECHA_PARANTESES);
    } else if( curr_token_id == CONST || is_basic_const(&curr_token_id)) {

        constante = curr_token;

        casa_token(curr_token_id);

        r_token = constante;

    } else {

        Token_pointer identifier = curr_token;

        casa_token(IDENTIFICADOR);

        error = verify_if_token_already_initialized(identifier);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,identifier->get_lexema()});

        if (curr_token_id == ABRE_COLCHETES) {

            casa_token(curr_token_id);

            error = verify_type_compatibility(identifier,TEXTO);
            if (error != NenhumErro) {
                throw_compiler_error(error,{curr_line});
            }

            r_token = producaoM();

            error = verify_type_compatibility(r_token, INTEIRO);
            if (error != NenhumErro) 
                throw_compiler_error(error,{curr_line,r_token->get_lexema()});

            casa_token(FECHA_COLCHETES);
        }

        r_token = identifier;
    }

    return r_token;
}

#endif