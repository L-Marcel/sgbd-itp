PARAMS = -g -W -pedantic -All_LC=Portuguese
COMPILE = gcc main.c \
	./build/modules/tables.o \
	./build/modules/prints.o \
	./build/modules/files.o \
	./build/modules/menus.o \
	-o ./build/main.exe
EXECUTE = "./build/main.exe"

dev: all ./build/main.exe
	${EXECUTE}
run: ./build/main.exe
	${EXECUTE}
all: main.c menus
	${COMPILE} ${PARAMS}
menus: ./modules/menus.c prints
	gcc ./modules/menus.c -o ./build/modules/menus.o -c ${PARAMS}
prints: ./modules/prints.c files
	gcc ./modules/prints.c -o ./build/modules/prints.o -c ${PARAMS}
files: ./modules/files.c tables
	gcc ./modules/files.c -o ./build/modules/files.o -c ${PARAMS}
tables: ./modules/tables.c
	gcc ./modules/tables.c -o ./build/modules/tables.o -c ${PARAMS}
