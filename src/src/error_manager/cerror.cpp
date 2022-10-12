#ifndef CERROR_CPP
#define CERROR_CPP

#include<cstdint>
#include<string>

/**
 * Classe para armazenar logica de erros de compilacao
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

CError::CError(uint32_t line_error, std::string error_information){
    this->error_information = error_information;
    this->line_error = line_error;
}

CError::~CError(){}

std::string CError::to_string() {
    return std::to_string(line_error) + "\n" + error_information;
}

#endif