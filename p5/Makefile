router.out : router.o TripsRunner.o  
	g++ -ansi -Wall -g -o router.out router.o TripsRunner.o  

router.o : router.cpp TripsRunner.h router.h 
	g++ -ansi -Wall -g -c router.cpp

TripsRunner.o : TripsRunner.cpp TripsRunner.h router.h CPUTimer.h 
	g++ -ansi -Wall -g -c TripsRunner.cpp

clean : 
	rm -f router.out router.o  TripsRunner.o   
