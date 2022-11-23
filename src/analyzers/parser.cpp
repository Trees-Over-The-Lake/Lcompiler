#ifndef ANALYZERS_PARSER_CPP
#define ANALYZERS_PARSER_CPP

#include"../symbol_table/symbol_table.cpp"
#include"../error_manager/cerror_manager.cpp"
#include"../generator/code_generator.cpp"
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
        CodeGenerator* cg;
    public:
        Parser(LexicalAnalyzer* la, CodeGenerator* cg);
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

Parser::Parser(LexicalAnalyzer* la, CodeGenerator* cg)
{
    this->la = la;
    this->cg = cg;
    this->symbol_table = SymbolTable();
    this->token_error = false;
    this->prev_token = Token();
}

Parser::~Parser()
{

}

/**
 * @brief Verify if the curr_token matches the expected_id
 * 
 * @param expected_id, is the current id being verified in the parser's grammar
*/
void Parser::casa_token(TokenID expected_id) {

    if (tokens_are_a_match(&expected_id))
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

/**
 * @brief Verify if the received id matches the current id
 * 
 * Obs.: There is also the case where is the curr_token is a basic const (True or False)
 * 
 * @param token_id the token to be verified
 * @return true if the tokens are a match, false if it does not
*/
bool Parser::tokens_are_a_match(const TokenID* token_id) {
    return *token_id == curr_token_id || (*token_id == CONST && is_basic_const(&curr_token_id));
}

/**
 * @brief Check if the id is a basic const (True or False)
 * 
 * @param id is to be verified
 * @return true if the id is a basic const, false if it is not
*/
bool Parser::is_basic_const(const TokenID* id) {
    return (*id == TRUE || *id == FALSE);
}

/**
 * @brief update the parser with lexical analyzer information
 * 
 * @param curr_token, is the lastest token read by the lexical analyzer
 * @param curr_line, the line in which the token was read from.
*/
void Parser::set_curr_token(Token_pointer curr_token, int curr_line) {
    this->curr_token = curr_token;
    this->curr_class = this->curr_token->get_classe();
    this->curr_token_id = this->curr_token->get_id();
    this->curr_line = std::to_string(curr_line);
}

/**
 * @brief S -> {(A | E)}* fim_arquivo
*/
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

/**
 * @brief A -> (B | D)
*/
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

/**
 * @brief B -> C identifier [:= [-]basicConst]{, identifier [:= [-]basicConst]}*; 
*/
void Parser::producaoB() {

    CErrorType error = NenhumErro;
    bool negate = false;

    producaoC();

    Token_pointer identification = curr_token;
    TokenType identificationType = curr_token->get_tipo();

    casa_token(IDENTIFICADOR);

    // [1] [6]
    error = verify_token_identification(identification,VARIAVEL);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identification->get_lexema()});

    cg->allocate_space_for_token(identification);

    if(curr_token_id == WALRUS) {

        casa_token(WALRUS);

        Token_pointer constant = std::make_shared <Token>();

        if(curr_token_id == SUBTRACAO) {
            
            casa_token(curr_token_id);

            // [7]
            negate = true;

            constant = curr_token;
            
            // [8]
            error = verify_token_is_number(constant);
            if(error != NenhumErro){
                throw_compiler_error(error,{curr_line,constant->get_lexema()});
            }
        }

        constant = curr_token;

        casa_token(CONST);

        // [9]
        error = compare_tokens(identification,constant);
        if(error != NenhumErro)
            throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
        else
            cg->store_token_on_data_section(identification,constant,negate);
    }
        
    while ( curr_token_id == VIRGULA) {

        casa_token(VIRGULA);

        identification = curr_token;
        curr_token->set_tipo(identificationType);
            
        casa_token(IDENTIFICADOR);

        // [1] [6]
        error = verify_token_identification(identification,VARIAVEL);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,identification->get_lexema()});

        cg->allocate_space_for_token(identification);

        if(curr_token_id == WALRUS) {

            casa_token(WALRUS);

            Token_pointer constant = std::make_shared <Token>();

            if(curr_token_id == SUBTRACAO) {
                
                casa_token(curr_token_id);

                // [7]
                negate = true;
                
                constant = curr_token;
                
                // [8]
                error = verify_token_is_number(constant);
                if(error != NenhumErro)
                    throw_compiler_error(error,{curr_line,constant->get_lexema()});
                
            }

            constant = curr_token;

            casa_token(CONST);

            // [9]
            error = compare_tokens(identification,constant);
            if(error != NenhumErro)
                throw_compiler_error(error,{curr_line,curr_token->get_lexema()});

            else 
                cg->store_token_on_data_section(identification,constant,negate);  
        }
    }

    casa_token(PONTO_VIRGULA);
}

/**
 * @brief C -> (int | float | string | boolean | char)
*/
void Parser::producaoC() {

    // [5]
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

/**
 * @brief D -> const identifier = [-]basicConst; // declaracao const
*/
void Parser::producaoD() {

    CErrorType error = NenhumErro;
    bool negate = false;

    casa_token(CONST);

    Token_pointer identifier = curr_token;

    casa_token(IDENTIFICADOR);

    // [2]
    error = verify_token_identification(identifier,CONSTANTE);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    casa_token(IGUAL);

    Token_pointer constant = std::make_shared <Token>();

    if(curr_token_id == SUBTRACAO) {
                
        casa_token(curr_token_id);

        // [7]
        negate = true;

        constant = curr_token;
        
        // [8]
        error = verify_token_is_number(constant);
        if(error != NenhumErro){
            throw_compiler_error(error,{curr_line,curr_token->get_lexema()});
        }
    }

    constant = curr_token;

    casa_token(CONST);

    // [10]
    identifier->set_tipo(constant->get_tipo());
    cg->allocate_space_for_const(identifier,constant);

    casa_token(PONTO_VIRGULA);
}

/**
 * @brief E -> [(F | G | I | K | L | S)];
*/
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

/**
 * @brief identifier[[M]] := M // atribuicao
*/
void Parser::producaoF(){

    Token_pointer m_token = std::make_shared <Token>();
    Token_pointer m1_token = std::make_shared <Token>();
    CErrorType error = NenhumErro;
    bool is_accessing_string_index = false;

    Token_pointer identifier = curr_token;

    casa_token(IDENTIFICADOR);

    // [3]
    error = verify_if_token_already_initialized(identifier);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    // [4]
    error = verify_class_compatibility(identifier, VARIAVEL);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    if(curr_token_id == ABRE_COLCHETES) {
        
        casa_token(curr_token_id);

        // [11]
        error = verify_type_compatibility(identifier, TEXTO);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,identifier->get_lexema()});
        
        else 
            is_accessing_string_index = true;
        

        m_token = producaoM();
        
        cg->reset_temporary_counter();

        // [12]
        error = verify_type_compatibility(m_token, INTEIRO);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,m_token->get_lexema()});

        casa_token(FECHA_COLCHETES);
    }

    casa_token(WALRUS);

    m1_token = producaoM();

    cg->reset_temporary_counter();

    // [13]
    if (is_accessing_string_index) {

        error = verify_type_compatibility(m1_token, CARACTERE);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,m1_token->get_lexema()});
    
    } else {

        error = compare_tokens(identifier,m1_token);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,m_token->get_lexema()});

    }

    cg->variable_atribution(identifier,m_token,m1_token,is_accessing_string_index);

    casa_token(PONTO_VIRGULA);
}

/**
 * @brief G -> while (M) H // while
*/
void Parser::producaoG(){

    CErrorType error = NenhumErro;
    Token_pointer m_token = std::make_shared <Token>();

    casa_token(WHILE);

    casa_token(ABRE_PARANTESES);

    Token_pointer identifier = curr_token;

    m_token = producaoM();

    int begin = cg->new_label();
    int end = cg->new_label();

    // [14]
    error = verify_type_compatibility(m_token, LOGICO);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,m_token->get_lexema()});

    cg->start_while_loop(m_token, begin, end);
    
    casa_token(FECHA_PARANTESES);

    producaoH();

    cg->end_scope(begin, end);

}

/**
 * @brief H -> (E | {{E}*})
*/
void Parser::producaoH(){

    if (curr_token_id == ABRE_CHAVES) {
        casa_token(curr_token_id);

        while(curr_token_id != FECHA_CHAVES) 
            producaoE();

        casa_token(FECHA_CHAVES);
    } else {

        producaoE();
    }

}

/**
 * @brief I -> if (M) J [else J] // if
*/
void Parser::producaoI(){

    CErrorType error = NenhumErro;
    bool is_else = false;
    Token_pointer m_token = std::make_shared <Token>();

    casa_token(IF);

    casa_token(ABRE_PARANTESES);

    m_token = producaoM();
    
    cg->reset_temporary_counter();

    int begin = cg->new_label();
    int end = cg->new_label();

    // [40]
    error = verify_type_compatibility(m_token, LOGICO);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,m_token->get_lexema()});
    
    cg->start_if(m_token, begin);
    
    casa_token(FECHA_PARANTESES);

    producaoJ();

    if (curr_token_id == ELSE) {
        casa_token(ELSE);

        is_else = true;

        cg->end_scope(end,begin);
        producaoJ();
    }

    cg->end_conditional_chain(is_else,begin,end);    
}

/**
 * @brief J -> (E | {{E}*}) // comando / sequencia de comandos
*/
void Parser::producaoJ(){
    if (curr_token_id == ABRE_CHAVES) {
        
        casa_token(ABRE_CHAVES);

        while (curr_token_id != FECHA_CHAVES) 
            producaoE();
    
        casa_token(FECHA_CHAVES);
    } else 
        producaoE();
    
}

/**
 * @brief K -> readln(identifier) // readln
*/
void Parser::producaoK(){

    CErrorType error = NenhumErro;

    casa_token(READLN);

    casa_token(ABRE_PARANTESES);

    Token_pointer identifier = curr_token;

    casa_token(IDENTIFICADOR);

    // [3]
    error = verify_if_token_already_initialized(identifier);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    // [4]
    error = verify_class_compatibility(identifier, VARIAVEL);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    // [15]
    error = verify_type_incompatibility(identifier, LOGICO);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,identifier->get_lexema()});

    cg->read_line(identifier);

    casa_token(FECHA_PARANTESES);

    casa_token(PONTO_VIRGULA);
}

/**
 * @brief L -> (write(M {, M}*) | writeln(M {, M}*)) // write / writeln
*/
void Parser::producaoL(){

    CErrorType error = NenhumErro;
    bool writeln_flag = false;
    Token_pointer m_token = std::make_shared <Token>();

    if (curr_token_id == WRITE) {
        casa_token(curr_token_id);

    } else { 
        writeln_flag = true;
        casa_token(WRITELN);
    }

    casa_token(ABRE_PARANTESES);

    m_token = producaoM();

    cg->reset_temporary_counter();

    // [16]
    error = verify_type_incompatibility(m_token, LOGICO);
    if (error != NenhumErro) 
        throw_compiler_error(error,{curr_line,m_token->get_lexema()});

    cg->write_into_terminal(m_token);

    while(curr_token_id == VIRGULA) {

        casa_token(curr_token_id);

        m_token = producaoM();

        // [17]
        error = verify_type_incompatibility(m_token, LOGICO);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,m_token->get_lexema()});

        cg->write_into_terminal(m_token);
    }

    casa_token(FECHA_PARANTESES);
    casa_token(PONTO_VIRGULA);

    cg->write_line_break(writeln_flag);
}

/**
 * @brief M -> N {(= | != | < | <= | > | >=) N}* // expressao precedencia 6
*/
Token_pointer Parser::producaoM(){

    Token_pointer m_token = std::make_shared <Token>();
    Token_pointer n_token = std::make_shared <Token>();
    Token_pointer n1_token = std::make_shared <Token>();

    TokenID operation;

    n_token = producaoN();

    // [33]
    attribute_tokens(m_token,n_token);

    while(curr_token_id == IGUAL || curr_token_id == DIFERENTE || curr_token_id == MENOR || curr_token_id == MENOR_IGUAL || curr_token_id == MAIOR || curr_token_id == MAIOR_IGUAL) {

        // [34]
        operation = curr_token->get_id();

        casa_token(curr_token_id);
        
        n1_token = producaoN();

        // [35]
        if (operation == IGUAL && m_token->get_tipo() == TEXTO && n1_token->get_tipo() == TEXTO) {

            cg->compare_string(m_token,n1_token);

        } else if (m_token->get_tipo() == CARACTERE && n1_token->get_tipo() == CARACTERE) {

            cg->char_operation(m_token, n1_token, operation);

        } else if ((m_token->get_tipo() == REAL || m_token->get_tipo() == INTEIRO) && 
        (n1_token->get_tipo() == REAL || n1_token->get_tipo() == INTEIRO)) {

            cg->number_operation(m_token, n_token, n1_token, operation);

        } else {

            throw_compiler_error(TiposIncompativeis,{curr_line});
        }
        
    }

    return m_token;
}

/**
 * @brief N -> [+ | -]O {(+ | - | ||) O}* // expressao precedencia 5
*/
Token_pointer Parser::producaoN(){

    Token_pointer n_token = std::make_shared <Token>();
    Token_pointer o_token = std::make_shared <Token>();
    Token_pointer o1_token = std::make_shared <Token>();
    CErrorType error = NenhumErro;
    bool negate = false;
    bool is_number = false;
    TokenID operation;
    
    // [29]
    if(curr_token_id == SOMA || curr_token_id == SUBTRACAO) {
        casa_token(curr_token_id);
        
        is_number = true;

        if (curr_token_id == SUBTRACAO)
            negate = true;
    }

    o_token = producaoO();

    if (is_number) {

        // [30]
        error = verify_token_is_number(o_token);
        if (error != NenhumErro)
            throw_compiler_error(TiposIncompativeis,{curr_line});
    }

    attribute_tokens(n_token,o_token);

    if (negate) 
        cg->negate_expression(n_token);

    while(curr_token_id == SOMA || curr_token_id == SUBTRACAO || curr_token_id == OR) {

        //[31]
        operation = curr_token->get_id();

        casa_token(curr_token_id);
        o1_token = producaoO();

        // [32]
        if (operation == OR) {
            if (n_token->get_tipo() != LOGICO || o1_token->get_tipo() != LOGICO) 
                throw_compiler_error(TiposIncompativeis,{curr_line});

            cg->or_operation(n_token,o1_token);

        }else {
            if ((n_token->get_tipo() != REAL && n_token->get_tipo() != INTEIRO) 
            || (o1_token->get_tipo() != REAL && o1_token->get_tipo() != INTEIRO)) 
                throw_compiler_error(TiposIncompativeis,{curr_line});

            
            if(operation == SOMA) {
                cg->add_operation(n_token,o1_token);
            } else {
                cg->sub_operation(n_token,o1_token);
            }
        }
        
    }

    return n_token;
}

/**
 * @brief O -> P {(* | / | mod | div | &&) P}* // expressao precedencia 4
*/
Token_pointer Parser::producaoO(){

    Token_pointer p_token = std::make_shared <Token>();
    Token_pointer o_token = std::make_shared <Token>();
    Token_pointer p1_token = std::make_shared <Token>();
    CErrorType error = NenhumErro;
    TokenID operation;

    p_token = producaoP();

    // [26]
    attribute_tokens(o_token,p_token);

    while(curr_token_id == MULTIPLICACAO || curr_token_id == DIVISAO || curr_token_id == MOD || curr_token_id == AND || curr_token_id == DIV) {

        // [27]
        operation = curr_token_id;

        casa_token(curr_token_id);

        p1_token = producaoP();
        
        // [28]
        switch (operation) {
            case AND:
                if (o_token->get_tipo() != LOGICO || p1_token->get_tipo() != LOGICO) 
                    throw_compiler_error(TiposIncompativeis,{curr_line});

                cg->and_operation(o_token,p1_token);
                break;
            
            case MULTIPLICACAO:
            case DIVISAO:

                if((o_token->get_tipo() != REAL && o_token->get_tipo() != INTEIRO) 
                || (p1_token->get_tipo() != REAL && p1_token->get_tipo() != INTEIRO)) 
                    throw_compiler_error(TiposIncompativeis,{curr_line});

                if (o_token->get_tipo() != p1_token->get_tipo()) {
                    o_token->set_tipo(REAL);

                    if (operation == MULTIPLICACAO) 
                        cg->multiple_numbers(o_token,p1_token);

                    else 
                        cg->divide_numbers(o_token,p1_token);

                } else {

                    if( o_token->get_tipo() == INTEIRO && operation == DIVISAO) 
                        throw_compiler_error(TiposIncompativeis,{curr_line});
                    
                    if (operation == MULTIPLICACAO) 

                        cg->multiple_float(o_token,p1_token);
                    else 
                        cg->divide_float(o_token,p1_token);
                    
                }

                break;
            default:

                if (o_token->get_tipo() != INTEIRO || p1_token->get_tipo() != INTEIRO ) 
                    throw_compiler_error(TiposIncompativeis,{curr_line});

                cg->module_or_div(o_token,p1_token,operation == MOD);
                break;
        }
    }
    return o_token;
}

/**
 * @brief P -> (Q | !Q) // expressao precedencia 3
*/
Token_pointer Parser::producaoP(){

    CErrorType error = NenhumErro;
    Token_pointer p_token = std::make_shared <Token>();
    Token_pointer q_token = std::make_shared <Token>();

    if (curr_token_id == NEGACAO) {
        casa_token(curr_token_id);

        q_token = producaoQ();
        // [24]
        attribute_tokens(p_token,q_token);

        // [25]
        error = verify_type_compatibility(q_token,LOGICO);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line});

        cg->negate_boolean(q_token);

    } else {
        q_token = producaoQ();
        attribute_tokens(p_token,q_token);
    }

    return p_token;
}

/**
 * @brief Q -> (R | float(M) | int(M)) // expressao precedencia 2
*/
Token_pointer Parser::producaoQ(){

    Token_pointer q_token = std::make_shared <Token>();
    Token_pointer m_token = std::make_shared <Token>();
    Token_pointer r_token = std::make_shared <Token>();

    if (curr_token_id == FLOAT) {

        casa_token(FLOAT);
        casa_token(ABRE_PARANTESES);

        m_token = producaoM();
        // [21]
        attribute_tokens(q_token,m_token);

        // [22]
        if(q_token->get_tipo() != REAL && q_token->get_tipo() != INTEIRO) {
            throw_compiler_error(TiposIncompativeis,{curr_line});
        } else {

            q_token->set_tipo(REAL);

            if (q_token->get_tipo() == INTEIRO) 
                cg->int_to_float(q_token);
            
        }

        casa_token(FECHA_PARANTESES);

    } else if (curr_token_id == INT) {

        casa_token(INT);
        casa_token(ABRE_PARANTESES);

        m_token = producaoM();
        attribute_tokens(q_token,m_token);

        // [23]
        if(q_token->get_tipo() != REAL && q_token->get_tipo() != INTEIRO) {
            throw_compiler_error(TiposIncompativeis,{curr_line});
        } else {

            q_token->set_tipo(INTEIRO);

            if (q_token->get_tipo() == REAL) 
                cg->float_to_int(q_token);
            
        }

        casa_token(FECHA_PARANTESES);
    }  
    else {

        r_token = producaoR();
        attribute_tokens(q_token,r_token);
    }

    return q_token;
}

/**
 * @brief (basicConst | identifier[[M]] | (M)) // expressao precedencia 1
*/
Token_pointer Parser::producaoR(){

    CErrorType error = NenhumErro;

    Token_pointer r_token = std::make_shared <Token>();
    Token_pointer constant = std::make_shared <Token>();
    Token_pointer m_token = std::make_shared <Token>();

    bool identifier_is_string = false;

    if (curr_token_id == ABRE_PARANTESES) {
        
        casa_token(curr_token_id);

        m_token = producaoM();
        // [20]
        attribute_tokens(r_token,m_token);

        casa_token(FECHA_PARANTESES);

    } else if( curr_token_id == CONST || is_basic_const(&curr_token_id)) {

        constant = curr_token;

        casa_token(curr_token_id);

        // [18]
        attribute_tokens(r_token,constant);

        cg->store_token_on_data_section(r_token,constant,false);
    } else {

        Token_pointer identifier = curr_token;

        casa_token(IDENTIFICADOR);

        // [3]
        error = verify_if_token_already_initialized(identifier);
        if (error != NenhumErro) 
            throw_compiler_error(error,{curr_line,identifier->get_lexema()});

        if (curr_token_id == ABRE_COLCHETES) {

            casa_token(curr_token_id);

            // [11]
            error = verify_type_compatibility(identifier,TEXTO);
            if (error != NenhumErro)
                throw_compiler_error(error,{curr_line});

            identifier_is_string = true;

            m_token = producaoM();
            attribute_tokens(r_token,m_token);

            // [12]
            error = verify_type_compatibility(m_token, INTEIRO);
            if (error != NenhumErro) 
                throw_compiler_error(error,{curr_line,m_token->get_lexema()});

            casa_token(FECHA_COLCHETES);
        }

        // [19]
        if(identifier_is_string)
            cg->add_character(r_token,identifier);
        
        else 
            attribute_tokens(r_token,identifier);
    }

    return r_token;
}

#endif