CXX?=g++

build_all:clean precompile compile run 

precompile:
	@echo -e "Precompilando main.cpp...\n\n"
	./precompilador.py main.cpp

compile:out.cpp
	@echo -e "Compilando arquivo final...\n\n"
	$(CXX) out.cpp

run:a.out
	@echo -e "Rodando o programa...\n\n"
	./a.out

clean:
	@echo -e "Limpando...\n\n"
	rm -f *.out