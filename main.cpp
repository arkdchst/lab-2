#include <iostream>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cmath>

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
		for(int i = 0; i < size; i++)
			this->data[i] = data[i];
	}

	DynamicArray(const DynamicArray<T> &array, int size) : DynamicArray(size){
		if(size > array.size) throw std::out_of_range(INDEX_OUT_OF_RANGE_MESSAGE);

		for(int i = 0; i < size; i++)
			this->data[i] = array.data[i];
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
		for(int i = 0; i < (this->size > size ? size : this->size); i++)
			newData[i] = data[i];

		delete[] data;
		this->data = newData;

		this->size = size;
	}


	bool operator==(const DynamicArray<T> &arr) const {
		if(this->size != arr.size) return false;

		for(int i = 0; i < this->size; i++)
			if(this->get(i) != arr.get(i)) return false;
		

		return true;
	}

	DynamicArray<T>& operator=(const DynamicArray &array){
		delete this->data;

		this->size = array.size;
		this->data = new T[this->size];

		for(int i = 0; i < size; i++)
			this->data[i] = array.data[i];

		return *this;
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


	LinkedList(int size) : LinkedList() {
		if(size < 0) throw std::length_error(NEGATIVE_SIZE_MESSAGE);

		Record **ptr = &(this->head);
		for(int i = 0; i < size; i++){
			*ptr = new Record;
			(*ptr)->item = T();
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
		this->size = 0;
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

	LinkedList<T>* getSublist(int start, int end) const { //end excluding
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


	bool operator==(const LinkedList<T> &list) const {
		if(this->size != list.size) return false;

		for(int i = 0; i < this->size; i++){
			if(this->get(i) != list.get(i)) return false;
		}

		return true;
	}

};



template <typename T> class Sequence{
protected:
	int size = 0;
public:

	virtual T getFirst() const = 0;
	virtual T getLast() const = 0;
	virtual T get(int index) const = 0;
	virtual int getSize() const { return this->size; }


	virtual Sequence<T>* getSubsequence(int start, int end) const = 0; //end excluding

	virtual void set(const T &item, int index) = 0;
	virtual void append(const T &item) = 0;
	virtual void prepend(const T &item) = 0;
	virtual void insertAt(const T &item, int index) = 0;

	virtual Sequence<T>* concat(const Sequence<T>& seq) const = 0;

	virtual bool operator==(const Sequence<T> &seq){
		if(this->size != seq.size) return false;

		for(int i = 0; i < this->size; i++){
			if(this->get(i) != seq.get(i)) return false;
		}

		return true;
	}

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
		this->array = new DynamicArray<T>(*seq.array);
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

	ArraySequence(int size){
		this->array = new DynamicArray<T>(size);
		this->size = size;
	}

	virtual ~ArraySequence(){
		delete this->array;
		this->size = 0;
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
		DynamicArray<T> *array = new DynamicArray<T>(this->size + seq.getSize());
		ArraySequence<T> *newSequence = new ArraySequence<T>(array);
		for(int i = 0; i < this->size; i++)
			newSequence->set(this->get(i), i);

		for(int i = 0; i < seq.getSize(); i++)
			newSequence->set(seq.get(i), i + this->size);

		return newSequence;
	}

};


template <typename T> class ListSequence : public Sequence<T>{
protected:
	LinkedList<T> *list;
public:
	ListSequence(){
		this->list = new LinkedList<T>();
		this->size = 0;
	}

	ListSequence(const ListSequence<T> &seq){
		this->list = new LinkedList<T>(*seq.list);
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

	ListSequence(int size){
		this->list = new LinkedList<T>(size);
		this->size = size;
	}

	virtual ~ListSequence(){
		delete this->list;
		this->size = 0;
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


	virtual ListSequence<T>* getSubsequence(int start, int end) const override {
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

	virtual ListSequence<T>* concat(const Sequence<T>& seq) const override {
		ListSequence<T> *newSequence = new ListSequence<T>();

		for(int i = 0; i < this->size; i++)
			newSequence->append(this->get(i));

		for(int i = 0; i < seq.getSize(); i++)
			newSequence->append(seq.get(i));

		return newSequence;
	}


};


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
};


template <typename T>
class DiagonalMatrix : public Matrix<T>{
public:
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
				throw std::out_of_range("trying to set non-diagonal element");
			return;
		}

		data->get(getDiagNumber(x,y))->set(item, (x < y) ? x : y );
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
