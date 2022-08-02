#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<ctime>
#include"avl.h"
#include"doublylinkedlist.h"
#include"nod.h"
using namespace std;
void deleteAllFiles(int filesNumebr, long int ID) {
	string ff = "";
	for (int i = 1; i < filesNumebr + 1; i++) {
		ff = "data_machine_" + to_string(ID) + "_" + to_string(i) + ".txt";
		remove(ff.c_str());
		cout << endl;
	}
}
long int checkpower(long int power) {//finding power //first parameter:power value
	long int result = 2;
	if (power == 1)
		return result;
	long int multiplier = 2;
	for (int mul = 1; mul < power; mul++) {
		result = result * multiplier;
	}
	return result;
}



template<typename B>
//B= long int
class linkedlist
{
public:
	nod* head;
	B lengthofMachines;
	B bits = -1;
	linkedlist()
	{
		lengthofMachines = 0;
		head = NULL;
	}
	void setKeyInTheSystem(nod* machineAddress, B keyToStore, string valueTostore) {//specifying the machine from which we want to insert data
		//fp: pointer of a machine from which we want to store data, Sp:The key to store, Tp: value to store
		if (keyToStore == machineAddress->machineID || lengthofMachines == 1) {//when key and machine id is same or 
			machineAddress->machinesData.insert(keyToStore, valueTostore);	   //there is only one machine
			cout << "Data Stored in Machine : " << machineAddress->machineID << endl;
			return;
		}
		nod* temp = NULL;
		temp = successor(keyToStore);
		if (temp->machineID == machineAddress->machineID) {//when the key successor is the same machine as from the called machine
			machineAddress->machinesData.insert(keyToStore, valueTostore);
			cout << "Data Stored in Machine : " << machineAddress->machineID << endl;
			return;
		}
		NODE<long int, nod>* headTemp = machineAddress->AllAddress.head;
		if (keyToStore > machineAddress->machineID && keyToStore <= headTemp->Address_->machineID) {
			//when the key is greater than the calling machine and 
			//less than the fist index of routing table so move to first index of routing table
			cout << "Moves to Machine : " << headTemp->Address_->machineID << endl;
			setKeyInTheSystem(headTemp->Address_, keyToStore, valueTostore);
			return;
		}
		int cou = 0;
		if (keyToStore < headTemp->Address_->machineID && keyToStore < machineAddress->machineID) {//when key is less than machine 
			cout << "Moves to Machine : " << headTemp->Address_->machineID << endl;//calling and less than the first index of routting 
			setKeyInTheSystem(headTemp->Address_, keyToStore, valueTostore);	//table of calling machine
			return;
		}
		while (true) {
			if (keyToStore == headTemp->Address_->machineID) {//when key is same as machine address then go to that machine
				cout << "Moves to Machine : " << headTemp->Address_->machineID << endl;
				setKeyInTheSystem(headTemp->Address_, keyToStore, valueTostore);
				return;
			}
			else if (keyToStore < headTemp->Address_->machineID) {//when key is less than machine id of routing table than go to 
				cout << "Moves to Machine : " << headTemp->prev->Address_->machineID << endl;//previous machine
				setKeyInTheSystem(headTemp->prev->Address_, keyToStore, valueTostore);
				return;
			}
			else if (keyToStore > headTemp->Address_->machineID) {//when key is greater than machine id and it is the last index of 
				if (headTemp->next == NULL) {					  //routing table then simply go to last index of routing table
					cout << "Moves to Machine : " << headTemp->Address_->machineID << endl;
					setKeyInTheSystem(headTemp->Address_, keyToStore, valueTostore);
					return;
				}
				cou++;
				if (cou == bits)//checking the last index of the routing table
					break;
				headTemp = headTemp->next;
				continue;
			}
		}
	}
	void deleteKeyFromTheSystem(nod* machineAddress, B keyToDelete) {//specifying the machine from which we want to delete data
		//fp: pointer of a machine from which we want to delete data, Sp:The key to delete
		if (keyToDelete == machineAddress->machineID || lengthofMachines == 1) {//when key and machine id is same
			cout << "Data delete from Machine : " << machineAddress->machineID << endl;
			cout << "Data To Delete : ";
			machineAddress->machinesData.removeAVLnode(machineAddress->machinesData.root, keyToDelete);
			machineAddress->machinesData.makeRootNullIfCounterZero();
			return;
		}
		nod* temp = NULL;
		temp = successor(keyToDelete);
		if (temp->machineID == machineAddress->machineID) {//when the key successor is the same machine as from the called machine
			cout << "Data delete from Machine : " << machineAddress->machineID << endl;
			cout << "x-----Data To Delete-----x" << endl;
			machineAddress->machinesData.removeAVLnode(machineAddress->machinesData.root, keyToDelete);
			machineAddress->machinesData.makeRootNullIfCounterZero();
			return;
		}
		NODE<long int, nod>* headTemp = machineAddress->AllAddress.head;
		if (keyToDelete > machineAddress->machineID && keyToDelete <= headTemp->Address_->machineID) {
			//when the key is greater than the calling machine and 
			//less than the fist index of routing table so move to first index of routing table
			cout << "Moves to Machine : " << headTemp->Address_->machineID << endl;
			deleteKeyFromTheSystem(headTemp->Address_, keyToDelete);
			return;
		}
		while (true) {
			if (keyToDelete > headTemp->Address_->machineID) {//when key is greater than machine id and it is the last index of
				if (headTemp->next == NULL) {//routing table then simply go to last index of routing table
					cout << "Moves to Machine : " << headTemp->Address_->machineID << endl;
					deleteKeyFromTheSystem(headTemp->Address_, keyToDelete);
					return;
				}
				headTemp = headTemp->next;
				continue;
			}
			else if (keyToDelete < headTemp->Address_->machineID) {//when key is less than machine id of routing table than go to 
				cout << "Moves to Machine : " << headTemp->prev->Address_->machineID << endl;//previous machine
				deleteKeyFromTheSystem(headTemp->prev->Address_, keyToDelete);
				return;
			}
			if (keyToDelete == headTemp->Address_->machineID) {//when key is same as machine address then go to that machine
				cout << "Moves to Machine : " << headTemp->Address_->machineID << endl;
				deleteKeyFromTheSystem(headTemp->Address_, keyToDelete);
				return;
			}
		}
	}
	nod* creating(B a) {
		nod* done;
		done = new nod;
		done->machineID = a;
		return done;
	}
	void deleteAllRoutingTable() {//function to delete all routing tables
		nod* temp = head;
		int l = getLength();
		for (int i = 0; i < l; i++) {
			temp->AllAddress.deleteAll();
			temp = temp->next;
		}
	}
	void setRoutingTableOfAllNodes() {//setting the routing tables of all machines
		nod* temp = head;
		int l = lengthofMachines;
		for (int i = 0; i < l; i++) {
			setRoutingTable(temp);
			cout << "Length of M " << temp->machineID << " is : " << temp->AllAddress.getLength() << endl;
			temp = temp->next;
		}
	}
	void setRoutingTable(nod* temp) {//setting the routing table of a single node
		//fp pointer of the machine to set a routing table
		if (temp != NULL) {
			nod* temp_address = NULL;
			cout << "Bitttt : " << bits << endl;
			for (int i = 1; i < bits + 1; i++) {
				temp_address = successor(temp->machineID + checkpower(i - 1));//returning address of the id
				if (temp_address != NULL) {//if machine exist otherwise it will return NULL
					temp->AllAddress.insert_end(temp_address);

				}
				else
					break;
			}
		}
		else
			cout << "Invalid Node address." << endl;
	}
	void printprintRoutingTableOfALlMachines() {
		nod* temp = head;
		for (int i = 0; i < lengthofMachines; i++) {
			printRoutingTable(temp);
			temp = temp->next;
		}
	}
	void printRoutingTable(nod* temp) {
		NODE<long int, nod>* headTemp = temp->AllAddress.head;
		if (headTemp == NULL) {
			cout << "\nThere is no data in the routing table." << endl;
			return;
		}
		cout << "\nRouting Table of Machine " << temp->machineID << endl;
		for (int j = 0; j < bits; j++) {
			cout << "Index : " << j + 1 << " : " << headTemp->Address_->machineID << endl << endl;
			headTemp = headTemp->next;
		}
	}
	void setBits(B b) {
		bits = b;
		//cout << "Bits set : " <<bits<< endl;
	}
	nod* successor(B key) {//will return machine id address
		if (head == NULL) {
			cout << "No data." << endl;
			return NULL;
		}
		if (key < 0) {//key cant be less than 0
			cout << "Key does not exist." << endl;
			return NULL;
		}
		key = key % checkpower(bits);//taking moduls exta check if key is greater tha identifier space
		nod* temp = head;
		int length_ = getLength();
		for (int i = 0; i < length_; i++) {
			if (key > temp->machineID) {
				temp = temp->next;
				if (temp == head)
					return head;
			}
			else
				return temp;
		}
	}
	bool checkDuplicates(B val) {
		if (head == NULL)
			return true;
		nod* temp = head;
		int length_ = getLength();
		for (int i = 0; i < length_; i++) {
			if (val == temp->machineID)
				return false;
			temp = temp->next;
		}
		return true;
	}
	void ALLMachinesData() {
		cout << "\n------Machines------\n" << endl;
		nod* temp;
		temp = head;
		if (head == NULL) {
			cout << "There is no data present" << endl;
		}
		else {
			while (temp->next != head)
			{
				cout << "Machine ID : " << temp->machineID << "\n-------Data-------\n" << endl;
				temp->machinesData.displayfilesData(temp->machinesData.root, temp->machineID);
				cout << endl;
				temp = temp->next;
			}
			cout << "Machine ID : " << temp->machineID << "\n-------Data-------\n" << endl;
			temp->machinesData.displayfilesData(temp->machinesData.root, temp->machineID);
			cout << endl;
		}
	}
	nod* findAddress(B keyToFind) {//it finds the address by specifying the key
		nod* temp = head;
		for (int i = 0; i < lengthofMachines; i++) {
			if (keyToFind == temp->machineID)
				return temp;
			temp = temp->next;
		}
		return NULL;
	}
	B get(int Index) {
		nod* temp = head;
		B final = 0;
		int count = 0;
		while (head != NULL)
		{
			if (count == Index)
			{
				final = temp->machineID;
				break;
			}
			count++;
			temp = temp->next;
		}
		return final;
	}
	int getLength() {
		return lengthofMachines;
	}
	void Display() {
		cout << "Machines ID : ";
		nod* temp;
		temp = head;
		if (head == NULL) {
			cout << "There is no data present" << endl;
		}
		else {
			for (int i = 0; i < lengthofMachines - 1; i++) {
				cout << temp->machineID << ",";
				temp = temp->next;
			}
			cout << temp->machineID << endl;
			/*while (temp->next != head){
				cout << temp->machineID << ",";
				temp = temp->next;
			}
			cout << temp->machineID << endl;*/
		}
	}
	int deleteByID(B ID) {//deletee by id;// return 0 when enter invalid id, 1 when no data, 2 when id found and deleted
		if (head == NULL) {//checking when there are no machines in the system
			cout << "There are no machines in the system." << endl;
			return 1;
		}
		int length_ = lengthofMachines--;
		if (length_ == 1 && head->machineID == ID) {//when there is only one machine in the system
			head->machinesData.delete_all(head->machinesData.root);
			deleteAllFiles(head->machinesData.fileNumber, head->machineID);
			head->machinesData.makeRootNullIfCounterZero();
			delete head;
			head = NULL;
			return 2;
		}
		else if (head->machineID == ID) {//when head is the node to be deleted
			addDataOfMachine1intoMachine2(head->machinesData.root, head->next->machinesData);//moving the data to the next machine
			deleteAllFiles(head->machinesData.fileNumber, head->machineID);
			nod* temp = head;
			head = head->next;
			head->previous = temp->previous;
			temp->previous->next = head;
			delete temp;
			temp = NULL;
			return 2;
		}
		else {
			nod* temp = head->next;
			nod* toDelete = NULL;
			for (int i = 1; i < length_; i++) {
				if (temp->machineID == ID) {//moving the data to the next machine when previous id is to be deleted
					addDataOfMachine1intoMachine2(temp->machinesData.root, temp->next->machinesData);
					deleteAllFiles(temp->machinesData.fileNumber, temp->machineID);
					temp->machinesData.makeRootNullIfCounterZero();
					toDelete = temp;
					temp->previous->next = temp->next;
					temp->next->previous = temp->previous;
					delete toDelete;
					toDelete = NULL;
					return 2;
				}
				temp = temp->next;
			}
			return 0;
		}
	}
	void addDataOfMachine1intoMachine2(AVLTreeNode<string, long int, int >* machine1, AVLTree<string, int>& machine2) {
		//it recevies head of machine1 to be deleted and avl object of machine 2 in which data is to add
		if (machine1 != NULL && machine1->counter != 0) {//couter of total nodes in AVL tree
			//cout << "\nID : " << machine1->Data << "\tValue : " << machine1->vvalue << endl;
			machine2.insert(machine1->Data, machine1->getValue());
			addDataOfMachine1intoMachine2(machine1->left, machine2);
			addDataOfMachine1intoMachine2(machine1->right, machine2);
		}
	}
	void addDataOfMachine1intoMachine2onCondition(AVLTreeNode<string, long int, int >* machine1, AVLTree<string, int>& machine2, long int newMachineID, long int nextMachineID, AVLTree<string, int>& temp) {
		//first parameter : root of AVL tree of next machine of new machine//second parameter : AVL object to store data of new machine
		//third parameter : new machine id//Fourth parameter : Machine id of the next machine from where data is getting
		//fifth parameter : reference of avl object to store the rest of the data
		//Description : split the data into new machine from next machine of the new machine
		if (machine1 != NULL && machine1->counter != 0) {//couter of total nodes in AVL tree
			if (machine1->Data == newMachineID) {
				machine2.insert(machine1->Data, machine1->getValue());
			}
			else if (machine1->Data < newMachineID && machine1->Data>nextMachineID) {
				machine2.insert(machine1->Data, machine1->getValue());
			}
			else {
				temp.insert(machine1->Data, machine1->getValue());//storing the rest part of the next machine//data which will be store back to next machine
			}
			addDataOfMachine1intoMachine2onCondition(machine1->left, machine2, newMachineID, nextMachineID, temp);
			addDataOfMachine1intoMachine2onCondition(machine1->right, machine2, newMachineID, nextMachineID, temp);
		}
	}
	void distributeData(nod* NewMachine) {
		//first parameter : pointer of new machine where data is to be stored from its next machine
		//Description     : split the data into new machine from next machine of the new machine
		AVLTree<string, int> temp;
		addDataOfMachine1intoMachine2onCondition(NewMachine->next->machinesData.root, NewMachine->machinesData, NewMachine->machineID, NewMachine->next->machineID, temp);
		NewMachine->next->machinesData.delete_all(NewMachine->next->machinesData.root);
		NewMachine->next->machinesData.root = NULL;
		addDataOfMachine1intoMachine2(temp.root, NewMachine->next->machinesData);
		temp.delete_all(temp.root);

	}
	void deleteAllData() {
		int length_ = getLength();
		nod* temp = head;
		for (int i = 0; i < length_; i++) {
			temp->AllAddress.deleteAll();
			temp->machinesData.delete_all(temp->machinesData.root);
			//temp->machinesData.deleteAllFiles(temp->machineID);
			deleteAllFiles(temp->machinesData.fileNumber, temp->machineID);
			temp = temp->next;
		}
		lengthofMachines = 0;
	}
	void insertNew(B val) {
		lengthofMachines++;
		nod* n = creating(val);
		n->machinesData.setFileName("data_machine_" + to_string(val) + "_" + to_string(n->machinesData.fileNumber));
		if (head == NULL) {//when adding first entry in the linkedlist
			head = n;
			n->next = head;
			n->previous = n;
			cout << "true" << endl;
			return;
		}
		if (head->machineID > val) {//when val is lesser than first node so add at start
			nod* lastNode = head->previous;
			n->next = head;
			n->previous = lastNode;
			lastNode->next = n;
			head->previous = n;
			head = n;
			cout << "true" << endl;
			return;
		}
		if (head->previous->machineID < val) {//when the val is greater than last node so add it at the end of linkedlist
			nod* temp = head->previous;//getting last node
			n->next = head;
			n->previous = temp;
			temp->next = n;
			head->previous = n;
			cout << "true" << endl;
			return;
		}
		nod* temp2 = head;
		while (true) {//inserting in sequence to make it ascending order
			if (val > temp2->machineID) {
				temp2 = temp2->next;
			}
			else {
				nod* changeNode = temp2;
				nod* previousNode = temp2->previous;
				previousNode->next = n;
				n->previous = previousNode;
				n->next = temp2;
				temp2->previous = n;
				cout << "true" << endl;
				return;
			}
			if (temp2->next == head)
				break;
		}
		cout << "true" << endl;
	}
};

