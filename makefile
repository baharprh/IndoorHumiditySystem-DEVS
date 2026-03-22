CC=g++
CFLAGS=-std=c++17 -g
INCLUDECADMIUM=-I./cadmium -I./include

bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
logs_folder := $(shell mkdir -p logs)

build/main.o: src/main.cpp
	$(CC) -c $(CFLAGS) $(INCLUDECADMIUM) src/main.cpp -o build/main.o

build/test_humistat.o: src/test_humistat.cpp
	$(CC) -c $(CFLAGS) $(INCLUDECADMIUM) src/test_humistat.cpp -o build/test_humistat.o

build/test_humidifier.o: src/test_humidifier.cpp
	$(CC) -c $(CFLAGS) $(INCLUDECADMIUM) src/test_humidifier.cpp -o build/test_humidifier.o

build/test_leakage.o: src/test_leakage.cpp
	$(CC) -c $(CFLAGS) $(INCLUDECADMIUM) src/test_leakage.cpp -o build/test_leakage.o

build/test_indoor_air.o: src/test_indoor_air.cpp
	$(CC) -c $(CFLAGS) $(INCLUDECADMIUM) src/test_indoor_air.cpp -o build/test_indoor_air.o

build/test_humidity_plant.o: src/test_humidity_plant.cpp
	$(CC) -c $(CFLAGS) $(INCLUDECADMIUM) src/test_humidity_plant.cpp -o build/test_humidity_plant.o

bin/MAIN: build/main.o
	$(CC) $(CFLAGS) -o bin/MAIN build/main.o

bin/TEST_HUMISTAT: build/test_humistat.o
	$(CC) $(CFLAGS) -o bin/TEST_HUMISTAT build/test_humistat.o

bin/TEST_HUMIDIFIER: build/test_humidifier.o
	$(CC) $(CFLAGS) -o bin/TEST_HUMIDIFIER build/test_humidifier.o

bin/TEST_LEAKAGE: build/test_leakage.o
	$(CC) $(CFLAGS) -o bin/TEST_LEAKAGE build/test_leakage.o

bin/TEST_INDOOR_AIR: build/test_indoor_air.o
	$(CC) $(CFLAGS) -o bin/TEST_INDOOR_AIR build/test_indoor_air.o

bin/TEST_HUMIDITY_PLANT: build/test_humidity_plant.o
	$(CC) $(CFLAGS) -o bin/TEST_HUMIDITY_PLANT build/test_humidity_plant.o

simulator: bin/MAIN

experiments: bin/TEST_HUMISTAT bin/TEST_HUMIDIFIER bin/TEST_LEAKAGE bin/TEST_INDOOR_AIR bin/TEST_HUMIDITY_PLANT

all: simulator experiments

.PHONY: clean simulator experiments all
clean:
	rm -f bin/* build/*
