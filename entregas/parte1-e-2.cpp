#include<iostream>
#include<vector>
#include<string>
#include<string.h>

//-----------------------Inicio da lib: utils/file_stream_reader.cpp-----------------------//
#ifndef FILE_STREAM_READER_CPP
#define FILE_STREAM_READER_CPP


//-----------------------Inicio da lib: constants.hpp-----------------------//
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#define DEFAULT_OUTPUT_FILE "saida.asm"
#define DEFAULT_INPUT "pub.in"

#endif
//-----------------------Fim da lib: constants.hpp-----------------------//
//-----------------------Inicio da lib: ../file/l_file.cpp-----------------------//
#ifndef L_FILE_CPP
#define L_FILE_CPP

#include<utility>

typedef std::pair<int, std::string> line_and_number;

class LFile {
private:
    std::vector<std::string> lines;
    std::vector<std::string>::iterator curr_line_iterator;
    int num_lines;
    int curr_line;
    bool file_ended;
public:
    LFile(std::vector<std::string>* arr = NULL);
    ~LFile();
    void read_file_from_vector(std::vector<std::string>* arr);
    std::string to_string();

    int get_num_lines();

    line_and_number get_curr_line();
    bool is_end_of_file();
};

LFile::LFile(std::vector<std::string>* arr) {
    if (arr == NULL) {
        num_lines = 0;
    } else {
        read_file_from_vector(arr);
    }
    curr_line = 1;
}

LFile::~LFile() {}

void LFile::read_file_from_vector(std::vector<std::string>* arr) {

    this->num_lines = arr->size();
    this->lines = *arr;
    this->curr_line_iterator = this->lines.begin();
    this->file_ended = false;
}

std::string LFile::to_string() {
    std::string s = + " num of lines: " + std::to_string(this->num_lines) + '\n';

    for(int i = 0; i < this->num_lines; i++) 
        s += this->lines[i] + "\n";

    return s;
}

line_and_number LFile::get_curr_line() {

    int curr_line_number = this->curr_line++;

    std::string curr_line = *this->curr_line_iterator;
        
    curr_line += '\0';
    
    this->curr_line_iterator++;

    //std::cout << "--> curr_line: " << this->curr_line << " num_lines: " << num_lines << "\n";
    if (this->curr_line > num_lines) {
        file_ended = true;
    }
    

    return {curr_line_number, curr_line};
}

bool LFile::is_end_of_file() {
    //std::cout << "file ended: " << (file_ended == true ? "TRUE" : "FALSE") << "\n";
    return file_ended;
}

int LFile::get_num_lines() {
    return this->num_lines;
}

#endif
//-----------------------Fim da lib: ../file/l_file.cpp-----------------------//
//-----------------------Inicio da lib: line_reader.cpp-----------------------//
#ifndef LINE_READER_CPP
#define LINE_READER_CPP

#include<algorithm>
#include<fstream>

std::vector<std::string> read_line_until_eof() {
    std::vector<std::string> lines;
    std::string curr_line = "";

    while (std::getline(std::cin, curr_line)) lines.push_back(curr_line);

    //lines.push_back("");
   
    return lines;
}

std::vector<std::string> read_lines_from_file(std::string file_path) {
    std::fstream file;
    file.open(file_path, std::ios::in);

    std::vector<std::string> lines;
    std::string curr_line = "";

    if (file.is_open()) {
        while (std::getline(file, curr_line)) lines.push_back(curr_line);

        file.close();
    } else {
        std::cout << "Erro! Arquivo " << file_path << " não existe!" << "\n";
        exit(1);
    }

    //lines.push_back("");

    return lines;
}

#endif
//-----------------------Fim da lib: line_reader.cpp-----------------------//


/**
 * Checar de onde esta vindo o arquivo de entrada e 
 * separar de forma correta para ser lido futuramente
 */
LFile get_file_from_stream(int argc, char* argv[]) {

    LFile file = LFile();
    std::vector<std::string> file_lines;

    // Ler arquivo direto pelo pub.in
    if (argc == 1) {
        file_lines = read_line_until_eof();
    }
    //Ler arquivo pela path dele 
    else if (argc >= 2) {

        std::string file_path;

        // Path do arquivo em branco, tentar encontrar pub.in no cwd
        if (strlen(argv[1]) == 0) 
            file_path = DEFAULT_INPUT;
            
        else  // Path especificada, ler dela
            file_path = std::string(argv[2]);
        
        file_lines = read_lines_from_file(DEFAULT_INPUT);
    
    } else {
        std::cout << "Error! Impossível ler entrada" << "\n";
        exit(1);
    }

    file.read_file_from_vector(&file_lines);

    return file;
}

#endif 
//-----------------------Fim da lib: utils/file_stream_reader.cpp-----------------------//
//-----------------------Inicio da lib: symbol_table/symbol_table.cpp-----------------------//
#ifndef SYMBOLS_TABLE_CPP
#define SYMBOLS_TABLE_CPP

#include<map>
#include<unordered_map>
#include<stdexcept>
#include<memory>

//-----------------------Inicio da lib: token/token.cpp-----------------------//
#ifndef TOKEN_CPP
#define TOKEN_CPP
 
//-----------------------Inicio da lib: token_type.cpp-----------------------//
#ifndef TOKEN_TYPE_CPP
#define TOKEN_TYPE_CPP

enum TokenType 
{
    CARACTERE,
    REAL,
    INTEIRO,
    LOGICO,
    TEXTO,
    HEXADECIMAL,
    NAO_DEFINIDO,
};

std::string token_type_to_string(TokenType type) {

    switch (type)
    {
    case CARACTERE:
        return "CARACTERE"; 
    case REAL:
        return "REAL"; 
    case INTEIRO:
        return "INTEIRO"; 
    case LOGICO:
        return "LOGICO"; 
    case TEXTO:
        return "TEXTO"; 
    case HEXADECIMAL:
        return "HEXADECIMAL"; 
    case NAO_DEFINIDO:
        return "NAO_DEFINIDO"; 
    default:
        return "NULL"; 
    }

    return "NULL";
}

#endif
//-----------------------Fim da lib: token_type.cpp-----------------------//
//-----------------------Inicio da lib: token_class.cpp-----------------------//
#ifndef TOKEN_CLASS_CPP
#define TOKEN_CLASS_CPP

enum TokenClass
{
    VARIAVEL,
    CONSTANTE,
    NENHUM,
};

std::string token_class_to_string(TokenClass tclass) {

    switch (tclass)
    {
    case VARIAVEL:
        return "VARIAVEL";
    case CONSTANTE:
        return "CONSTANTE";
    case NENHUM:
        return "NENHUM";
    default:
        return "NULL"; 
    }

    return "NULL";
}

#endif
//-----------------------Fim da lib: token_class.cpp-----------------------//
//-----------------------Inicio da lib: token_id.cpp-----------------------//
#ifndef TOKEN_ID_CPP
#define TOKEN_ID_CPP


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
    ATRIBUICAO,         // =
    IGUAL,              // ==
    WALRUS,             // :=
    MAIOR,              // >
    MENOR,              // <
    MAIOR_IGUAL,        // <=
    MENOR_IGUAL,        // >=
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
    FIM_DE_ARQUIVO      // \0
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
    case ATRIBUICAO:    
        return "ATRIBUICAO";      
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
//-----------------------Fim da lib: token_id.cpp-----------------------//
#include <cstdint>

class Token {
    private:
        TokenID id;
        std::string lexema;
        TokenType tipo;
        TokenClass classe;
        uint8_t tamanho;
    public:
        Token(TokenID id = TokenID::ATRIBUICAO, std::string lexema = "", TokenType tipo = TokenType::NAO_DEFINIDO, TokenClass classe = TokenClass::NENHUM, uint8_t tamanho = 1);
        ~Token();

        std::string get_lexema();
        TokenType get_tipo();
        TokenClass get_classe();
        uint8_t get_tamanho();
        TokenID get_id();

        Token clone();

        void set_lexema(std::string lexema);
        void set_tipo(TokenType tipo);
        void set_classe(TokenClass classe);
        void set_tamanho(uint8_t tamanho);
        void set_id(TokenID id);

        std::string to_string();
};

Token::Token(TokenID id, std::string lexema, TokenType tipo, TokenClass classe, uint8_t tamanho) {
    this->id = id;
    this->lexema = lexema;
    this->tipo = tipo;
    this->classe = classe;
    this->tamanho = tamanho;
}

Token::~Token()
{

}

std::string Token::get_lexema() {
    return this->lexema;
}

TokenType Token::get_tipo() {
    return this->tipo;
}

TokenClass Token::get_classe() {
    return this->classe;
}

uint8_t Token::get_tamanho() {
    return this->tamanho;
}

TokenID Token::get_id() {
    return this->id;
}

void Token::set_lexema(std::string lexema) {
    this->lexema = lexema;
}

void Token::set_tipo(TokenType tipo) {
    this->tipo = tipo;
}

void Token::set_classe(TokenClass classe) {
    this->classe = classe;
}

void Token::set_tamanho(uint8_t tamanho) {
    this->tamanho = tamanho;
}

void Token::set_id(TokenID id) {
    this->id = id;
}

Token Token::clone() {
    Token c;
    c.classe = this->classe;
    c.id = this->id;
    c.lexema = this->lexema;
    c.tipo = this->tipo;
    c.tamanho = this->tamanho;

    return c;
}

std::string Token::to_string() {
    return "token_id: " + token_id_to_string(this->id) + "\t lexema: " + this->lexema + "\t tipo: " + \
            token_type_to_string(this->tipo) + "\t classe: " + token_class_to_string(this->classe) + "\t tamanho: " + std::to_string(this->tamanho);
}

#endif
//-----------------------Fim da lib: token/token.cpp-----------------------//
//-----------------------Inicio da lib: lexeme.cpp-----------------------//
#ifndef LEXEME_CPP
#define LEXEME_CPP


const std::vector<char> VALID_CHARACTERS{
        ' ',
        '|',
        '!', 
        '"', 
        '%', 
        '@',
        '?',
        '&', 
        '(', 
        ')', 
        '{', 
        '}', 
        '[', 
        ']', 
        '*', 
        '+', 
        '-', 
        '/', 
        ',', 
        '.', 
        ':', 
        ';', 
        '<', 
        '>', 
        '=', 
        '_', 
        '\'',
        '\\', 
        '\r',
        '\t',
        '\n',
        '\0'
};

const std::vector<char> VALID_HEXA_SYMBOLS{
        'A', 
        'B', 
        'C', 
        'D', 
        'E', 
        'F', 
        'a', 
        'b', 
        'c', 
        'd', 
        'e', 
        'f'
};

const std::map<TokenID,std::string> LEXEMES = {
    {TokenID::CONST, "const"},
    {TokenID::INT, "int"},
    {TokenID::FLOAT, "float"},
    {TokenID::CHAR, "char"},
    {TokenID::STRING, "string"},
    {TokenID::BOOLEAN, "boolean"},
    {TokenID::TRUE, "true"},
    {TokenID::FALSE, "false"},
    {TokenID::IF, "if"},
    {TokenID::ELSE, "else"},
    {TokenID::WHILE, "while"},
    {TokenID::MOD, "mod"},
    {TokenID::DIV, "div"},
    {TokenID::WRITE, "write"},
    {TokenID::WRITELN, "writeln"},
    {TokenID::READLN, "readln"},
    {TokenID::NEGACAO, "!"},
    {TokenID::ATRIBUICAO, "="},
    {TokenID::IGUAL, "=="},
    {TokenID::WALRUS, ":="},
    {TokenID::MAIOR, ">"},
    {TokenID::MENOR, "<"},
    {TokenID::MAIOR_IGUAL, ">="},
    {TokenID::MENOR_IGUAL, "<="},
    {TokenID::DIFERENTE, "!="},
    {TokenID::VIRGULA, ","},
    {TokenID::SOMA, "+"},
    {TokenID::SUBTRACAO, "-"},
    {TokenID::MULTIPLICACAO, "*"},
    {TokenID::DIVISAO, "/"},
    {TokenID::PONTO_VIRGULA, ";"},
    {TokenID::ABRE_PARANTESES, "("},
    {TokenID::FECHA_PARANTESES, ")"},
    {TokenID::ABRE_CHAVES, "{"},
    {TokenID::FECHA_CHAVES, "}"},
    {TokenID::ABRE_COLCHETES, "["},
    {TokenID::FECHA_COLCHETES, "]"},
    {TokenID::AND, "&&"},
    {TokenID::OR, "||"},
    {TokenID::FIM_DE_ARQUIVO, "\0"}
};

#endif
//-----------------------Fim da lib: lexeme.cpp-----------------------//
//-----------------------Inicio da lib: ../utils/string_utils.cpp-----------------------//
#ifndef STRING_UTILS_CPP
#define STRING_UTILS_CPP

#include <cctype>

std::string to_lower(const std::string s) {
    std::string lowered = s;
    std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return lowered;
}

#endif
//-----------------------Fim da lib: ../utils/string_utils.cpp-----------------------//
#include<locale>

typedef std::shared_ptr<Token> Token_pointer;

class SymbolTable {
    private:

        static std::unordered_map<std::string,Token_pointer> table;
        static bool table_initialized;

        void initiate_symbol_table();

    public:
        SymbolTable();
        ~SymbolTable();

        Token_pointer add_id(std::string lexeme);
        Token_pointer find_lexeme(std::string lexeme);
        std::string to_string();

        bool is_character_valid(const char c);
};

bool SymbolTable::table_initialized = false;
std::unordered_map<std::string,Token_pointer> SymbolTable::table;

SymbolTable::SymbolTable(){

    if (!table_initialized)
        initiate_symbol_table();
}

void SymbolTable::initiate_symbol_table() {
    for(auto iter = LEXEMES.begin(); iter != LEXEMES.end(); ++iter) {
        TokenID id = iter->first;
        std::string lexeme = iter->second;

        Token_pointer token = std::make_shared<Token>(id,lexeme);

        SymbolTable::table.insert({lexeme, token});
    }
}

SymbolTable::~SymbolTable(){}

Token_pointer SymbolTable::add_id(std::string lexeme) {

    auto lowered_lexeme = to_lower(lexeme);
    Token_pointer token = nullptr;

    try {
        token = this->table[lowered_lexeme];
        if (token == nullptr) {
            token = std::make_shared<Token>(IDENTIFICADOR, lowered_lexeme);
            this->table.insert({lowered_lexeme, token});
        }
    
    } catch(std::exception e ) {

        token = std::make_shared<Token>(IDENTIFICADOR, lowered_lexeme);
        this->table.insert({lowered_lexeme, token});

    } 

    return token;
}

Token_pointer SymbolTable::find_lexeme(std::string lexeme) {
    
    Token_pointer token = nullptr;

    try {
        token = this->table[lexeme];

    } catch(std::exception e ) {} 

    return token;
}

bool SymbolTable::is_character_valid(const char c) {
    return std::isalnum(c) ||
           std::find(VALID_CHARACTERS.begin(), VALID_CHARACTERS.end(), c) != VALID_CHARACTERS.end();
}

std::string SymbolTable::to_string() {

    std::string result = "";

    for(auto iter = SymbolTable::table.begin(); iter != SymbolTable::table.end(); ++iter) {
        std::string lexeme = iter->first;
        Token_pointer token = iter->second;

        result += "lexeme: " + lexeme + "\ttoken: \n" + token->to_string() + "\n\n" ;
    }

    return result;
}

#endif
//-----------------------Fim da lib: symbol_table/symbol_table.cpp-----------------------//
//-----------------------Inicio da lib: analyzers/lexical_analyzer.cpp-----------------------//
#ifndef LEXICAL_ANALYZER_CPP
#define LEXICAL_ANALYZER_CPP

//-----------------------Inicio da lib: ../error_manager/cerror_manager.cpp-----------------------//
#ifndef CERROR_MANAGER_CPP
#define CERROR_MANAGER_CPP


//-----------------------Inicio da lib: cerror_type.cpp-----------------------//
#ifndef CERROR_TYPE_CPP
#define CERROR_TYPE_CPP

enum CErrorType {
    CaractereInvalido,
    LexemaInvalido,
    TokenNaoEsperado,
    IdentificadorNaoDeclarado,
    IdentificadorJaDeclarado,
    ClasseDeIdentificadorIncompativel,
    TiposIncompativeis,
    TamanhoVetorExcedido,
    FimDeArquivoNaoEsperado
};


#endif
//-----------------------Fim da lib: cerror_type.cpp-----------------------//
//-----------------------Inicio da lib: cerror.cpp-----------------------//
#ifndef CERROR_CPP
#define CERROR_CPP


/**
 * Classe para armazenar logica de erros de compilacao
 */
class CError {
    private:
        uint32_t line_error;
        std::string error_information;
    public:
        CError(uint32_t line_error, std::string error_information);
        ~CError();

        std::string to_string();
};

CError::CError(uint32_t line_error, std::string error_information){
    this->error_information = error_information;
    this->line_error = line_error;
}

CError::~CError(){}

std::string CError::to_string() {
    return std::to_string(line_error) + "\n" + error_information;
}

#endif
//-----------------------Fim da lib: cerror.cpp-----------------------//

#define LINE_ERROR 0
#define ERROR_DETAIL 1

void throw_compiler_error(CErrorType error_type, std::vector<std::string> error_content) {

    uint32_t line_error = static_cast<uint32_t>(std::stoul(error_content[LINE_ERROR]));  
    std::string error_information = "";

    switch (error_type) {
        case CaractereInvalido:
            error_information = "caractere invalido.";
            break;

        case FimDeArquivoNaoEsperado:
            error_information = "fim de arquivo nao esperado.";
            break;        

        case LexemaInvalido:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "lexema nao identificado [" + lexema + "].";
            break;
        }
        case TokenNaoEsperado:
        {
            std::string token = error_content[ERROR_DETAIL];
            error_information = "token nao esperado [" + token + "].";
            break;
        } default:
            break;
    }  

    CError error = CError(line_error, error_information);
    std::cout << error.to_string() << "\n";
    exit(1);
}

#endif
//-----------------------Fim da lib: ../error_manager/cerror_manager.cpp-----------------------//
#include<regex>

typedef std::string::const_iterator iterator;

class LexicalAnalyzer {
    private:
        LFile* file_to_analyze;
        int curr_state;
        SymbolTable symbol_table;

        static const std::regex isolate_symbols;

        std::string curr_line;
        int curr_line_number;
        iterator curr_char;
        iterator line_start;
        iterator line_end;

        const uint8_t END_STATE = 1;
        const uint8_t FIRST_STATE = 0;

        bool file_ended;

        void return_char();
        void next_char();
        void update_curr_line();

        bool estado0(const char c, std::string* lexeme, Token* token);
        Token estado1(std::string* lexeme, Token* token);
        bool estado2(const char c, std::string* lexeme, Token* token);
        bool estado3(const char c, std::string* lexeme, Token* token);
        bool estado4(const char c, std::string* lexeme, Token* token);
        bool estado5(const char c, std::string* lexeme, Token* token);
        bool estado6(const char c, std::string* lexeme, Token* token);
        bool estado7(const char c, std::string* lexeme, Token* token);
        bool estado8(const char c, std::string* lexeme, Token* token);
        bool estado9(const char c, std::string* lexeme, Token* token);
        bool estado10(const char c, std::string* lexeme, Token* token);
        bool estado11(const char c, std::string* lexeme, Token* token);
        bool estado12(const char c, std::string* lexeme, Token* token);
        bool estado13(const char c, std::string* lexeme, Token* token);
        bool estado14(const char c, std::string* lexeme, Token* token);
        bool estado15(const char c, std::string* lexeme, Token* token);
        bool estado16(const char c, std::string* lexeme, Token* token);
        bool estado17(const char c, std::string* lexeme, Token* token);
        bool estado18(const char c, std::string* lexeme, Token* token);

    public:
        LexicalAnalyzer(LFile* file);
        ~LexicalAnalyzer();

        int get_curr_line_number();

        Token get_next_token();
        bool no_more_tokens();
};

const std::regex LexicalAnalyzer::isolate_symbols = std::regex(R"(=|%|,|-|\+|;|\(|\)|\*|\[|\]|\{|\})");

LexicalAnalyzer::LexicalAnalyzer(LFile* file) {
    this->file_to_analyze = file;
    this->curr_state = 0;
    this->symbol_table = SymbolTable();

    this->file_ended = false;

    if(!file_to_analyze->is_end_of_file())
        update_curr_line();
}

LexicalAnalyzer::~LexicalAnalyzer() {}

void LexicalAnalyzer::update_curr_line() {
    auto curr_line = file_to_analyze->get_curr_line();

    this->curr_line = curr_line.second;
    this->curr_line_number = curr_line.first;

    this->line_start = this->curr_line.cbegin();
    this->line_end = this->curr_line.cend();

    this->curr_char = this->line_start;
}

void LexicalAnalyzer::return_char() {
    --curr_char;
}

void LexicalAnalyzer::next_char() {
    ++curr_char;
}

bool LexicalAnalyzer::no_more_tokens() {
    return this->file_ended;
}

int LexicalAnalyzer::get_curr_line_number() {
    return curr_line_number;
}

bool LexicalAnalyzer::estado0(const char c, std::string* lexeme, Token* token) {
    bool error_found = false;

    std::string c_string = std::string(1,c);
    
    if(c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\0') {
        curr_state = 0;
    }
    else if(c == '!') {
        curr_state = 5;
        *lexeme += c;
    }
    else if(c == '<' || c == '>') {
        curr_state = 7;
        *lexeme += c;
    }
    else if(c == '_' || std::isalpha(c)) {
        curr_state = 12;
        *lexeme += c;
    }
    else if(std::regex_match(c_string, LexicalAnalyzer::isolate_symbols)) {
        curr_state = 1;
        *lexeme += c;
    }
    else if(c == '0') {
        token->set_classe(CONSTANTE);
        curr_state = 6;
        *lexeme += c;
    }
    else if(std::isdigit(c) && c != '0') {
        token->set_classe(CONSTANTE);
        token->set_tipo(INTEIRO);
        curr_state = 17;
        *lexeme += c;
    }
    else if(c == '.') {
        token->set_classe(CONSTANTE);
        token->set_tipo(REAL);
        curr_state = 13;
        *lexeme += c;
    }
    else if(c == '\'') {
        token->set_classe(CONSTANTE);
        token->set_tipo(CARACTERE);
        curr_state = 9;
        *lexeme += c;
    }
    else if(c == '"') {
        token->set_classe(CONSTANTE);
        token->set_tipo(TEXTO);
        curr_state = 11;
        *lexeme += c;
    }
    else if(c == ':') {
        curr_state = 8;
        *lexeme += c;
    }
    else if(c == '/') {
        curr_state = 2;
        *lexeme += c;
    }
    else if (c == '|') {
        token->set_tipo(LOGICO);
        curr_state = 18;
        *lexeme += c;
    }
    else {
        error_found = true;
    }

    return error_found;
}

Token LexicalAnalyzer::estado1(std::string* lexeme, Token* token) {

    Token t = token->clone();

    if (t.get_classe() == CONSTANTE) {
        t.set_id(TokenID::CONST);
        t.set_lexema(*lexeme);
        
    } else {
        t = *this->symbol_table.add_id(*lexeme);
    }

    *lexeme = "";

    return t;
}

bool LexicalAnalyzer::estado2(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;
    }
    if(c == '*') {
        curr_state = 3;
        *lexeme = "";
    }
    else {
        return_char();
        curr_state = 1;
    }

    return error_found;
}

bool LexicalAnalyzer::estado3(const char c, std::string* lexeme, Token* token) {

    if(c == '*') {
        curr_state = 4;
    }
    else {
        curr_state = 3;
    }

    return false;
}

bool LexicalAnalyzer::estado4(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;
    }
    else if(c == '*') {
        curr_state = 4;
    }
    else if (c == '/'){
        curr_state = 0;
    }
    else {
        curr_state = 3;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado5(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (c == '=') {
        curr_state = 1;
        *lexeme += c;
    }
    else {
        error_found = true;
    }

    return error_found;    
}

bool LexicalAnalyzer::estado6(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (c == 'x') {
        curr_state = 15;
        *lexeme += c;
        token->set_tipo(HEXADECIMAL);
    }
    else if (std::isdigit(c)) {
        curr_state = 17;
        *lexeme += c;
        token->set_tipo(INTEIRO);
    }
    else {
        token->set_tipo(INTEIRO);
        return_char();
        curr_state = 1;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado7(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (c == '=') {
        curr_state = 1;
        *lexeme += c;
    }
    else {
        return_char();
        curr_state = 1;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado8(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (c == '=') {
        curr_state = 1;
        *lexeme += c;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado9(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isalnum(c)) {
        curr_state = 10;
        *lexeme += c;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado10(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (c == '\'') {
        curr_state = 1;
        *lexeme += c;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado11(const char c, std::string* lexeme, Token* token) {


    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isalnum(c)) {
        curr_state = 11;
        *lexeme += c;
    }
    else if (c == '"'){
        curr_state = 1;
        *lexeme += c;
    } else {
        *lexeme += c;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado12(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isdigit(c) || std::isalpha(c) || c == '_') {
        curr_state = 12;
        *lexeme += c;
    }
    else {   
        return_char();
        curr_state = 1;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado13(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isdigit(c)) {
        curr_state = 14;
        *lexeme += c;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado14(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isalnum(c)) {
        curr_state = 14;
        *lexeme += c;
    }
    else {
        return_char();        
        curr_state = 1;   
    }

    return error_found;  
}

bool LexicalAnalyzer::estado15(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isxdigit(c)) {
        curr_state = 16;
        *lexeme += c;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado16(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isxdigit(c)) {
        curr_state = 1;
        *lexeme += c;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado17(const char c, std::string* lexeme, Token* token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if(std::isdigit(c)) {
        curr_state = 17;
        *lexeme += c;
    }
    else if (c == '.') {
        curr_state = 14;
        *lexeme += c;
    }
    else {     
        curr_state = 1;
        return_char();
    }

    return error_found;  
}

bool LexicalAnalyzer::estado18(const char c, std::string* lexeme, Token* token) {
    bool error_found = false;

    if (c == '|') {
        curr_state = 1;
        *lexeme += c;
    } else {
        error_found = true;
    }

    return error_found;
}

// Função do Analisador Léxico.
Token LexicalAnalyzer::get_next_token()
{
    Token next_token;

    curr_state = FIRST_STATE;

    std::string lexeme;

    if (file_ended) {
        return next_token;
    }


    while (curr_state != END_STATE) {

        if(this->curr_char == this->line_end) {

            if(this->file_to_analyze->is_end_of_file()){
                next_token.set_lexema("\0");
                next_token = estado1(&lexeme,&next_token);
                file_ended = true;
                curr_state == END_STATE;
                break;
            }

            update_curr_line();
        }

        const char c = *curr_char;

        if(!this->symbol_table.is_character_valid(c)) 
            throw_compiler_error(CErrorType::CaractereInvalido, 
                                {std::to_string(this->curr_line_number)});

        bool error_detected = false;

        switch (curr_state)
        {
            case 0:
                error_detected = estado0(c,&lexeme,&next_token);
                break;

            case 2:
                error_detected = estado2(c,&lexeme,&next_token);
                break;

            case 3:
                error_detected = estado3(c,&lexeme,&next_token);
                break;

            case 4:
                error_detected = estado4(c,&lexeme,&next_token);
                break;

            case 5:
                error_detected = estado5(c,&lexeme,&next_token);
                break;

            case 6:
                error_detected = estado6(c,&lexeme,&next_token);
                break;

            case 7:
                error_detected = estado7(c,&lexeme,&next_token);
                break;

            case 8:
                error_detected = estado8(c,&lexeme,&next_token);
                break;

            case 9:
                error_detected = estado9(c,&lexeme,&next_token);
                break;

            case 10:
                error_detected = estado10(c,&lexeme,&next_token);
                break;

            case 11:
                error_detected = estado11(c,&lexeme,&next_token);
                break;

            case 12:
                error_detected = estado12(c,&lexeme,&next_token);
                break;

            case 13:
                error_detected = estado13(c,&lexeme,&next_token);
                break;

            case 14:
                error_detected = estado14(c,&lexeme,&next_token);
                break;

            case 15:
                error_detected = estado15(c,&lexeme,&next_token);
                break;

            case 16:
                error_detected = estado16(c,&lexeme,&next_token);
                break;

            case 17:
                error_detected = estado17(c,&lexeme,&next_token);
                break;

            case 18:
                error_detected = estado18(c,&lexeme,&next_token);
                break;

            default:
                break;
        }

        if(error_detected){

            if (this->file_to_analyze->is_end_of_file()) 
                throw_compiler_error(FimDeArquivoNaoEsperado, 
                                    {std::to_string(this->curr_line_number)});
            else 
                throw_compiler_error(LexemaInvalido, 
                                    {std::to_string(this->curr_line_number), lexeme});
        } 

        next_char();

        if(curr_state == END_STATE) {
            next_token = estado1(&lexeme,&next_token);
        }
    }

    if(file_ended && curr_state != 0) {
        throw_compiler_error(CErrorType::FimDeArquivoNaoEsperado, {std::to_string(this->curr_line_number+1)});
    }

    return next_token;
}               

#endif
//-----------------------Fim da lib: analyzers/lexical_analyzer.cpp-----------------------//
//-----------------------Inicio da lib: analyzers/parser.cpp-----------------------//
#ifndef PARSER_CPP
#define PARSER_CPP


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
            casa_token(INT);
            break;
        case FLOAT:
            casa_token(FLOAT);
            break;
        case CHAR:
            casa_token(CHAR);
            break;
        case STRING:
            casa_token(STRING);
            break;
        case BOOLEAN:
            casa_token(BOOLEAN);
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

        while(curr_token_id != FECHA_CHAVES) {
            producaoE();
        }

        casa_token(FECHA_CHAVES);
    } else {

        producaoE();
    }

}
void Parser::producaoI(){
    
    casa_token(IF);

    casa_token(ABRE_PARANTESES);

    producaoM();
    
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
//-----------------------Fim da lib: analyzers/parser.cpp-----------------------//

LFile get_file_from_stream(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    SymbolTable st = SymbolTable();
    LFile file = get_file_from_stream(argc,argv);

    LexicalAnalyzer la = LexicalAnalyzer(&file);
    Parser p = Parser(&la);

    Token t;
    t = la.get_next_token();

    p.set_curr_token(t,la.get_curr_line_number());
    p.producaoS();

    std::cout << file.get_num_lines() + 1 << " linhas compiladas." << "\n";
    
    return 0;
}
