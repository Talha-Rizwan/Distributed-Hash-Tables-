#pragma once
#include<iostream>
class nod;

template<typename C1, typename C2 >
//C1=long int, C2=nod

class NODE {//Class for doubly linked list
public:
	C2* Address_;//data memeber of type node pointer for storing address of a machine
	NODE* next;
	NODE* prev;
	static C1 lengthofDoubly;
	NODE() {
		Address_ = NULL;
		next = NULL;
		prev = NULL;
		lengthofDoubly++;
	}
	NODE(nod* d) {
		Address_ = d;
		next = NULL;
		prev = NULL;
		lengthofDoubly++;
	}
};