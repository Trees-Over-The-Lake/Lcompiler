#ifndef ERROR_MANAGER_CERROR_MANAGER_CPP
#define ERROR_MANAGER_CERROR_MANAGER_CPP

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

    // switch to return error messages to the console
    switch (error_type) {
        // error type invalid character
        case CaractereInvalido:
            error_information = "caractere invalido.";
            break;
        // unexpected end of file.
        case FimDeArquivoNaoEsperado:
            error_information = "fim de arquivo nao esperado.";
            break;        

        // unidentified lexeme
        case LexemaInvalido:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "lexema nao identificado [" + lexema + "].";
            break;
        }
        // unexpected token
        case TokenNaoEsperado:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "token nao esperado [" + lexema + "].";
            break;
        } 
        // undeclared identifier
        case IdentificadorNaoDeclarado:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "identificador nao declarado [" + lexema + "].";
            break;
        }
        // identifier already declared
        case IdentificadorJaDeclarado:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "identificador ja declarado [" + lexema + "].";
            break;        
        }
        // mismatched identifier class
        case ClasseDeIdentificadorIncompativel:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "classe de identificador incompativel [" + lexema + "].";
            break;
        }
        // incompatible types
        case TiposIncompativeis:
        {
            error_information = "tipos incompativeis";
            break;
        } 
        // vector size exceeded
        case TamanhoVetorExcedido:
        {
            error_information = "tamanho de vetor excedido";
            break;
        }
        // If the error was not identified within the if, error message not informed
        default:
        {
            error_information = "erro não informado";
            break;
        }
    }  

    // print error message
    CError error = CError(line_error, error_information);
    std::cout << error.to_string() << "\n";
    exit(1);
}

#endif