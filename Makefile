OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -lm -g -lGL -lGLU -lglut -Wall -pedantic -Wextra -Wwrite-strings
EXE 	 := trabalhocg
PROJETO  := all

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
all: clean $(OBJ)/dists.o $(OBJ)/$(PROJETO).o
	gcc $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/dists.o: $(SRC)/dists.c $(INC)/dists.h
	gcc -c $(CFLAGS) "$(SRC)/dists.c" -o "$(OBJ)/dists.o"

$(OBJ)/$(PROJETO).o: $(PROJETO).c
	gcc -c $(CFLAGS) $(PROJETO).c -o "$(OBJ)/$(PROJETO).o"

# Limpa objetos e o executável do programa
clean:
	-rm $(OBJ)/*.o
	-rm $(EXE)
