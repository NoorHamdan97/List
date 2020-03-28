#ifndef LIST_H_
#define LIST_H_

#include "library2.h"
#include <stdio.h>
#include <stdlib.h>

template<class T>
class Node {
public:
	int key;
	T* data;
	Node<T>* next;
	Node<T>* prev;
	Node(int k = 0, T* d = NULL, Node<T>* n = NULL, Node<T>* p = NULL) :
			key(k), data(d), next(n), prev(p) {
	}
	Node(const T& temp) :
			data(new T(temp)), key(0), next(NULL), prev(NULL) {
	}

	~Node()=default;

	T* getData();
	int getkey();
	Node<T>* getprev();
	Node<T>* getnext();
	Node<T>* getcurr();
};
template<class T>
T* Node<T>::getData() {
	return this->data;
}

//template <class T>
//Node<T>::~Node(){
////	delete data;
//}

template<class T>
int Node<T>::getkey() {
	return key;
}

template<class T>
Node<T>* Node<T>::getprev() {
	return this->prev;
}

template<class T>
Node<T>* Node<T>::getnext() {
	return this->next;
}
template<class T>
Node<T>* Node<T>::getcurr() {
	return this;
}

template<class T>
class List {
private:
	Node<T>* head;
	Node<T>* tail;
	int size;

public:
	List(Node<T>* h = NULL, Node<T>* t = NULL, int s = 0) :
			head(h), tail(t), size(s) {
	}
	List(const List<T>& temp) = default;
	void Quit();
	~List();
	Node<T>* begin();
	StatusType Add(int k, T* data, Node<T>* node);
	StatusType Adding(int k, T* data);
	StatusType Delete(int k);
	StatusType Find(int key, T* value);
	StatusType Finding (int k);
	StatusType Size(int* n);
	StatusType DeleteByPointer(Node<T>* node);
};
template<class T>
void List<T>::Quit() {
	Node<T>* it = this->begin();
	while (it != NULL) {
		delete it->data;
		delete it;
		it = this->begin();
	}
}

//************************************************************************
template<class T>
List<T>::~List() {
	Node<T>* it = this->head;
	while (it != NULL) {
		Node<T>* temp = it->next;
		delete it->data;
		delete it;
		size--;
		it = temp;
	}
}

template<class T>
StatusType List<T>::Add(int k, T* data, Node<T>* node) {
	if (node == NULL) { return INVALID_INPUT;}
	Node<T>* it = this->head;
	while (it != NULL) {
		if (it->key == k) {
			return FAILURE;;
		}
		it = it->next;
	}
	T* datatoadd=new T;
	*datatoadd=*data;
	Node<T> *newNode = new Node<T>(k,datatoadd); //must check if the is an aloocation error
	node = newNode;
	if (head == NULL) {
		head = newNode;
		tail = head;
		size++;
		return SUCCESS;
	}

	tail->next = newNode;
	newNode->prev = tail;
	newNode->next = NULL;
	tail = newNode;
	size++;
	return SUCCESS;
}

template<class T>
StatusType List<T>::Adding(int k, T* data){
	//if (node == NULL) { return INVALID_INPUT;}
		Node<T>* it = this->head;
		while (it != NULL) {
			if (it->key == k) {
				return FAILURE;;
			}
			it = it->next;
		}
		T* datatoadd=new T;
		*datatoadd=*data;
		Node<T> *newNode = new Node<T>(k,datatoadd); //must check if the is an aloocation error
		//node = newNode;
		if (head == NULL) {
			head = newNode;
			tail = head;
			size++;
			return SUCCESS;
		}

		tail->next = newNode;
		newNode->prev = tail;
		newNode->next = NULL;
		tail = newNode;
		size++;
		return SUCCESS;
}


//*************************************************************************
template<class T>
Node<T>* List<T>::begin() {
	return this->head;
}

//************************************************************************
template<class T>
StatusType List<T>::Size(int* n) {
	if (n == NULL) {
		return INVALID_INPUT;
	}
	*n = size;
	return SUCCESS;
}

//************************************************************************
template<class T>
StatusType List<T>::Find(int key, T* value) {
	if (value == NULL) {
		return INVALID_INPUT;
	}
	Node<T>* it = this->begin();
	while (it != NULL) {
		if (it->key == key) {
			*value = it->data;
			return SUCCESS;
		}
		it=it->next;
	}
	return FAILURE;
}

template<class T>
StatusType List<T>::Finding (int k){
	Node<T>* it = this->begin();
		while (it != NULL) {
			if (it->key == k) {
				return SUCCESS;
			}
			it=it->next;
		}
		return FAILURE;
}

//************************************************************************
template<class T>
StatusType List<T>::Delete(int k) {
	Node<T>* it = this->head;
	int flag =0;
	while (it != NULL) {
		if (it->key == k) {
			flag=1;
			break;
		}
		it=it->next;
	}
	if(!flag) return FAILURE;
	if (it == head){
		if (head==tail){
			delete it->data;
			delete it;
			size--;
			head=NULL;
			tail=NULL;
			return SUCCESS;
		}
		head=head->next;
		delete it->data;
		delete it;
		head->prev=NULL;
		size--;
		return SUCCESS;
	}
	if (it == tail){
		if (head==tail){
			delete it->data;
			delete it;
			size--;
			head=NULL;
			tail=NULL;
			return SUCCESS;
		}
		tail=tail->prev;
		delete it->data;
		delete it;
		tail->next=NULL;
		size--;
		return SUCCESS;
	}
	if (it->prev != NULL) {(it->prev)->next = it->next;}
	if (it->next != NULL) {(it->next)->prev = it->prev;}
	delete it->data;
	delete it;
	size--;
	return SUCCESS;
}

//************************************************************************
template<class T>
StatusType List<T>::DeleteByPointer(Node<T>* node) {
	if (node == NULL) {
		return INVALID_INPUT;
	}
	//should i check if it is a member first ?
	Node<T>* it = node;
	if (it->prev != NULL) {
		(it->prev)->next = it->next;
	}
	if (it->next != NULL) {
		(it->next)->prev = it->prev;
	}
	delete it->data;
	delete it;
	size--;
	return SUCCESS;

}

//************************************************************************

#endif
