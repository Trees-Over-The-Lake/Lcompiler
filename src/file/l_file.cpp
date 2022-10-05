#ifndef L_FILE_CPP
#define L_FILE_CPP

#include<string>
#include<vector>
#include<utility>

typedef std::pair<int, std::string> line_and_number;

class LFile {
private:
    std::vector<std::string> lines;
    std::vector<std::string>::iterator curr_line_iterator;
    std::vector<std::string>::iterator end_iterator;
    int num_lines;
    int curr_line;
public:
    LFile(std::vector<std::string>* arr = NULL);
    ~LFile();
    void read_file_from_vector(std::vector<std::string>* arr);
    std::string to_string();

    int get_num_lines();

    line_and_number get_curr_line();
    bool is_end_of_file();
};

LFile::LFile(std::vector<std::string>* arr) {
    if (arr == NULL) {
        num_lines = 0;
    } else {
        read_file_from_vector(arr);
    }
    curr_line = 1;
}

LFile::~LFile() {}

void LFile::read_file_from_vector(std::vector<std::string>* arr) {

    this->num_lines = arr->size();
    this->lines = *arr;
    this->curr_line_iterator = this->lines.begin();
    this->end_iterator = this->lines.end();
}

std::string LFile::to_string() {
    std::string s = + " num of lines: " + std::to_string(this->num_lines) + '\n';

    for(int i = 0; i < this->num_lines; i++) 
        s += this->lines[i] + "\n";

    return s;
}

line_and_number LFile::get_curr_line() {

    int curr_line_number = this->curr_line++;
    std::string curr_line = *this->curr_line_iterator;
    this->curr_line_iterator++;

    return {curr_line_number, curr_line};
}

bool LFile::is_end_of_file() {
    return this->curr_line_iterator == this->end_iterator;
}

int LFile::get_num_lines() {
    return this->num_lines;
}

#endif