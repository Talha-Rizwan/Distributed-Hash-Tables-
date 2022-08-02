#pragma once
#include<iostream>
#include<fstream>
#include"avlNode.h"
using namespace std;
long int AVLTreeNode<string, long int, int >::counter = 0;


template<typename A1, typename A2>
//A1=string and A2=int 
class AVLTree {
public:
	AVLTreeNode<string, long int, int >* root;
	A1 filename;//current filename for storing data 
	A2 line_no;//current lie number to where data has to be store
	A2 fileNumber;//couting of files when a file exceeds from 100 lines
	AVLTree() {
		root = NULL;
		line_no = 0;
		fileNumber = 1;
	}
	AVLTreeNode<string, long int, int >* getroot() {
		return root;
	}
	void setFileName(A1 name) {
		filename = name + ".txt";
	}
	int maxHeight(A2 a1, A2 a2) {
		if (a1 > a2)
			return a1;
		else
			return a2;
	}
	int getHeight(AVLTreeNode<string, long int, int >* n) {
		if (n == NULL)
			return -1;
		return n->h;
	}
	int findBalance(AVLTreeNode<string, long int, int >* n) {
		return getHeight(n->left) - getHeight(n->right);
	}
	AVLTreeNode<string, long int, int >* leftRotate(AVLTreeNode<string, long int, int >* a1) {
		AVLTreeNode<string, long int, int >* a2 = a1->right;
		AVLTreeNode<string, long int, int >* tp = a2->left;
		//rotating left
		a2->left = a1;
		a1->right = tp;
		//updating height
		a1->h = maxHeight(getHeight(a1->left), getHeight(a1->right)) + 1;
		a2->h = maxHeight(getHeight(a2->left), getHeight(a2->right)) + 1;
		return a2;
	}
	AVLTreeNode<string, long int, int >* rightRotate(AVLTreeNode<string, long int, int >* a2) {
		AVLTreeNode<string, long int, int >* a1 = a2->left;
		AVLTreeNode<string, long int, int >* tp = a1->right;
		//rotating right
		a1->right = a2;
		a2->left = tp;
		//updating height
		a2->h = maxHeight(getHeight(a2->left), getHeight(a2->right)) + 1;
		a1->h = maxHeight(getHeight(a1->left), getHeight(a1->right)) + 1;
		return a1;
	}
	void insert(A2 data, A1 value) {
		root = insert(root, data, value);
	}
	void checkFileExist(A1 file) {//checking that the file exist or not
		ifstream f;
		f.open(file);
		if (f) {
			f.close();
			return;
		}
		ofstream ff;
		ff.open(file);
		ff.close();
	}
	void setDataInFile(A1 value) {//setting the data in the file at correct position
		ofstream g;
		checkFileExist(filename);
		g.open(filename, ios::app);
		g << value << endl;
		g.close();
		line_no++;
	}
	AVLTreeNode<string, long int, int >* insert(AVLTreeNode<string, long int, int >* temp, int data, string value) {
		if (temp == NULL) {
			if (line_no == 100) {//checking for maximum lines enter in the file
				fileNumber++;//if line no is 100 then change the file number of the curent machine
				line_no = 0;
				for (int ci = 0; ci < 5; ci++)
					filename.pop_back();//removing the file number from the file and .txt
				filename += to_string(fileNumber) + ".txt";
			}
			setDataInFile(value);
			temp = new AVLTreeNode<string, long int, int >(data, filename, line_no);
			//cout << "the line_no is :" << temp->linenumber << " and the value is : " << value << endl;
		}
		else if (temp->Data > data) {
			temp->left = insert(temp->left, data, value);
		}
		else if (temp->Data < data) {
			temp->right = insert(temp->right, data, value);
		}
		temp->h = maxHeight(getHeight(temp->left), getHeight(temp->right)) + 1;
		int bf = findBalance(temp);
		//left of left case
		if (bf > 1 && data < temp->left->Data) {
			return rightRotate(temp);
			cout << "left of left case" << endl << temp->Data << endl;
		}
		//right of right case
		if (bf < -1 && data > temp->right->Data) {
			return leftRotate(temp);
			cout << "right of right case" << endl << temp->Data << endl;
		}
		//left of right case
		if (bf > 1 && data > temp->left->Data) {
			temp->left = leftRotate(temp->left);
			return rightRotate(temp);
			cout << "left of right case" << endl << temp->Data << endl;
		}
		//right of left case
		if (bf < -1 && data < temp->right->Data) {
			temp->right = rightRotate(temp->right);
			return leftRotate(temp);
			cout << "right of left case" << endl << temp->Data << endl;
		}
		return temp;

	}
	bool retrieve(AVLTreeNode<string, long int, int >* temp, A2 data) {
		if (temp == NULL) {
			return false;
		}
		else if (temp->Data == data) {
			cout << temp->Data << " ";

			return true;
		}
		else if (temp->Data > data) {
			if (temp->left != NULL) {
				return retrieve(temp->left, data);
			}
			else {
				return false;
			}
		}
		else {
			if (temp->right != NULL) {
				return retrieve(temp->right, data);
			}
			else {
				return false;
			}
		}
	}
	bool isEmpty() {
		if (root == NULL)
			return true;
		return false;
	}
	AVLTreeNode<string, long int, int >* mostLeft(AVLTreeNode<string, long int, int >* n)
	{
		AVLTreeNode<string, long int, int >* present = n;
		while (present->left != NULL)
			present = present->left;
		return present;			//returning the left most node on bottom
	}
	string removeDataFromFile(A1 filename_, A2 lineToDelete) {//removing the data from the file at givn line number
		ifstream f;
		ofstream g;
		int r = rand();
		string fr = to_string(r);
		string filename1 = fr + ".txt";
		g.open(filename1);
		f.open(filename_);
		string s = "";
		string valueThatWillDelete = "";
		int c = 0;
		f >> s;
		while (!f.eof()) {
			c++;
			if (c == lineToDelete) {
				valueThatWillDelete = s;
				s = "///";
			}
			g << s << endl;
			f >> s;
		}
		f.close();
		g.close();
		remove(filename_.c_str());
		rename(filename1.c_str(), filename_.c_str());
		return valueThatWillDelete;
	}
	AVLTreeNode<string, long int, int >* removeAVLnode(AVLTreeNode<string, long int, int >* n, int data)
	{
		if (n == NULL)
			return n;
		if (data < n->Data)
			n->left = removeAVLnode(n->left, data);
		else if (data > n->Data)
			n->right = removeAVLnode(n->right, data);
		else {
			// when nodes have zero or one child  
			if ((n->left == NULL) ||
				(n->right == NULL))
			{
				AVLTreeNode<string, long int, int >* temp = n->left ?
					n->left :
					n->right;
				// when both left and right are null  
				if (temp == NULL) {
					temp = n;
					n = NULL;
				}
				else // when left or right is not null  
					*n = *temp;
				cout << "Key : " << data << ", Value : " << removeDataFromFile(temp->filepath, temp->linenumber) << endl;
				delete temp;
				temp = NULL;
			}
			else {
				// when node has two children  
				AVLTreeNode<string, long int, int >* t1 = mostLeft(n->right);
				n->Data = t1->Data;
				n->right = removeAVLnode(n->right, t1->Data);
			}
		}
		//for node having only one child
		if (n == NULL)
			return n;
		//changing the height accordingly
		n->h = 1 + maxHeight(getHeight(n->left),
			getHeight(n->right));
		int bf = findBalance(n);
		//total 4 cases below
		// right of right Case  
		if (bf < -1 && findBalance(n->right) <= 0) {
			return leftRotate(n);
		}
		// left of left Case  
		if (bf > 1 && findBalance(n->left) >= 0) {
			return rightRotate(n);
		}
		// left of right Case  
		if (bf > 1 && findBalance(n->left) < 0) {
			n->left = leftRotate(n->left);
			return rightRotate(n);
		}
		// right of left Case  
		if (bf < -1 && findBalance(n->right) > 0) {
			n->right = rightRotate(n->right);
			return leftRotate(n);
		}
		return n;
	}
	void displayFile(A1 nameOfFile) {
		int line = 0;
		ifstream f;
		f.open(nameOfFile);
		string s;
		cout << "\nthe file path for this machine is " << nameOfFile << endl;
		f >> s;
		cout << "x-Showing all the data of the machine-x" << endl;
		while (!f.eof()) {
			line++;
			if (s != "///")
				cout << setw(9) << left << "line no: " << line << " , Value : " << s << endl;
			f >> s;
		}
		f.close();
	}
	void display(AVLTreeNode<string, long int, int >* temp) {
		if (temp != NULL && temp->counter != 0) {//couter of total nodes in AVL tree
			cout << "ID : " << temp->Data << endl;
			display(temp->left);
			display(temp->right);
		}
		else if (temp->counter == 0)
			cout << "No Data in Machine\n" << endl;
		return;
	}
	void displayfilesData(AVLTreeNode<string, long int, int >* temp, long int ID) {
		if (temp != NULL && temp->counter != 0) {//couter of total nodes in AVL tree
			for (int i = 1; i < fileNumber + 1; i++) {
				displayFile("data_machine_" + to_string(ID) + "_" + to_string(i) + ".txt");
				cout << endl;
			}
		}
		else if (temp->counter == 0)
			cout << "No Data in Machine\n" << endl;
		return;
	}
	void makeRootNullIfCounterZero() {
		if (root->counter == 0)
			root = NULL;
	}
	void delete_all(AVLTreeNode<string, long int, int >* temp) {
		if (temp != NULL && temp->counter != 0) {//couter of total nodes in AVL tree
			delete_all(temp->left);
		}
		if (temp != NULL && temp->counter != 0) {//couter of total nodes in AVL tree

			delete_all(temp->right);
		}
		if (temp->counter == 0) {
			root = NULL;
			delete temp;
			temp = NULL;
		}
		else if (temp->counter == 0) {
			cout << "\nNo Data in Machine\n" << endl;
		}
		return;
	}
};