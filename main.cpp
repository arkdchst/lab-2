#include <iostream>
#include <algorithm>
#include <cstring>

#include <stdexcept>

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"
#define NEGATIVE_SIZE_MESSAGE "size is negative"


template <typename T> class DynamicArray{
private:
	T *data = nullptr;
	int size = 0;

public:
	DynamicArray(int size){
		if(size < 0) throw new std::length_error(NEGATIVE_SIZE_MESSAGE);

		this->data = (T*)calloc(size, sizeof(T));
		this->size = size;
	}


	DynamicArray(T *data, int size) : DynamicArray(size) {
		std::memcpy(this->data, data, size * sizeof(T));
	}

	DynamicArray(const DynamicArray<T> &array) : 
		DynamicArray(array.data, array.size) {}


	T get(int index) const {
		if(index < 0 || index >= size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		return data[index];
	}

	int getSize() const { return size; }

	void set(const T &value, int index){
		if(index < 0 || index >= size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		data[index] = value;
	}	

	void resize(int size){
		if(size < 0) throw new std::length_error(NEGATIVE_SIZE_MESSAGE);

		data = 	(T*)realloc(data, size * sizeof(T));
		this->size = size;
	}

};



template <typename T> class LinkedList{
private:
	struct Record{
		T item;
		Record *next = nullptr;
	};

	Record *head = nullptr;
	int size = 0;
public:
	LinkedList() {}

	LinkedList(T *items, int size) : LinkedList() {
		if(size < 0) throw new std::length_error(NEGATIVE_SIZE_MESSAGE);

		Record **ptr = &head;
		for(int i = 0; i < size; i++){
			*ptr = new Record;
			(*ptr)->item = items[i];
			ptr = &((*ptr)->next);
		}

		this->size = size;
	}


	LinkedList(const LinkedList<T> &list){
		Record *ptr = list.head;
		Record **newPtr = &head;

		for(int i = 0; i < list.size; i++, ptr = ptr->next){
			*newPtr = new Record;
			(*newPtr)->item = ptr->item;
			newPtr = &((*newPtr)->next);

		}

		size = list.size;
	}

	T getFirst() const {
		if(size == 0) throw new std::length_error("size is 0");

		return head->item;
	}

	T getLast() const {
		if(size == 0) throw new std::length_error("size is 0");

		Record *ptr = head;
		while(ptr->next != nullptr) ptr = ptr->next;
		return ptr->item;
	}
	
	T get(int index) const {
		if(index < 0 || index >= size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record *ptr;
		{
		int i = 0;
		for(i = 0, ptr = head; i < index; i++, ptr = ptr->next);
		}

		return ptr->item;
	}

	void set(const T &item, int index){
		if(index < 0 || index >= size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record *ptr;
		{
		int i = 0;
		for(i = 0, ptr = head; i < index; i++, ptr = ptr->next);
		}

		ptr->item = item;
	}

	LinkedList<T>* getSublist(int start, int end) const {
		if(start < 0 || start >= size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(end < 0 || end > size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(start > end) throw new std::logic_error("end must be not less than start");

		LinkedList<T> *newList = new LinkedList<T>();


		Record *ptr = head;
		Record **newPtr = &newList->head;

		for(int i = 0; i < end; i++, ptr = ptr->next){
			if(i >= start){
				*newPtr = new Record;
				(*newPtr)->item = ptr->item;
				newPtr = &((*newPtr)->next);
			}

		}

		newList->size = end - start;

		return newList;
	}

	int getSize() const { return size; }
	
	void append(const T &item){
		Record **ptr = &head;
		while(*ptr != nullptr) ptr = &((*ptr)->next);

		(*ptr) = new Record;
		(*ptr)->item = item;

		size++;
	}
	
	void prepend(const T &item){
		Record *ptr = new Record{item, head};
		head = ptr;

		size++;		
	}

	void insertAt(const T &item, int index){
		if(index < 0 || index > size) throw new std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record preHead = {(T)0, head};
		Record *ptr;

		{
		int i = 0;
		for(i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}

		ptr->next = new Record{item, ptr->next};
		head = preHead.next;

		size++;
	}

	LinkedList<T>* concat(const LinkedList<T> &list) const {
		Record *ptr1 = head;
		Record *ptr2 = list.head;

		LinkedList<T> *newList = new LinkedList<T>();
		Record **ptr = &(newList->head);
		while(ptr1 != nullptr){
			*ptr = new Record{
				ptr1->item,
				ptr1->next
			};

			ptr1 = ptr1->next;
			ptr = &((*ptr)->next);
		}
		while(ptr2 != nullptr){
			*ptr = new Record{
				ptr2->item,
				ptr2->next
			};

			ptr2 = ptr2->next;
			ptr = &((*ptr)->next);
		}

		newList->size = size + list.size;
		return newList;
	}


};




int main(int argc, const char *argv[]){

	return 0;
}