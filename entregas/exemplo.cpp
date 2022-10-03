#include<iostream>
#include<string>

int main(int argc, char* argv[]) {
    
    std::string line;
    int i = 0;

    //Enquanto nao for EOF, contar numero de linhas
    while (std::getline(std::cin, line)) i++;
    
    std::cout << ++i << " linhas compiladas." << std::endl;
    
    return 0;
}