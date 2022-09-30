# Como rodar o programa

Em vez de fazer qualquer passo de compilação, apenas rode o arquivo makefile

## Rodar

Para rodar o programa, apenas use:

```
make
```

## Principais secoes

``` 
make                            # Compilar e rodar programa
make build                     # Apenas compilar
make debug_gdb            # Debugar programa com GDB
make debug_valgrind       # Gerar relatório de memória 

```

## Variáveis

* CXX : Compilador utilizado (padrão é o gcc)
* PUB_IN : Passar entrada padrao para o programa
* FLAGS : Passar flags para o processo de compilação 

### Como utilizar as variáveis

```
make PUB_IN="<pub.in"
```
