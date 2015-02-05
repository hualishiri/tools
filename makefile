CC = g++ -std=c++11 
CCFLAG = -g -I ./src

GCC = $(CC) $(CCFLAG)
OUTPUT = bin
OBJECTS = testharness.o event_test.o

OUTPUTOJBECTS = $(patsubst %, $(OUTPUT)/%, $(OBJECTS))

TESTS = \
	event_test

default : all
	
all : $(OBJECTS)

test : all $(TESTS)
	for t in $(TESTS); do echo "*** Running $$t"; ./$(OUTPUT)/$$t || exit 1; done

testharness.o : src/util/testharness.h src/util/testharness.cpp
	$(GCC) -c src/util/testharness.cpp -o $(OUTPUT)/testharness.o

event_test.o : src/event/event.h src/event/event_test.cpp
	$(GCC) -c src/event/event_test.cpp -o $(OUTPUT)/event_test.o
	
event_test : testharness.o event_test.o
	$(GCC) $(OUTPUTOJBECTS) -o $(OUTPUT)/event_test
	
clean:
	rm -rf $(OUTPUTOJBECTS)
