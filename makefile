CC = g++ -std=c++11 
CCFLAG = -g -I ./src -Wall -Werror

GCC = $(CC) $(CCFLAG)
OUTPUT = bin
OBJECTS = testharness.o map.o map_projection.o tool.o logger.o \
					js_create_object.o

OUTPUTOJBECTS = $(patsubst %, $(OUTPUT)/%, $(OBJECTS))

TESTS = \
	event_test \
	map_test \
	map_projection_test \
	tool_test \
	logger_test \
	js_create_object_test

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
tool.o : src/util/tool.h src/util/tool.cpp
	$(GCC) -c src/util/tool.cpp -o $(OUTPUT)/tool.o
logger.o : src/util/logger.h src/util/logger.cpp
	$(GCC) -c src/util/logger.cpp -o $(OUTPUT)/logger.o
js_create_object.o : src/webkit/js_create_object.h src/webkit/js_create_object.cpp
	$(GCC) -c src/webkit/js_create_object.cpp -o $(OUTPUT)/js_create_object.o


event_test.o : src/event/event.h src/event/event_test.cpp
	$(GCC) -c src/event/event_test.cpp -o $(OUTPUT)/event_test.o
map_test.o : map.o src/map/map_test.cpp
	$(GCC) -c src/map/map_test.cpp -o $(OUTPUT)/map_test.o
map_projection_test.o : map_projection.o src/map/map_projection_test.cpp
	$(GCC) -c src/map/map_projection_test.cpp -o $(OUTPUT)/map_projection_test.o
tool_test.o : src/util/tool.h src/util/tool_test.cpp
	$(GCC) -c src/util/tool_test.cpp -o $(OUTPUT)/tool_test.o
logger_test.o : src/util/logger.h src/util/logger_test.cpp
	$(GCC) -c src/util/logger_test.cpp -o $(OUTPUT)/logger_test.o
js_create_object_test.o : src/webkit/js_create_object.h \
	src/webkit/js_create_object_test.cpp
	$(GCC) -c src/webkit/js_create_object_test.cpp -o \
		$(OUTPUT)/js_create_object_test.o
	
event_test : testharness.o event_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/event_test.o -o $(OUTPUT)/event_test
map_test : testharness.o map.o map_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/map_test.o -o $(OUTPUT)/map_test
map_projection_test : testharness.o map_projection.o map_projection_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/map_projection_test.o \
		-o $(OUTPUT)/map_projection_test
tool_test : testharness.o tool.o tool_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/tool_test.o \
		-o $(OUTPUT)/tool_test
logger_test : testharness.o logger.o logger_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/logger_test.o \
		-o $(OUTPUT)/logger_test
js_create_object_test : js_create_object_test.o 
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/js_create_object_test.o \
		-o $(OUTPUT)/js_create_object_test
	
clean :
	rm -rf $(OUTPUTOJBECTS)
