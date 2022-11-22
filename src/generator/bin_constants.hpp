#ifndef GENERATOR_BIN_CONSTANTS_HPP
#define GENERATOR_BIN_CONSTANTS_HPP

// Linux Executable and Linkable File Default Header
const char *ELF_HEADER = "global _start\n\tsection .data\n\nM:\n\tresb 10000h\n\tsection .text\n\n_start:\n";

// Maximum binary size
const int MAX_BIN_SIZE = 0x10000;

// Size for each variable type
const int L_CHAR_SIZE = 0x1;
const int L_NUMBER_SIZE = 0x4;
const int L_STRING_SIZE = 0x100;
const int L_BOOLEAN_SIZE = 0x1;

#endif