#include<iostream>
#include<vector>
#include<algorithm>
#include<string>

std::vector<std::string> read_line_until_eof() {
    std::vector<std::string> lines;
    std::string curr_line = "";

    while (std::getline(std::cin, curr_line)) lines.push_back(curr_line);
   
    return lines;
}
