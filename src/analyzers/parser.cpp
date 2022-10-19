#ifndef PARSER_CPP
#define PARSER_CPP

#include"../symbol_table/symbol_table.cpp"
#include"../error_manager/cerror_manager.cpp"
#include"lexical_analyzer.cpp"

class Parser
{
private:
    SymbolTable symbol_table;
    Token curr_token;
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
    void set_curr_token(Token curr_token, int curr_line);
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
    void producaoM();
    void producaoN();
    void producaoO();
    void producaoP();
    void producaoQ();
    void producaoR();
};

Parser::Parser(LexicalAnalyzer* la)
{
    this->la = la;
    this->symbol_table = SymbolTable();
    this->token_error = false;
}

Parser::~Parser()
{

}

void Parser::casa_token(TokenID token_id) {

    if (tokens_are_a_match(&token_id))
    {
        if(curr_class == VARIAVEL || curr_class == CONSTANTE) {
            prev_token = curr_token;
        }
        
        if(token_error) {
            throw_compiler_error(cerror_type,{curr_line, error_information});
        }

        Token t = la->get_next_token();
        set_curr_token(t,la->get_curr_line_number());
    }
    else {

        if(curr_token.get_id() == FIM_DE_ARQUIVO) 
            throw_compiler_error(FimDeArquivoNaoEsperado, 
                            {curr_line});
        else 
            throw_compiler_error(TokenNaoEsperado,
                                {curr_line, curr_token.get_lexema()});
    }
    
}

bool Parser::tokens_are_a_match(const TokenID* token_id) {
    return *token_id == curr_token_id || (*token_id == CONST && (curr_token_id == TRUE || curr_token_id == FALSE));
}

void Parser::set_curr_token(Token curr_token, int curr_line) {
    this->curr_token = curr_token;
    this->curr_class = this->curr_token.get_classe();
    this->curr_token_id = this->curr_token.get_id();
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

    producaoC();

    casa_token(IDENTIFICADOR);

    if(curr_token_id == ATRIBUICAO || curr_token_id == WALRUS) {

        casa_token(curr_token_id);

        if(curr_token_id == SUBTRACAO) {
            casa_token(curr_token_id);
        }

        casa_token(CONST);
    }

    while ( curr_token_id == VIRGULA) {

        casa_token(VIRGULA);

        casa_token(IDENTIFICADOR);

        if( curr_token_id == ATRIBUICAO || curr_token_id == WALRUS) {

            casa_token(curr_token_id);

            if(curr_token_id == SUBTRACAO) {
                casa_token(curr_token_id);
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
            casa_token(TokenID::INT);
            break;
        case FLOAT:
            casa_token(TokenID::FLOAT);
            break;
        case CHAR:
            casa_token(TokenID::CHAR);
            break;
        case STRING:
            casa_token(TokenID::STRING);
            break;
        case BOOLEAN:
            casa_token(TokenID::BOOLEAN);
            break;
        default:
            break;
    }

}

void Parser::producaoD() {

    casa_token(CONST);
    casa_token(IDENTIFICADOR);
    casa_token(ATRIBUICAO);

    if(curr_token_id == SUBTRACAO) {
        casa_token(curr_token_id);
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
                //std::cout << "curr_token: " << curr_token.to_string() << "\n";
                //producaoS();
                break;
        }

}

void Parser::producaoF(){

    casa_token(IDENTIFICADOR);

    if(curr_token_id == ABRE_COLCHETES) {
        casa_token(curr_token_id);

        producaoM();

        casa_token(FECHA_COLCHETES);
    }

    casa_token(WALRUS);

    producaoM();

    casa_token(PONTO_VIRGULA);
}
void Parser::producaoG(){

    casa_token(WHILE);

    producaoM();

    producaoH();

}
void Parser::producaoH(){

    if (curr_token_id == ABRE_CHAVES) {
        casa_token(curr_token_id);

        while(curr_token_id != FECHA_CHAVES && curr_token_id != FIM_DE_ARQUIVO) {
            producaoE();
        }

        casa_token(FECHA_CHAVES);
    } else {

        producaoE();
    }

}
void Parser::producaoI(){
    //TODO: producao
}
void Parser::producaoJ(){
    //TODO: producao
}
void Parser::producaoK(){

    casa_token(READLN);

    casa_token(ABRE_PARANTESES);

    casa_token(IDENTIFICADOR);

    casa_token(FECHA_PARANTESES);

    casa_token(PONTO_VIRGULA);
}
void Parser::producaoL(){
    
    if (curr_token_id == WRITE) {
        casa_token(curr_token_id);
    } else {
        casa_token(WRITELN);
    }

    casa_token(ABRE_PARANTESES);

    producaoM();

    while(curr_token_id == VIRGULA) {
        casa_token(curr_token_id);

        producaoM();
    }

    casa_token(FECHA_PARANTESES);
    casa_token(PONTO_VIRGULA);
}
void Parser::producaoM(){

    producaoN();

    while(curr_token_id == IGUAL || curr_token_id == DIFERENTE || curr_token_id == MENOR || curr_token_id == MENOR_IGUAL || curr_token_id == MAIOR || curr_token_id == MAIOR_IGUAL) {

        casa_token(curr_token_id);
        
        producaoN();
    }

}
void Parser::producaoN(){

    if(curr_token_id == SOMA || curr_token_id == SUBTRACAO) {
        casa_token(curr_token_id);
    }

    producaoO();

    while(curr_token_id == SOMA || curr_token_id == SUBTRACAO || curr_token_id == OR) {

        casa_token(curr_token_id);
        producaoO();
    }

}
void Parser::producaoO(){

    producaoP();

    while(curr_token_id == MULTIPLICACAO || curr_token_id == DIVISAO || curr_token_id == MOD || curr_token_id == DIVISAO || curr_token_id == DIV) {

        casa_token(curr_token_id);

        producaoP();
    }

}
void Parser::producaoP(){

    if (curr_token_id == NEGACAO) {
        casa_token(curr_token_id);
    } 

    producaoQ();
}
void Parser::producaoQ(){

    if (curr_token_id == FLOAT || curr_token_id == INT) {

        casa_token(curr_token_id);
        casa_token(ABRE_PARANTESES);

        producaoM();

        casa_token(FECHA_PARANTESES);
    } else {

        producaoR();
    }
}
void Parser::producaoR(){

    if (curr_token_id == ABRE_PARANTESES) {
        
        casa_token(curr_token_id);

        producaoM();

        casa_token(FECHA_PARANTESES);
    } else if( curr_token_id == CONST) {
        casa_token(curr_token_id);
    } else {

        casa_token(IDENTIFICADOR);

        if (curr_token_id == ABRE_COLCHETES) {

            casa_token(curr_token_id);

            producaoM();

            casa_token(FECHA_COLCHETES);
        }
    }
}

#endif