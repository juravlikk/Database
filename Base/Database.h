#include "stdafx.h"
#include <string>
#include "HashMap.cpp"
#include "Tree.cpp"

#pragma once

using namespace std;

template <class Data>
class Database
{
	HashMap<Data> *m;
	Tree<Data> *t;
	int Size;
public:
	Database();
	Database(int Size);
	~Database();
	void Add (Data d, int key, string skey);
	Node<Data>* Find (int key);
	Top<Data>* Find (string key);
	bool Delete(int key);
	bool Delete(string key);
	void PrintByKeyS(string s);
	void PrintByKeyI(string s);
	void ReadF(string s);
	void WriteF(string s);
};