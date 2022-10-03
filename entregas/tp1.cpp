#include<iostream>
#include<vector>
#include<string>

//-----------------------Inicio da lib: symbol_table/symbol_table.cpp-----------------------//
#ifndef SYMBOLS_TABLE_CPP
#define SYMBOLS_TABLE_CPP

#include<map>
#include<unordered_map>
#include<stdexcept>
#include<algorithm>

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

#endif
//-----------------------Fim da lib: token_type.cpp-----------------------//
//-----------------------Inicio da lib: token_class.cpp-----------------------//
#ifndef TOKEN_CLASS_CPP
#define TOKEN_CLASS_CPP

enum TokenClasse
{
    VARIAVEL,
    CONSTANTE,
    NENHUM,
};

#endif
//-----------------------Fim da lib: token_class.cpp-----------------------//
//-----------------------Inicio da lib: token_id.cpp-----------------------//
#ifndef TOKEN_ID_CPP
#define TOKEN_ID_CPP

enum TokenID
{
    CONST,              // const
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
    PONTO_VIRGULA,      // ;
    ABRE_PARANTESES,    // (
    FECHA_PARANTESES,   // )
    ABRE_CHAVES,        // {
    FECHA_CHAVES,       // }
    ABRE_COLCHETES,     // [
    FECHA_COLCHETES,    // ]
    AND,                // &&
    OR,                 // ||
};

#endif
//-----------------------Fim da lib: token_id.cpp-----------------------//
#include <cstdint>

class Token {
    private:
        TokenID id;
        std::string lexema;
        TokenType tipo;
        uint8_t tamanho;
    public:
        Token(TokenID id = TokenID::ATRIBUICAO, std::string lexema = "", TokenType tipo = TokenType::NAO_DEFINIDO, uint8_t tamanho = 1);
        ~Token();

        std::string to_string();
};

Token::Token(TokenID id, std::string lexema, TokenType tipo, uint8_t tamanho) {
    this->id = id;
    this->lexema = lexema;
    this->tipo = tipo;
    this->tamanho = tamanho;
}

Token::~Token()
{

}

std::string Token::to_string() {
    return "token_id: " + std::to_string(this->id) + "| lexema: " + this->lexema + "| tipo: " + \
            std::to_string(this->tipo) + "| tamanho: " + std::to_string(this->tamanho);
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

class SymbolTable {
    private:

        static std::unordered_map<std::string,Token> table;
        static bool table_initialized;

        void initiate_symbol_table();

    public:
        SymbolTable();
        ~SymbolTable();

        Token* add_id(std::string lexeme);
        Token* find_lexeme(std::string lexeme);
        std::string to_string();

        bool is_character_valid(const char c);
};

bool SymbolTable::table_initialized = false;
std::unordered_map<std::string,Token> SymbolTable::table;

SymbolTable::SymbolTable(){

    if (!table_initialized)
        initiate_symbol_table();
}

void SymbolTable::initiate_symbol_table() {
    for(auto iter = LEXEMES.begin(); iter != LEXEMES.end(); ++iter) {
        TokenID id = iter->first;
        std::string lexeme = iter->second;

        SymbolTable::table.insert({lexeme, Token(id,lexeme)});
    }
}

SymbolTable::~SymbolTable(){}

Token* SymbolTable::add_id(std::string lexeme) {

    auto lowered_lexeme = to_lower(lexeme);
    Token* token = NULL;

    try {
        token = &(this->table[lexeme]);
    
    } catch(std::exception e ) {
        token = new Token(TokenID::ATRIBUICAO, lexeme);
        this->table.insert({lexeme, *token});

    } 

    return token;
}

Token* SymbolTable::find_lexeme(std::string lexeme) {
    
    Token* token = NULL;

    try {
        token = &(this->table[lexeme]);

    } catch(std::exception e ) {} 

    return token;
}

/**
 * Dado um certo caractere, verificar se o mesmo eh valido na linguagem
 */
bool SymbolTable::is_character_valid(const char c) {
    return std::find(VALID_CHARACTERS.begin(), VALID_CHARACTERS.end(), c) != VALID_CHARACTERS.end();
}

std::string SymbolTable::to_string() {

    std::string result = "";

    for(auto iter = SymbolTable::table.begin(); iter != SymbolTable::table.end(); ++iter) {
        std::string lexeme = iter->first;
        Token token = iter->second;

        result += "lexeme: " + lexeme + "\ttoken: " + token.to_string() + "\n" ;
    }

    return result;
}

#endif
//-----------------------Fim da lib: symbol_table/symbol_table.cpp-----------------------//
//-----------------------Inicio da lib: utils/line_reader.cpp-----------------------//

std::vector<std::string> read_line_until_eof() {
    std::vector<std::string> lines;
    std::string curr_line = "";

    while (std::getline(std::cin, curr_line)) lines.push_back(curr_line);
   
    return lines;
}

//-----------------------Fim da lib: utils/line_reader.cpp-----------------------//
//-----------------------Inicio da lib: file/l_file.cpp-----------------------//
#ifndef L_FILE_CPP
#define L_FILE_CPP

#include<utility>

typedef std::pair<int, std::string> line_and_number;

class LFile {
private:
    std::vector<std::string> lines;
    std::vector<std::string>::iterator curr_line_iterator;
    std::vector<std::string>::iterator end_iterator;
    int num_lines;
    int curr_line;
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
    this->end_iterator = this->lines.end();
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
    this->curr_line_iterator++;

    return {curr_line_number, curr_line};
}

bool LFile::is_end_of_file() {
    return this->curr_line_iterator == this->end_iterator;
}

int LFile::get_num_lines() {
    return this->num_lines;
}

#endif
//-----------------------Fim da lib: file/l_file.cpp-----------------------//
//-----------------------Inicio da lib: analyzers/lexical_analyzer.cpp-----------------------//
#ifndef LEXICAL_ANALYZER_CPP
#define LEXICAL_ANALYZER_CPP

#include<locale>

class LexicalAnalyzer {
    private:
        LFile file_to_analyze;
        uint8_t curr_state;
        SymbolTable symbol_table;

        const uint8_t END_STATE = 1;
        const uint8_t FIRST_STATE = 0;

    public:
        LexicalAnalyzer(LFile* file);
        ~LexicalAnalyzer();

        void analyze();
        bool is_valid_token(const char c);
};

LexicalAnalyzer::LexicalAnalyzer(LFile* file) {
    this->file_to_analyze = *file;
    this->curr_state = 0;
    this->symbol_table = SymbolTable();
}

LexicalAnalyzer::~LexicalAnalyzer() {}

// Função do Analisador Léxico.
void LexicalAnalyzer::analyze()
{
    curr_state = FIRST_STATE;

    std::string lexeme;

    while (curr_state != END_STATE) {

        if (file_to_analyze.is_end_of_file()) 
            break;
        
        auto curr_line = file_to_analyze.get_curr_line();

        std::string line = curr_line.second;
        int line_number  = curr_line.first;

        for (char const &curr_char : line) {
            if(!is_valid_token(curr_char)) {
                std::cout << line_number << "\n" << "caractere invalido." << "\n";
                exit(1);
            }
        }
    }
}

bool LexicalAnalyzer::is_valid_token(const char c) {
    return std::isalnum(c) || this->symbol_table.is_character_valid(c);
}
            
        

#endif
//-----------------------Fim da lib: analyzers/lexical_analyzer.cpp-----------------------//

LFile get_file_from_stream(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    SymbolTable st = SymbolTable();
    LFile file = get_file_from_stream(argc,argv);

    LexicalAnalyzer la = LexicalAnalyzer(&file);

    la.analyze();

    std::cout << file.get_num_lines() + 1 << " linhas compiladas." << "\n";
    
    return 0;
}

/**
 * Checar de onde esta vindo o arquivo de entrada e 
 * separar de forma correta para ser lido futuramente
 */
LFile get_file_from_stream(int argc, char* argv[]) {

    LFile file = LFile();

    // Ler arquivo direto pelo pub.in
    if (argc == 1) {
        std::vector<std::string> file_lines;
        file_lines = read_line_until_eof();

        file.read_file_from_vector(&file_lines);
    }
    //Ler arquivo pela path dele 
    else if (argc >= 2) {

        std::string path(argv[2]);
    } else {

        exit(1);
    }

    return file;
}
