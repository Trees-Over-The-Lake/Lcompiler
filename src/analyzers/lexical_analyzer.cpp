#ifndef LEXICAL_ANALYZER_CPP
#define LEXICAL_ANALYZER_CPP

#include"../file/l_file.cpp"
#include"../symbol_table/symbol_table.cpp"
#include<cstdint>
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