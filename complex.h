#include <complex>


template <typename T>
class Complex {
private:
	T real_part;
	T imag_part;

public:
	Complex(T real_part = T(), T imag_part = T())
		: real_part(real_part), imag_part(imag_part){}

	T real() const {
		return this->real_part;
	}

	T imag() const {
		return this->imag_part;
	}

	Complex operator+(int val) const {
		return Complex(this->real_part + val, this->imag_part);
	}

	Complex operator+(const Complex<T> &val) const {
		return Complex(this->real_part + val.real_part, this->imag_part + val.imag_part);
	}

	template <typename U>
	Complex operator*(U val) const {
		return Complex(this->real_part * val, this->imag_part * val);
	}

	template <typename U>
	bool operator==(const Complex<U> &val) const {
		return this->real_part == val.real() && this->imag_part == val.imag();
	}

	template <typename U>
	bool operator!=(const Complex<U> &val) const {
		return !this->operator==(val);
	}

};

