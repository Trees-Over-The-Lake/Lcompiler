#ifndef CERROR_MANAGER_CPP
#define CERROR_MANAGER_CPP

#include<string>
#include<vector>
#include<cstdint>
#include<iostream>

#include"cerror_type.cpp"
#include"cerror.cpp"

#define LINE_ERROR 0
#define ERROR_DETAIL 1

void throw_compiler_error(CErrorType error_type, std::vector<std::string> error_content) {

    uint32_t line_error = static_cast<uint32_t>(std::stoul(error_content[LINE_ERROR]));  
    std::string error_information = "";

    switch (error_type) {
        case CaractereInvalido:
            error_information = "caractere invalido.";
            break;
        
        case LexemaInvalido:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "lexema nao identificado [" + lexema + "].";
            break;
        }
        default:
            break;
    }  

    CError error = CError(line_error, error_information);
    std::cout << error.to_string() << "\n";
    exit(1);
}

#endif