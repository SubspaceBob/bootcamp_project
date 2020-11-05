compiler=g++

build: example.o frameToBus.o socketcan_cpp.o 
	$(compiler) -o example example.o frameToBus.o socketcan_cpp.o 


example.o : example.cpp 
	$(compiler) -c example.cpp  -o example.o

frameToBus.o : frameToBus.cpp 
	$(compiler) -c frameToBus.cpp -o frameToBus.o

socketcan_cpp.o : ../socketcan_cpp/socketcan_cpp.cpp
	$(compiler) -c ../socketcan_cpp/socketcan_cpp.cpp -I ../socketcan_cpp/ -o socketcan_cpp.o

clean:
	rm *.o
	rm example

run: example
	./example

