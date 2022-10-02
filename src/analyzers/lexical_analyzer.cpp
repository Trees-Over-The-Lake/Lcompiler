#ifndef LEXICAL_ANALYZER_CPP
#define LEXICAL_ANALYZER_CPP

int CHAR_COUNT = 0;
int LINE_COUNT = 1;
int LABEL_COUNT = 1;
int SYMBOL_COUNT = 0;

string SOURCE_FILE;

class LexicalAnalyzer {
    private:
        /* data */
    public:
        LexicalAnalyzer(/* args */);
        ~LexicalAnalyzer();
};

LexicalAnalyzer::LexicalAnalyzer(/* args */)
{
}

LexicalAnalyzer::~LexicalAnalyzer()
{
}


// Struct token - puxar do outro arquivo como esta
// token READ_TOKEN;


// Função do Analisador Léxico.
void analizador_lexico()
{
    int state = 0;

    char caractere;

    string lexeme;

    while (state != 1)
    {
        if (CHAR_COUNT < SOURCE_FILE.length() && SOURCE_FILE[CHAR_COUNT] == '\r')
        {
            CHAR_COUNT++;
        }
        else
        {
            if (CHAR_COUNT < SOURCE_FILE.length())
            {
                caractere = SOURCE_FILE[CHAR_COUNT++];

                if (!isalnum(caractere) && find(VALID_CHAR.rbegin(), VALID_CHAR.rend(), caractere) == VALID_CHAR.rend())
                {
                    cout << LINE_COUNT << endl << "caractere invalido." << endl;
                    exit(1);
                }
            }
            else
            {
                caractere = '\0';
            }
    
            // switch (state)
            // {
        }}}
            
        

#endif