#pragma once
#include <functional>
#include <queue>
#include <iostream>
#include <stack>

template<class T>
class OrderdSet;

template<class T>
class SetIterator;

template<class T>
class Node{
private:
	T value;
	Node* left;
	Node* right;
public:
	Node(const T& val, Node* left, Node* right);
	friend class OrderdSet<T>;
	friend class SetIterator<T>;
};

template<class T>
inline Node<T>::Node(const T& val, Node* left, Node* right){
	this->right = right;
	this->left = left;
	this->value = val;
}

template<class T>
class OrderdSet{
private:
	int size;
	Node<T>* root;
	std::function<bool(const T& el1, const T& rel2)> rel;
	void erase_nodes(Node<T>* p);
	Node<T>* recursive_add(Node<T>* p, const T& el, bool& adaugat);
	bool recursive_find(Node<T>* p, const T& element) const;
	Node<T>* min(Node<T>* p) const;
	Node<T>* recursive_remove(Node<T>* p, const T& element, bool& sters);
public:
	OrderdSet(const OrderdSet<T>& ot); //copy constructor
	OrderdSet(std::function<bool(const T& element1, const T& element2)> relatie);
	~OrderdSet();
	OrderdSet<T>& operator=(const OrderdSet<T>& ot); //assigment operator
	bool add(const T& el); //adds elements to list
	bool find(const T& el) const; //searches for elements in list
	int get_size() const; //get size of list
	bool remove(const T& element); //remove an element from list
	friend class SetIterator<T>; //iterator over tree
	SetIterator<T> iterator();
};

template<class T>
inline SetIterator<T> OrderdSet<T>::iterator(){
	// indicates the memory addresses of the containers
	return SetIterator<T>(*this);
}

template<class T>
inline OrderdSet<T>::OrderdSet(std::function<bool(const T& element1, const T& element2)> relation){
	this->size = 0;
	this->root = nullptr;
	this->rel = relation;
}

template<class T>
inline void OrderdSet<T>::erase_nodes(Node<T>* node){
	// the method deletes the node
	// param node : the node we want to delete
	if (node != nullptr){
		erase_nodes(node->right);
		erase_nodes(node->left);
		delete node;
	}
}

template<class T>
inline Node<T>* OrderdSet<T>::min(Node<T>* node) const{ 
	//finds the node with the smallest value
	Node<T>* p = node;
	while (p->left != nullptr)
		p = p->left;
	return p;
}

template<class T>
inline Node<T>* OrderdSet<T>::recursive_remove(Node<T>* p, const T& el, bool& deleted){
	if (p == nullptr)
		return nullptr;
	else{
		if (rel(el, p->value) && el != p->value){
			p->left = recursive_remove(p->left, el, deleted);
			return p;
		}
		else{
			if (!rel(el, p->value) && el != p->value){
				p->right = recursive_remove(p->right, el, deleted);
				return p;
			}
			else{ //we find the node
				deleted = true;
				if (p->left != nullptr && p->right != nullptr){
					Node<T>* aux = min(p->right);
					p->value = aux->value;
					p->right = recursive_remove(p->right, p->value, deleted);
					return p;
				}
				else{
					Node<T>* aux2 = p;
					Node<T>* aux3;
					if (p->left == nullptr)
						aux3 = p->right;
					else
						aux3 = p->left;
					delete aux2;
					return aux3;
				}
			}
		}
	}
}

template<class T>
inline bool OrderdSet<T>::remove(const T& el){
	bool deleteld = false;
	Node<T>* p = this->recursive_remove(this->root, el, deleteld);
	this->root = p;
	return deleteld;
}

template<class T>
inline OrderdSet<T>::~OrderdSet(){
	// destructor
	this->erase_nodes(this->root);
}

template<class T>
inline OrderdSet<T>::OrderdSet(const OrderdSet<T>& ot){ 
	//copy all the users 
	this->root = nullptr;
	this->rel = ot.rel;
	std::stack<Node<T>*>stack;
	stack.push(ot.root);
	while (!stack.empty()){
		Node<T>* node = stack.top();
		stack.pop();
		if (node->right != nullptr)
			stack.push(node->right);
		if (node->left != nullptr)
			stack.push(node->left);
		this->add(node->value);
	}
}

template<class T>
inline OrderdSet<T>& OrderdSet<T>::operator=(const OrderdSet<T>& ot){
	this->erase_nodes(this->root);
	this->root = nullptr;
	this->rel = ot.rel;
	std::stack<Node<T>*>stack;
	stack.push(ot.root);
	while (!stack.empty()){
		Node<T>* node = stack.top();
		stack.pop();
		if (node->right != nullptr)
			stack.push(node->right);
		if (node->left != nullptr)
			stack.push(node->left);
		this->add(node->value);
	}
	return *this;
}

template<class T>
inline Node<T>* OrderdSet<T>::recursive_add(Node<T>* p, const T& el, bool& added){
	if (p != nullptr){ 
		if (p->value != el) {
			if (this->rel(el, p->value)){
				p->left = recursive_add(p->left, el, added);
			}
			else{
				p->right = recursive_add(p->right, el, added);
			}
		}
	}
	else{
		p = new Node<T>(el, nullptr, nullptr);
		added = true;
	}
	return p;
}

template<class T>
inline bool OrderdSet<T>::recursive_find(Node<T>* p, const T& el) const{
	if (p == nullptr){
		return false;
	}
	if (p->value == el)
		return true;
	if (this->rel(el, p->value))
		return this->recursive_find(p->left, el);
	else
		return this->recursive_find(p->right, el);
}

template<class T>
inline bool OrderdSet<T>::add(const T& el){
	bool added = false;
	this->root = recursive_add(this->root, el, added);
	if (added == true)
		this->size++;
	return added;
}

template<class T>
inline bool OrderdSet<T>::find(const T& el) const{
	bool ok = recursive_find(this->root, el);
	return ok;
}

template<class T>
inline int OrderdSet<T>::get_size() const{
	return this->size;
}

template<class T>
class SetIterator{
private:
	std::stack<Node<T>*> stack;
	OrderdSet<T>& orderdSet;
	Node<T>* current_node;
public:
	bool valid() const;
	SetIterator(OrderdSet<T>& orderdSet);
	T& get_element();
	void next();
	void first();
};

template<class T>
inline bool SetIterator<T>::valid() const{
	return this->current_node != nullptr || !this->stack.empty();
}

template<class T>
inline SetIterator<T>::SetIterator(OrderdSet<T>& orderdSet) :orderdSet{ orderdSet }{
	this->first();
}

template<class T>
inline T& SetIterator<T>::get_element(){ 
	//inorder iteration
	if (!this->valid())
		throw(std::exception("Invalid iterator!"));
	while (this->current_node != nullptr){
		this->stack.push(this->current_node);
		this->current_node = this->current_node->left;
	}
	this->current_node = this->stack.top();
	this->stack.pop();
	return this->current_node->value;
}

template<class T>
inline void SetIterator<T>::next(){
	if (!this->valid())
		throw(std::exception("Iterator invalid!"));
	this->current_node = this->current_node->right;
}

template<class T>
inline void SetIterator<T>::first(){
	this->current_node = this->orderdSet.root;
}