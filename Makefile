.PHONY: all clean
all: tests interface

CMD := g++

tests: tests.cpp base.h sequence.h matrix.h
	$(CMD) tests.cpp -o tests
	
interface: interface.cpp base.h sequence.h matrix.h
	$(CMD) interface.cpp -o interface

clean:
	rm tests interface