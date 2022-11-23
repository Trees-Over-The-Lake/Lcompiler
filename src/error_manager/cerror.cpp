#ifndef ERROR_MANAGER_CERROR_HPP
#define ERROR_MANAGER_CERROR_HPP

#include<cstdint>
#include<string>

/**
 * Class to store compilation error logic
 */

class CError {
    private:
        uint32_t line_error;
        std::string error_information;
    public:
        CError(uint32_t line_error, std::string error_information);
        ~CError();

        std::string to_string();
};

// function to identify and return line and type error

CError::CError(uint32_t line_error, std::string error_information){
    this->error_information = error_information;
    this->line_error = line_error;
}

CError::~CError(){}

std::string CError::to_string() {
    return std::to_string(line_error) + "\n" + error_information;
}

#endif