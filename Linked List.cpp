//Creates a random student information that can be sorted based on how user wants
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include "LinkedList.h"
#include "Student.h"
#include <cmath>
#include <random>
#include <array>
#include <chrono>
#include <cstdio>
#include <ctime>
#include <algorithm>

using namespace std;

//Array Prototypes
LinkedList<string> bubbleSort(LinkedList<string>[], int, int); //buuble sort function
LinkedList<string> InsertionSort(LinkedList<string>[], int, int); // Insertion sort function
LinkedList<string> QuickSort(LinkedList<string>[], int, int, int); //Quciksort function
char randomGenerator(int, int); //Creates random character to add to a string because I'm too lazy to create the information for 50 people manually
int randomGeneratorInt(int , int) ; //Creates a random number for length of the names.
string FirstRand(int);  //Creates the first name
string LastRand(int); //Creates the last name
string MNumRand(int); //Creates the MNumber

const int n = 50; //Can change this later at will.

int main()
{
	int lenFirst = 0; //This will be randomly generated later
	int lenLast = 0; //This will be randomly generated later
	int lenMnum = 6; //MNumber length is 6
	string First;
	string Last;
	string mnum;

	LinkedList<string> AJ[n]; //Array of linked lists
	Student Persons; //Information for each person

	string arr[n]; //Array for firstnames
	string arr2[n]; //Array for lastnames
	string arr3[n]; //Array for mnumbers

	//This whole loop actually assigns and creates the arrays for use in the linked list section
	for (int i = 0; i < n; i++) {
		lenFirst = randomGeneratorInt(2, 12); //Random length 
		lenLast = randomGeneratorInt(3, 12);
		First = FirstRand(lenFirst); //Creates the first
		Last = LastRand(lenLast); //Creats the last
		mnum = "M08" + MNumRand(lenMnum); //Creates the MNumber

		//Sets all the information for the student class to send to the arrays
		Persons.SetFirst(First);
		Persons.SetLast(Last);
		Persons.SetMNum(mnum);

		//Randomly generates information
		string firstGet = Persons.GetFirst(); //Gets the information from the student class
		string lastGet = Persons.GetLast();
		string MGet = Persons.GetMNumber();

		//Sets the array values
		arr[i] = firstGet;
		arr2[i] = lastGet;
		arr3[i] = MGet;
	}


	int input, input2;
	bool works = false;

	cout << "This program will randomly generate 50 character random 'names'." << endl;
	cout << "The user can choose how it will be sorted and by what method, and what to display the information about each 'student' by." << endl;
	cout << "The student information consists of First Name, Last Name, and School M number (School Id starting with M08).\n" << endl;
	cout << "Type into keyboard: \n   1 for bubble sort accending \n   2 for Insert accending \n   3 for quick accending \n   4 for bubblesort decending \n   5 Insertion decending \n   6 quicksort" << endl;
	cin >> input;
	cout << "Choose what order to display: \n   1 for first names \n   2 for last names \n   3 for MNumbers" << endl;
	cin >> input2;

	//These if statements creates the list in a specific order to match how to compare them
	//The values that are compared will be on the top of the list
	if (input2 == 1) {
		for (int j = 0; j < n; j++) {
			AJ[j].AddItem(arr[j]);
			AJ[j].AddItem(arr2[j]);
			AJ[j].AddItem(arr3[j]);
		}
	}
	else if (input2 == 2) {
		//This adds Items to the linked list array
		for (int j = 0; j < n; j++) {
			AJ[j].AddItem(arr2[j]);
			AJ[j].AddItem(arr[j]);
			AJ[j].AddItem(arr3[j]);
		}
	}
	else if (input2 == 3) {
		//This adds Items to the linked list array
		for (int j = 0; j < n; j++) {
			AJ[j].AddItem(arr3[j]);
			AJ[j].AddItem(arr[j]);
			AJ[j].AddItem(arr2[j]);
		}
	}
	else  {
		cout << "Not correct input for what to to sort by." << endl;
	}

	//This section takes the inputs from user and creates the output accordingly
	//[(n -1) - spot] creates the reverse order of the array so in decending order
	//Bubble sort, quick sort, and merge sort were used because that is what I had working at the time and easiest to manipulate
	LinkedList<string> arrNew[n];
	while (works == false) {
		if (input == 1) {
			for (int spot = 0; spot < n; spot++) {
				arrNew[spot] = bubbleSort(AJ, n, spot);
			}
			works = true;
		}
		else if (input == 4) {
			for (int spot = 0; spot < n; spot++) {
				arrNew[(n - 1) - spot] = bubbleSort(AJ, n, spot);
			}
			works = true;
		}
		else if (input == 2) {
			for (int spot = 0; spot < n; spot++) {
				arrNew[spot] = InsertionSort(AJ, n, spot);
			}
			works = true;
		}
		else if (input == 5) {
			for (int spot = 0; spot < n; spot++) {
				arrNew[(n - 1) - spot] = InsertionSort(AJ, n, spot);
			}
			works = true;
		}
		else if (input == 3) {
			for (int spot = 0; spot < n; spot++) {
				arrNew[spot] = QuickSort(AJ, 0, n - 1, spot);
			}
			works = true;
		}
		else if (input == 6) {
			for (int spot = 0; spot < n; spot++) {
				arrNew[(n - 1) - spot] = QuickSort(AJ, 0, n - 1, spot);
			}
			works = true;
		}
		else {
			cout << "You did not input a correct file." << endl;
		}
	}
	cout << endl;

	//This will print the array asked for
	for (int m = 0; m < n; m++) {
		arrNew[m].PrintList();
		cout << "-----------------------------" << endl;
	}

	return 0;
}

//////////////////////////Bubble Sort/////////////////////////////////////
//This is all the sorting arrays
LinkedList<string> bubbleSort(LinkedList<string> arr[], int len, int spot) {
	LinkedList<string> tempHold; //Temp Holder
	for (int i = 0; i < len; i++) { //The number of times to initiate the loop
		for (int n = 0; n < len - i - 1; n++) { //The actual spots in the array being compared using for loop
			if (arr[n] > arr[n + 1]) { //To check if the spot is smaller than next spot  
				tempHold = arr[n]; //If yes then assign tempHold to the smaller compared item
				arr[n] = arr[n + 1]; //Set the spot of larger spot to the smaller value of the comparison
				arr[n + 1] = tempHold; //Set the spot that was smaller equal to the tempHold that held the larger value
			}
		}
	}
	//printArray(arr, len); //Prints new array
	return arr[spot];
}

/////////////////////Insertion sort//////////////////////////////////////
LinkedList<string> InsertionSort(LinkedList<string> arr[], int len, int spot) {
	LinkedList<string> TempVal; //Temporary Holder Val
	int CompVal; //The comparing Value spot
	for (int i = 1; i < len; i++) { //Runs the length of the array
		TempVal = arr[i]; //Sets the temp value to the second spot in the array
		CompVal = i - 1; //Sets the compare value starter spot behind the temp value
		while (CompVal >= 0 && arr[CompVal] > TempVal) { //Makes sure the compare value start spot is above zero and the array value is greater than the temp value
			arr[CompVal + 1] = arr[CompVal]; //While above is true, set the next spot for comparing equal to the current spot 
			CompVal = CompVal - 1; //Keep moving down the list in the opposite direction
		}
		arr[CompVal + 1] = TempVal; //Once its done go on to the next spot and set equal to temp value
	}
	return arr[spot];
	//printArray(arr, len);
}

//////////////////Quick sort code///////////////////////////////////////
int sortStart(LinkedList<string> arr[], int spot1, int spot2) { //This creates the seperate sections for either below, equal, or greater than the pivot
	LinkedList<string> pivot = arr[spot2]; //Pivot compare variable is equal to array spot
	int small = spot1 - 1; //The smaller number starts at 1 - start spot

	for (int i = spot1; i < spot2; i++) { //for the itterations from below to the value of spot2
		if (arr[i] <= pivot) { //check if the array value at spot1 is less than spot2
			small++; //Add 1 to small 
			swap(arr[i], arr[small]); //swap the values of array value and where the small itterator is at
		}
	}
	swap(arr[spot2], arr[small + 1]); //Swap the spots again
	return small + 1; //Return the itterator + 1
}

LinkedList<string> QuickSort(LinkedList<string> arr[], int start, int end, int spot) { //Where the recurrsion occurs
	if (start < end) { //If start is less than end
		int pos = sortStart(arr, start, end); //The position equals the values that will be sorted
		QuickSort(arr, start, pos - 1, spot); //Quick sort for all values less than pivot
		QuickSort(arr, pos + 1, end, spot);//Quick sort all values equal or greater than pivot
	}
	return arr[spot];
}

//////////////////////////////////Used for generating the names and other information ////////////////////////
char randomGenerator(int start, int end) {
	//This was taken from
	//https://msdn.microsoft.com/en-us/library/bb982398.aspx
	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> dist(start, end); //Returns a random number
	return static_cast<char> (dist(gen));
}

int randomGeneratorInt(int start, int end) {
	//This was taken from
	//https://msdn.microsoft.com/en-us/library/bb982398.aspx
	random_device rd;   // non-deterministic generator  
	mt19937 gen(rd());  // to seed mersenne twister.  
	uniform_int_distribution<> dist(start, end); //Returns a random number
	return (dist(gen));
}

//These functions are used to create the strings that are made from randomly generated characters.
string FirstRand(int len) {
	string First;
	First += randomGenerator(65, 90);
	for (int i = 1; i < len; i++) {
		First += randomGenerator(97, 122);
	}
	return First;
}

string LastRand(int len) {
	string Last;
	Last += randomGenerator(65, 90);
	for (int i = 1; i < len; i++) {
		Last += randomGenerator(97, 122);
	}
	return Last;
}

string MNumRand(int len) {
	string MNumb;
	for (int i = 0; i < len; i++) {
		MNumb += randomGenerator(48, 57);
	}
	return MNumb;
}



