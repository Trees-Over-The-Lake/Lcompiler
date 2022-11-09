CXX?=g++
PUB_IN?=""
FLAGS?=-g

build_and_run:build run 

build:clean precompile compile

debug_gdb:build run_gdb

debug_valgrind:build run_valgrind

precompile:
	@echo -e "Precompilando main.cpp...\n\n"
	./precompilador.py main.cpp

compile:out.cpp
	@echo -e "Compilando arquivo final...\n\n"
	$(CXX) out.cpp $(FLAGS)

run:a.out
	@echo -e "Rodando o programa...\n\n"
	./a.out $(PUB_IN)

run_gdb:a.out 
	gdb a.out

run_valgrind:a.out 
	valgrind --leak-check=full --log-file="log-valgrind.log" ./a.out $(PUB_IN)

clean:
	@echo -e "Limpando...\n\n"
	rm -f *.out