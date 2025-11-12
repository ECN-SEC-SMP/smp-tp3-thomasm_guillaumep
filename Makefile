EXEC= tp3
CXXFLAGS= -g -O0 -Wall -std=c++17

$(EXEC) : outils.o chargesauve.o main.o
	g++ -o $(EXEC) outils.o chargesauve.o main.o

main.o : main.cpp chargesauve.h outils.h
	g++ -c $(CXXFLAGS) main.cpp

outils.o : outils.cpp outils.h
	g++ -c $(CXXFLAGS) outils.cpp

chargesauve.o : chargesauve.cpp chargesauve.h
	g++ -c $(CXXFLAGS) chargesauve.cpp

clean :
	rm -f $(EXEC) *.o