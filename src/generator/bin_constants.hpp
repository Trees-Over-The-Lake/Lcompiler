#ifndef GENERATOR_BIN_CONSTANTS_HPP
#define GENERATOR_BIN_CONSTANTS_HPP

// Linux Executable and Linkable File Default Header
const char *ELF_HEADER = "global _start\n\tsection .data\n\nM:\n\tresb 10000h\n\tsection .text\n\n_start:\n";

// Maximum binary size
const int MAX_BIN_SIZE = 0x10000;

#endif