#ifndef LEXICAL_ANALYZER_CPP
#define LEXICAL_ANALYZER_CPP

#include"../file/l_file.cpp"
#include"../symbol_table/symbol_table.cpp"
#include"../error_manager/cerror_manager.cpp"
#include<cstdint>
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

        bool estado0(const char c, std::string* lexeme);
        Token estado1(std::string* lexeme);
        bool estado2(const char c, std::string* lexeme);
        bool estado3(const char c, std::string* lexeme);
        bool estado4(const char c, std::string* lexeme);
        bool estado5(const char c, std::string* lexeme);
        bool estado6(const char c, std::string* lexeme);
        bool estado7(const char c, std::string* lexeme);
        bool estado8(const char c, std::string* lexeme);
        bool estado9(const char c, std::string* lexeme);
        bool estado10(const char c, std::string* lexeme);
        bool estado11(const char c, std::string* lexeme);
        bool estado12(const char c, std::string* lexeme);
        bool estado13(const char c, std::string* lexeme);
        bool estado14(const char c, std::string* lexeme);
        bool estado15(const char c, std::string* lexeme);
        bool estado16(const char c, std::string* lexeme);
        bool estado18(const char c, std::string* lexeme);

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

bool LexicalAnalyzer::estado0(const char c, std::string* lexeme) {
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
    else if(c == '\'') {
        curr_state = 9;
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
        curr_state = 6;
        *lexeme += c;
    }
    else if(std::isdigit(c) && c != '0') {
        curr_state = 18;
        *lexeme += c;
    }
    else if(c == '.') {
        curr_state = 13;
        *lexeme += c;
    }
    else if(c == '"') {
        curr_state = 11;
        *lexeme += c;
    }
    else if(c == ':') {
        curr_state = 8;
        *lexeme += c;
    }
    else if(c == '/') {
        curr_state = 2;
    }
    else {
        error_found = true;
    }

    return error_found;
}

Token LexicalAnalyzer::estado1(std::string* lexeme) {

    Token token;
    token.set_lexema(*lexeme);

    *lexeme = "";

    return token;
}

bool LexicalAnalyzer::estado2(const char c, std::string* lexeme) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;
    }
    if(c == '*') {
        curr_state = 3;
    }
    else {
        return_char();
        curr_state = 1;
    }

    return error_found;
}

bool LexicalAnalyzer::estado3(const char c, std::string* lexeme) {

    if(c == '*') {
        curr_state = 4;
    }
    else {
        curr_state = 3;
    }

    return false;
}

bool LexicalAnalyzer::estado4(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado5(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado6(const char c, std::string* lexeme) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (c == 'x') {
        curr_state = 15;
        *lexeme += c;
    }
    else if (std::isdigit(c)) {
        curr_state = 18;
        *lexeme += c;
    }
    else {
        return_char();
        curr_state = 1;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado7(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado8(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado9(const char c, std::string* lexeme) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isalnum(c)) {
        curr_state = 10;
        *lexeme += c;
    }

    return error_found;  
}

bool LexicalAnalyzer::estado10(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado11(const char c, std::string* lexeme) {


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

bool LexicalAnalyzer::estado12(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado13(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado14(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado15(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado16(const char c, std::string* lexeme) {

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

bool LexicalAnalyzer::estado18(const char c, std::string* lexeme) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if(std::isdigit(c)) {
        curr_state = 18;
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

        // Automato
        switch (curr_state)
        {
            case 0:
                error_detected = estado0(c,&lexeme);
                break;

            case 2:
                error_detected = estado2(c,&lexeme);
                break;

            case 3:
                error_detected = estado3(c,&lexeme);
                break;

            case 4:
                error_detected = estado4(c,&lexeme);
                break;

            case 5:
                error_detected = estado5(c,&lexeme);
                break;

            case 7:
                error_detected = estado7(c,&lexeme);
                break;

            case 11:
                error_detected = estado11(c,&lexeme);
                break;

            case 8:
                error_detected = estado8(c,&lexeme);
                break;

            case 12:
                error_detected = estado12(c,&lexeme);
                break;

            case 9:
                error_detected = estado9(c,&lexeme);
                break;

            case 10:
                error_detected = estado10(c,&lexeme);
                break;

            case 6:
                error_detected = estado6(c,&lexeme);
                break;

            case 18:
                error_detected = estado18(c,&lexeme);
                break;

            case 15:
                error_detected = estado15(c,&lexeme);
                break;

            case 14:
                error_detected = estado14(c,&lexeme);
                break;

            case 13:
                error_detected = estado13(c,&lexeme);
                break;

            case 16:
                error_detected = estado16(c,&lexeme);
                break;

            default:

                break;
        }

        if(error_detected){

            if ( this->file_to_analyze->is_end_of_file()) 
                throw_compiler_error(CErrorType::FimDeArquivoNaoEsperado, 
                                    {std::to_string(this->curr_line_number)});
            else 
                throw_compiler_error(CErrorType::LexemaInvalido, 
                                    {std::to_string(this->curr_line_number), lexeme});
        } 

        next_char();

        if(curr_state == END_STATE) {
            next_token = estado1(&lexeme);
        }
    }

    if(file_ended && curr_state != 0) {
        throw_compiler_error(CErrorType::FimDeArquivoNaoEsperado, {std::to_string(this->curr_line_number+1)});
    }

    return next_token;
}               

#endif