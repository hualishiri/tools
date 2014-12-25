GPP = g++ -std=c++11 -g -Wall 

eopera : copera
		./opera
copera : clean opera_test.o shape.o track_unit.o	track.o track_set.o sensor.o sensor_set.o opera.o
		$(GPP) -o opera opera_test.o shape.o track_unit.o track.o track_set.o sensor.o sensor_set.o opera.o
esensor_set : csensor_set
		./sensor_set
csensor_set:clean  sensor_set_test.o shape.o track_unit.o track_set.o sensor.o track.o sensor_set.o
	$(GPP) -o sensor_set sensor_set_test.o shape.o track_unit.o track_set.o sensor.o track.o sensor_set.o
esensor : csensor
	./sensor
csensor :clean  shape.o track_unit.o track_set.o sensor.o track.o sensor_test.o
	$(GPP) -o sensor shape.o track_unit.o track_set.o sensor.o track.o sensor_test.o
etrack_set : ctrack_set
	./track_set
ctrack_set :clean  shape.o track_unit.o track.o track_set.o track_set_test.o
	$(GPP) -o track_set shape.o track_unit.o track.o track_set.o track_set_test.o
etrack : ctrack
	./track
ctrack : clean shape.o track_unit.o track.o track_test.o
	$(GPP) -o track track_test.o track.o track_unit.o shape.o -g 
etrack_unit : track_unit_test_compile
	./track_unit
ctrack_unit:clean  shape.o track_unit.o track_unit_test.o
	$(GPP) -o track_unit track_unit_test.o track_unit.o shape.o -g
eshape : cshape
	./shape
cshape :clean shape.o shape_test.o
	$(GPP) -o shape shape.o shape_test.o -g

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
		-rm -f *.o *_test *out
