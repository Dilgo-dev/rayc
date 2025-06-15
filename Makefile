CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = main
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

SOURCES = $(shell find $(SRC_DIR) -name '*.c')
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
SUBDIRS = $(shell find $(SRC_DIR) -type d)
OBJ_SUBDIRS = $(SUBDIRS:$(SRC_DIR)%=$(OBJ_DIR)%)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
	@echo "✓ Compilation terminée : $(TARGET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_SUBDIRS)
	$(CC) $(CFLAGS) $(INCLUDES) -I$(INC_DIR) -c $< -o $@
	@echo "✓ Compilé: $<"

$(OBJ_SUBDIRS):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(TARGET)
	@echo "✓ Nettoyage terminé"

rebuild: clean all

debug:
	@echo "Sources trouvées:"
	@echo $(SOURCES)
	@echo "Objets à créer:"
	@echo $(OBJECTS)
	@echo "Sous-dossiers objets:"
	@echo $(OBJ_SUBDIRS)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

help:
	@echo "Commandes disponibles:"
	@echo "  make        - Compile le projet"
	@echo "  make clean  - Supprime les fichiers générés"
	@echo "  make rebuild- Nettoie et recompile"
	@echo "  make debug  - Affiche les fichiers détectés"
	@echo "  make help   - Affiche cette aide"

.PHONY: all clean rebuild debug help install