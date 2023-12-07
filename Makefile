INCLUDE_PATH = -IC:\msys64\mingw64\include\SDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
LIB_PATH = -LC:\msys64\mingw64\lib
LIBS = -lmingw32 -lSDL2main -lSDL2
FLAGS = -w -Wl,-subsystem,windows

SDL = $(INCLUDE_PATH) $(LIB_PATH) $(FLAGS) $(LIBS)

menu: src/menu.cpp
	g++ $< $(SDL) -o bin/$@

me: menu
	./bin/menu

main: src/main.cpp
	g++ $< $(SDL) -o bin/$@

m: main
	./bin/main

mini: src/mini.cpp
	g++ $< $(SDL) -o bin/$@

min: mini
	./bin/mini