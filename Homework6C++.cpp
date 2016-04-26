// Homework6C++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <sstream>

using namespace std;
stack<string> Read_File(string filename);
int Quadratic_probing(string key, int *& hash_table, int M);
//int Hash_Quadratic(int val, int M);
int Extract(string val);



/*int Hash_Quadratic(int val, int M)
{
	int i = 1 / ((M - 1) / 2);

	return ((val * M) + (i * i));
}*/

int Quadratic_probing(string key, int *&hash_table, int M) //The quadratic probing equation
{
	int pos, i; //the two values for the probing
	pos = Extract(key); //the position is the hashed extraction
		
	for (i = pos + 1; i%M != pos; i++) //while it goes through the numbers
	{
		pos = (pos + i * i) % M; //<--The quadratic probing
		if (hash_table[pos] == 0) //if the position is nothing, or empty
		{
			hash_table[pos] = stoi(key); //then store that postition
			return pos; //return it
		} 
	}		
		
	
			return -1; //if it isn't empty, return -1
}

stack<string> Read_File(string filename) //reading in the file
{
	ifstream in; //needed for the file
	in.open(filename); //opening the filename that's in main
	string store; //needed for storing lines
	stack<string> hold; //stack to hold all the numbers

	if (in.is_open()) //while the file is open
	{
		while (in.peek() != EOF) //while it reads to the end of the file
		{	
			getline(in, store, ','); //get each line, store it in store, and get rid of the commas
			hold.push(store); //push that string into the stack
			//cout << store << endl; <--used to test splitting of numbers
		}
	}
	else
	{
		cout << "File location not found" << endl; //if not, then you're screwed
	}
	in.clear(); //clear the file
	in.close(); //close the file
	return hold //return the stack
}

int Extract(string val) //the extraction method
{
	string pos; //position
	pos.append(val.begin()+3, val.begin() + 4); //appending each position using .begin();
	pos.append(val.begin() + 5, val.begin() + 6); 
	pos.append(val.begin() + 7, val.begin() + 8);
	pos.append(val.begin() + 8, val.begin() + 9);
	int key = stoi(pos); //the key is the string position. Converted using STOI
	return key; //return the integer
}
int main()
{
	//int * Numbers; <--Not needed
	
	string File_location = "everybodys_socials.txt"; //opening the file
	stack<string> s = Read_File(File_location); //reading the file and storing it in stack s

	int * hash = new int[70000]; //the hash table
	int size=0;//needed to run
	for (int i = 0; i < 70000; i++) hash[i] = 0; //needed so it can probe with ease. 
	cout << "Enter a number between 1 and 450million" << endl; //user inputted max value
	int Max;
	cin >> Max;

	while (!s.empty()) //while the stack isn't empty
	{
		size++; //add on to the size
		string top = s.top(); //top will hold the top of the stack
		int store = Extract(top); //my index STORE will hold that value
		s.pop(); //pop the top
		
		if (hash[store] == 0) //if it's empty
		{
			hash[store] = stoi(top); //store key in table
		}
		else
		{
			cout << "probe" << endl;
			Quadratic_probing(top, hash, Max); //do the quadratic probe
		}
	
	}
	ofstream out; //output file
	out.open("socials.txt"); //opening the output file

	for (int a = 0; a < size-1; a++) //for loop to print out the outputs
	{
		out << hash[a] << ","; //output the table, add comma
	}
	out << hash[size - 1]; //output the table
	out.clear(); //clear the file
	out.close(); //close the file
	//delete[] hash; //<--for memory's sake

    return 0;//return nothing to make it happy happy :)
}

