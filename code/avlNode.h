#pragma once
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

template<typename T1, typename T2, typename T3>
// T1=string , T2=long int , T3 = int 
struct AVLTreeNode {
	//	string 
	T1 filepath;
	static /*long int*/ T2 counter;//counter for total objects
//	int 
	T3 linenumber;
	//	int 
	T3 Data;//key of the data
//	int 
	T3 h;
	AVLTreeNode* left;
	AVLTreeNode* right;
	AVLTreeNode() {
		counter++;
		filepath = "";
		linenumber = -1;
		Data = 0;
		left = NULL;
		right = NULL;
		h = -1;
	}
	AVLTreeNode(T3 data, T1 filePath, T3 lineNumber) {
		filepath = filePath;
		linenumber = lineNumber;
		Data = data;
		left = NULL;
		right = NULL;
		h = 0;
		counter++;
	}
	string getValue() {//getting the value of the data
		ifstream gg;
		string s;
		gg.open(filepath);
		int c = 1;
		while (getline(gg, s)) {
			if (c == linenumber)
				return s;
			c++;
		}
		gg.close();
	}
	~AVLTreeNode() {
		counter--;
	}
};