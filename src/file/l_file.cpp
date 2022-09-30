#ifndef L_FILE_CPP
#define L_FILE_CPP

#include<string>
#include<vector>

class LFile {
private:
    std::string* lines;
    int num_lines;
public:
    LFile();
    ~LFile();
    void read_file_from_vector(std::vector<std::string>* arr);
    std::string to_string();
};

LFile::LFile() {}

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

#endif