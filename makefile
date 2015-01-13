CC = g++ -std=c++11 
CCFLAG = -g -I /home/wnlo/tools/src/

GCC = $(CC) $(CCFLAG)
OUTPUT = bin

estate : cstate
	./$(OUTPUT)/state_test
cstate :tool.o event.o state.o state_test.o
	$(GCC) bin/tool.o bin/event.o bin/state.o bin/state_test.o -o $(OUTPUT)/state_test
eevent : cevent
	./$(OUTPUT)/event_test
cevent : event.o event_test.o
	$(GCC)  bin/event.o bin/event_test.o -o bin/event_test
emap_projection : cmap_projection
	./map_projection
cmap_projection : map_projection.o map_projection_test.o
	$(GCC) $(OUTPUT)/map_projection.o $(OUTPUT)/map_projection_test.o \
		-o $(OUTPUT)/map_projection

event.o : src/event/event.h src/event/event.cpp
	$(GCC) -c src/event/event.cpp -o $(OUTPUT)/event.o
state.o : src/state/state.h src/state/state.cpp
	$(GCC) -c src/state/state.cpp -o $(OUTPUT)/state.o
tool.o : src/util/tool.h src/util/tool.cpp
	$(GCC) -c src/util/tool.cpp -o $(OUTPUT)/tool.o
map_projection.o : src/map/map_projection.h src/map/map_projection.cpp
	$(GCC) -c src/map/map_projection.cpp -o $(OUTPUT)/map_projection.o

event_test.o : src/event/event_test.cpp
	$(GCC) -c src/event/event_test.cpp -o $(OUTPUT)/event_test.o
state_test.o : src/state/state_test.cpp
	$(GCC) -c src/state/state_test.cpp -o $(OUTPUT)/state_test.o
map_projection_test.o : src/map/map_projection_test.cpp
	$(GCC) -c src/map/map_projection_test.cpp -o $(OUTPUT)/map_projection_test.o

test : estate eevent emap_projection

clean :
	rm -Rf $(OUTPUT)/*.o $(OUTPUT)/state_test $(OUTPUT)/event_test
