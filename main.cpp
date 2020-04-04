#include <iostream>
#include <algorithm>
#include <cstring>

#include <stdexcept>

template <typename T> class DynamicArray{
private:
	T *data;
	int size;

public:
	DynamicArray(int size){
		this->data = (T*)calloc(size, sizeof(T));
		this->size = size;
	}


	DynamicArray(T *data, int count) : DynamicArray(count) {
		std::memcpy(this->data, data, count * sizeof(T));
	}

	DynamicArray(const DynamicArray<T> &dynamicArray) : 
		DynamicArray(dynamicArray.data, dynamicArray.size) {}


	T get(int index) const {
		if(index < 0 || index >= size) throw new std::out_of_range("index out of range");

		return data[index];
	}

	int getSize() const {
		return size;
	}

	void set(T value, int index){
		if(index < 0 || index >= size) throw new std::out_of_range("index out of range");

		data[index] = value;
	}	

	void resize(int size){
		if(size < 0) throw new std::length_error("size is negative");

		data = 	(T*)realloc(data, size * sizeof(T));
		this->size = size;
	}

};




int main(int argc, const char *argv[]){

	return 0;
}