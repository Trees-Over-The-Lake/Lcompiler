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
    void casa_token(TokenID curr_token_id);
    void producaoS();
    void producaoA();
    void producaoB();
    void producaoC();
    void producaoD();
    void producaoE();
/*     void producaoF();
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
    void producaoR(); */
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

    if (curr_token_id == token_id)
    {
        if(curr_class == TokenClass::VARIAVEL || curr_class == TokenClass::CONSTANTE) {
            prev_token = curr_token;
        }
        
        if(token_error) {
            throw_compiler_error(cerror_type,{curr_line, error_information});
        }

        Token t = la->get_next_token();
        set_curr_token(t,la->get_curr_line_number());
    }
    else {
        throw_compiler_error(CErrorType::TokenNaoEsperado,{curr_line, curr_token.get_lexema()});
    }
    
}

void Parser::set_curr_token(Token curr_token, int curr_line) {
    this->curr_token = curr_token;
    this->curr_class = this->curr_token.get_classe();
    this->curr_token_id = this->curr_token.get_id();
    this->curr_line = std::to_string(curr_line);
}

void Parser::producaoS() {

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
            //producaoE();
        break;
    }

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

    casa_token(TokenID::IDENTIFICADOR);

    switch (curr_token_id)
    {
    case ATRIBUICAO:
    case SUBTRACAO:
        casa_token(curr_token_id);
    default:
        break;
    }
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

    casa_token(TokenID::CONST);
    casa_token(TokenID::IDENTIFICADOR);
    casa_token(TokenID::ATRIBUICAO);

    if(curr_token_id == SUBTRACAO) {
        casa_token(curr_token_id);
    }

    casa_token(TokenID::VIRGULA);
}

void Parser::producaoE() {

    switch (curr_token_id)
    {
        case ATRIBUICAO:
            //producaoF();
            break;
        case WHILE:
            //producaoG();
            break;
        case IF:
            //producaoI();
            break;
        case READLN:
            //producaoK();
            break;
        case WRITE:           
        case WRITELN:
            //producaoL();        
            break;

        default:
            producaoS();
            break;
    }

}

#endif