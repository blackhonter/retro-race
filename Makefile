build:
	g++ -g -Wall -std=c++17 ./src/*.c ./src/*.cpp -o game `sdl2-config --cflags --libs` -lSDL2 -lSDL2_mixer -lm;

buildw:
	i686-w64-mingw32-gcc-win32 ./src/*.c ./src/*.cpp -o game.exe `$(SDL_ROOT_DIR)/bin/sdl2-config --libs` -Wall -Wextra -lSDL2 -lSDL2_mixer -lm;

run:
	./game

clean:
	rm game
