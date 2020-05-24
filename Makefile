FILES=src/main.c src/GameState.c src/MainState.c src/JeuState.c src/Mario.c
LIBSW=-lmingw32 -lSDL2main -lSDL2.dll -lSDL2_image
LIBSU=-lSDL2 -lSDL2_image
INCS=-I/usr/include/SDL2 
OPTS=-Wall -Wextra -pedantic -iquoteinclude
OUTPUT=SMB

windows:
	gcc $(OPTS) $(FILES) -mwindows $(LIBSW) -o $(OUTPUT)

all:
	gcc $(OPTS) $(FILES) $(INCS) $(LIBSU) -o $(OUTPUT)
