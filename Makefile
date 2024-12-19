CC = g++
CFLAGS = -I C:/mingw64/include
LDFLAGS = -lglfw3 -lopengl32 -lgdi32 -luser32
SRC = main.cpp glad.c
OUT = glfw.exe

$(OUT): $(SRC)
	$(CC) $(SRC) $(CFLAGS) $(LDFLAGS) -o $(OUT)
