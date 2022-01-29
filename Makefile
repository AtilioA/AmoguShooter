CC       := g++
OBJ      := obj
SRC      := src
INC      := include
CFLAGS   := -std=c++17 -lm -g -lGL -lGLU -lglut -Wall -pedantic -Wextra -Wno-unused-parameter -Wwrite-strings
EXE 	 := trabalhocg
PROJETO  := main

# Cria objetos de todos os arquivos de código-fonte para então linká-los no programa final
all: clean $(OBJ)/gunshot.o $(OBJ)/$(PROJETO).o $(OBJ)/game.o $(OBJ)/character.o $(OBJ)/terrain.o $(OBJ)/svg_reader.o $(OBJ)/utils.o $(OBJ)/player.o $(OBJ)/enemy.o $(OBJ)/tinyxml2.o
	$(CC) $(OBJ)/*.o -o $(EXE) $(CFLAGS)

$(OBJ)/$(PROJETO).o: $(PROJETO).cpp
	$(CC) -c $(CFLAGS) $(PROJETO).cpp -o "$(OBJ)/$(PROJETO).o"

$(OBJ)/game.o: $(SRC)/game.cpp $(INC)/game.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/game.cpp" -o "$(OBJ)/game.o"

$(OBJ)/gunshot.o: $(SRC)/gunshot.cpp $(INC)/gunshot.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/gunshot.cpp" -o "$(OBJ)/gunshot.o"

$(OBJ)/character.o: $(SRC)/character.cpp $(INC)/character.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/character.cpp" -o "$(OBJ)/character.o"

$(OBJ)/terrain.o: $(SRC)/terrain.cpp $(INC)/terrain.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/terrain.cpp" -o "$(OBJ)/terrain.o"

$(OBJ)/svg_reader.o: $(SRC)/svg_reader.cpp $(INC)/svg_reader.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/svg_reader.cpp" -o "$(OBJ)/svg_reader.o"

$(OBJ)/utils.o: $(SRC)/utils.cpp $(INC)/utils.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/utils.cpp" -o "$(OBJ)/utils.o"

$(OBJ)/player.o: $(SRC)/player.cpp $(INC)/player.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/player.cpp" -o "$(OBJ)/player.o"

$(OBJ)/enemy.o: $(SRC)/enemy.cpp $(INC)/enemy.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/enemy.cpp" -o "$(OBJ)/enemy.o"

$(OBJ)/tinyxml2.o: $(SRC)/tinyxml2.cpp $(INC)/tinyxml2.hpp
	$(CC) -c $(CFLAGS) "$(SRC)/tinyxml2.cpp" -o "$(OBJ)/tinyxml2.o"

run: all
	./$(EXE) input/arena_teste.svg

val: all
	valgrind ./$(EXE) input/arena_teste.svg

debug: all
	./$(EXE) input/arena_teste.svg -d

exe:
	./$(EXE) input/arena_teste.svg

release: clean
	-tar -cvf AtilioAntonioDadalto.zip include/* input/arena_teste.svg obj/ src/* LICENSE main.cpp Makefile README.md

# Limpa objetos e o executável do programa
clean:
	-rm -f $(OBJ)/*.o
	-rm -f $(EXE)
