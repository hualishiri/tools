CC = g++ -std=c++11 
CCFLAG = -g -I /home/wnlo/tools/src/

GCC = $(CC) $(CCFLAG)
OUTPUT = bin
OBJECTS = map.o map_projection.o event.o webkit.o tool.o data_state_circle.o\
					data_state_line.o data_state_radar.o data_track_unit_list.o \
					opera_context.o opera_option.o state.o state_internal_handle.o \
					state_radar_centered.o state_radar_selected.o \
					state_track_circle_centered.o state_track_circle_selected.o \
					state_track_circle_sided.o state_track_circle_started.o \
					state_track_line_selected.o state_track_line_started.o \
					wheel_handle.o
OUTPUTOJBECTS = $(patsubst %, $(OUTPUT)/%, $(OBJECTS))
	#$(OUTPUTOJBECTS);

estate : cstate
	./$(OUTPUT)/state_test
cstate : webkit.o map.o map_projection.o tool.o event.o state.o state_test.o
	$(GCC) bin/tool.o bin/map.o bin/map_projection.o bin/event.o \
		bin/state.o bin/state_test.o bin/webkit.o -o $(OUTPUT)/state_test
eevent : cevent
	./$(OUTPUT)/event_test
cevent : event.o event_test.o
	$(GCC)  bin/event.o bin/event_test.o -o bin/event_test
emap_projection : cmap_projection
	./map_projection
cmap_projection : map_projection.o map_projection_test.o
	$(GCC) $(OUTPUT)/map_projection.o $(OUTPUT)/map_projection_test.o \
		-o $(OUTPUT)/map_projection
ewebkit : cwebkit
	./$(OUTPUT)/webkit_test
cwebkit : webkit.o webkit_test.o
	$(GCC) $(OUTPUT)/webkit.o $(OUTPUT)/webkit_test.o -o $(OUTPUT)/webkit_test
edata_state_radar : cdata_state_radar
	./$(OUTPUT)/data_state_radar_test
cdata_state_radar : data_state_radar.o data_state_radar_test.o tool.o
	$(GCC) $(OUTPUT)/data_state_radar.o $(OUTPUT)/data_state_radar_test.o \
		$(OUTPUT)/tool.o -o $(OUTPUT)/data_state_radar_test
edata_state_line : cdata_state_line
	./$(OUTPUT)/data_state_line_test
cdata_state_line : data_state_line.o data_state_line_test.o tool.o
	$(GCC) $(OUTPUT)/data_state_line.o $(OUTPUT)/data_state_line_test.o \
		$(OUTPUT)/tool.o -o $(OUTPUT)/data_state_line_test
edata_track_unit_list : cdata_track_unit_list
	./$(OUTPUT)/data_track_unit_list_test
cdata_track_unit_list : data_track_unit_list.o data_track_unit_list_test.o tool.o
	$(GCC) $(OUTPUT)/data_track_unit_list.o $(OUTPUT)/data_track_unit_list_test.o \
		$(OUTPUT)/tool.o -o $(OUTPUT)/data_track_unit_list_test
eopera_option : copera_option
	./$(OUTPUT)/opera_option_test
copera_option : opera_option.o opera_option_test.o tool.o
	$(GCC) $(OUTPUT)/opera_option.o $(OUTPUT)/opera_option_test.o \
		$(OUTPUT)/tool.o -o $(OUTPUT)/opera_option_test
ewheel_handle : cwheel_handle
	./$(OUTPUT)/wheel_handle_test
cwheel_handle : map.o map_projection.o wheel_handle.o wheel_handle_test.o tool.o
	$(GCC) $(OUTPUT)/wheel_handle.o $(OUTPUT)/wheel_handle_test.o \
	$(OUTPUT)/map.o $(OUTPUT)/map_projection.o $(OUTPUT)/tool.o \
	-o $(OUTPUT)/wheel_handle_test
estate_radar_selected : cstate_radar_selected
	./$(OUTPUT)/state_radar_selected_test
cstate_radar_selected : map.o map_projection.o state_radar_selected.o \
	state_radar_selected_test.o tool.o webkit.o event.o state.o \
	data_state_radar.o state_radar_centered.o
	$(GCC) $(OUTPUT)/state_radar_selected.o $(OUTPUT)/state_radar_selected_test.o \
	$(OUTPUT)/map.o $(OUTPUT)/map_projection.o $(OUTPUT)/tool.o $(OUTPUT)/webkit.o \
	$(OUTPUT)/event.o $(OUTPUT)/state.o $(OUTPUT)/data_state_radar.o \
	$(OUTPUT)/state_radar_centered.o -o $(OUTPUT)/state_radar_selected_test
estate_track_line_selected : cstate_track_line_selected
	./$(OUTPUT)/state_track_line_selected_test
cstate_track_line_selected : $(OBJECTS) state_track_line_selected_test.o
	$(GCC) -o $(OUTPUT)/state_track_line_selected_test $(OUTPUTOJBECTS) \
	$(OUTPUT)/state_track_line_selected_test.o 
estate_track_line_started : cstate_track_line_started
	./$(OUTPUT)/state_track_line_started_test
cstate_track_line_started : $(OBJECTS) state_track_line_started_test.o
	$(GCC) -o $(OUTPUT)/state_track_line_started_test $(OUTPUTOJBECTS) \
	$(OUTPUT)/state_track_line_started_test.o 


event.o : src/event/event.h src/event/event.cpp
	$(GCC) -c src/event/event.cpp -o $(OUTPUT)/event.o
state.o : src/state/state.h src/state/state.cpp
	$(GCC) -c src/state/state.cpp -o $(OUTPUT)/state.o
tool.o : src/util/tool.h src/util/tool.cpp
	$(GCC) -c src/util/tool.cpp -o $(OUTPUT)/tool.o
map_projection.o : src/map/map_projection.h src/map/map_projection.cpp
	$(GCC) -c src/map/map_projection.cpp -o $(OUTPUT)/map_projection.o
map.o : src/map/map.h src/map/map.cpp
	$(GCC) -c src/map/map.cpp -o $(OUTPUT)/map.o
webkit.o : src/webkit/webkit.cpp src/webkit/webkit.h
	$(GCC) -c src/webkit/webkit.cpp -o $(OUTPUT)/webkit.o
data_state_radar.o : src/state/data_state_radar.cpp src/state/data_state_radar.h
	$(GCC) -c src/state/data_state_radar.cpp -o $(OUTPUT)/data_state_radar.o
data_state_line.o : src/state/data_state_line.cpp src/state/data_state_line.h
	$(GCC) -c src/state/data_state_line.cpp -o $(OUTPUT)/data_state_line.o
data_state_circle.o : src/state/data_state_circle.cpp src/state/data_state_circle.h
	$(GCC) -c src/state/data_state_circle.cpp -o $(OUTPUT)/data_state_circle.o
data_track_unit_list.o : src/state/data_track_unit_list.cpp \
	src/state/data_track_unit_list.h
	$(GCC) -c src/state/data_track_unit_list.cpp -o $(OUTPUT)/data_track_unit_list.o
opera_option.o : src/state/opera_option.cpp src/state/opera_option.h
	$(GCC) -c src/state/opera_option.cpp -o $(OUTPUT)/opera_option.o
opera_context.o : src/state/opera_context.cpp src/state/opera_context.h
	$(GCC) -c src/state/opera_context.cpp -o $(OUTPUT)/opera_context.o
wheel_handle.o : src/state/wheel_handle.cpp src/state/wheel_handle.h
	$(GCC) -c src/state/wheel_handle.cpp -o $(OUTPUT)/wheel_handle.o
state_radar_selected.o : src/state/state_radar_selected.cpp \
	src/state/state_radar_selected.h
	$(GCC) -c src/state/state_radar_selected.cpp -o $(OUTPUT)/state_radar_selected.o
state_radar_centered.o : src/state/state_radar_centered.cpp \
	src/state/state_radar_centered.h
	$(GCC) -c src/state/state_radar_centered.cpp -o $(OUTPUT)/state_radar_centered.o
state_internal_handle.o : src/state/state_internal_handle.h \
	 src/state/state_internal_handle.cpp
	$(GCC) -o $(OUTPUT)/state_internal_handle.o -c src/state/state_internal_handle.cpp
state_track_line_selected.o : src/state/state_track_line_selected.h \
	src/state/state_track_line_selected.cpp
	$(GCC) -o $(OUTPUT)/state_track_line_selected.o \
		-c src/state/state_track_line_selected.cpp
state_track_line_started.o : src/state/state_track_line_started.h \
	src/state/state_track_line_started.cpp
	$(GCC) -o $(OUTPUT)/state_track_line_started.o \
		-c src/state/state_track_line_started.cpp
state_track_circle_selected.o : src/state/state_track_circle_selected.h \
	src/state/state_track_circle_selected.cpp
	$(GCC) -o $(OUTPUT)/state_track_circle_selected.o \
		-c src/state/state_track_circle_selected.cpp
state_track_circle_started.o : src/state/state_track_circle_started.h \
	src/state/state_track_circle_started.cpp
	$(GCC) -o $(OUTPUT)/state_track_circle_started.o \
		-c src/state/state_track_circle_started.cpp
state_track_circle_centered.o : src/state/state_track_circle_centered.h \
	src/state/state_track_circle_centered.cpp
	$(GCC) -o $(OUTPUT)/state_track_circle_centered.o \
		-c src/state/state_track_circle_centered.cpp
state_track_circle_sided.o : src/state/state_track_circle_sided.h \
	src/state/state_track_circle_sided.cpp
	$(GCC) -o $(OUTPUT)/state_track_circle_sided.o \
		-c src/state/state_track_circle_sided.cpp

event_test.o : src/event/event_test.cpp
	$(GCC) -c src/event/event_test.cpp -o $(OUTPUT)/event_test.o
state_test.o : src/state/state_test.cpp
	$(GCC) -c src/state/state_test.cpp -o $(OUTPUT)/state_test.o
map_projection_test.o : src/map/map_projection_test.cpp
	$(GCC) -c src/map/map_projection_test.cpp -o $(OUTPUT)/map_projection_test.o
map_test.o : src/map/map_test.cpp
	$(GCC) -c src/map/map_test.cpp -o $(OUTPUT)/map_test.o
webkit_test.o : src/webkit/webkit_test.cpp
	$(GCC) -c src/webkit/webkit_test.cpp -o $(OUTPUT)/webkit_test.o
data_state_radar_test.o : src/state/data_state_radar_test.cpp 
	$(GCC) -c src/state/data_state_radar_test.cpp \
		-o $(OUTPUT)/data_state_radar_test.o
data_state_line_test.o : src/state/data_state_line_test.cpp 
	$(GCC) -c src/state/data_state_line_test.cpp \
		-o $(OUTPUT)/data_state_line_test.o
data_track_unit_list_test.o : src/state/data_track_unit_list_test.cpp 
	$(GCC) -c src/state/data_track_unit_list_test.cpp \
		-o $(OUTPUT)/data_track_unit_list_test.o
opera_option_test.o : src/state/opera_option_test.cpp 
	$(GCC) -c src/state/opera_option_test.cpp \
		-o $(OUTPUT)/opera_option_test.o
wheel_handle_test.o : src/state/wheel_handle_test.cpp 
	$(GCC) -c src/state/wheel_handle_test.cpp \
		-o $(OUTPUT)/wheel_handle_test.o
state_radar_selected_test.o : src/state/state_radar_selected_test.cpp 
	$(GCC) -c src/state/state_radar_selected_test.cpp \
		-o $(OUTPUT)/state_radar_selected_test.o
state_radar_centered_test.o : src/state/state_radar_centered_test.cpp 
	$(GCC) -c src/state/state_radar_centered_test.cpp \
		-o $(OUTPUT)/state_radar_centered_test.o
state_track_line_selected_test.o : src/state/state_track_line_selected_test.cpp
	$(GCC) -o $(OUTPUT)/state_track_line_selected_test.o \
	-c src/state/state_track_line_selected_test.cpp
state_track_line_started_test.o : src/state/state_track_line_started_test.cpp
	$(GCC) -o $(OUTPUT)/state_track_line_started_test.o \
	-c src/state/state_track_line_started_test.cpp

test : estate eevent emap_projection ewebkit

clean :
	rm -Rf $(OUTPUT)/*.o $(OUTPUT)/state_test $(OUTPUT)/event_test \
		$(OUTPUT)/webkit_test $(OUTPUT)/map_projection
