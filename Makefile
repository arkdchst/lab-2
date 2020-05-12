all: tests interface

tests: tests.cpp main.cpp
	g++ tests.cpp -o tests
	
interface: interface.cpp main.cpp
	g++ interface.cpp -o interface
