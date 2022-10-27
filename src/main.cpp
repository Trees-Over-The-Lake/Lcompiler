#include<iostream>
#include<vector>
#include<string>
#include<string.h>

#include"utils/file_stream_reader.cpp"
#include"symbol_table/symbol_table.cpp"
#include"file/l_file.cpp"
#include"analyzers/lexical_analyzer.cpp"
#include"analyzers/parser.cpp"

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
