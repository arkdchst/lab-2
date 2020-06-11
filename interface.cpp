
#include <iostream>
#include <string>
#include <limits>

#include <boost/format.hpp>

#include "base.h"
#include "sequence.h"
#include "matrix.h"


using complexf = complex<float>;

enum Type {INT, COMPLEX};

struct TypedDiagonalMatrix{

	Type type;
	void *value;

	DiagonalMatrix<int>* asInt() const {
		return static_cast<DiagonalMatrix<int>*>(value);
	}

	DiagonalMatrix<complexf>* asComplex() const {
		return static_cast<DiagonalMatrix<complexf>*>(value);
	}

	TypedDiagonalMatrix(Type type, int width, int height, int diag) : type(type){
		if(type == INT)
			value = new DiagonalMatrix<int>(width, height, diag);
		else if(type == COMPLEX)
			value = new DiagonalMatrix<complexf>(width, height, diag);
	}

	TypedDiagonalMatrix(Type type, void *value)
		: type(type), value(value){}

	~TypedDiagonalMatrix(){
		if(type == INT)
			delete asInt();
		else if(type == COMPLEX)
			delete asComplex();
	}


	int getWidth() const {
		if(type == INT)
			return asInt()->getWidth();
		else if(type == COMPLEX)
			return asComplex()->getWidth();
		else
			return -1;
	}

	int getHeight() const {
		if(type == INT)
			return asInt()->getHeight();
		else if(type == COMPLEX)
			return asComplex()->getHeight();
		else
			return -1;
	}

	int getDiag() const {
		if(type == INT)
			return asInt()->getDiag();
		else if(type == COMPLEX)
			return asComplex()->getDiag();
		else
			return -1;
	}

	void print() const {
		for(int y = 0; y < this->getHeight(); y++){
			for(int x = 0; x < this->getWidth(); x++){
				if(this->type == INT){
					std::cout << this->asInt()->get(x, y) << " ";
				}
				else if(this->type == COMPLEX){
					std::cout << boost::format("%1$.1f%2$+.1fi\t") % this->asComplex()->get(x, y).real() % this->asComplex()->get(x, y).imag();
				}
			}
			std::cout << "\n";
		}
		std::cout << "\n\n";
	}

	TypedDiagonalMatrix* operator+(const TypedDiagonalMatrix &matrix) const {
		TypedDiagonalMatrix *newMatrix;
		Type type;
		void *value;

		if(this->type == INT && matrix.type == INT){
			type = INT;
			value = *asInt() + *matrix.asInt();
		}
		else if(this->type == INT && matrix.type == COMPLEX){
			type = COMPLEX;
			value = *matrix.asComplex() + *asInt();
		}
		else if(this->type == COMPLEX && matrix.type == INT){
			type = COMPLEX;
			value = *asComplex() + *matrix.asInt();
		}
		else if(this->type == COMPLEX && matrix.type == COMPLEX){
			type = COMPLEX;
			value = *asComplex() + *matrix.asComplex();
		}

		newMatrix = new TypedDiagonalMatrix(type, value);
		return newMatrix;
	}

	TypedDiagonalMatrix* operator*(float val) const {
		TypedDiagonalMatrix *newMatrix;
		Type type;
		void *value;

		if(this->type == INT){
			type = INT;
			value = *asInt() * val;
		}
		else if(this->type == COMPLEX){
			type = COMPLEX;
			value = *asComplex() * val;
		}

		newMatrix = new TypedDiagonalMatrix(type, value);
		return newMatrix;
	}

};


void print(std::string str){
	if(str.empty()) return;

	if(str.back() == ':')
		std::cout << str << "\n";
	else
		std::cout << str << "\n\n";

	std::cout.flush();
}

int readInt(int from=std::numeric_limits<int>::min(), int to=std::numeric_limits<int>::max()){
	while(true){
		try{
			std::string line;
			std::getline(std::cin, line);
			if(line.empty()) throw std::exception();

			int read = std::stoi(line);
			if(read < from || read > to) throw std::exception();

			std::cout << "\n";
			return read;
		}catch(...){
			print("please, enter a number from " + std::to_string(from) + " to " + std::to_string(to) + ":");
		}

	}
}

float readFloat(float from=std::numeric_limits<float>::lowest(), float to=std::numeric_limits<float>::max()){
	while(true){
		try{
			std::string line;
			std::getline(std::cin, line);
			if(line.empty()) throw std::exception();

			float read = std::stof(line);
			if(read < from || read > to) throw std::exception();

			std::cout << "\n";
			return read;
		}catch(...){
			print("please, enter a float number from " + std::to_string(from) + " to " + std::to_string(to) + ":");
		}

	}
}


TypedDiagonalMatrix* readMatrix(){
	print("1. integer\n2. complex");
	int choice = readInt(1,2);

	print("enter width:");
	int width = readInt(1);

	print("enter height:");
	int height = readInt(1);

	int diag = 0;
	while(true){
		print("enter diagonality:");
		diag = readInt(1, (std::min(width, height) - 1) * 2 + 1);
		if(diag % 2 != 1)
			print("diagonality must be odd");
		else
			break;
	}

	if(choice == 1){
		TypedDiagonalMatrix *matrix = new TypedDiagonalMatrix(INT, width, height, diag);

		for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++){
			print("enter element (" + std::to_string(y+1) + "," + std::to_string(x+1) + "):");
			int read = readInt();
			matrix->asInt()->set(read, x, y);
		}

		return matrix;
	}
	else if(choice == 2){
		TypedDiagonalMatrix *matrix = new TypedDiagonalMatrix(COMPLEX, width, height, diag);

		for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++){
			print("enter element (" + std::to_string(y+1) + "," + std::to_string(x+1) + ") real part:");
			float real = readFloat();
			print("enter element (" + std::to_string(y+1) + "," + std::to_string(x+1) + ") imag part:");
			float imag = readFloat();

			complexf read(real, imag);
			matrix->asComplex()->set(read, x, y);
		}

		return matrix;
	}

	return nullptr;

}



void printMenu(){
	print("1. set A\n2. set B\n3. set c\n4. get A+B\n5. get c*A\n6. exit");
}

void menu(){
	TypedDiagonalMatrix *A = nullptr;
	TypedDiagonalMatrix *B = nullptr;
	float c = 0;

	while(true){	
		printMenu();
		int choice = readInt(1,6);

		switch(choice){
			case 1:
				delete A;
				A = readMatrix();
				break;
			case 2:
				delete B;
				B = readMatrix();
				break;
			case 3:
				print("enter c:");
				c = readFloat();
				break;
			case 4:
				{
				if(!A || !B){
					print("A or B isn't set");
					break;
				}

				TypedDiagonalMatrix *D = nullptr;
				try{
					D = *A + *B;
					D->print();
				}catch(...){
					print("A and B have different size");
				}
				delete D;
				break;
				}
			case 5:
				{
				if(!A){
					print("A isn't set");
					break;
				}

				TypedDiagonalMatrix *D = nullptr;
				D = *A * c;
				D->print();
				delete D;
				break;
				}
			case 6:
				return;
		}
	}
}


int main(){
	menu();

	return 0;
}