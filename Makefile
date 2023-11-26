INCLUDE_PATH= -IC:\msys64\mingw64\include\SDL2
LIB_PATH = -LC:\msys64\mingw64\lib
LIBS = 	-lmingw32 -lSDL2main -lSDL2
FLAGS = -w -Wl,-subsystem,windows

SDL = $(INCLUDE_PATH) $(LIB_PATH) $(FLAGS) $(LIBS)

all :  tutorial2 tutorial4 

tutorial2 : src/menu_img.cpp
	g++ $< $(SDL) -o bin/$@ 

runt2 : tutorial2
	./bin/tutorial2

tutorial4 : src/direccion.cpp
	g++ $< $(SDL) -o bin/$@ 

runt4 : tutorial4
	./bin/tutorial4



