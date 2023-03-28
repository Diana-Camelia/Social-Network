#pragma once
#define MAX_SIZE 5 // Max array size using #define [duplicate]
#include <exception>

template <class T>
class List{
private:
	int max_size;
	int size;
	T* values;
	void providesListCapacity(); // asigura capacitatea listei
public:
	List(const List<T>& ot);
	List();
	int get_size() const;
	int find(const T& ot) const;
	void add(const T& ot);
	List<T>& operator=(const List<T>& ot);
	T remove_at_position(int position);
	T at(int position) const;
	T& operator[](int position);
	~List();
};

template<class T>
inline void List<T>::add(const T& element){
	// add an item to the list of items
	// param element: the element we want to add
	this->providesListCapacity();
	this->values[this->size] = element;
	this->size++;
}

template<class T>
void List<T>::providesListCapacity(){
	// resize
	if (this->max_size == this->size){
		this->max_size *= 2;
		T* listaNouaElemente = new T[this->max_size];
		for (int i = 0; i < this->size; i++)
			listaNouaElemente[i] = this->values[i];
		delete[] this->values;
		this->values = listaNouaElemente;
	}
}

template<class T>
inline List<T>::List(){
	this->max_size = MAX_SIZE;
	this->values = new T[MAX_SIZE];
	this->size = 0;
}

template<class T>
inline T List<T>::at(int position) const{
	// Check if the position is valid
	// param position : the position we want to check
	if (position >= this->size || position < 0)
		throw(std::exception("Invalid position!"));
	return this->values[position];
}

template<class T>
inline List<T>::List(const List<T>& ot){ //copy constructor
	this->max_size = ot.max_size;
	this->size = ot.size;
	this->values = new T[this->max_size];
	//copy the elements:
	for (int i = 0; i < this->size; i++)
		this->values[i] = ot.values[i]; 
}

template<class T>
inline int List<T>::get_size() const{
	// return the number of elemets
	return this->size;
}

template<class T>
inline List<T>& List<T>::operator = (const List<T>& ot){
	if (this == &ot) {
		return *this;
	}
	this->size = ot.size;
	this->max_size = ot.max_size;
	delete[] this->values; //delete the old values
	this->values = new T[this->max_size];
	for (int i = 0; i < this->size; i++)
		this->values[i] = ot.values[i];
	return *this;
}

template<class T>
inline int List<T>::find(const T& el) const{
	// search for an item in the set of items
	// param el : the element we want to look for 
	for (int i = 0; i < this->size; i++)
		if (this->values->at(i) == el)
			return i;
	return -1;
}

template<class T>
inline T List<T>::remove_at_position(int position){
	// delete function by position
	// param position : the position at which the deletion is made
	if (position >= this->size || position < 0)
		throw(std::exception("Invalid position!"));
	T element = this->values[position];
	for (int i = position; i < this->size - 1; i++){
		this->values[i] = this->values[i + 1];
	}
	this->size--;
	return element;
}

template<class T>
inline T& List<T>::operator[](int position){
	if (position >= this->size || position < 0)
		throw(std::exception("Invalid position!"));
	return this->values[position];
}

template<class T>
inline List<T>::~List(){ //destructor
	delete[] this->values;
}