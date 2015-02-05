CC = g++ -std=c++11 
CCFLAG = -g -I ./src

GCC = $(CC) $(CCFLAG)
OUTPUT = bin
OBJECTS = testharness.o map.o map_projection.o

OUTPUTOJBECTS = $(patsubst %, $(OUTPUT)/%, $(OBJECTS))

TESTS = \
	event_test \
	map_test \
	map_projection_test

default : all
	
all : $(OBJECTS)

test : all $(TESTS)
	for t in $(TESTS); do echo "*** Running $$t"; ./$(OUTPUT)/$$t || exit 1; done

testharness.o : src/util/testharness.h src/util/testharness.cpp
	$(GCC) -c src/util/testharness.cpp -o $(OUTPUT)/testharness.o
map.o : src/map/map.h src/map/map.cpp
	$(GCC) -c src/map/map.cpp -o $(OUTPUT)/map.o
map_projection.o : src/map/map_projection.h src/map/map_projection.cpp
	$(GCC) -c src/map/map_projection.cpp -o $(OUTPUT)/map_projection.o

event_test.o : src/event/event.h src/event/event_test.cpp
	$(GCC) -c src/event/event_test.cpp -o $(OUTPUT)/event_test.o
map_test.o : map.o src/map/map_test.cpp
	$(GCC) -c src/map/map_test.cpp -o $(OUTPUT)/map_test.o
map_projection_test.o : map_projection.o src/map/map_projection_test.cpp
	$(GCC) -c src/map/map_projection_test.cpp -o $(OUTPUT)/map_projection_test.o

	
event_test : testharness.o event_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/event_test.o -o $(OUTPUT)/event_test
map_test : testharness.o map.o map_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/map_test.o -o $(OUTPUT)/map_test
map_projection_test : testharness.o map_projection.o map_projection_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/map_projection_test.o \
		-o $(OUTPUT)/map_projection_test
	
clean :
	rm -rf $(OUTPUTOJBECTS)
