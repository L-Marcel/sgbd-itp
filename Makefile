PARAMS = -g -W -pedantic -All_LC=Portuguese.utf8
COMPILE = gcc main.c \
	./build/modules/utils.o \
	./build/modules/tables.o \
	./build/modules/prints.o \
	./build/modules/files.o \
	./build/modules/menus.o \
	./build/modules/procedures.o \
	./build/seeds/users.o \
	-o ./build/main.exe
EXECUTE = "./build/main.exe"

dev.seeded: all ./build/main.exe
	${EXECUTE} --seed
dev: all ./build/main.exe
	${EXECUTE}
run.seeded: ./build/main.exe
	${EXECUTE} --seed
run: ./build/main.exe
	${EXECUTE}
all: main.c seeds
	${COMPILE} ${PARAMS}
seeds: ./seeds/users.c procedures
	gcc ./seeds/users.c -o ./build/seeds/users.o -c ${PARAMS}
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
