CC=g++
CFLAGS=-std=c++17 -g
INCLUDECADMIUM=-I./cadmium -I./include

bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
logs_folder := $(shell mkdir -p logs)

main.o: src/main.cpp
	$(CC) -c $(CFLAGS) $(INCLUDECADMIUM) src/main.cpp -o build/main.o

simulator: main.o
	$(CC) $(CFLAGS) -o bin/MAIN build/main.o

.PHONY: clean
clean:
	rm -f bin/* build/*
