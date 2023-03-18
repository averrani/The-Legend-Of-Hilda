CC					= g++
CPPFLAGS 			= -Wall -ggdb   #-O2   
OBJ_DIR 			= obj
SRC_DIR 			= src
BIN_DIR 			= bin
INCLUDE_DIR			= -Isrc -I$(SRC_DIR)/ 
LIBS_SFML = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

default: make_dir make_dir2 $(BIN_DIR)/mainSFML $(BIN_DIR)/mainDefil $(BIN_DIR)/mainTxt

make_dir:
	test -d $(OBJ_DIR) || mkdir -p $(OBJ_DIR) 

make_dir2:
	test -d $(BIN_DIR) || mkdir -p $(BIN_DIR) 


$(BIN_DIR)/mainSFML  : $(OBJ_DIR)/mainSFML.o $(OBJ_DIR)/input.o $(OBJ_DIR)/jeu.o $(OBJ_DIR)/monster.o $(OBJ_DIR)/music.o $(OBJ_DIR)/dessin.o $(OBJ_DIR)/map.o $(OBJ_DIR)/player.o $(OBJ_DIR)/windowTxt.o
	$(CC) $(CPPFLAGS) $(OBJ_DIR)/mainSFML.o $(OBJ_DIR)/input.o $(OBJ_DIR)/jeu.o $(OBJ_DIR)/monster.o $(OBJ_DIR)/music.o $(OBJ_DIR)/dessin.o $(OBJ_DIR)/map.o $(OBJ_DIR)/player.o $(OBJ_DIR)/windowTxt.o -o $(BIN_DIR)/mainSFML $(LIBS_SFML)

$(BIN_DIR)/mainTxt  : $(OBJ_DIR)/mainTxt.o $(OBJ_DIR)/input.o $(OBJ_DIR)/jeu.o $(OBJ_DIR)/monster.o $(OBJ_DIR)/music.o $(OBJ_DIR)/dessin.o $(OBJ_DIR)/map.o $(OBJ_DIR)/player.o $(OBJ_DIR)/windowTxt.o
	$(CC) $(CPPFLAGS) $(OBJ_DIR)/mainTxt.o $(OBJ_DIR)/input.o $(OBJ_DIR)/jeu.o $(OBJ_DIR)/monster.o $(OBJ_DIR)/music.o $(OBJ_DIR)/dessin.o $(OBJ_DIR)/map.o $(OBJ_DIR)/player.o $(OBJ_DIR)/windowTxt.o -o $(BIN_DIR)/mainTxt $(LIBS_SFML)

$(BIN_DIR)/mainDefil  : $(OBJ_DIR)/mainDefil.o $(OBJ_DIR)/input.o $(OBJ_DIR)/jeu.o $(OBJ_DIR)/monster.o $(OBJ_DIR)/music.o $(OBJ_DIR)/dessin.o $(OBJ_DIR)/map.o $(OBJ_DIR)/player.o $(OBJ_DIR)/windowTxt.o
	$(CC) $(CPPFLAGS) $(OBJ_DIR)/mainDefil.o $(OBJ_DIR)/input.o $(OBJ_DIR)/jeu.o $(OBJ_DIR)/monster.o $(OBJ_DIR)/music.o $(OBJ_DIR)/dessin.o $(OBJ_DIR)/map.o $(OBJ_DIR)/player.o $(OBJ_DIR)/windowTxt.o -o $(BIN_DIR)/mainDefil $(LIBS_SFML)

$(OBJ_DIR)/mainSFML.o : $(SRC_DIR)/mainSFML.cpp $(SRC_DIR)/input.h $(SRC_DIR)/jeu.h $(SRC_DIR)/monster.h $(SRC_DIR)/music.h $(SRC_DIR)/map.h $(SRC_DIR)/player.h $(SRC_DIR)/dessin.h
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/mainSFML.cpp -o $@

$(OBJ_DIR)/mainDefil.o : $(SRC_DIR)/mainDefil.cpp $(SRC_DIR)/input.h $(SRC_DIR)/jeu.h $(SRC_DIR)/monster.h $(SRC_DIR)/music.h $(SRC_DIR)/map.h $(SRC_DIR)/player.h $(SRC_DIR)/dessin.h 
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/mainDefil.cpp -o $@

$(OBJ_DIR)/mainTxt.o : $(SRC_DIR)/mainTxt.cpp $(SRC_DIR)/input.h $(SRC_DIR)/jeu.h $(SRC_DIR)/map.h $(SRC_DIR)/player.h $(SRC_DIR)/windowTxt.h
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/mainTxt.cpp -o $@

$(OBJ_DIR)/input.o : $(SRC_DIR)/input.cpp $(SRC_DIR)/input.h 
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/input.cpp -o $@

$(OBJ_DIR)/dessin.o : $(SRC_DIR)/dessin.cpp $(SRC_DIR)/dessin.h
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/dessin.cpp -o $@

$(OBJ_DIR)/map.o : $(SRC_DIR)/map.cpp $(SRC_DIR)/map.h 
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/map.cpp -o $@

$(OBJ_DIR)/player.o : $(SRC_DIR)/player.cpp $(SRC_DIR)/player.h 
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/player.cpp -o $@

$(OBJ_DIR)/jeu.o : $(SRC_DIR)/jeu.cpp $(SRC_DIR)/jeu.h 
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/jeu.cpp -o $@

$(OBJ_DIR)/monster.o : $(SRC_DIR)/monster.cpp $(SRC_DIR)/monster.h 
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/monster.cpp -o $@
	
$(OBJ_DIR)/music.o : $(SRC_DIR)/music.cpp $(SRC_DIR)/music.h 
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/music.cpp -o $@

$(OBJ_DIR)/windowTxt.o : $(SRC_DIR)/windowTxt.cpp $(SRC_DIR)/windowTxt.h
	$(CC) $(CPPFLAGS) -c $(SRC_DIR)/windowTxt.cpp -o $@

clean:
ifeq ($(OS),Windows_NT)
	del /f $(OBJ_DIR)\*.o $(BIN_DIR)\*.exe
else
	rm -rf $(OBJ_DIR) $(BIN_DIR) doc/html
endif
