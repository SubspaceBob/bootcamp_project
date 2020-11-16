compiler=g++

build: unitEngine.o 
	$(compiler) -o unitEngine unitEngine.o


unitEngine.o : unitEngine.cpp 
	$(compiler) -c unitEngine.cpp  -o unitEngine.o

clean:
	rm *.o
	rm unitEngine

run: unitEngine
	./unitEngine

