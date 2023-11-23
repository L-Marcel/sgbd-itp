PARAMS = -g -W -pedantic -All_LC=Portuguese
dev:
	make all \
	make run
run: ./build/main.exe
	./build/main.exe
all: main.c prints files tables
	gcc main.c ./build/modules/prints.o ./build/modules/files.o -o ./build/main ${PARAMS}
prints: ./modules/prints.c files tables
	gcc ./modules/prints.c -o ./build/modules/prints.o -c ${PARAMS}
files: ./modules/files.c tables
	gcc ./modules/files.c -o ./build/modules/files.o -c ${PARAMS}
tables: ./modules/tables.c
	gcc ./modules/tables.c -o ./build/modules/tables.o -c ${PARAMS}