GPP = g++ -std=c++11 -g -Wall 

opera_execute : opera_compile
		./opera_test
opera_compile : opera_test.o shape.o track_unit.o	track.o track_set.o sensor.o sensor_set.o opera.o
		$(GPP) -o opera_test
sensor_set_execute : sensor_set_compile
		./sensor_set_test
sensor_set_compile : sensor_set_test.o shape.o track_unit.o track_set.o sensor.o track.o 
	$(GPP) -o sensor_set_test
sensor_execute : sensor_compile
	./sensor_test
sensor_compile : shape.o track_unit.o track_set.o sensor.o track.o sensor_test.o
	$(GPP) -o sensor_test shape.o track_unit.o track_set.o sensor.o track.o sensor_test.o
track_set_execute : track_set_compile 
	./track_set_test
track_set_compile : clean shape.o track_unit.o track.o track_set.o track_set_test.o
	$(GPP) -o track_set_test shape.o track_unit.o track.o track_set.o track_set_test.o
track_test_execute : track_test_compile
	./track_test
track_test_compile : clean shape.o track_unit.o track.o track_test.o
	$(GPP) -o track_test track_test.o track.o track_unit.o shape.o -g 
track_unit_test_execute : track_unit_test_compile
	./track_unit_test
track_unit_test_compile : shape.o track_unit.o track_unit_test.o
	$(GPP) -o track_unit_test track_unit_test.o track_unit.o shape.o -g
shape_test_execute : shape_test_compile
	./shape_test
shape_test_compile: shape.o shape_test.o
	$(GPP) -o shape_test shape.o shape_test.o -g

shape.o : shape.cpp shape.h
	$(GPP) -c shape.cpp
track_unit.o : track_unit.cpp track_unit.h
	$(GPP) -c track_unit.cpp
track.o : track.cpp track.h
	$(GPP) -c track.cpp
track_set.o : track_set.cpp track_set.h
	$(GPP) -c track_set.cpp
sensor.o : sensor.h sensor.cpp
	$(GPP) -c sensor.cpp
sensor_set.o : sensor_set.h sensor_set.cpp
	$(GPP) -c sensor_set.cpp
opera.o : opera.cpp opera.h
	$(GPP) -c opera.cpp

shape_test.o : shape_test.cpp
	$(GPP) -c shape_test.cpp
track_unit_test.o : track_unit_test.cpp
	$(GPP) -c track_unit_test.cpp
track_test.o : track_test.cpp
	$(GPP) -c track_test.cpp
	g++ -std=c++11 -c track_test.cpp -g
track_set_test.o : track_set_test.cpp
	$(GPP) -c track_set_test.cpp
sensor_test.o : sensor_test.cpp
	$(GPP) -c sensor_test.cpp
sensor_set_test.o : sensor_set_test.cpp
	$(GPP) -c sensor_set_test.cpp
opera_test.o : opera_test.cpp
	$(GPP) -c opera_test.cpp

clean :
		-rm -f *.o *_test
