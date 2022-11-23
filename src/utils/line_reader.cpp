#ifndef UTIL_LINE_READER_CPP
#define UTIL_LINE_READER_CPP

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>

/**
 * @brief Read lines from the keyboard until eof
 * 
 * @return std::vector<std::string> is the lines read from the keyboard
 */
std::vector<std::string> read_line_until_eof() {
    std::vector<std::string> lines;
    std::string curr_line = "";

    while (std::getline(std::cin, curr_line)) lines.push_back(curr_line);
   
    return lines;
}

/**
 * @brief Read lines from a file, and return a vector of strings containing them
 * 
 * @param file_path is the file path containg the file to be read
 * @return std::vector<std::string> is the content of the file in a string vector
 */
std::vector<std::string> read_lines_from_file(std::string file_path) {
    std::fstream file;
    file.open(file_path, std::ios::in);

    std::vector<std::string> lines;
    std::string curr_line = "";

    if (file.is_open()) {
        while (std::getline(file, curr_line)) lines.push_back(curr_line);

        file.close();
    } else {
        std::cout << "Erro! the file does not " << file_path << "exist!" << "\n";
        exit(1);
    }

    return lines;
}

#endif