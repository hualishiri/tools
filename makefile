CC = g++ -std=c++11 
CCFLAG = -pg -g -I ./src -Wall -Werror $(VERSION)

VERSION = $(RELEASE)

DEBUG = -D LOGDEBUG
RELEASE = -D NDEBUG

GCC = $(CC) $(CCFLAG)
OUTPUT = bin
OBJECTS = testharness.o map.o map_projection.o tool.o logger.o \
					js_create_object.o line.o circle.o eclipse.o track_unit.o \
					track.o track_set.o radar_mechanical.o radar_set.o \
					opera_option.o opera.o radar_sector.o radar_noise_gauss.o \
					opera_random.o

OUTPUTOJBECTS = $(patsubst %, $(OUTPUT)/%, $(OBJECTS))

TESTS = \
	event_test \
	map_test \
	map_projection_test \
	tool_test \
	logger_test \
	js_create_object_test \
	line_test \
	circle_test \
	eclipse_test \
	track_unit_test \
	track_test \
	track_set_test \
	radar_mechanical_test \
	radar_set_test \
	opera_option_test \
	opera_test \
	radar_noise_gauss_test \
	opera_random_test

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
js_create_object.o : src/webkit/js_create_object.h \
	src/webkit/js_create_object.cpp
	$(GCC) -c src/webkit/js_create_object.cpp -o $(OUTPUT)/js_create_object.o
line.o : src/opera/line.h src/opera/line.cpp
	$(GCC) -c src/opera/line.cpp -o $(OUTPUT)/line.o
circle.o : src/opera/circle.h src/opera/circle.cpp
	$(GCC) -c src/opera/circle.cpp -o $(OUTPUT)/circle.o
eclipse.o : src/opera/eclipse.h src/opera/eclipse.cpp
	$(GCC) -c src/opera/eclipse.cpp -o $(OUTPUT)/eclipse.o
track_unit.o : src/opera/track_unit.h src/opera/track_unit.cpp
	$(GCC) -c src/opera/track_unit.cpp -o $(OUTPUT)/track_unit.o
track.o : src/opera/track.h src/opera/track.cpp
	$(GCC) -c src/opera/track.cpp -o $(OUTPUT)/track.o
track_set.o : src/opera/track_set.h src/opera/track_set.cpp
	$(GCC) -c src/opera/track_set.cpp -o $(OUTPUT)/track_set.o
radar_mechanical.o : src/opera/radar_mechanical.h src/opera/radar_mechanical.cpp
	$(GCC) -c src/opera/radar_mechanical.cpp -o $(OUTPUT)/radar_mechanical.o
radar_set.o : src/opera/radar_set.h src/opera/radar_set.cpp
	$(GCC) -c src/opera/radar_set.cpp -o $(OUTPUT)/radar_set.o
opera_option.o : src/opera/opera_option.h src/opera/opera_option.cpp
	$(GCC) -c src/opera/opera_option.cpp -o $(OUTPUT)/opera_option.o
opera.o : src/opera/opera.h src/opera/opera.cpp
	$(GCC) -c src/opera/opera.cpp -o $(OUTPUT)/opera.o
radar_sector.o : src/opera/radar_sector.h src/opera/radar_sector.cpp
	$(GCC) -c src/opera/radar_sector.cpp -o $(OUTPUT)/radar_sector.o
radar_noise_gauss.o : src/opera/radar_noise_gauss.h src/opera/radar_noise_gauss.cpp
	$(GCC) -c src/opera/radar_noise_gauss.cpp -o $(OUTPUT)/radar_noise_gauss.o
opera_random.o : src/opera/opera_random.h src/opera/opera_random.cpp
	$(GCC) -c src/opera/opera_random.cpp -o $(OUTPUT)/opera_random.o


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
line_test.o : src/opera/line.h src/opera/line_test.cpp
	$(GCC) -c src/opera/line_test.cpp -o $(OUTPUT)/line_test.o
circle_test.o : src/opera/circle.h src/opera/circle_test.cpp
	$(GCC) -c src/opera/circle_test.cpp -o $(OUTPUT)/circle_test.o
eclipse_test.o : src/opera/eclipse.h src/opera/eclipse_test.cpp
	$(GCC) -c src/opera/eclipse_test.cpp -o $(OUTPUT)/eclipse_test.o
track_unit_test.o : src/opera/track_unit.h src/opera/track_unit_test.cpp
	$(GCC) -c src/opera/track_unit_test.cpp -o $(OUTPUT)/track_unit_test.o
track_test.o : src/opera/track.h src/opera/track_test.cpp
	$(GCC) -c src/opera/track_test.cpp -o $(OUTPUT)/track_test.o
track_set_test.o : src/opera/track_set.h src/opera/track_set_test.cpp
	$(GCC) -c src/opera/track_set_test.cpp -o $(OUTPUT)/track_set_test.o
radar_mechanical_test.o : src/opera/radar_mechanical.h \
	src/opera/radar_mechanical_test.cpp
	$(GCC) -c src/opera/radar_mechanical_test.cpp \
		-o $(OUTPUT)/radar_mechanical_test.o
radar_set_test.o : src/opera/radar_set.h src/opera/radar_set_test.cpp
	$(GCC) -c src/opera/radar_set_test.cpp -o $(OUTPUT)/radar_set_test.o
opera_option_test.o : src/opera/opera_option.h src/opera/opera_option_test.cpp
	$(GCC) -c src/opera/opera_option_test.cpp -o $(OUTPUT)/opera_option_test.o
opera_test.o : src/opera/opera.h src/opera/opera_test.cpp
	$(GCC) -c src/opera/opera_test.cpp -o $(OUTPUT)/opera_test.o
radar_noise_gauss_test.o : radar_noise_gauss.o tool.o\
	src/opera/radar_noise_gauss_test.cpp
	$(GCC) -c src/opera/radar_noise_gauss_test.cpp -o $(OUTPUT)/radar_noise_gauss_test.o
opera_random_test.o : src/opera/opera_random.h src/opera/opera_random_test.cpp \
	src/opera/opera_random.cpp
	$(GCC) -c src/opera/opera_random_test.cpp -o $(OUTPUT)/opera_random_test.o
	
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
line_test : line_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/line_test.o -o $(OUTPUT)/line_test
circle_test : circle_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/circle_test.o -o $(OUTPUT)/circle_test
eclipse_test : eclipse_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/eclipse_test.o -o $(OUTPUT)/eclipse_test
track_unit_test : track_unit_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/track_unit_test.o \
		-o $(OUTPUT)/track_unit_test
track_test : track_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/track_test.o -o $(OUTPUT)/track_test
track_set_test : track_set_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/track_set_test.o -o $(OUTPUT)/track_set_test
radar_mechanical_test : radar_mechanical_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/radar_mechanical_test.o \
		-o $(OUTPUT)/radar_mechanical_test
radar_set_test : radar_set_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/radar_set_test.o -o $(OUTPUT)/radar_set_test
opera_option_test : opera_option_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/opera_option_test.o -o $(OUTPUT)/opera_option_test
opera_test : opera_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/opera_test.o -o $(OUTPUT)/opera_test
radar_noise_gauss_test : radar_noise_gauss_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/radar_noise_gauss_test.o -o $(OUTPUT)/radar_noise_gauss_test
opera_random_test : opera_random_test.o
	$(GCC) $(OUTPUTOJBECTS) $(OUTPUT)/opera_random_test.o -o $(OUTPUT)/opera_random_test
	
clean :
	rm -rf $(OUTPUTOJBECTS)
