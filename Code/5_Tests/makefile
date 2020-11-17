compiler=g++

build: unitEngine.o 
	$(compiler) -o unitEngine unitEngine.o


unitEngine.o : unitengine.cpp 
	$(compiler) -c unitengine.cpp  -o unitEngine.o

clean:
	rm *.o
	rm unitEngine

run: unitEngine
	./unitEngine

