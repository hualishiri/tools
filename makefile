execute : compile
	./track_set_test
compile : clean shape.o track_unit.o track.o track_set.o track_set_test.o
	g++ -std=c++11 -o track_set_test shape.o track_unit.o track.o track_set.o track_set_test.o -g
track_test : clean shape.o track_unit.o track.o track_test.o
	g++ -std=c++11 -o track_test track_test.o track.o track_unit.o shape.o -g 
track_unit_test : shape.o track_unit.o track_unit_test.o
	g++ -std=c++11 -o track_unit_test track_unit_test.o track_unit.o shape.o -g
shape_test : shape.o shape_test.o
	g++ -std=c++11 -o shape_test shape.o shape_test.o -g

shape.o : shape.cpp shape.h
	g++ -std=c++11 -c shape.cpp -g
track_unit.o : track_unit.cpp track_unit.h
	g++ -std=c++11 -c track_unit.cpp -g
track.o : track.cpp track.h
	g++ -std=c++11 -c track.cpp -g
track_set.o : track_set.cpp track_set.h
	g++ -std=c++11 -c track_set.cpp -g

shape_test.o : shape_test.cpp
	g++ -std=c++11 -c shape_test.cpp -g
track_unit_test.o : track_unit_test.cpp
	g++ -std=c++11 -c track_unit_test.cpp -g
track_test.o : track_test.cpp
	g++ -std=c++11 -c track_test.cpp -g
track_set_test.o : track_set_test.cpp
	g++ -std=c++11 -c track_set_test.cpp -g

clean :
		-rm -f *.o *_test
