export EM_CACHE:=/home/salim_belkacem/.emscripten_cache

CC = emcc
IN = main.c
BIN = bin

ldir = /home/salim_belkacem/libs/raylib-5.5_webassembly
libs = $(ldir)/lib/libraylib.a -I. -I$(ldir)/include/ -L. -L$(ldir)/lib/libraylib.a


main.html: $(IN)
	$(CC) -o $(BIN)/$@ $< $(libs) -Os -Wall -s USE_GLFW=3 --shell-file ./shell.html -DPLATFORM_WEB
