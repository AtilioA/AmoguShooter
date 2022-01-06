CC       := g++
OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -std=c++17 -lm -g -lGL -lGLU -lglut -Wall -pedantic -Wextra -Wno-unused-parameter -Wwrite-strings
EXE 	 := trabalhocg
PROJETO  := main

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
all: clean $(OBJ)/tinyxml2.o $(OBJ)/svg_reader.o $(OBJ)/$(PROJETO).o
	$(CC) $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/tinyxml2.o: $(SRC)/tinyxml2.cpp $(INC)/tinyxml2.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/tinyxml2.cpp" -o "$(OBJ)/tinyxml2.o"

$(OBJ)/svg_reader.o: $(SRC)/svg_reader.cpp $(INC)/svg_reader.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/svg_reader.cpp" -o "$(OBJ)/svg_reader.o"

$(OBJ)/$(PROJETO).o: $(PROJETO).cpp
	$(CC) -c $(CFLAGS) $(PROJETO).cpp -o "$(OBJ)/$(PROJETO).o"

run: all
	./$(EXE)

exe:
	./$(EXE)

# Limpa objetos e o executável do programa
clean:
	-rm $(OBJ)/*.o
	-rm $(EXE)
