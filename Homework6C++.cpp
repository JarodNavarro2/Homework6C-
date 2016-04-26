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

int Quadratic_probing(string key, int *&hash_table, int M)
{
	int pos, i; //int temp;
	pos = Extract(key);
		
	for (i = pos + 1; i%M != pos; i++)
	{
		pos = (pos + i * i) % M; //<--The quadratic probing
		if (hash_table[pos] == 0)
		{
			hash_table[pos] = stoi(key);
			return pos;
		} 
	}		
		
	
			return -1;
}

stack<string> Read_File(string filename)
{
	ifstream in;
	in.open(filename);
	string store;
	stack<string> hold;

	if (in.is_open())
	{
		while (in.peek() != EOF)
		{	
			getline(in, store, ',');
			hold.push(store);
			//cout << store << endl; <--used to test splitting of numbers
		}
	}
	else
	{
		cout << "File location not found" << endl;
	}
	in.clear();
	in.close();
	return hold;
}

int Extract(string val)
{
	string pos;
	pos.append(val.begin()+3, val.begin() + 4);
	pos.append(val.begin() + 5, val.begin() + 6); ///<---breakpoint?
	pos.append(val.begin() + 7, val.begin() + 8);
	pos.append(val.begin() + 8, val.begin() + 9);
	int key = stoi(pos);
	return key;
}
int main()
{
	int * Numbers;
	
	string File_location = "everybodys_socials.txt";
	stack<string> s = Read_File(File_location);

	int * hash = new int[70000];
	int size=0;
	for (int i = 0; i < 70000; i++) hash[i] = 0;
	cout << "Enter a number between 1 and 450million" << endl;
	int Max;
	cin >> Max;

	while (!s.empty())
	{
		size++;
		string top = s.top();
		int store = Extract(top);
		s.pop();
		
		if (hash[store] == 0)
		{
			hash[store] = stoi(top); //store key in table
		}
		else
		{
			cout << "probe" << endl;
			Quadratic_probing(top, hash, Max); //Not sure if right
		}
	
	}
	ofstream out;
	out.open("socials.txt");

	for (int a = 0; a < size-1; a++)
	{
		out << hash[a] << ",";
	}
	out << hash[size - 1];
	out.clear();
	out.close();
	//delete[] hash; //<--for memory's sake

    return 0;
}

