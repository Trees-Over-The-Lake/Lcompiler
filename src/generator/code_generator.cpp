#ifndef CODE_GENERATOR_CPP
#define CODE_GENERATOR_CPP

#include<string>
#include<fstream>
#include"../utils/constants.hpp"

class CodeGenerator {
    private:
        std::string asm_file_path;
        std::ofstream asm_file;

        long memory_counter;
        long temporary_counter;
    public:
        CodeGenerator(std::string asm_file_path = DEFAULT_OUTPUT_FILE);
        ~CodeGenerator();

        void write_into_file(std::string s);
};

CodeGenerator::CodeGenerator(std::string asm_file_path)
{
    this->asm_file_path = asm_file_path;
    this->asm_file.open(asm_file_path);

    this->memory_counter = 0x10000;
    this->temporary_counter = 0x0;
    this->write_into_file("global _start\nsection .data\nM:\nresb 10000h\nsection .text\n_start:\n");
}

CodeGenerator::~CodeGenerator()
{
    this->asm_file.close();
}

void CodeGenerator::write_into_file(std::string s) {
    this->asm_file << s << std::endl;
}

#endif
