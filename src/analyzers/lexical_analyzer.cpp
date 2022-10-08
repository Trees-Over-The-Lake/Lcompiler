#ifndef LEXICAL_ANALYZER_CPP
#define LEXICAL_ANALYZER_CPP

#include"../file/l_file.cpp"
#include"../symbol_table/symbol_table.cpp"
#include"../error_manager/cerror_manager.cpp"
#include<cstdint>

typedef std::string::const_iterator iterator;

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
        bool estado0(const char c, iterator* it);
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

LexicalAnalyzer::LexicalAnalyzer(LFile* file) {
    this->file_to_analyze = *file;
    this->curr_state = 0;
    this->symbol_table = SymbolTable();
}

LexicalAnalyzer::~LexicalAnalyzer() {}

bool LexicalAnalyzer::estado0(const char c, iterator* it) {
    bool error_found = false;
    
    if(c == ' ' || c == '\n') {
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
    else if(c == '=' || c == '%' || c == '(' || c == ')' || c == '*' || c == '+' || c == ',' || c == '-' || c == ';' || c == '[' || c == ']') {
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
    if (std::isalnum(c)) {
        curr_state = 11;
    }
    else if (c == '"'){
        curr_state = 1;
    }

    return c;  
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

    while (curr_state != END_STATE) {

        if (file_to_analyze.is_end_of_file()) 
            break;
        
        auto curr_line = file_to_analyze.get_curr_line();

        std::string line = curr_line.second;
        int line_number  = curr_line.first;

        for (auto it = line.cbegin(); it != line.cend(); ++it) {
            char curr_char = *it;

            if(!this->symbol_table.is_character_valid(curr_char)) 
                throw_compiler_error(CErrorType::CaractereInvalido, 
                                    {std::to_string(line_number)});

            bool error_detected = false;

            switch (curr_state)
            {
                case 0:
                    error_detected = estado0(curr_char,&it);
                break;
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

            if(!error_detected){
                throw_compiler_error(CErrorType::LexemaInvalido, {std::to_string(line_number), lexeme});
            } 
            else {
                lexeme += curr_char;
            }

        }
    }
}               

#endif