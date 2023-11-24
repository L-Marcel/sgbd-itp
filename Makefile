PARAMS = -g -W -pedantic -All_LC=Portuguese
COMPILE = gcc main.c \
	./build/modules/tables.o \
	./build/modules/prints.o \
	./build/modules/files.o \
	./build/modules/menu.o \
	-o ./build/main
EXECUTE = "./build/main.exe"

dev: all ./build/main.exe
	${EXECUTE}
run: ./build/main.exe
	${EXECUTE}
all: main.c prints
	${COMPILE} ${PARAMS}
prints: ./modules/prints.c files
	gcc ./modules/prints.c -o ./build/modules/prints.o -c ${PARAMS}
files: ./modules/files.c tables
	gcc ./modules/files.c -o ./build/modules/files.o -c ${PARAMS}
tables: ./modules/tables.c
	gcc ./modules/tables.c -o ./build/modules/tables.o -c ${PARAMS}
menu: ./modules/menu.c
	gcc ./modules/menu.c -o ./build/modules/menu.o -c ${PARAMS}

# O "menu.c" não tá compilando em nenhum dos makes dev e all. Copiei tudo certinho e não sei a diferença. Ainda vou ler o material do notion sobre