#ifndef ANALYZERS_LEXICAL_ANALYZER
#define ANALYZERS_LEXICAL_ANALYZER

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

        bool estado0(const char c, std::string* lexeme, Token_pointer& token);
        Token_pointer estado1(std::string* lexeme, Token_pointer& token);
        bool estado2(const char c, std::string* lexeme, Token_pointer& token);
        bool estado3(const char c, std::string* lexeme, Token_pointer& token);
        bool estado4(const char c, std::string* lexeme, Token_pointer& token);
        bool estado5(const char c, std::string* lexeme, Token_pointer& token);
        bool estado6(const char c, std::string* lexeme, Token_pointer& token);
        bool estado7(const char c, std::string* lexeme, Token_pointer& token);
        bool estado8(const char c, std::string* lexeme, Token_pointer& token);
        bool estado9(const char c, std::string* lexeme, Token_pointer& token);
        bool estado10(const char c, std::string* lexeme, Token_pointer& token);
        bool estado11(const char c, std::string* lexeme, Token_pointer& token);
        bool estado12(const char c, std::string* lexeme, Token_pointer& token);
        bool estado13(const char c, std::string* lexeme, Token_pointer& token);
        bool estado14(const char c, std::string* lexeme, Token_pointer& token);
        bool estado15(const char c, std::string* lexeme, Token_pointer& token);
        bool estado16(const char c, std::string* lexeme, Token_pointer& token);
        bool estado17(const char c, std::string* lexeme, Token_pointer& token);
        bool estado18(const char c, std::string* lexeme, Token_pointer& token);
        bool estado19(const char c, std::string* lexeme, Token_pointer& token);

    public:
        LexicalAnalyzer(LFile* file);
        ~LexicalAnalyzer();

        int get_curr_line_number();

        Token_pointer get_next_token();
        bool no_more_tokens();
};

const std::regex LexicalAnalyzer::isolate_symbols = std::regex(R"(=|%|,|-|\+|;|\(|\)|\*|\[|\]|\{|\})");

/**
 * @brief Constructor for LexicalAnalyzer class 
 * @param file LFile* to be read by analyzer
*/
LexicalAnalyzer::LexicalAnalyzer(LFile* file) {
    this->file_to_analyze = file;
    this->curr_state = 0;
    this->symbol_table = SymbolTable();

    this->file_ended = false;

    if(!file_to_analyze->is_end_of_file())
        update_curr_line();
}

/**
 * @brief Destructor for LexicalAnalyzer class 
*/
LexicalAnalyzer::~LexicalAnalyzer() {}

/**
 * @brief Changes the line of the file that is being read
*/
void LexicalAnalyzer::update_curr_line() {
    auto curr_line = file_to_analyze->get_curr_line();

    this->curr_line = curr_line.second;
    this->curr_line_number = curr_line.first;

    this->line_start = this->curr_line.cbegin();
    this->line_end = this->curr_line.cend();

    this->curr_char = this->line_start;
}

/**
 * @brief Returns the char
*/
void LexicalAnalyzer::return_char() {
    --curr_char;
}

/**
 * @brief Goes for the next char
*/
void LexicalAnalyzer::next_char() {
    ++curr_char;
}

/**
 * @return End of File (EOF)
*/
bool LexicalAnalyzer::no_more_tokens() {
    return this->file_ended;
}

/**
 * @return Current line number of the file
*/
int LexicalAnalyzer::get_curr_line_number() {
    return curr_line_number;
}

/**
 * @brief State 0 (initial state) of the Deterministic Finite Automaton
 * @param c char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado0(const char c, std::string* lexeme, Token_pointer& token) {
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
    else if (c == '&') {
        token->set_tipo(LOGICO);
        curr_state = 19;
        *lexeme += c;
    }
    else {
        error_found = true;
    }

    return error_found;
}

/**
 * @brief State 1 (final state) of the Deterministic Finite Automaton
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return Token_pointer of current Token 
*/
Token_pointer LexicalAnalyzer::estado1(std::string* lexeme, Token_pointer& token) {

    if (token->get_classe() == CONSTANTE) {
        token->set_id(TokenID::CONST);
        token->set_lexema(*lexeme);

        token_size new_token_size = symbol_table.get_token_type_size(token->get_tipo(),token->get_lexema());
        token->set_tamanho(new_token_size);
        
    } else {
        token = this->symbol_table.add_id(*lexeme);
    }

    *lexeme = "";
    return token;
}

/**
 * @brief State 2 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado2(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 3 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado3(const char c, std::string* lexeme, Token_pointer& token) {

    if(c == '*') {
        curr_state = 4;
    }
    else {
        curr_state = 3;
    }

    return false;
}

/**
 * @brief State 4 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado4(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 5 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado5(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 6 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado6(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 7 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado7(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 8 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado8(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 9 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado9(const char c, std::string* lexeme, Token_pointer& token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if (std::isalnum(c)) {
        curr_state = 10;
        *lexeme += c;
    }

    return error_found;  
}

/**
 * @brief State 10 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado10(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 11 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado11(const char c, std::string* lexeme, Token_pointer& token) {


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

/**
 * @brief State 12 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado12(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 13 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado13(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 14 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado14(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 15 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado15(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 16 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado16(const char c, std::string* lexeme, Token_pointer& token) {

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

/**
 * @brief State 17 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado17(const char c, std::string* lexeme, Token_pointer& token) {

    bool error_found = false;

    if(c == '\0') {
        error_found = true;

    } else if(std::isdigit(c)) {
        curr_state = 17;
        *lexeme += c;
    }
    else if (c == '.') {
        token->set_tipo(REAL);
        curr_state = 14;
        *lexeme += c;
    }
    else {     
        curr_state = 1;
        return_char();
    }

    return error_found;  
}

/**
 * @brief State 18 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado18(const char c, std::string* lexeme, Token_pointer& token) {
    bool error_found = false;

    if (c == '|') {
        curr_state = 1;
        *lexeme += c;
    } else {
        error_found = true;
    }

    return error_found;
}

/**
 * @brief State 19 of the Deterministic Finite Automaton
 * @param c const char to be analyzed 
 * @param lexeme string* to be analyzed
 * @param token Token_pointer& to set certain parameters for the token
 * @return bool to verify if an error has occurred 
*/
bool LexicalAnalyzer::estado19(const char c, std::string* lexeme, Token_pointer& token) {
    bool error_found = false;

    if (c == '&') {
        curr_state = 1;
        *lexeme += c;
    } else {
        error_found = true;
    }

    return error_found;
}

/**
 * @brief Lexical Analyser function
 * @return Token_pointer of the next token
*/
Token_pointer LexicalAnalyzer::get_next_token()
{
    Token_pointer next_token = std::make_shared<Token>();

    curr_state = FIRST_STATE;

    std::string lexeme;

    if (file_ended) {
        return next_token;
    }


    while (curr_state != END_STATE) {

        if(this->curr_char == this->line_end) {

            if(this->file_to_analyze->is_end_of_file()){
                next_token->set_lexema("\0");
                estado1(&lexeme,next_token);
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
                error_detected = estado0(c,&lexeme,next_token);
                break;

            case 2:
                error_detected = estado2(c,&lexeme,next_token);
                break;

            case 3:
                error_detected = estado3(c,&lexeme,next_token);
                break;

            case 4:
                error_detected = estado4(c,&lexeme,next_token);
                break;

            case 5:
                error_detected = estado5(c,&lexeme,next_token);
                break;

            case 6:
                error_detected = estado6(c,&lexeme,next_token);
                break;

            case 7:
                error_detected = estado7(c,&lexeme,next_token);
                break;

            case 8:
                error_detected = estado8(c,&lexeme,next_token);
                break;

            case 9:
                error_detected = estado9(c,&lexeme,next_token);
                break;

            case 10:
                error_detected = estado10(c,&lexeme,next_token);
                break;

            case 11:
                error_detected = estado11(c,&lexeme,next_token);
                break;

            case 12:
                error_detected = estado12(c,&lexeme,next_token);
                break;

            case 13:
                error_detected = estado13(c,&lexeme,next_token);
                break;

            case 14:
                error_detected = estado14(c,&lexeme,next_token);
                break;

            case 15:
                error_detected = estado15(c,&lexeme,next_token);
                break;

            case 16:
                error_detected = estado16(c,&lexeme,next_token);
                break;

            case 17:
                error_detected = estado17(c,&lexeme,next_token);
                break;

            case 18:
                error_detected = estado18(c,&lexeme,next_token);
                break;
            
            case 19:
                error_detected = estado19(c,&lexeme,next_token);
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
            estado1(&lexeme,next_token);
        }
    }

    if(file_ended && curr_state != 0) {
        throw_compiler_error(CErrorType::FimDeArquivoNaoEsperado, {std::to_string(this->curr_line_number+1)});
    }

    return next_token;
}               

#endif