#ifndef UTIL_FILE_STREAM_READER_CPP
#define UTIL_FILE_STREAM_READER_CPP

#include<string.h>

#include"constants.hpp"
#include"../file/l_file.cpp"
#include"line_reader.cpp"


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

#endif 