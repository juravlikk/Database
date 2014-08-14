#include <string>
#include "Node.h"
#pragma once

using namespace std;

template <class Data>
class List
{
	Node<Data> *pbeg;
	Node<Data> *pend;
	int Size;

public:
	List<Data>();
	~List<Data>();

	Node<Data>* Add (Data d, int key, string skey);
	Node<Data>* Find (int key);
	bool Delete(int key);
	void Print();
	void PrintF(string s);
};
