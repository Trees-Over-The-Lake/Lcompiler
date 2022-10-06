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
        char estado0(const char c, iterator* it);
        char estado2(const char c, iterator* it);
        char estado3(const char c, iterator* it);
        char estado4(const char c, iterator* it);
        char estado5(const char c, iterator* it);
        char estado7(const char c, iterator* it);
        char estado8(const char c, iterator* it);
        char estado9(const char c, iterator* it);
        char estado10(const char c, iterator* it);
        char estado11(const char c, iterator* it);
        char estado12(const char c, iterator* it);

        void analyze();
};

LexicalAnalyzer::LexicalAnalyzer(LFile* file) {
    this->file_to_analyze = *file;
    this->curr_state = 0;
    this->symbol_table = SymbolTable();
}

LexicalAnalyzer::~LexicalAnalyzer() {}

char LexicalAnalyzer::estado0(const char c, iterator* it) {
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
        curr_state = 1;
    }

    return c;
}

char LexicalAnalyzer::estado2(const char c, iterator* it) {
    if(c == '*') {
        curr_state = 3;
    }
    else {
        --*it;
        curr_state = 1;
    }
}

char LexicalAnalyzer::estado3(const char c, iterator* it) {
    if(c == '*') {
        curr_state = 4;
    }
    else {
        curr_state = 3;
    }
}

char LexicalAnalyzer::estado4(const char c, iterator* it) {
    if(c == '*') {
        curr_state = 4;
    }
    else if (c == '/'){
        curr_state = 0;
    }
    else {
        curr_state = 3;
    }
}

char LexicalAnalyzer::estado5(const char c, iterator* it) {
    if (c == '=') {
        curr_state = 1;
    }
}

char LexicalAnalyzer::estado7(const char c, iterator* it) {
    if (c == '=') {
        curr_state = 1;
    }
    else {
        --*it;
        curr_state = 1;
    }
}

char LexicalAnalyzer::estado8(const char c, iterator* it) {
    if (c == '=') {
        curr_state = 1;
    }
}

char LexicalAnalyzer::estado9(const char c, iterator* it) {
    if (std::isalnum(c)) {
        curr_state = 10;
    }
}

char LexicalAnalyzer::estado10(const char c, iterator* it) {
    if (c == '\'') {
        curr_state = 1;
    }
}

char LexicalAnalyzer::estado11(const char c, iterator* it) {
    if (std::isalnum(c)) {
        curr_state = 11;
    }
    else if (c == '"'){
        curr_state = 1;
    }
}

char LexicalAnalyzer::estado12(const char c, iterator* it) {
    if (std::isdigit(c) || std::isalpha(c) || c == '_') {
        curr_state = 12;
    }
    else {
        --*it;        
        curr_state = 1;
    }
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
            switch (curr_state)
            {
                case 0:
                    lexeme += estado0(curr_char,&it);
                break;
                case 2:
                    lexeme += estado2(curr_char,&it);
                break;
                case 3:
                    lexeme += estado3(curr_char,&it);
                break;
                case 4:
                    lexeme += estado4(curr_char,&it);
                break;
                case 5:
                    lexeme += estado5(curr_char,&it);
                break;
                case 7:
                    lexeme += estado7(curr_char,&it);
                break;
                case 11:
                    lexeme += estado11(curr_char,&it);
                break;
                case 8:
                    lexeme += estado8(curr_char,&it);
                break;
                case 12:
                    lexeme += estado12(curr_char,&it);
                break;
                case 9:
                    lexeme += estado9(curr_char,&it);
                break;
                case 10:
                    lexeme += estado10(curr_char,&it);
                break;


                default:
                
                break;
            }
        }
    }
}               

#endif