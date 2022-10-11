this->symbol_table = SymbolTable();

// S -> {(A | E)}* fim_arquivo
void symbol_S()
{
    while (READ_TOKEN.lexeme != "fim_arquivo")
    {
        if (READ_TOKEN.lexeme == "char" || READ_TOKEN.lexeme == "float" || READ_TOKEN.lexeme == "string" || READ_TOKEN.lexeme == "boolean" || READ_TOKEN.lexeme == "int" || READ_TOKEN.lexeme == "const")
        {
            symbol_A();
        }
        else
        {
            symbol_E();
        }
    }

    match_token("fim_arquivo");
}


