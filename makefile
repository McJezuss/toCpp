toCpp: toCpp.o
	g++ *.o -o toCpp

toCpp.o: toCpp.cpp
	g++ -g -c toCpp.cpp

run: toCpp
	./toCpp $(FILENAME)

tar:
	tar -cf toCpp.tar toCpp.cpp Guide.txt makefile

clean:
	rm toCpp *.o *.h.gch