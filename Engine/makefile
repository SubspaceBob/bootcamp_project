compiler=g++

build: unitEngineClass.o 
	$(compiler) -o unitEngineClass unitEngineClass.o


unitEngineClass.o : unitEngineClass.cpp 
	$(compiler) -c unitEngineClass.cpp  -o unitEngineClass.o

clean:
	rm *.o
	rm unitEngineClass

run: unitEngineClass
	./unitEngineClass

