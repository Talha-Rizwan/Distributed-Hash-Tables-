#pragma once
#include<iostream>
#include"NODE.h"
using namespace std;
long int NODE<long int, nod>::lengthofDoubly = 0;
template<typename D>
//D=nod
class doublylinkedlist
{
public:
	NODE<long int, D>* head;
	doublylinkedlist() {
		head = NULL;
	}
	NODE<long int, D>* creating(D* a) {//creating a new node of the passing the value
		NODE<long int, nod>* done;
		done = new NODE<long int, nod>;
		done->Address_ = a;
		return done;

	}
	void deleteAll() {//deleting all nodes in the list
		NODE<long int, nod>* temp = head;
		NODE<long int, nod>* todelete = NULL;
		while (temp != NULL) {
			todelete = temp;
			temp = temp->next;
			delete todelete;
		}
		head = NULL;
	}
	void insert_end(D* val) {//inserting a new node in the list
		NODE<long int, nod>* ptr = new NODE<long int, D>(val);
		if (head == NULL) {
			head = ptr;
		}
		else {
			NODE<long int, D>* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = ptr;
			ptr->prev = temp;
		}
	}
	int getLength() {//function to calculate the length of the list
		return this->head->lengthofDoubly;
	}
};