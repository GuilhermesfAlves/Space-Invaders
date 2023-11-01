CC = gcc
Cflags = -Wall
#Para compilação dos programas que usam allegro5.h
allegro := $$(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_image-5 --libs --cflags)

#arquivos objeto
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_DIR = objects
SRC_DIR = source
TARGET = space_invaders

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^ $(allegro)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(TARGET)