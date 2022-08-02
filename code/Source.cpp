#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<ctime>
#include"linkedlist.h"
using namespace std;
template <typename Type_of_data>
bool isLeftGreaterThanRight(Type_of_data left_value, Type_of_data right_value) {
	if (left_value > right_value)
		return true;
	return false;
}
void menu(int question_number) {			
	if (question_number == 1) {
		cout << "Please specify number of Machines : ";
	}
	else if (question_number == 2) {
		cout << "Please specify size of identifier space in bits : ";
	}
	else if (question_number == 3) {
		cout << "Want to Assign id manually? (Y/N) : ";
	}
	else if (question_number == 4) {//main menu
		cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
		cout << "|1.Want to Insert Data?                       |" << endl;
		cout << "|2.Want to Remove Data?                       |" << endl;
		cout << "|3.Want to print Routing Table of any machine?|" << endl;
		cout << "|4.Want to print AVL Tree of any machine?     |" << endl;
		cout << "|5.Want to add new machine?                   |" << endl;
		cout << "|6.Want to remove any machine?                |" << endl;
		cout << "|7.Want to print the data of Whole System?    |" << endl;
		cout << "|8.To Exit.                                   |" << endl;
		cout << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;
	}
}
bool isStringDigit(string number) {//checking if number is a number or not
	int i = 0;
	while (number[i] != '\0') {
		if (isdigit(number[i]) == 0)
			return false;
		i++;
	}
	return true;
}
string enterString() {//ftn to to get a string from user
	string inputToReturn = "";
	while (true) {
		getline(cin, inputToReturn);
		if (inputToReturn != "")//checking for empty string enter by user
			return inputToReturn;
		cout << "You have entered an empty string." << endl;
		cout << "Invalid Input.\nEnter Again please : ";
	}
}
long int hashTheValueOverSpecifiedLengthOfSystem(string key, long int lengthOfSystem) {//first parameter: key to hash,   
	static hash<string> hashObject;	//using hash stl library for hasing the value      //second parameter:taking mode over specified range 
	long int hashed = hashObject(key) % lengthOfSystem;							 	   //                 of the system
	return hashed;
}
long int findpower(long int power) {//finding power //first parameter:power value
	long int result = 2;
	if (power == 1)
		return result;
	long int multiplier = 2;
	for (int mul = 1; mul < power; mul++) {
		result = result * multiplier;
	}
	return result;
}

char askFtn() {
	char input = ' ';
	while (true) {
		menu(3);	//Asking for manually assigning ids
		cin >> input;
		if (input == 'n' || input == 'N' || input == 'Y' || input == 'y')
			break;
		cout << "Invalid Input." << endl;
	}
	return input;
}
string getrandomValue() {
	long int  v = 0;
	while (true) {
		v = rand();
		if (v > -1)
			return to_string(v);
	}
}
///////
int main() {
	string machines = "";
	char bits = ' ';
	long int hashedValue = 0;
	long int machinesLongType = 0;//total machines
	long int lengthOfLinkList = 0;//identifier space
	string inputKey = "";
	string inputValue = "";
	string inputMachine = "";
	linkedlist<long int > Machines;
	srand(time(NULL));
	while (true) {	//Getting Machines Number
		menu(1);
		machines = enterString();
		if (isStringDigit(machines) == true) {
			//for comparing it to lengthoflinkedlist
			if (isLeftGreaterThanRight((stol(machines)), (long int)0))
				break;
			cout << "Invalid Input." << endl;
			//machines number in (int)machine
		}
		else
			cout << "Enter a digit please." << endl;
	}
	cout << "Correct Input." << endl;
	machinesLongType = stol(machines);
	cout << "Total Machines : " << machinesLongType << endl;
	while (true) {	//Getting bits space
		menu(2);//checking is there enough space according to bits
		inputKey.clear();
		inputKey = enterString();//taking bits
		if (isStringDigit(inputKey)) {
			if (isLeftGreaterThanRight(stol(inputKey), (long int)0)) {
				lengthOfLinkList = findpower(stol(inputKey));//first calculating 2^bits then
				if (lengthOfLinkList + 1 > machinesLongType) {// caparing is length is equal or greater than machines
					Machines.setBits(stol(inputKey));
					break;
				}
				cout << "Invalid Bits." << endl;
			}
			else
				cout << "Invalid Input." << endl;
		}
		else
			cout << "Enter a digit please." << endl;
	}
	cout << "Correct Input." << endl;
	cout << "Identifier Space : " << lengthOfLinkList << endl;
	char input = askFtn();//Asking to manually store id or not//y is yes and n is no
	cin.ignore();
	if (input == 'Y' || input == 'y') {
		cout << "Assign Manually" << endl;
		for (long int m = 0; m < machinesLongType; m++) {
			while (true) {
				cout << "Enter Machine ID : ";
				inputKey.clear();
				inputKey = enterString();
				if (isStringDigit(inputKey) == true) {
					hashedValue = stol(inputKey);//converting to long 
					if (hashedValue > -1 && hashedValue < lengthOfLinkList) {//checking it is between 0 and lengthoflinkedlist-1
						if (Machines.checkDuplicates(hashedValue) == true) {//returns true when hashedValue is not already in linkedlist
							Machines.insertNew(hashedValue);
							break;
						}
						else
							cout << "Duplicates are not allowed!\nInvalid Input." << endl;
					}
					else {
						cout << "Machines ID should be greater than or equal to 0 and less than " << lengthOfLinkList << "." << endl;
						cout << "Invalid Input." << endl;
					}
				}
				else
					cout << "Please enter in Digits!!!.\nInvalid Input." << endl;
			}
		}
	}
	else {
		cout << "Assign Automatically." << endl;
		cout << "Total Machines : " << machinesLongType << endl;
		for (long int m = 0; m < machinesLongType; m++) {
			while (true) {
				hashedValue = hashTheValueOverSpecifiedLengthOfSystem(getrandomValue(), lengthOfLinkList);
				if (Machines.checkDuplicates(hashedValue)) {
					//cout << "ture" << endl;
					Machines.insertNew(hashedValue);
					break;
				}
			}
		}
	}
	Machines.Display();
	cout << "Bits : " << Machines.bits << endl;
	Machines.setRoutingTableOfAllNodes();
	//main menu
	string option = "";
	int temp_1 = 0;
	nod* temp = NULL;
	while (true) {
		menu(4);
		option.clear();
		cout << "Enter Option Number : ";
		option = enterString();
		if (isStringDigit(option)) {//checking input is digit or not
			if (option == "1") {
				//cin.ignore();
				if (machinesLongType == 0) {
					cout << "\nThere is no Machines in the System.\nPlease select option 5 to add a machine in the system\n" << endl;
					continue;
				}
				Machines.Display();//Display All machines Names to make it easier for user to enter machine name
				while (true) {
					cout << "Enter Machine from which you want to store data : ";
					inputMachine = enterString();
					if (isStringDigit(inputMachine) == true) {
						temp = Machines.findAddress(stol(inputMachine));//returning address of the machine id(not found=NULL || found=id address)
						if (temp != NULL) {//checking id is valid or not
							cout << "Machine : " << temp->machineID << endl;
							inputMachine.clear();
							cout << "\nEnter Key : ";
							inputKey = enterString();
							cout << "\nEnter Value : ";
							inputValue = enterString();
							hashedValue = hashTheValueOverSpecifiedLengthOfSystem(inputKey, lengthOfLinkList);
							cout << "Key to Store : " << hashedValue << endl;
							cout << "x-----Path of the Insertion-----x" << endl;
							cout << "Insertion Start from Machine : " << temp->machineID << endl;
							Machines.setKeyInTheSystem(temp, hashedValue, inputValue);
							cout << "x-----Path end-----x" << endl;
							inputKey.clear();
							inputValue.clear();
							break;
						}
						else
							cout << "Invalid Machine ID." << endl;
					}
					else
						cout << "Invalid Input.\nEnter Digits Please!!" << endl;
				}
			}
			else if (option == "2") {
				//cin.ignore();
				if (machinesLongType == 0) {
					cout << "\nThere is no Machines in the System.\nPlease select option 5 to add a machine in the system\n" << endl;
					continue;
				}
				Machines.Display();
				while (true) {
					cout << "Enter Machine from which you want to delete data : ";
					inputMachine = enterString();
					if (isStringDigit(inputMachine) == true) {
						temp = Machines.findAddress(stol(inputMachine));//returning address of the machine id(not found=NULL || found=id address)
						if (temp != NULL) {//checking id is valid or not
							if (temp->machinesData.root->counter == 0) {
								cout << "\nThere is no data in the machine ID " << temp->machineID << ".\n" << endl;
								break;
							}
							cout << "Machnie id : " << temp->machineID << endl;
							inputMachine.clear();
							cout << "\nEnter Key : ";
							inputKey = enterString();
							hashedValue = hashTheValueOverSpecifiedLengthOfSystem(inputKey, lengthOfLinkList);
							cout << "x-----Path of Deletion-----x" << endl;
							cout << "Deletion start from Machine : " << temp->machineID << endl;
							Machines.deleteKeyFromTheSystem(temp, hashedValue);
							cout << "x-----Path end-----x" << endl;
							temp->machinesData.display(temp->machinesData.root);
							inputKey.clear();
							break;
						}
						else
							cout << "Invalid Machine ID." << endl;
					}
					else
						cout << "Invalid Input.\nEnter Digits Please!!" << endl;
				}
			}
			else if (option == "3") {
				//cin.ignore();
				if (machinesLongType == 0) {
					cout << "\nThere is no Machines in the System.\nPlease select option 5 to add a machine in the system\n" << endl;
					continue;
				}
				Machines.Display();
				while (true) {
					cout << "Enter Machine ID to print its routing table : ";
					inputMachine = enterString();
					if (isStringDigit(inputMachine) == true) {
						temp = Machines.findAddress(stol(inputMachine));//returning address of the machine id(not found=NULL || found=id address)
						if (temp != NULL) {//checking id is valid or not
							Machines.printRoutingTable(temp);//function tp print routing table of passing node
							inputMachine.clear();
							break;
						}
						else
							cout << "Invalid Machine ID." << endl;
					}
					else
						cout << "Invalid Input.\nEnter Digits Please!!" << endl;
				}
			}
			else if (option == "4") {
				//cin.ignore();
				if (machinesLongType == 0) {
					cout << "\nThere is no Machines in the System.\nPlease select option 5 to add a machine in the system\n" << endl;
					continue;
				}
				Machines.Display();	//Display All machines Names to make it easier for user to enter machine name
				while (true) {
					cout << "Enter Machine ID to print its AVL tree : ";
					inputMachine = enterString();
					if (isStringDigit(inputMachine) == true) {
						temp = Machines.findAddress(stol(inputMachine));//returning address of the machine id(not found=NULL || found=id address)
						if (temp != NULL) {//checking id is valid or not
							cout << "\nAVL DATA of Machine ID : " << temp->machineID << endl << endl;
							temp->machinesData.displayfilesData(temp->machinesData.root, temp->machineID);//displaying AVL data of a machine
							cout << endl;
							inputMachine.clear();
							break;
						}
						else
							cout << "Invalid Machine ID." << endl;
					}
					else
						cout << "Invalid Input.\nEnter Digits Please!!" << endl;
				}
			}
			else if (option == "5") {
				if (machinesLongType == lengthOfLinkList) {//checking for maximum machines
					cout << "\nMaximum Machines are already in the identifier space." << endl;
					cout << "You cannot add more machines.\n" << endl;
					continue;
				}
				machinesLongType++;
				//cin.ignore();
				Machines.Display();
				input = ' ';
				input = askFtn();
				cin.ignore();
				if (input == 'Y' || input == 'y') {
					cout << "Assign Manually" << endl;
					while (true) {
						cout << "Enter Machine ID : ";
						inputKey.clear();
						inputKey = enterString();
						if (isStringDigit(inputKey) == true) {
							hashedValue = stol(inputKey);//converting to long 
							if (hashedValue > -1 && hashedValue < lengthOfLinkList) {//checking it is between 0 and lengthoflinkedlist-1
								if (Machines.checkDuplicates(hashedValue) == true) {//returns true when hashedValue is not already in linkedlist
									Machines.insertNew(hashedValue);
									break;
								}
								else
									cout << "Duplicates are not allowed!\nInvalid Input." << endl;
							}
							else {
								cout << "Machines ID should be greater than or equal to 0 and less than " << lengthOfLinkList << "." << endl;
								cout << "Invalid Input." << endl;
							}
						}
						else
							cout << "Please enter in Digits!!!.\nInvalid Input." << endl;
					}
				}
				else {
					cout << "Assign Automatically." << endl;
					while (true) {
						hashedValue = hashTheValueOverSpecifiedLengthOfSystem(to_string(rand()), lengthOfLinkList);
						if (Machines.checkDuplicates(hashedValue)) {
							Machines.insertNew(hashedValue);
							break;
						}
					}
				}
				temp = NULL;
				Machines.deleteAllRoutingTable();
				Machines.setRoutingTableOfAllNodes();
				temp = Machines.findAddress(hashedValue);//finding the new machine address to pass it to routing table
				Machines.distributeData(temp);
			}
			else if (option == "6") {
				//cin.ignore();
				Machines.Display();//Display All machines Names to make it easier for user to enter machine name
				if (machinesLongType == 0) {
					cout << "\nThere is no Machines in the System.\nPlease select option 5 to add a machine in the system\n" << endl;
					continue;
				}
				while (true) {
					cout << "Enter Machine ID to delete it : ";
					inputMachine = enterString();
					if (isStringDigit(inputMachine) == true) {
						temp_1 = Machines.deleteByID(stol(inputMachine));
						if (temp_1 == 0)
							cout << "Invalid Machine ID" << endl;
						else {
							machinesLongType--;
							break;
						}
					}
					else
						cout << "Invalid Input.\nEnter Digits Please!!" << endl;
				}
			}
			else if (option == "7") {
				if (Machines.getLength() == 0) {
					cout << "\nThere is no Machines in the System.\nPlease select option 5 to add a machine in the system\n" << endl;
					continue;
				}
				Machines.ALLMachinesData();
			}
			else if (option == "8") {
				cout << "Closing the system." << endl;
				cout << "Thank You for using our system." << endl;
				Machines.deleteAllData();
				break;
			}
			else
				cout << "Invalid Input.\nEnter number between 1 and 8." << endl;
		}
		else
			cout << "Invalid Input.\nEnter a Digit!!!" << endl;
	}
	return 0;
}