PARAMS = -g -W -pedantic -All_LC=Portuguese.utf8
COMPILE = gcc main.c \
	./build/modules/utils.o \
	./build/modules/tables.o \
	./build/modules/prints.o \
	./build/modules/files.o \
	./build/modules/menus.o \
	./build/modules/procedures.o \
	./build/modules/searches.o \
	./build/modules/seeds.o \
	-o ./build/main.exe
FILES = ./main.c \
	./modules/files.c \
	./modules/menus.c \
	./modules/prints.c \
	./modules/procedures.c \
	./modules/searches.c \
	./modules/seeds.c \
	./modules/tables.c \
	./modules/utils.c \
	./modules/headers/files.h \
	./modules/headers/menus.h \
	./modules/headers/prints.h \
	./modules/headers/procedures.h \
	./modules/headers/searches.h \
	./modules/headers/seeds.h \
	./modules/headers/tables.h \
	./modules/headers/utils.h \
	./modules/headers/core.h \
	./modules/headers/enums.h
EXECUTE = "./build/main.exe"

format:
	clang-format -i ${FILES}
seed: all ./build/main.exe
	${EXECUTE} --seed
dev: all ./build/main.exe
	${EXECUTE}
run: ./build/main.exe
	${EXECUTE}
all: main.c seeds
	${COMPILE} ${PARAMS}
seeds: ./modules/seeds.c searches
	gcc ./modules/seeds.c -o ./build/modules/seeds.o -c ${PARAMS}
searches: ./modules/searches.c procedures
	gcc ./modules/searches.c -o ./build/modules/searches.o -c ${PARAMS}
procedures: ./modules/procedures.c menus
	gcc ./modules/procedures.c -o ./build/modules/procedures.o -c ${PARAMS}
menus: ./modules/menus.c prints
	gcc ./modules/menus.c -o ./build/modules/menus.o -c ${PARAMS}
prints: ./modules/prints.c files
	gcc ./modules/prints.c -o ./build/modules/prints.o -c ${PARAMS}
files: ./modules/files.c tables
	gcc ./modules/files.c -o ./build/modules/files.o -c ${PARAMS}
tables: ./modules/tables.c utils
	gcc ./modules/tables.c -o ./build/modules/tables.o -c ${PARAMS}
utils: ./modules/utils.c
	gcc ./modules/utils.c -o ./build/modules/utils.o -c ${PARAMS}
