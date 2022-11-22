#ifndef FILE_L_FILE_CPP
#define FILE_L_FILE_CPP

#include<string>
#include<vector>
#include<utility>

// Contents of the file + the number of the line
typedef std::pair<int, std::string> line_and_number;

/**
 * @brief Class storing the contents of the L program
 * 
 */
class LFile {

    private:

        std::vector<std::string> lines;
        std::vector<std::string>::iterator curr_line_iterator;
        int num_lines;
        int curr_line;
        bool file_ended;

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

/**
 * @brief Check weather the file had reached its ending
 * 
 * @return true if the file already ended and 
 * @return false if there is still more content to be read
 */
bool LFile::is_end_of_file() {
    return file_ended;
}


/**
 * @brief Return the number of lines inside of the file
 * 
 * @return an integer containing the number of lines
 */
int LFile::get_num_lines() {
    return this->num_lines;
}

/**
 * @brief From the contents of the vector assign as the content of file
 * 
 * @param arr is the vector to be read
 */
void LFile::read_file_from_vector(std::vector<std::string>* arr) {

    this->num_lines = arr->size();
    this->lines = *arr;
    this->curr_line_iterator = this->lines.begin();
    this->file_ended = false;
}

/**
 * @brief Tranform the contents of the class into a string
 * 
 * @return std::string is the string representation of the file contents
 */
std::string LFile::to_string() {
    std::string s = + " num of lines: " + std::to_string(this->num_lines) + '\n';

    for(int i = 0; i < this->num_lines; i++) 
        s += this->lines[i] + "\n";

    return s;
}

/**
 * @brief Get the current line from the file
 * 
 * @return the line content and the line number of said line
 */
line_and_number LFile::get_curr_line() {

    int curr_line_number = this->curr_line++;

    std::string curr_line = *this->curr_line_iterator;
        
    curr_line += '\0';
    
    this->curr_line_iterator++;

    if (this->curr_line > num_lines) 
        file_ended = true;

    return {curr_line_number, curr_line};
}

#endif