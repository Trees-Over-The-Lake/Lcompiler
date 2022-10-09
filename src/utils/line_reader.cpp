#ifndef LINE_READER_CPP
#define LINE_READER_CPP

#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include<fstream>

std::vector<std::string> read_line_until_eof() {
    std::vector<std::string> lines;
    std::string curr_line = "";

    while (std::getline(std::cin, curr_line)) lines.push_back(curr_line);
   
    return lines;
}

std::vector<std::string> read_lines_from_file(std::string file_path) {
    std::fstream file;
    file.open(file_path, std::ios::in);

    std::vector<std::string> lines;
    std::string curr_line = "";

    if (file.is_open()) {
        while (std::getline(file, curr_line)) lines.push_back(curr_line);

        file.close();
    } else {
        std::cout << "Erro! Arquivo " << file_path << " não existe!" << "\n";
        exit(1);
    }

    return lines;
}

#endif