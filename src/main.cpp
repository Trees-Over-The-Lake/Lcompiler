#include<iostream>
#include<vector>
#include<string>

#include"symbol_table/symbol_table.cpp"
#include"utils/line_reader.cpp"
#include"file/l_file.cpp"
#include"analyzers/lexical_analyzer.cpp"

LFile get_file_from_stream(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    SymbolTable st = SymbolTable();
    LFile file = get_file_from_stream(argc,argv);

    LexicalAnalyzer la = new LexicalAnalyzer(&file);

    la.analyze();
    
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
