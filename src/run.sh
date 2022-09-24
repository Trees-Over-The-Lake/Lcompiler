echo "Precompilando main.cpp...\n\n"
./precompilador.py main.cpp
echo "Compilando arquivo final...\n\n"
g++ out.cpp
echo "Rodando o programa...\n\n"
./a.out