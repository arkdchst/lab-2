#include <iostream>
#include <algorithm>
#include <cstring>

#include <stdexcept>

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"
#define NEGATIVE_SIZE_MESSAGE "size is negative"


template <typename T> class DynamicArray{
private:
	T *data;
	int size;

public:
	DynamicArray(int size){
		if(size < 0) throw new std::length_error(NEGATIVE_SIZE_MESSAGE);

		this->data = (T*)calloc(size, sizeof(T));
		this->size = size;
	}


	DynamicArray(T *data, int count) : DynamicArray(count) {
		std::memcpy(this->data, data, count * sizeof(T));
	}

	DynamicArray(const DynamicArray<T> &dynamicArray) : 
		DynamicArray(dynamicArray.data, dynamicArray.size) {}


	T get(int index) const {
		if(index < 0 || index >= size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		return data[index];
	}

	int getSize() const {
		return size;
	}

	void set(T value, int index){
		if(index < 0 || index >= size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		data[index] = value;
	}	

	void resize(int size){
		if(size < 0) throw new std::length_error(NEGATIVE_SIZE_MESSAGE);

		data = 	(T*)realloc(data, size * sizeof(T));
		this->size = size;
	}

};





int main(int argc, const char *argv[]){

	return 0;
}