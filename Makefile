.PHONY: all clean
all: tests interface

CMD := g++

tests: tests.cpp main.cpp
	$(CMD) tests.cpp -o tests
	
interface: interface.cpp main.cpp
	$(CMD) interface.cpp -o interface

clean:
	rm tests interface