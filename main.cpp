#include <iostream>
#include <algorithm>
#include <cstring>

#include <stdexcept>

#define INDEX_OUT_OF_RANGE_MESSAGE "index out of range"
#define NEGATIVE_SIZE_MESSAGE "size is negative"
#define ZERO_SIZE_MESSAGE "size is 0"


template <typename T> class DynamicArray{
private:
	T *data = nullptr;
	int size = 0;
public:
	DynamicArray() : size(0) {}

	DynamicArray(int size) : size(size) {
		if(size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		this->data = new T[size];
	}


	DynamicArray(T *data, int size) : DynamicArray(size) {
		std::memcpy(this->data, data, size * sizeof(T));
	}

	DynamicArray(const DynamicArray<T> &array, int size){
		if(size > array.size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		*this = DynamicArray(array.data, size);
	}

	DynamicArray(const DynamicArray<T> &array) : 
		DynamicArray(array.data, array.size) {}

	virtual ~DynamicArray(){
		delete[] this->data;
		this->size = 0;
	}


	T get(int index) const {
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		return this->data[index];
	}

	int getSize() const { return this->size; }

	void set(const T &value, int index){
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->data[index] = value;
	}	

	void resize(int size){
		if(size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		T *newData = new T[size];
		std::memcpy(newData, this->data, (this->size > size ? size : this->size) * sizeof(T));
		delete[] data;
		this->data = newData;

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
	LinkedList() : size(0) {}

	LinkedList(T *items, int size) : LinkedList() {
		if(size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		Record **ptr = &(this->head);
		for(int i = 0; i < size; i++){
			*ptr = new Record;
			(*ptr)->item = items[i];
			ptr = &((*ptr)->next);
		}

		this->size = size;
	}


	LinkedList(const LinkedList<T> &list){
		Record *ptr = list.head;
		Record **newPtr = &(this->head);

		for(int i = 0; i < list.size; i++, ptr = ptr->next){
			*newPtr = new Record;
			(*newPtr)->item = ptr->item;
			newPtr = &((*newPtr)->next);

		}

		this->size = list.size;
	}

	virtual ~LinkedList(){
		Record *ptr = this->head;
		Record *next;
		while(ptr != nullptr){
			next = ptr->next;
			delete ptr;
			ptr = next;
		}
	}


	T getFirst() const {
		if(this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);

		return this->head->item;
	}

	T getLast() const {
		if(this->size == 0) throw std::length_error(ZERO_SIZE_MESSAGE);

		Record *ptr = this->head;
		while(ptr->next != nullptr) ptr = ptr->next;
		return ptr->item;
	}
	
	T get(int index) const {
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record *ptr;
		{
		int i = 0;
		for(i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
		}

		return ptr->item;
	}

	void set(const T &item, int index){
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record *ptr;
		{
		int i = 0;
		for(i = 0, ptr = this->head; i < index; i++, ptr = ptr->next);
		}

		ptr->item = item;
	}

	LinkedList<T>* getSublist(int start, int end) const {
		if(start < 0 || start >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(end < 0 || end > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(start > end) throw std::logic_error("end must be not less than start");

		LinkedList<T> *newList = new LinkedList<T>();


		Record *ptr = this->head;
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

	int getSize() const { return this->size; }
	
	void append(const T &item){
		Record **ptr = &(this->head);
		while(*ptr != nullptr) ptr = &((*ptr)->next);

		(*ptr) = new Record;
		(*ptr)->item = item;

		this->size++;
	}
	
	void prepend(const T &item){
		Record *ptr = new Record{item, this->head};
		this->head = ptr;

		this->size++;		
	}

	void removeAt(int index){
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record preHead = {.next = this->head};
		Record *ptr;

		{
		int i = 0;
		for(i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}

		Record *tmp = ptr->next;
		ptr->next = ptr->next->next;
		delete tmp;

		this->head = preHead.next;

		this->size--;
	}

	void insertAt(const T &item, int index){
		if(index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);


		Record preHead = {.next = this->head};
		Record *ptr;

		{
		int i = 0;
		for(i = 0, ptr = &preHead; i < index; i++, ptr = ptr->next);
		}

		ptr->next = new Record{item, ptr->next};
		this->head = preHead.next;

		this->size++;
	}

	LinkedList<T>* concat(const LinkedList<T> &list) const {
		Record *ptr1 = this->head;
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

		newList->size = this->size + list.size;
		return newList;
	}


};



template <typename T> class Sequence{
public:
	int size = 0;
	Sequence(){}
public:

	virtual T getFirst() const = 0;
	virtual T getLast() const = 0;
	virtual T get(int index) const = 0;
	virtual int getSize() const { return this->size; }


	virtual Sequence<T>* getSubsequence(int start, int end) const = 0;

	virtual void set(const T &item, int index) = 0;
	virtual void append(const T &item) = 0;
	virtual void prepend(const T &item) = 0;
	virtual void insertAt(const T &item, int index) = 0;

	virtual Sequence<T>* concat(const Sequence<T>& seq) const = 0;

};


template <typename T> class ArraySequence : public Sequence<T>{
protected:
	DynamicArray<T> *array;

public:
	ArraySequence(){
		this->array = new DynamicArray<T>();
		this->size = 0;
	}

	ArraySequence(const ArraySequence<T> &seq){
		this->array = new DynamicArray<T>(seq.array);
		this->size = seq.size;
	}

	ArraySequence(DynamicArray<T>* array){
		this->array = array;
		this->size = array->getSize();
	}


	ArraySequence(T *items, int size){
		this->array = new DynamicArray<T>(items, size);
		this->size = size;
	}

	virtual ~ArraySequence(){
		delete this->array;
	}

	virtual T getFirst() const override {
		return this->array->get(0);
	}

	virtual T getLast() const override {
		return this->array->get(this->size - 1);
	}

	virtual T get(int index) const override {
		return this->array->get(index);
	}

	virtual void set(const T &item, int index) override {
		if(index < 0 || index >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->array->set(item, index);
	}


	virtual ArraySequence<T>* getSubsequence(int start, int end) const override {
		if(start < 0 || start >= this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(end < 0 || end > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);
		if(start > end) throw std::logic_error("end must be not less than start");


		T subArray[end - start];
		for(int i = 0; i < end - start; i++)
			subArray[i] = this->array->get(i + start);
		
		ArraySequence<T> *subSequence = new ArraySequence<T>(subArray, end - start);

		return subSequence;
	}

	virtual void append(const T &item) override {
		this->array->resize(this->size + 1);
		this->array->set(item, this->size);
		this->size++;
	}

	virtual void prepend(const T &item) override {
		this->array->resize(this->size + 1);
		T t1 = this->array->get(0);
		T t2;
		for(int i = 0; i < this->size; i++){
			t2 = t1;
			t1 = this->array->get(i + 1);
			this->array->set(t2, i + 1);
		}
		this->array->set(item, 0);

		this->size++;
	}

	virtual void insertAt(const T &item, int index) override {
		if(index < 0 || index > this->size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		this->array->resize(this->size + 1);
		T t1 = this->array->get(index);
		T t2;
		for(int i = index; i < this->size; i++){
			t2 = t1;
			t1 = this->array->get(i + 1);
			this->array->set(t2, i + 1);
		}
		this->array->set(item, index);

		this->size++;
	}

	virtual ArraySequence<T>* concat(const Sequence<T>& seq) const override {
		DynamicArray<T> *array = new DynamicArray<T>(this->size + seq.size);
		ArraySequence<T> *newSequence = new ArraySequence<T>(array);
		for(int i = 0; i < this->size; i++)
			newSequence->set(this->get(i), i);

		for(int i = 0; i < seq.size; i++)
			newSequence->set(seq.get(i), i + this->size);

		return newSequence;
	}

};


template <typename T> class ListSequence : public Sequence<T>{
	LinkedList<T> *list;
public:
	ListSequence(){
		this->list = new LinkedList<T>();
		this->size = 0;
	}

	ListSequence(const ListSequence<T> &seq){
		this->list = new LinkedList<T>(seq.list);
		this->size = seq.size;
	}

	ListSequence(LinkedList<T> *list){
		this->list = list;
		this->size = list->getSize();
	}

	ListSequence(T *items, int size){
		this->list = new LinkedList<T>(items, size);
		this->size = size;
	}

	virtual ~ListSequence(){
		delete this->list;
	}


	virtual T getFirst() const override {
		return this->list->getFirst();
	}
	
	virtual T getLast() const override {
		return this->list->getLast();
	}

	virtual T get(int index) const override {
		return this->list->get(index);
	}


	virtual Sequence<T>* getSubsequence(int start, int end) const override {
		LinkedList<T> *subList = this->list->getSublist(start, end);
		ListSequence<T> *seq = new ListSequence<T>(subList);
		return seq;
	}

	virtual void set(const T &item, int index) override {
		this->list->set(item, index);
	}

	virtual void append(const T &item) override {
		this->list->append(item);
		this->size++;
	}

	virtual void prepend(const T &item) override {
		this->list->prepend(item);
		this->size++;
	}

	virtual void insertAt(const T &item, int index) override {
		this->list->insertAt(item, index);
		this->size++;
	}

	virtual Sequence<T>* concat(const Sequence<T>& seq) const override {
		ListSequence<T> *newSequence = new ListSequence<T>();

		for(int i = 0; i < this->size; i++)
			newSequence->append(this->get(i));

		for(int i = 0; i < seq.size; i++)
			newSequence->append(seq.get(i));

		return newSequence;
	}


};


int main(int argc, const char *argv[]){

	return 0;
}