.PHONY: all clean
all: tests interface

CMD := g++ -std=c++17

tests: tests.cpp base.h sequence.h matrix.h complex.h
	$(CMD) tests.cpp -o tests
	
interface: interface.cpp base.h sequence.h matrix.h complex.h
	$(CMD) interface.cpp -o interface

clean:
	rm tests interface