#include <string>

#pragma once

using namespace std;

template <class Data>
class Node
{
public:
	int key;
	Data d;
	string skey;
	Node<Data> *next;
	Node<Data> *prev;
	Node<Data>(Data dat = 0, int k = 0, string akey = "")
	{
		skey = akey;
		d = dat;
		key = k;
		next = NULL;
		prev = NULL;
	}
};