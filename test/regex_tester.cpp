#include<iostream>
#include<regex>
#include<string>
#include<locale>

int main(int argc, char* argv[]) {

    //std::cout << "argv[1][0]: " << argv[1][0] << "\n"; 

    /*if (std::regex_match (std::string(1,']'), std::regex(R"(=|%|,|-|;|\(|\)|\*|\[|\])") ))
        std::cout << "string:literal => matched\n";*/

    if (std::isalnum(' ')) {
        std::cout << "cheguei aqui" << "\n";
    }
}