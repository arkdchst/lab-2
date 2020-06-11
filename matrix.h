#include <stdexcept>
#include <cmath>

template <typename T>
class Matrix{
protected:
	int width = 0, height = 0;
public:
	virtual T get(int x, int y) const = 0;
	virtual void set(T item, int x, int y) = 0;

	int getWidth() const {
		return this->width;
	}

	int getHeight() const {
		return this->height;
	}

	bool operator==(const Matrix<T> &matrix) const {
		if(this->width != matrix.width || this->height != matrix.height) return false;

		for(int i = 0; i < this->width; i++)
			for(int j = 0; j < this->height; j++)
				if(this->get(i, j) != matrix.get(i, j)) return false;
	

		return true;
	}

	float getNorm() const {
		float sum = 0;
		for(int i = 0; i < this->width; i++)
			for(int j = 0; j < this->height; j++){
				T elem = this->get(i, j);
				sum += elem * elem;
			}

		return sqrt(sum);
	}
};


template <typename T>
class DiagonalMatrix : public Matrix<T>{
private:
	Sequence<Sequence<T>*> *data;
	int diag = 0; //diagonality

	int getDiagLength(int x, int y) const {
		return getDiagLength(getDiagNumber(x,y));
	}

	int getDiagLength(int diagNum) const {
		diagNum = this->diag / 2 - diagNum;
		int x = 0, y = 0;
		if(diagNum >= 0){
			x = diagNum;
			y = 0;
		}else{
			x = 0;
			y = -diagNum;
		}

		int t1 = this->width - x;
		int t2 = this->height - y;
		return (t1 < t2 ? t1 : t2);
	}

	int getDiagNumber(int x, int y) const {
		return y - x + this->diag/2;
	}

public:

	DiagonalMatrix(int width, int height, int diag){
		if(width < 0 || height < 0 || diag < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		this->width = width;
		this->height = height;
		this->diag = diag;

		data = (Sequence<Sequence<T>*>*) new ListSequence<ListSequence<T>*>;
		for(int i = 0; i < diag; i++){
			data->append(new ListSequence<T>(getDiagLength(i)));
		}
	}

	T get(int x, int y) const override {
		if(x < 0 || x >= this->width || y < 0 || y >= this->height) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		int num = this->getDiagNumber(x, y);
		if(num < 0 || num >= this->diag) return 0;

		return data->get(getDiagNumber(x,y))->get( (x < y) ? x : y );
	}

	void set(T item, int x, int y) override {
		if(x < 0 || x >= this->width || y < 0 || y >= this->height)  throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		int num = this->getDiagNumber(x, y);
		if(num < 0 || num >= this->diag){
			if(item != 0)
				throw std::domain_error("trying to set non-diagonal element");
			return;
		}

		data->get(getDiagNumber(x,y))->set(item, (x < y) ? x : y );
	}

	int getDiag() const {
		return this->diag;
	}

	DiagonalMatrix<T>* operator+(const DiagonalMatrix<T> &matrix) const {
		DiagonalMatrix<T> *newMatrix = new DiagonalMatrix<T>(this->width, this->height, (this->diag > matrix.diag ? this->diag : matrix.diag));
		for(int i = 0; i < this->width; i++)
			for(int j = 0; j < this->height; j++){
				newMatrix->set(this->get(i, j) + matrix.get(i, j), i, j);
			}

		return newMatrix;
	}

	template <typename U>
	DiagonalMatrix<T>* operator*(U k) const {
		DiagonalMatrix<T> *newMatrix = new DiagonalMatrix<T>(this->width, this->height, this->diag);
		for(int i = 0; i < this->width; i++)
			for(int j = 0; j < this->height; j++){
				newMatrix->set(this->get(i, j) * k, i, j);
			}

		return newMatrix;
	}


};
