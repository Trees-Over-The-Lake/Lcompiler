#ifndef GENERATOR_CODE_GENERATOR_CPP
#define GENERATOR_CODE_GENERATOR_CPP

#include<string>
#include<fstream>
#include"../utils/constants.hpp"
#include"../utils/string_utils.cpp"
#include"bin_constants.hpp"
#include"../symbol_table/symbol_table.cpp"
#include <sstream>

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
        void add_character(Token_pointer& r, Token_pointer& identifier);
        void int_to_float(Token_pointer& t);
        void float_to_int(Token_pointer& t);
        void negate_boolean(Token_pointer& p);
        void and_operation(Token_pointer& p, Token_pointer& o);
        void multiple_numbers(Token_pointer& p, Token_pointer& o);
        void divide_numbers(Token_pointer& p, Token_pointer& o);
        void multiple_float(Token_pointer& p, Token_pointer& o);
        void divide_float(Token_pointer& p, Token_pointer& o);
        void read_line(Token_pointer& p);
        void module_or_div(Token_pointer& p, Token_pointer& o, const bool is_module);
        void compare_string(Token_pointer& p, Token_pointer& o);
        void char_operation(Token_pointer& p, Token_pointer& o, const TokenID operation);
        void number_operation(Token_pointer& p, Token_pointer& o, const TokenID operation);
        void negate_expression(Token_pointer& p);
        void or_operation(Token_pointer& p, Token_pointer& q);
        void add_operation(Token_pointer& p, Token_pointer& q);
        void sub_operation(Token_pointer& p, Token_pointer& q);
        
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
        default: 
            break;    
    }

    start_text_section();
}

int CodeGenerator::new_label() {
    return this->label_counter++;
}

void CodeGenerator::reset_temporary_counter() {
    this->temporary_counter = 0x0;
}

void CodeGenerator::allocate_space_for_const(Token_pointer& identifier, Token_pointer& constant) {

    identifier->set_tipo(constant->get_tipo());
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
            write(format("db %s,%d", constant->get_lexema().c_str(), constant->get_tamanho()));
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


void CodeGenerator::store_token_on_data_section(Token_pointer& t, Token_pointer& constant, bool negate) {

    switch (t->get_tipo()) {

        case REAL: {
            t->set_endereco(this->memory_counter);
            this->memory_counter += constant->get_tamanho();

            start_data_section();

            char negate_char = (negate) ? ' ' : '-';

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
            t->set_endereco(this->memory_counter);
            this->memory_counter += constant->get_tamanho();
            
            start_data_section();
     
            write(format("db %s,0", constant->get_lexema().c_str()));

            start_text_section();
            break;

        case INTEIRO:

            write(format("mov eax, %s", constant->get_lexema().c_str()));
            if (negate) 
                write("neg eax");

            write(format("mov [qword M + %ld], eax", constant->get_endereco()));
            break;

        default:
            write(format("mov al, %s", constant->get_lexema().c_str()));
            write(format("mov [qword M + %ld], eax", t->get_endereco()));
            break;
    }

}

void CodeGenerator::variable_atribution(Token_pointer& identifier, Token_pointer& m, Token_pointer& m1, bool is_string) {

    if (is_string) {

        write(format("mov al, [qword M + %ld]", m1->get_endereco()));
        write(format("mov rax, [qword M + %ld]", m->get_endereco()));
        write(format("add rax, M + %ld", identifier->get_endereco()));
        write("mov [rax], al");
    } else if (identifier->get_tipo() == REAL || m1->get_tipo() == INTEIRO) {

        write(format("mov rax, [qword M + %ld]", m->get_endereco()));
        write("cvtsi2ss xmm0, rax");
        write(format("movss [qword M + %ld], xmm0", identifier->get_endereco()));
    } else {

        if(identifier->get_tipo() == REAL) {

            write(format("mov xmm0, [qword M + %ld]", m1->get_endereco()));
            write(format("mov [qword M + %ld], xmm0", identifier->get_endereco()));
        } else if(identifier->get_tipo() == LOGICO || identifier->get_tipo() == CARACTERE) {

            write(format("mov al, [qword M + %ld]", m1->get_endereco()));
            write(format("mov [qword M + %ld], al", identifier->get_endereco()));   
        } else if (identifier->get_tipo() == TEXTO) {
            // TODO
        
        } else {
            write(format("mov eax, [qword M + %ld]", m1->get_endereco()));
            write(format("mov [qword M + %ld], eax", identifier->get_endereco()));   
        }
    }
}

void CodeGenerator::start_while_loop(Token_pointer& t, const int begin, const int end) {

    write(format("l%d:", begin));
    write(format("mov al, [qword M + %ld]", t->get_endereco()));
    write("cmp al, 0");
    write(format("je l%d", end));
}

void CodeGenerator::start_if(Token_pointer& t, const int begin) {
    write(format("mov al, [qword M + %ld]", t->get_endereco()));
    write("cmp al, 0");
    write(format("je l%d", begin));
}

void CodeGenerator::end_scope(const int begin, const int end) {
    write(format("jmp l%d", begin));
    write(format("l%d:", end));
}

void CodeGenerator::end_conditional_chain(const bool is_else, const int begin, const int end) {
    if (is_else) 
        write(format("l%d:", end));

    else 
        write(format("l%d:", begin));
}

void CodeGenerator::read_line(Token_pointer& p) {

    long temporary_buffer = new_temporary(TEXTO);
    p->set_endereco(new_temporary(p->get_tipo()));

    write(format("mov rsi, M + %ld", temporary_buffer));
    write("mov rax, 0");
    write("mov rdi, 0");
    write("mov rdx, 100h");
    write("syscall");
    write(format("mov byte [M+%ld-1+rax], 0",temporary_buffer));

    if (p->get_tipo() == INTEIRO) {

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
        write(format("jz l%d", label3),1);
        write("inc rcx");
        write("sub rdx, '0'");
        write("add rax, rax");
        write("lea rax, [rax + rax * 4]");
        write("add rax, rdx");
        write(format("jmp l%ld", label2));
        write(format("l%d:", label3),1);
        write(format("mov rcx, M + %ld", p->get_endereco()));
        write("mov rbx, 10");
        write("mov [rcx], rbx");
        write("inc rcx");
        write(format("mov [M+%ld], rcx", p->get_endereco()));
    }
}

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

    } else if (t->get_tipo() == TEXTO || t->get_tipo() == CARACTERE) {

        write(format("mov rsi, M + %d", t->get_endereco()));
        write("mov rdx, 100h");
        write("mov rax, 0");
        write("mov rdx, 100h");
        write("mov rdi, 0");
    } else {

        long buffer_address = new_temporary(TEXTO);

        int label1 = new_label();
        int label2 = new_label();
        int label3 = new_label();

        write(format("mov eax, [qword M+%ld]", buffer_address));
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

void CodeGenerator::add_character(Token_pointer& r, Token_pointer& identifier) {

    r->set_tipo(CARACTERE);

    r->set_endereco(new_temporary(CARACTERE));

    write(format("mov rax, [qword M + %ld]", r->get_endereco()));
    write(format("mov rax, M + %ld", identifier->get_endereco()));
    write("mov al, [rax]");
    write(format("mov [qword M + %ld], al", r->get_endereco()));
}

void CodeGenerator::int_to_float(Token_pointer& t) {

    write(format("mov rax, [qword M + %ld]", t->get_endereco()));

    t->set_endereco(new_temporary(REAL));

    write("cvtsi2ss xmm0, rax");
    write("movss [qword M + %ld], xmm0");
}

void CodeGenerator::float_to_int(Token_pointer& t) {

    write(format("movss xmm0, [qword M + %ld]", t->get_endereco()));
    write("cvtsi2ss rax, xmm0");

    t->set_endereco(new_temporary(INTEIRO));

    write("mov [qword M + %ld], rax");
}

void CodeGenerator::negate_boolean(Token_pointer& p) {

    write(format("mov al, [qword M + %ld]", p->get_endereco()));
    write("neg al");
    write("add al, 1");

    p->set_endereco(new_temporary(LOGICO));

    write(format("mov [qowrd M + %ld], al", p->get_endereco()));
}

void CodeGenerator::and_operation(Token_pointer& p, Token_pointer& o) {

    write(format("mov eax, [qword M + %d]", o->get_endereco()));
    write(format("mov ebx, [qword M + %ld]", p->get_endereco()));
    write("imul ebx");

    o->set_endereco(new_temporary(LOGICO));

    write(format("mov [qword M + %ld], eax", o->get_endereco()));
}

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

void CodeGenerator::divide_float(Token_pointer& p, Token_pointer& o) {

    write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
    write(format("movss xmm1, [qword M + %ld]", o->get_endereco()));
    write("divss xmm0, xmm1");

    p->set_endereco(new_temporary(REAL));
    
    write(format("movss [qword M + %ld], xmm0", p->get_endereco()));

}

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
}

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

void CodeGenerator::compare_string(Token_pointer& p, Token_pointer& o) {
    
    p->set_tipo(LOGICO);
    //
}

void CodeGenerator::char_operation(Token_pointer& p, Token_pointer& o, const TokenID operation) {
    
    p->set_tipo(LOGICO);
    
    write(format("mov al, [qword M + %ld]", p->get_endereco()));
    write(format("mov bl, [qword M + %ld]", o->get_endereco()));
    write("cmp al, bl");

    int label = new_label();

    switch(operation) {

        case IGUAL:

            write(format("je l %ld", label));
            break;
        case DIFERENTE:

            write(format("jne l %ld", label));
            break;
        case MENOR:

            write(format("jl l %ld", label));
            break;
        case MENOR_IGUAL:

            write(format("jle l %ld", label));
            break;
        case MAIOR:

            write(format("jg l %ld", label));
            break;
        case MAIOR_IGUAL:

            write(format("jge l %ld", label));
            break;

        default:
            break;
    }

    write("mov cl, 0");

    int end_label = new_label();

    write(format("jmp l%d", end_label));
    write(format("l%d", label));
    write("mov cl, 1");
    write(format("l%d", end_label));

    p->set_endereco(new_temporary(CARACTERE));

    write(format("mov [qword M + %ld], cl", p->get_endereco()));
}

void CodeGenerator::number_operation(Token_pointer& p, Token_pointer& o, const TokenID operation) {
    
    p->set_tipo(LOGICO);
    
    write(format("movss xmm0, [qword M + %ld]", p->get_endereco()));
    write(format("movss xmm1, [qword M + %ld]", o->get_endereco()));
    write("comiss xmm0, xmm1");

    int label = new_label();

    switch(operation) {

        case IGUAL:

            write(format("je l %ld", label));
            break;
        case DIFERENTE:

            write(format("jne l %ld", label));
            break;
        case MENOR:

            write(format("jb l %ld", label));
            break;
        case MENOR_IGUAL:

            write(format("jbe l %ld", label));
            break;
        case MAIOR:

            write(format("ja l %ld", label));
            break;
        case MAIOR_IGUAL:

            write(format("jae l %ld", label));
            break;

        default:
            break;
    }

    write("mov al, 0");

    int end_label = new_label();

    write(format("jmp l%d", end_label));
    write(format("l%d", label));
    write("mov al, 1");
    write(format("l%d", end_label));

    p->set_endereco(new_temporary(LOGICO));

    write(format("mov [qword M + %ld], al", p->get_endereco()));
}

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

void CodeGenerator::add_operation(Token_pointer& p, Token_pointer& o) {
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
}

void CodeGenerator::sub_operation(Token_pointer& p, Token_pointer& o) {

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
}

#endif
