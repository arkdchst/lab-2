
#include "main.cpp"


DiagonalMatrix<float>* inputMatrix(){
	DiagonalMatrix<float> *matrix;

	int width = -1;
	int height = -1;
	int diag = -1;

	while(true){
		std::cout << "width: ";
		std::cin >> width;
		if(width > 0) break;
		std::cout << "width must be positive";
	}

	while(true){
		std::cout << "height: ";
		std::cin >> height;
		if(height > 0) break;
		std::cout << "height must be positive";
	}

	while(true){
		std::cout << "diagonality: ";
		std::cin >> diag;
		if(diag > 0 && diag % 2 == 1) break;
		std::cout << "diagonality must be positive and odd";
	}

	matrix = new DiagonalMatrix<float>(width, height, diag);

	std::cout << "elements of matrix:\n";
	for(int y = 0; y < height; y++){
		for(int x = 0; x < width; x++){
			float in;
			std::cin >> in;
			matrix->set(in, x, y);
		}
	}

	return matrix;
}

void printMatrix(DiagonalMatrix<float> *matrix){
	for(int y = 0; y < matrix->getHeight(); y++){
		for(int x = 0; x < matrix->getWidth(); x++){
			std::cout << matrix->get(x, y) << " ";
		}
		std::cout << "\n";
	}
}

void printSum(DiagonalMatrix<float> *A, DiagonalMatrix<float> *B){
	if(A == nullptr || B == nullptr){
			std::cout << "A or B isn't set\n";
			return;
	}

	if(A->getWidth() != B->getWidth() || A->getHeight() != B->getHeight()){
		std::cout << "A and B has different sizes\n";
		return;
	}
	
	DiagonalMatrix<float> *D = *A + *B;
	printMatrix(D);
	delete D;
}

void printMul(DiagonalMatrix<float> *A, float C){
	if(A == nullptr){
		std::cout << "A isn't set\n";
		return;
	}
	DiagonalMatrix<float> *D = *A * C;
	printMatrix(D);
	delete D;
}

void printNorm(DiagonalMatrix<float> *A){
	if(A == nullptr){
		std::cout << "A isn't set\n";
		return;
	}
	std::cout << A->getNorm() << "\n";
}

void printMenu(){
	std::cout << "1. set A\n2. set B\n3. set c\n4. get A+B\n5. get c*A\n6. get norm of A\n7. exit\n\nchoose: ";
}


void interface(){
	DiagonalMatrix<float> *A = nullptr;
	DiagonalMatrix<float> *B = nullptr;
	float C = 0;

	while(true){
		printMenu();

		int choose = 0;
		std::cin >> choose;

		switch(choose){
			case 1:
				if(A) delete A;
				A = inputMatrix();
				break;
			case 2:
				if(B) delete B;
				B = inputMatrix();
				break;
			case 3:
				std::cout << "C: ";
				std::cin >> C;
				break;
			case 4:
				printSum(A, B);
				break;
			case 5:
				printMul(A, C);
				break;
			case 6:
				printNorm(A);
				break;
			case 7:
				exit(0);
				break;
			default:
				std::cout << "choose number from 1 to 7\n";
		}
		std::cout << "\n\n";
	}

}

int main(int argc, const char *argv[]){
	interface();

	return 0;
}