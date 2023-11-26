INCLUDE_PATH= -IC:\msys64\mingw64\include\SDL2
LIB_PATH = -LC:\msys64\mingw64\lib
LIBS = 	-lmingw32 -lSDL2main -lSDL2
FLAGS = -w -Wl,-subsystem,windows

SDL = $(INCLUDE_PATH) $(LIB_PATH) $(FLAGS) $(LIBS)

all :  menu direccion 

menu : src/menu_img.cpp
	g++ $< $(SDL) -o bin/$@ 

m : menu
	./bin/menu

direccion : src/direccion.cpp
	g++ $< $(SDL) -o bin/$@ 

d : direccion
	./bin/direccion



