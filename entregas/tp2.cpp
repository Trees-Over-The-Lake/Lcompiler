#include<iostream>
#include<vector>
#include<string>
#include<string.h>

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
#include<locale>

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
    return std::isalnum(c) ||
           std::find(VALID_CHARACTERS.begin(), VALID_CHARACTERS.end(), c) != VALID_CHARACTERS.end();
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
#ifndef LINE_READER_CPP
#define LINE_READER_CPP

#include<fstream>

std::vector<std::string> read_line_until_eof() {
    std::vector<std::string> lines;
    std::string curr_line = "";

    while (std::getline(std::cin, curr_line)) lines.push_back(curr_line);
   
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

    return lines;
}

#endif
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
    std::string curr_line = *this->curr_line_iterator + "\n";
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

//-----------------------Inicio da lib: ../error_manager/cerror_manager.cpp-----------------------//
#ifndef CERROR_MANAGER_CPP
#define CERROR_MANAGER_CPP


//-----------------------Inicio da lib: cerror_type.cpp-----------------------//
#ifndef CERROR_TYPE_CPP
#define CERROR_TYPE_CPP

enum CErrorType {
    CaractereInvalido,
    LexemaInvalido
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
        
        case LexemaInvalido:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "lexema nao identificado [" + lexema + "].";
            break;
        }
        default:
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
        LFile file_to_analyze;
        int curr_state;
        SymbolTable symbol_table;

        static const std::regex isolate_symbols;

        const uint8_t END_STATE = 1;
        const uint8_t FIRST_STATE = 0;

    public:
        LexicalAnalyzer(LFile* file);
        ~LexicalAnalyzer();
        bool estado0(const char c, iterator* it);
        void estado1(std::string* lexeme, iterator* it);
        bool estado2(const char c, iterator* it);
        bool estado3(const char c, iterator* it);
        bool estado4(const char c, iterator* it);
        bool estado5(const char c, iterator* it);
        bool estado6(const char c, iterator* it);
        bool estado7(const char c, iterator* it);
        bool estado8(const char c, iterator* it);
        bool estado9(const char c, iterator* it);
        bool estado10(const char c, iterator* it);
        bool estado11(const char c, iterator* it);
        bool estado12(const char c, iterator* it);
        bool estado13(const char c, iterator* it);
        bool estado14(const char c, iterator* it);
        bool estado15(const char c, iterator* it);
        bool estado16(const char c, iterator* it);
        bool estado18(const char c, iterator* it);

        void analyze();
};

const std::regex LexicalAnalyzer::isolate_symbols = std::regex(R"(=|%|,|-|\+|;|\(|\)|\*|\[|\]|\{|\})");

LexicalAnalyzer::LexicalAnalyzer(LFile* file) {
    this->file_to_analyze = *file;
    this->curr_state = 0;
    this->symbol_table = SymbolTable();
}

LexicalAnalyzer::~LexicalAnalyzer() {}

bool LexicalAnalyzer::estado0(const char c, iterator* it) {
    bool error_found = false;

    std::string c_string = std::string(1,c);
    
    if(c == ' ' || c == '\n' || c == '\r' || c == '\t') {
        curr_state = 0;
    }
    else if(c == '!') {
        curr_state = 5;
    }
    else if(c == '<' || c == '>') {
        curr_state = 7;
    }
    else if(c == '\'') {
        curr_state = 9;
    }
    else if(c == '_' || std::isalpha(c)) {
        curr_state = 12;
    }
    else if(std::regex_match(c_string, LexicalAnalyzer::isolate_symbols)) {
        curr_state = 1;
    }
    else if(c == '0') {
        curr_state = 6;
    }
    else if(std::isdigit(c) && c != '0') {
        curr_state = 18;
    }
    else if(c == '.') {
        curr_state = 13;
    }
    else if(c == '"') {
        curr_state = 11;
    }
    else if(c == ':') {
        curr_state = 8;
    }
    else if(c == '/') {
        curr_state = 2;
    }
    else {
        error_found = true;
    }

    return error_found;
}

void LexicalAnalyzer::estado1(std::string* lexeme, iterator* it) {
    *lexeme = "";
    curr_state = 0;
    --*it;
}

bool LexicalAnalyzer::estado2(const char c, iterator* it) {
    if(c == '*') {
        curr_state = 3;
    }
    else {
        --*it;
        curr_state = 1;
    }

    return false;
}

bool LexicalAnalyzer::estado3(const char c, iterator* it) {
    if(c == '*') {
        curr_state = 4;
    }
    else {
        curr_state = 3;
    }

    return false;
}

bool LexicalAnalyzer::estado4(const char c, iterator* it) {
    if(c == '*') {
        curr_state = 4;
    }
    else if (c == '/'){
        curr_state = 0;
    }
    else {
        curr_state = 3;
    }

    return false;  
}

bool LexicalAnalyzer::estado5(const char c, iterator* it) {
    bool error_found = false;
    
    if (c == '=') {
        curr_state = 1;
    }
    else {
        error_found = true;
    }

    return error_found;    
}

bool LexicalAnalyzer::estado6(const char c, iterator* it) {
    if (c == 'x') {
        curr_state = 15;
    }
    else if (std::isdigit(c)) {
        curr_state = 18;
    }
    else {
        --*it;
        curr_state = 1;
    }

    return false;  
}

bool LexicalAnalyzer::estado7(const char c, iterator* it) {
    if (c == '=') {
        curr_state = 1;
    }
    else {
        --*it;
        curr_state = 1;
    }

    return false;  
}

bool LexicalAnalyzer::estado8(const char c, iterator* it) {
    bool error_found = false;
    
    if (c == '=') {
        curr_state = 1;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado9(const char c, iterator* it) {
    if (std::isalnum(c)) {
        curr_state = 10;
    }

    return false;  
}

bool LexicalAnalyzer::estado10(const char c, iterator* it) {
    bool error_found = false;
    
    if (c == '\'') {
        curr_state = 1;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado11(const char c, iterator* it) {
    bool error_found = false;
    
    if (std::isalnum(c)) {
        curr_state = 11;
    }
    else if (c == '"'){
        curr_state = 1;
    } 
    else if(c == '\n') {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado12(const char c, iterator* it) {
    if (std::isdigit(c) || std::isalpha(c) || c == '_') {
        curr_state = 12;
    }
    else {
        --*it;        
        curr_state = 1;
    }

    return false;  
}

bool LexicalAnalyzer::estado13(const char c, iterator* it) {
    bool error_found = false;
    
    if (std::isdigit(c)) {
        curr_state = 14;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado14(const char c, iterator* it) {
    if (std::isalnum(c)) {
        curr_state = 14;
    }
    else {
        --*it;        
        curr_state = 1;   
    }

    return false;  
}

bool LexicalAnalyzer::estado15(const char c, iterator* it) {
    bool error_found = false;
    
    if (std::isxdigit(c)) {
        curr_state = 16;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado16(const char c, iterator* it) {
    bool error_found = false;
    
    if (std::isxdigit(c)) {
        curr_state = 1;
    }
    else {
        error_found = true;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado18(const char c, iterator* it) {
    if (std::isdigit(c)) {
        curr_state = 18;
    }
    else if (c == '.') {
        curr_state = 14;
    }
    else {
        --*it;        
        curr_state = 1;
    }

    return false;  
}

// Função do Analisador Léxico.
void LexicalAnalyzer::analyze()
{
    curr_state = FIRST_STATE;

    std::string lexeme;

    while (!file_to_analyze.is_end_of_file()) {
        
        auto curr_line = file_to_analyze.get_curr_line();

        std::string line = curr_line.second;
        int line_number  = curr_line.first;

        for (auto it = line.cbegin(); it != line.cend(); ++it) {
            char curr_char = *it;

            if(!this->symbol_table.is_character_valid(curr_char)) 
                throw_compiler_error(CErrorType::CaractereInvalido, 
                                    {std::to_string(line_number)});

            bool error_detected = false;

            // Automato
            switch (curr_state)
            {
                case 0:
                    error_detected = estado0(curr_char,&it);
                break;
                case 1:

                    estado1(&lexeme,&it);
                    continue;

                case 2:
                    error_detected = estado2(curr_char,&it);
                break;
                case 3:
                    error_detected = estado3(curr_char,&it);
                break;
                case 4:
                    error_detected = estado4(curr_char,&it);
                break;
                case 5:
                    error_detected = estado5(curr_char,&it);
                break;
                case 7:
                    error_detected = estado7(curr_char,&it);
                break;
                case 11:
                    error_detected = estado11(curr_char,&it);
                break;
                case 8:
                    error_detected = estado8(curr_char,&it);
                break;
                case 12:
                    error_detected = estado12(curr_char,&it);
                break;
                case 9:
                    error_detected = estado9(curr_char,&it);
                break;
                case 10:
                    error_detected = estado10(curr_char,&it);
                break;
                case 6:
                    error_detected = estado6(curr_char,&it);
                break;
                case 18:
                    error_detected = estado18(curr_char,&it);
                break;
                case 15:
                    error_detected = estado15(curr_char,&it);
                break;
                case 14:
                    error_detected = estado14(curr_char,&it);
                break;
                case 13:
                    error_detected = estado13(curr_char,&it);
                break;
                case 16:
                    error_detected = estado16(curr_char,&it);
                break;

                default:

                break;
            }

            if(error_detected){
                throw_compiler_error(CErrorType::LexemaInvalido, {std::to_string(line_number), lexeme});
            } 

            lexeme += curr_char;
        }
        lexeme = "";
    }
}               

#endif
//-----------------------Fim da lib: analyzers/lexical_analyzer.cpp-----------------------//

#define DEFAULT_INPUT "pub.in"

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
