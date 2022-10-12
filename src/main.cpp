#include<iostream>
#include<vector>
#include<string>
#include<string.h>

#include"symbol_table/symbol_table.cpp"
#include"utils/line_reader.cpp"
#include"file/l_file.cpp"
#include"analyzers/lexical_analyzer.cpp"

#define DEFAULT_INPUT "pub.in"

LFile get_file_from_stream(int argc, char* argv[]);

int main(int argc, char* argv[]) {

    SymbolTable st = SymbolTable();
    LFile file = get_file_from_stream(argc,argv);

    LexicalAnalyzer la = LexicalAnalyzer(&file);

    while (!la.no_more_tokens()) {
        Token t;
        t = la.get_next_token();

        // TODO: Analisador sintatico vai aqui
        //std::cout << t.to_string() << std::endl;
    }

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
