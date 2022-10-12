#ifndef PARSER_CPP
#define PARSER_CPP

#include"../symbol_table/symbol_table.cpp"
#include"../error_manager/cerror_manager.cpp"

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
public:
    Parser(/* args */);
    ~Parser();
    void casa_token(TokenID curr_token_id);
    void set_curr_token(Token *curr_token, int curr_line);
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

Parser::Parser(/* args */)
{
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
    }
    else {
        throw_compiler_error(CErrorType::TokenNaoEsperado,{curr_line, curr_token.get_lexema()});
    }
    
}

void Parser::set_curr_token(Token *curr_token, int curr_line) {
    this->curr_token = *curr_token;
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
            producaoE();
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

}

void Parser::producaoC() {

    switch (curr_token_id)
    {
        case INT:
            casa_token(curr_token_id);
        break;
        case FLOAT:
            casa_token(curr_token_id);
        break;
        case CHAR:
            casa_token(curr_token_id);
        break;
        case STRING:
            casa_token(curr_token_id);
        break;
        case BOOLEAN:
            casa_token(curr_token_id);
        break;

        default:
        break;
    }

}

void Parser::producaoE() {

    switch (curr_token_id)
    {
        case ATRIBUICAO:
            producaoF();
        break;
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
            producaoS(NULL);
        break;
    }

}

#endif