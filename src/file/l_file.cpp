#ifndef L_FILE_CPP
#define L_FILE_CPP

#include<string>
#include<vector>
#include<pair>

typedef std::pair<int, std::string> line_and_number;

class LFile {
private:
    std::string* lines;
    int num_lines;
    int curr_line;
public:
    LFile(std::vector<std::string>* arr = NULL);
    ~LFile();
    void read_file_from_vector(std::vector<std::string>* arr);
    std::string to_string();

    line_and_number get_curr_line();
    bool is_end_of_file();
};

LFile::LFile(std::vector<std::string>* arr = NULL) {
    if (arr == NULL) {
        num_lines = 0;
        lines = NULL;
    } else {
        read_file_from_vector(arr);
    }
    curr_line = 1;
}

LFile::~LFile() {
    if (lines != NULL)
        delete[] lines;
}

void LFile::read_file_from_vector(std::vector<std::string>* arr) {

    this->num_lines = arr->size();
    this->lines = new std::string[this->num_lines];
    std::copy(arr->begin(),arr->end(),this->lines);
}

std::string LFile::to_string() {
    std::string s = + " num of lines: " + std::to_string(this->num_lines) + '\n';

    for(int i = 0; i < this->num_lines; i++) {
        s += this->lines[i] + "\n";
    }
    return s;
}

line_and_number LFile::get_curr_line() {

    int curr_line_number = this->curr_line;
    std::string curr_line = this->lines[this->curr_line++] + "\n";

    return {curr_line_number, curr_line}
}

bool LFile::is_end_of_file() {
    return curr_line == num_lines -1;
}

#endif