#ifndef UTIL_FILE_STREAM_READER_CPP
#define UTIL_FILE_STREAM_READER_CPP

#include<string.h>

#include"constants.hpp"
#include"../file/l_file.cpp"
#include"line_reader.cpp"


/**
 * @brief Through argc and argv check through where the content that needs to be read is 
 * coming from
 * 
 * @param argc is the argument counter 
 * @param argv is the argument vector
 * @return LFile is the file containg the file with the L language code
 */
LFile get_file_from_stream(int argc, char* argv[]) {

    LFile file = LFile();
    std::vector<std::string> file_lines;

    // Read pub.in
    if (argc == 1) {
        file_lines = read_line_until_eof();
    }
    //Read from path inside argv
    else if (argc >= 2) {

        std::string file_path;

        // Path not specified, try to find the DEFAULT_INPUT inside CWD
        if (strlen(argv[1]) == 0) 
            file_path = DEFAULT_INPUT;
            
        else  // Path specified, read that
            file_path = std::string(argv[2]);
        
        file_lines = read_lines_from_file(DEFAULT_INPUT);
    
    } else {
        std::cout << "Error! Impossible to read input" << "\n";
        exit(1);
    }

    file.read_file_from_vector(&file_lines);

    return file;
}

#endif 