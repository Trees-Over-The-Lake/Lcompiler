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

    switch (error_type) {
        case CaractereInvalido:
            error_information = "caractere invalido.";
            break;

        case FimDeArquivoNaoEsperado:
            error_information = "fim de arquivo nao esperado.";
            break;        

        case LexemaInvalido:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "lexema nao identificado [" + lexema + "].";
            break;
        }
        case TokenNaoEsperado:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "token nao esperado [" + lexema + "].";
            break;
        } 
        case IdentificadorNaoDeclarado:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "identificador nao declarado [" + lexema + "].";
            break;
        }
        case IdentificadorJaDeclarado:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "identificador ja declarado [" + lexema + "].";
            break;        
        }
        case ClasseDeIdentificadorIncompativel:
        {
            std::string lexema = error_content[ERROR_DETAIL];
            error_information = "classe de identificador incompativel [" + lexema + "].";
            break;
        }
        case TiposIncompativeis:
        {
            error_information = "tipos incompativeis";
            break;
        } 
        case TamanhoVetorExcedido:
        {
            error_information = "tamanho de vetor excedido";
            break;
        }
        default:
        {
            error_information = "erro não informado";
            break;
        }
    }  

    CError error = CError(line_error, error_information);
    std::cout << error.to_string() << "\n";
    exit(1);
}

#endif