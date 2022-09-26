echo -e "Precompilando main.cpp...\n\n"
./precompilador.py main.cpp

echo -e "Compilando arquivo final...\n\n"
g++ out.cpp

echo -e "Rodando o programa...\n\n"
./a.out