#ifndef GENERATOR_CODE_GENERATOR_CPP
#define GENERATOR_CODE_GENERATOR_CPP

#include<string>
#include<fstream>
#include"../utils/constants.hpp"
#include"../utils/string_utils.cpp"
#include"bin_constants.hpp"
#include"../symbol_table/symbol_table.cpp"
#include <sstream>

/**
 * @brief Class for generating x86_64 assembly on linux
 * 
 */
class CodeGenerator {
    private:

        std::string asm_file_path;
        std::ofstream asm_file;

        long memory_counter;
        long temporary_counter;

        int label_counter;

        void start_data_section();
        void start_text_section();

        long new_temporary(const TokenType t);

    public:
    
        CodeGenerator(std::string asm_file_path = DEFAULT_OUTPUT_FILE);
        ~CodeGenerator();

        // Data allocation

        void allocate_space_for_token(Token_pointer& t);
        void allocate_space_for_const(Token_pointer& identifier, Token_pointer& constant);
        void variable_atribution(Token_pointer& identifier, Token_pointer& m, Token_pointer& m1, bool is_string);
        void store_token_on_data_section(Token_pointer& identifier, Token_pointer& constant, bool negate);

        void reset_temporary_counter();

        void start_while_loop(Token_pointer& t, const int begin, const int end);
        void start_if(Token_pointer& t, const int begin);
        void end_scope(const int begin, const int end);
        void end_conditional_chain(const bool is_else, const int begin, const int end);

        void write_into_terminal(Token_pointer& t);
        void write_line_break(const bool writeln);
        void read_line(Token_pointer& p);

        void int_to_float(Token_pointer& t);
        void float_to_int(Token_pointer& t);
        
        void add_character(Token_pointer& r, Token_pointer& identifier);

        void multiple_numbers(Token_pointer& p, Token_pointer& o);
        void divide_numbers(Token_pointer& p, Token_pointer& o);
        void multiple_float(Token_pointer& p, Token_pointer& o);
        void divide_float(Token_pointer& p, Token_pointer& o);
        
        void add_operation(Token_pointer& p, Token_pointer& q);
        void sub_operation(Token_pointer& p, Token_pointer& q);

        void module_or_div(Token_pointer& p, Token_pointer& o, const bool is_module);
        void compare_string(Token_pointer& p, Token_pointer& o);
        void char_operation(Token_pointer& p, Token_pointer& o, const TokenID operation);
        void number_operation(Token_pointer& m, Token_pointer& n1, Token_pointer& n2, const TokenID operation);

        void negate_expression(Token_pointer& p);
        void negate_boolean(Token_pointer& p);
        void or_operation(Token_pointer& p, Token_pointer& q);
        void and_operation(Token_pointer& p, Token_pointer& o);
        
        void end_program();

        int new_label();

        void write(std::string s, int num_tabs = 2);
};

CodeGenerator::CodeGenerator(std::string asm_file_path)
{
    this->asm_file_path = asm_file_path;
    this->asm_file.open(asm_file_path);

    this->memory_counter = MAX_BIN_SIZE;
    this->temporary_counter = 0x0;
    this->label_counter = 1;
    this->write(std::string(ELF_HEADER),0);
}

CodeGenerator::~CodeGenerator()
{
    this->asm_file.close();
}

void CodeGenerator::start_data_section() {
    write("section .data", 0);
}

void CodeGenerator::start_text_section() {
    write("section .text", 0);
}

void CodeGenerator::end_program() {
    
    start_text_section();
    write("mov rax,60");
    write("mov rdi,0");
    write("syscall");
}

void CodeGenerator::write(std::string s, int num_tabs) {

    std::string tabs = "";

    for(int i = 0; i < num_tabs; i++, tabs+="\t" );

    this->asm_file << tabs << s << std::endl;
}

long CodeGenerator::new_temporary(const TokenType type) {

    long address = this->temporary_counter;

    switch (type) {
    case TEXTO:

        this->temporary_counter += L_STRING_SIZE;
        break;
    
    case CARACTERE:
    case LOGICO:
        
        this->temporary_counter += L_CHAR_SIZE;
        break; 

    case INTEIRO:
    case REAL:
    
        this->temporary_counter += L_NUMBER_SIZE;
        break;

    default:
        break;
    }

    return address;
}

/**
 * @brief Alocate the necessary bytes for the token t
 * @param t is the variable we want to allocate in memory
 */
void CodeGenerator::allocate_space_for_token(Token_pointer& t) {
    t->set_endereco(this->memory_counter);

    start_data_section();

    switch(t->get_tipo()) {
        case LOGICO:
        case CHAR:
            this->memory_counter += L_CHAR_SIZE;
            write("resb 1");
            break;
        case TEXTO:
            this->memory_counter += L_STRING_SIZE;
            write("resb 100h");
            break;
        case INTEIRO:
        case REAL:
            this->memory_counter += L_NUMBER_SIZE;
            write("resd 1");
            break;
        default: 
            break;    
    }

    start_text_section();
}

/**
 * @brief Create a new label
 */
int CodeGenerator::new_label() {
    return this->label_counter++;
}

/**
 * @brief Reset the counter for temporary data on M
 * 
 */
void CodeGenerator::reset_temporary_counter() {
    this->temporary_counter = 0x0;
}

/**
 * @brief Alocate data for a constant in the data section
 * 
 * @param identifier is the token that is allocating a constant
 * @param constant is the token with the information of the value we want to store
 */
void CodeGenerator::allocate_space_for_const(Token_pointer& identifier, Token_pointer& constant) {

    identifier->set_endereco(this->memory_counter);

    start_data_section();

    switch(identifier->get_tipo()) {

        case LOGICO:
            this->memory_counter += constant->get_tamanho();

            if (constant->get_id() == TRUE)
                write("db 1");
            else 
                write("db 0");
            
            break;

        case CHAR:

            this->memory_counter += constant->get_tamanho();
            write(format("db %s,0", constant->get_lexema().c_str()));

            break;

        case TEXTO:

            this->memory_counter += constant->get_tamanho();
            write(format("db %s,0", constant->get_lexema().c_str()));

            break;
        default: 
            this->memory_counter += constant->get_tamanho();
            
            write(format("dd %s", constant->get_lexema().c_str()));

            break;    
    }

    start_text_section();
}


/**
 * @brief Store the value of constant into the position of the pointer t
 * 
 * @param t is where the value is going to be stored
 * @param constant is where the value we want to allocate is
 * @param negate boolean expressing if we need to invert the value in the constant
 */
void CodeGenerator::store_token_on_data_section(Token_pointer& t, Token_pointer& constant, bool negate) {

    switch (t->get_tipo()) {

        case REAL: {
            
            t->set_endereco(this->memory_counter);
            this->memory_counter += constant->get_tamanho();

            start_data_section();

            char negate_char = (negate) ? '-' : ' ';

            if (constant->get_lexema()[0] == '.') {
                std::string new_constant = '0' + constant->get_lexema();
                constant->set_lexema(new_constant);
            }

            write(format("dd%c%s", negate_char, constant->get_lexema().c_str()));

            start_text_section();
            break;

        } case LOGICO:
        
            if (constant->get_id() == TRUE)
                write("mov al, 1");

            else 
                write("mov al, 0");

            write(format("mov [qword M + %ld], al", constant->get_endereco()));
            break;

        case TEXTO:

            t->set_endereco(this->memory_counter - L_STRING_SIZE + constant->get_lexema().size() - 1);
            this->memory_counter += constant->get_tamanho();
            
            start_data_section();
     
            write(format("db %s,0", constant->get_lexema().c_str(), 0));

            start_text_section();
            break;

        case INTEIRO:

            t->set_endereco(new_temporary(INTEIRO));

            write(format("mov eax, %s", constant->get_lexema().c_str()));
            if (negate) 
                write("neg eax");

            write(format("mov [qword M + %ld], eax", t->get_endereco()));
            break;

        default:

            t->set_endereco(new_temporary(CARACTERE));

            write(format("mov al, %s", constant->get_lexema().c_str()));
            write(format("mov [qword M + %ld], eax", t->get_endereco()));
            break;
    }

}

/**
 * @brief Atribute the identifier with a variable
 * 
 * @param identifier 
 * @param m 
 * @param m1 
 * @param is_string 
 */
void CodeGenerator::variable_atribution(Token_pointer& identifier, Token_pointer& m, Token_pointer& m1, bool accessing_string_index) {

    if (accessing_string_index) {

        write(format("mov al, [qword M + %ld]", m1->get_endereco()));
        write(format("mov rax, [qword M + %ld]", m->get_endereco()));
        write(format("add rax, M + %ld", identifier->get_endereco()));
        write("mov [rax], al");
    } else if (identifier->get_tipo() == REAL && m1->get_tipo() == INTEIRO) {

        write(format("mov rax, [qword M + %ld]", m->get_endereco()));
        write("cvtsi2ss xmm0, rax");
        write(format("movss [qword M + %ld], xmm0", identifier->get_endereco()));
    } else {

        if(identifier->get_tipo() == REAL) {

            write(format("movss xmm0, [qword M + %ld]", m1->get_endereco()));
            write(format("movss [qword M + %ld], xmm0", identifier->get_endereco()));
        } else if(identifier->get_tipo() == LOGICO || identifier->get_tipo() == CARACTERE) {

            write(format("mov al, [qword M + %ld]", m1->get_endereco()));
            write(format("mov [qword M + %ld], al", identifier->get_endereco()));   
        } else if (identifier->get_tipo() == TEXTO) {

            write(format("mov rax, M + %ld", m1->get_endereco()));
            write(format("mov [qword M + %ld], [rax]", identifier->get_endereco()));   
        
        } else {
            write(format("mov eax, [qword M + %ld]", m1->get_endereco()));
            write(format("mov [qword M + %ld], eax", identifier->get_endereco()));   
        }
    }
}

/**
 * @brief Start a while loop
 * 
 * @param t is the token containg the codition for stopping the loop
 * @param begin is label containing the beggining of the loop
 * @param end is the label containing the end of the loop
 */
void CodeGenerator::start_while_loop(Token_pointer& t, const int begin, const int end) {

    write(format("l%d:", begin),1);
    write(format("mov al, [qword M + %ld]", t->get_endereco()));
    write("cmp al, 0");
    write(format("je l%d", end));
    write("mov al, 1");
}

/**
 * @brief Start a if conditioning
 * 
 * @param t is the boolean containing the start of the if chain
 * @param begin is the label containing the beginning of the if chain 
 */
void CodeGenerator::start_if(Token_pointer& t, const int begin) {
    write(format("mov al, [qword M + %ld]", t->get_endereco()));
    write("cmp al, 0");
    write(format("je l%d", begin));
}

/**
 * @brief End the if chain or while loop
 * 
 * @param begin is the begin label for the while/if chain
 * @param end is the label containing the end of the if chain
 */
void CodeGenerator::end_scope(const int begin, const int end) {
    write(format("jmp l%d", begin));
    write(format("l%d:", end),1);
}

/**
 * @brief End if/else chain
 * 
 * @param is_else boolean expressing if the chain started was an else if chain
 * @param begin is the beggining label
 * @param end is the end label
 */
void CodeGenerator::end_conditional_chain(const bool is_else, const int begin, const int end) {
    if (is_else) 
        write(format("l%d:", end),1);

    else 
        write(format("l%d:", begin),1);
}

/**
 * @brief Read user input and store in pointer p
 * @param p is the token where the variable will be stored into
 */
void CodeGenerator::read_line(Token_pointer& p) {

    if (p->get_tipo() == CARACTERE) {

        write(format("mov rsi, M + %ld", p->get_endereco()));
        write("mov rax, 0");
        write("mov rdi, 0");
        write("mov rdx, 1");
        write("syscall");

    } else if (p->get_tipo() == TEXTO) {

        write(format("mov rsi, M + %ld", p->get_endereco()));
        write("mov rax, 0");
        write("mov rdi, 0");
        write("mov rdx, 100h");
        write("syscall");
        write(format("mov byte [M+%ld+rax-1], 0",p->get_endereco())); // Armazenar \0 na ultima posicao da string
    }

    else if ( p->get_tipo() == INTEIRO) {

        // Criar variavel temporaria

        long temporary_buffer = new_temporary(TEXTO);
        p->set_endereco(new_temporary(INTEIRO));

        // Ler string do teclado
        
        write(format("mov rsi, M + %ld", temporary_buffer));
        write("mov rax, 0");
        write("mov rdi, 0");
        write("mov rdx, 100h");
        write("syscall");
        write(format("mov byte [M+%ld-1+rax], 0",temporary_buffer)); // Armazenar \0 na ultima posicao da string

        // Converter String para inteiro

        int label1 = new_label();
        int label2 = new_label();
        int label3 = new_label();

        write(format("l%d:", label1),1);
        write("mov rbx, 10");
        write("xor rax, rax");
        write(format("mov rcx, M+%ld", temporary_buffer));
        write(format("l%d:", label2),1);
        write("movzx rdx, byte [rcx]");
        write("test rdx, rdx");
        write(format("jz l%d", label3));
        write("inc rcx");
        write("sub rdx, '0'");
        write("add rax, rax");
        write("lea rax, [rax + rax * 4]");
        write("add rax, rdx");
        write(format("jmp l%ld", label2));
        write(format("l%d:", label3),1);
        write(format("mov [M+%ld], rax", p->get_endereco()));
    }
}

/**
 * @brief Write the content of the pointer t into the terminal
 * @param t is the variable we want to print on the screen
 */
void CodeGenerator::write_into_terminal(Token_pointer& t) {

    if (t->get_tipo() == REAL) {

        long buffer_address = new_temporary(TEXTO);

        int label1 = new_label();
        int label2 = new_label();
        int label3 = new_label();
        int label4 = new_label();
        int label5 = new_label();

        write(format("movss xmm0, [qword M + %ld]", t->get_endereco()));
        write(format("mov rsi, M+ %ld", buffer_address));
        write("mov rcx, 0 ");
        write("mov rdi, 6 ");
        write("mov rbx, 10 ");
        write("cvtsi2ss xmm2, rbx ");
        write("subss xmm1, xmm1 ");
        write("comiss xmm0, xmm1 ");
        write(format("jae l%d", label1));
        write("mov dl, '-' ");
        write("mov [rsi], dl");
        write("mov rdx, -1 ;Carrega -1 em RDX");
        write("cvtsi2ss xmm1, rdx ;Converte para real");
        write("mulss xmm0, xmm1 ;Toma módulo");
        write("add rsi, 1 ;incrementa índice");
        write(format("l%d:", label1),1);
        write("roundss xmm1, xmm0, 0b0011 ;parte inteira xmm1");
        write("subss xmm0, xmm1");
        write("cvtss2si rax, xmm1");
        write(format("l%d:", label2),1);
        write("add rcx, 1");
        write("cdq");
        write("idiv ebx");
        write("push dx");
        write("cmp eax, 0");
        write(format("jne l%d", label2));
        write("sub rdi, rcx");
        write(format("l%d:", label3),1);
        write("pop dx");
        write("add dl, '0'");
        write("mov [rsi], dl");
        write("add rsi, 1");
        write("sub rcx, 1");
        write("cmp rcx, 0");
        write(format("jne l%d", label3));
        write("mov dl, '.'");
        write("mov [rsi], dl");
        write("add rsi, 1");
        write(format("l%d:", label4),1);
        write("cmp rdi, 0");
        write(format("jle l%d", label5));
        write("mulss xmm0,xmm2");
        write("roundss xmm1,xmm0,0b0011");
        write("subss xmm0,xmm1");
        write("cvtss2si rdx, xmm1");
        write("add dl, '0'");
        write("mov [rsi], dl");
        write("add rsi, 1");
        write("sub rdi, 1");
        write(format("jmp l%d", label4));
        write(format("l%d:", label5),1);
        write("mov dl, 0");
        write("mov [rsi], dl");
        write("mov rdx, rsi");
        write(format("mov rbx, M+%ld", buffer_address));
        write("sub rdx, rbx");
        write(format("mov rsi, M+%ld", buffer_address));
        write("mov rax, 1");
        write("mov rdi, 1");
        write("syscall");

    } else if (t->get_tipo() == TEXTO ) {

        write(format("mov rsi, M + %d", t->get_endereco()));
        write("mov rdx, 100h");
        write("mov rax, 1");
        write("mov rdi, 1");
        write("syscall");
    } else if (t->get_tipo() == CARACTERE){

        write(format("mov rsi, M + %d", t->get_endereco()));
        write("mov rdx, 1");
        write("mov rax, 1");
        write("mov rdi, 1");
        write("syscall");
    } else {

        long buffer_address = new_temporary(TEXTO);

        int label1 = new_label();
        int label2 = new_label();
        int label3 = new_label();

        write(format("mov eax, [qword M+%ld]", t->get_endereco()));
        write(format("mov rsi, M+%ld", buffer_address));
        write("mov rcx, 0");
        write("mov rdi, 0");
        write("cmp eax, 0");
        write(format("jge l%d",label1));
        write("mov bl, '-' ");
        write("mov [rsi], bl");
        write("add rsi, 1");
        write("add rdi, 1");
        write("neg eax");
        write(format("l%ld:",label1),1);
        write("mov ebx, 10");
        write(format("l%ld:",label2),1);
        write("add rcx, 1");
        write("cdq");
        write("idiv ebx");
        write("push dx");
        write("cmp eax, 0");
        write(format("jne l%d", label2));
        write("add rdi,rcx");
        write(format("l%ld:",label3),1);
        write("pop dx");
        write("add dl, '0'");
        write("mov [rsi], dl");
        write("add rsi, 1");
        write("sub rcx, 1");
        write("cmp rcx, 0");
        write(format("jne l%d", label3));
        write(format("mov rsi, M+%ld",buffer_address));
        write("mov rax, 1");
        write("mov rdi, 1");
        write("syscall");

    }
}

/**
 * @brief Write a line break in the code
 * 
 * @param writeln is the expression saying if is really necessary insert a line break
 */
void CodeGenerator::write_line_break(const bool writeln) {

    if (writeln) {

        long line_break = new_temporary(TEXTO);

        write("mov al, 0Ah");
        write(format("mov [qword M + %ld], al", line_break));
        write(format("mov rsi, M + %ld", line_break));
        write("mov rdx, 1");
        write("mov rax, 1");
        write("mov rdi, 1");
        write("syscall");
    }
}

/**
 * @brief Add a character to a register
 * 
 * @param r is the register we want to allocate to
 * @param identifier is the token containing the character we want to add
 */
void CodeGenerator::add_character(Token_pointer& r, Token_pointer& identifier) {

    r->set_tipo(CARACTERE);

    r->set_endereco(new_temporary(CARACTERE));

    write(format("mov rax, [qword M + %ld]", r->get_endereco()));
    write(format("mov rax, M + %ld", identifier->get_endereco()));
    write("mov al, [rax]");
    write(format("mov [qword M + %ld], al", r->get_endereco()));
}

/**
 * @brief Convert a token containing an integer into a floating number
 * 
 * @param t is the token containing the float
 */
void CodeGenerator::int_to_float(Token_pointer& t) {

    write(format("mov rax, [qword M + %ld]", t->get_endereco()));

    t->set_endereco(new_temporary(REAL));

    write("cvtsi2ss xmm0, rax");
    write("movss [qword M + %ld], xmm0");
}

/**
 * @brief Convert a token containing a float into an integer
 * 
 * @param t is the token containing the integer
 */
void CodeGenerator::float_to_int(Token_pointer& t) {

    write(format("movss xmm0, [qword M + %ld]", t->get_endereco()));
    write("cvtsi2ss rax, xmm0");

    t->set_endereco(new_temporary(INTEIRO));

    write("mov [qword M + %ld], rax");
}

/**
 * @brief Negate a boolean expression
 * 
 * @param p is the token containing the boolean
 */
void CodeGenerator::negate_boolean(Token_pointer& p) {

    write(format("mov al, [qword M + %ld]", p->get_endereco()));
    write("neg al");
    write("add al, 1");

    p->set_endereco(new_temporary(LOGICO));

    write(format("mov [qword M + %ld], al", p->get_endereco()));
}

/**
 * @brief make an and operation with the content of two registers
 * 
 * @param p is the content of the second register
 * @param o is the content of the first register, and the one 
 * where the variable of the operation is going to be stored 
 */
void CodeGenerator::and_operation(Token_pointer& p, Token_pointer& o) {

    write(format("mov eax, [qword M + %d]", o->get_endereco()));
    write(format("mov ebx, [qword M + %ld]", p->get_endereco()));
    write("imul ebx");

    o->set_endereco(new_temporary(LOGICO));

    write(format("mov [qword M + %ld], eax", o->get_endereco()));
}

/**
 * @brief Multiply two floating point numbers
 * 
 * @param p is the first token with the register where the variable is going to be stored
 * @param o is the second token for the operation
 */
void CodeGenerator::multiple_float(Token_pointer& p, Token_pointer& o) {

    if(p->get_tipo() == REAL) {

        write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
        write(format("movss xmm1, [qword M + %ld]", o->get_endereco()));
        write("mulss xmm0, xmm1");

        p->set_endereco(new_temporary(REAL));
        
        write(format("movss [qword M + %ld], xmm0", p->get_endereco()));

    } else {

        write(format("mov eax, [qword M + %ld]", p->get_endereco()));
        write(format("mov ebx, [qword M + %ld]", o->get_endereco()));
        write("imul ebx");

        p->set_endereco(new_temporary(REAL));
        
        write(format("mov [qword M + %ld], eax", p->get_endereco()));
    }
}

/**
 * @brief Divide the content of two floating point numbers
 * 
 * @param p is the first token, and is where the result
 * of the operation is going to be stored
 * @param o is the second token for the operation
 */
void CodeGenerator::divide_float(Token_pointer& p, Token_pointer& o) {

    write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
    write(format("movss xmm1, [qword M + %ld]", o->get_endereco()));
    write("divss xmm0, xmm1");

    p->set_endereco(new_temporary(REAL));
    
    write(format("movss [qword M + %ld], xmm0", p->get_endereco()));
}

/**
 * @brief Multiply two floating point numbers
 * 
 * @param p is the first token with the register where the variable is going to be stored
 * @param o is the second token for the operation
 */
void CodeGenerator::multiple_numbers(Token_pointer& p, Token_pointer& o) {

    if(p->get_tipo() == REAL) {

        write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
        write(format("mov eax, [qword M + %ld]", o->get_endereco()));
        write("cdqe");
        write("cvtsi2ss xmm1, rax");

    } else {

        write(format("mov eax, [qword M + %ld]", p->get_endereco()));
        write("cdqe");
        write("cvtsi2ss xmm0, rax");
        write(format("movss xmm1, [qword M + %ld]", o->get_endereco()));
    }

    write("mulss xmm0, xmm1");

    p->set_endereco(new_temporary(REAL));

    write(format("movss [qword M + %ld], xmm0", p->get_endereco()));
}

/**
 * @brief Divide the content of two numbers
 * 
 * @param p is the first token, and is where the result
 * of the operation is going to be stored
 * @param o is the second token for the operation
 */
void CodeGenerator::divide_numbers(Token_pointer& p, Token_pointer& o) {

    if(p->get_tipo() == REAL) {

        write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
        write(format("mov eax, [qword M + %ld]", o->get_endereco()));
        write("cdqe");
        write("cvtsi2ss xmm1, rax");

    } else {

        write(format("mov eax, [qword M + %ld]", p->get_endereco()));
        write("cdqe");
        write("cvtsi2ss xmm0, rax");
        write(format("movss xmm1, [qword M + %ld]",o->get_endereco()));
    }

    write("divss xmm0, xmm1");

    p->set_endereco(new_temporary(REAL));
    write(format("movss [qword M + %ld], xmm0", p->get_endereco()));
}


/**
 * @brief Make a module or a div operation
 * 
 * @param p is the first token for the operation
 * @param o is the second token, and where the result of the
 * operation is going to be stored
 * @param is_module boolean expressing if the operation is a module one
 */
void CodeGenerator::module_or_div(Token_pointer& p, Token_pointer& o, const bool is_module) {
    
    p->set_tipo(o->get_tipo());

    write(format("mov eax, [qword M + %ld]", p->get_endereco()));
    write("cdq");
    write(format("mov ebx, [qword M + %ld]", o->get_endereco()));
    write("idiv ebx");

    o->set_endereco(new_temporary(REAL));

    if (is_module) 
        write(format("mov [qword M + %ld], edx", o->get_endereco()));

    else 
        write(format("mov [qword M + %ld], eax",o->get_endereco()));


}

/**
 * @brief Compare the content of two strings
 * 
 * @param p is the first string
 * @param o is the second string
 */
void CodeGenerator::compare_string(Token_pointer& p, Token_pointer& o) {
    
    p->set_tipo(LOGICO);
    //
}

/**
 * @brief Compare the content of two characters
 * 
 * @param p is the first character
 * @param o is the second character
 * @param operation is the operation that is going to be with the caracthers
 */
void CodeGenerator::char_operation(Token_pointer& p, Token_pointer& o, const TokenID operation) {
    
    p->set_tipo(LOGICO);
    
    write(format("mov al, [qword M + %ld]", p->get_endereco()));
    write(format("mov bl, [qword M + %ld]", o->get_endereco()));
    write("cmp al, bl");

    int label = new_label();

    switch(operation) {

        case IGUAL:

            write(format("je l%ld", label));
            break;
        case DIFERENTE:

            write(format("jne l%ld", label));
            break;
        case MENOR:

            write(format("jl l%ld", label));
            break;
        case MENOR_IGUAL:

            write(format("jle l%ld", label));
            break;
        case MAIOR:

            write(format("jg l%ld", label));
            break;
        case MAIOR_IGUAL:

            write(format("jge l%ld", label));
            break;

        default:
            break;
    }

    write("mov cl, 0");

    int end_label = new_label();

    write(format("jmp l%d", end_label));
    write(format("l%d:", label),1);
    write("mov cl, 1");
    write(format("l%d:", end_label),1);

    p->set_endereco(new_temporary(CARACTERE));

    write(format("mov [qword M + %ld], cl", p->get_endereco()));
}

/**
 * @brief Make a operation with the numbers
 * 
 * @param m is the token where the result from the boolean will be stored
 * @param n1 is the firs tnumber
 * @param n2 is the second number
 * @param operation is the operation that is going to be made
 */
void CodeGenerator::number_operation(Token_pointer& m, Token_pointer& n1, Token_pointer& n2, const TokenID operation) {
    
    m->set_tipo(LOGICO);

    if (n1->get_tipo() == n2->get_tipo() ) {

        if(n1->get_tipo() == INTEIRO) {
            write(format("mov eax, [qword M + %ld]", m->get_endereco()));
            write(format("mov ebx, [qword M + %ld]", n2->get_endereco()));
            write("cmp eax, ebx");

        } else {
            write(format("movss xmm0, [qword M + %ld]", m->get_endereco()));
            write(format("movss xmm1, [qword M + %ld]", n2->get_endereco()));
            write("comiss xmm0, xmm1");
        }
    } else {

        if(n1->get_tipo() == INTEIRO) {
            write(format("movss xmm0, [qword M + %ld]", n2->get_endereco()));
            write(format("mov rax, [qword M + %ld]", m->get_endereco()));
            write("cvtsi2ss xmm1, rax");

        } else {
            write(format("movss xmm0, [qword M + %ld]", m->get_endereco()));
            write(format("mov rax, [qword M + %ld]", n2->get_endereco()));
            write("cvtsi2ss xmm1, rax");
            
        }
        write("comiss xmm0, xmm1");
    }

    int label = new_label();

    switch(operation) {

        case IGUAL:

            write(format("je l%ld", label));
            break;
        case DIFERENTE:

            write(format("jne l%ld", label));
            break;
        case MAIOR:

            write(format("jg l%ld", label));
            
            break;
        case MAIOR_IGUAL:

            write(format("jge l%ld", label));

            break;
        case MENOR:

            write(format("jl l%ld", label));

            break;
        case MENOR_IGUAL:

            write(format("jle l%ld", label));
            break;

        default:
            break;
    }

    write("mov al, 0");

    int end_label = new_label();

    write(format("jmp l%d", end_label));
    write(format("l%d:", label),1);
    write("mov al, 1");
    write(format("l%d:", end_label),1);

    m->set_endereco(new_temporary(LOGICO));

    write(format("mov [qword M + %ld], al", m->get_endereco()));
}

/**
 * @brief Negate an entire expression containing inside of a token
 * 
 * @param p is the token we need to negate
 */
void CodeGenerator::negate_expression(Token_pointer& p) {

    if (p->get_tipo() == REAL) {

        write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
        write("mov rax, -1");
        write("cvtsi2ss xmm1, rax");
        write("mulss xmm0, xmm1");

        p->set_endereco(new_temporary(INTEIRO));

        write(format("movss [qword M + %ld], xmm0", p->get_endereco()));

    } else {

        write(format("movss eax, [qword M + %ld]", p->get_endereco()));
        write("neg eax");

        p->set_endereco(new_temporary(INTEIRO));

        write(format("mov [qword M + %ld], eax", p->get_endereco()));
    }
}

/**
 * @brief Make a or operation on two tokens
 * 
 * @param p is the first token, and the one that is going to contain the result
 * @param o is the second token
 */
void CodeGenerator::or_operation(Token_pointer& p, Token_pointer& o) {

    write(format("mov eax, [qword M + %ld]", p->get_endereco()));
    write(format("mov ebx, [qword M + %ld]", p->get_endereco()));
    write(format("mov ecx, [qword M + %ld]", o->get_endereco()));
    write("imul ecx");
    write("add ebx, ecx");
    write("sub ebx, eax");

    p->set_endereco(new_temporary(LOGICO));

    write("mov [qword M + %ld], ebx");
}

/**
 * @brief Make a sum operation on two tokens
 * 
 * @param p is the first token, and the one that will containg the result of the operation
 * @param o is the second token
 */
void CodeGenerator::add_operation(Token_pointer& p, Token_pointer& o) {
    
    if(p->get_tipo() != o->get_tipo()) {

        if(p->get_tipo() == REAL) {

            write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
            write(format("mov eax, [qword M + %ld]", o->get_endereco()));
            write("cdqe");
            write("cvtsi2ss xmm1, rax");

        } else {

            write(format("mov eax, [qword M + %ld]", p->get_endereco()));
            write("cdqe");
            write("cvtsi2ss xmm0, rax");
            write(format("movss xmm1, [qword M + %ld]",o->get_endereco()));
        }

        write("addss xmm1, xmm0");

        p->set_endereco(new_temporary(INTEIRO));

        write(format("movss [qword M + %ld], xmm1", p->get_endereco()));
    } else {

        if (p->get_tipo() == REAL) {

            write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
            write(format("movss xmm1, [qword M + %ld]", o->get_endereco()));
            write("addss xmm1, xmm0");

            p->set_endereco(new_temporary(REAL));

            write(format("movss [qword M + %ld], xmm1", p->get_endereco()));
        } else {

            write(format("mov eax, [qword M + %ld]", p->get_endereco()));
            write(format("mov ebx, [qword M + %ld]", o->get_endereco()));
            write("add eax, ebx");

            p->set_endereco(new_temporary(INTEIRO));

            write(format("mov [qword M + %ld], eax", p->get_endereco()));
        }
    }
}

/**
 * @brief Make a sum operation on two tokens
 * 
 * @param p is the first token, and the one that will containg the result of the operation
 * @param o is the second token
 */
void CodeGenerator::sub_operation(Token_pointer& p, Token_pointer& o) {

    if(p->get_tipo() != o->get_tipo()) {

        if(p->get_tipo() == REAL) {

            write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
            write(format("mov eax, [qword M + %ld]", o->get_endereco()));
            write("cdqe");
            write("cvtsi2ss xmm1, rax");

        } else {

            write(format("mov eax, [qword M + %ld]", p->get_endereco()));
            write("cdqe");
            write("cvtsi2ss xmm0, rax");
            write(format("movss xmm1, [qword M + %ld]",o->get_endereco()));
        }

        write("subss xmm1, xmm0");

        p->set_endereco(new_temporary(INTEIRO));

        write(format("movss [qword M + %ld], xmm1", p->get_endereco()));
    } else {

        if (p->get_tipo() == REAL) {

            write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
            write(format("movss xmm1, [qword M + %ld]", o->get_endereco()));
            write("subss xmm1, xmm0");

            p->set_endereco(new_temporary(REAL));

            write(format("movss [qword M + %ld], xmm1", p->get_endereco()));
        } else {

            write(format("mov eax, [qword M + %ld]", p->get_endereco()));
            write(format("mov ebx, [qword M + %ld]", o->get_endereco()));
            write("sub eax, ebx");

            p->set_endereco(new_temporary(INTEIRO));

            write(format("mov [qword M + %ld], eax", p->get_endereco()));
        }
    }
}

#endif