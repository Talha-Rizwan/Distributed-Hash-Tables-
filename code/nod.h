#pragma once
#include"avl.h"
#include"doublylinkedlist.h"


class nod
{
public:
	AVLTree<string, int> machinesData;//data member to store data of a machine
	long int machineID;//use for storing the id of the machine
	nod* next;
	nod* previous;
	doublylinkedlist<nod> AllAddress;//use for routing table
	nod() {
		previous = NULL;
		machineID = 0;
		next = NULL;
	}
	nod(long int d) {
		machineID = d;
		next = NULL;
		previous = NULL;
	}
};
