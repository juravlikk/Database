#include <string>

#pragma once

using namespace std;

template <class Data>
class Top
{
public:
	string value;
	bool state;
	Top<Data>* next;
	Top<Data>* son;
	Data* d;
	int key;
	Top<Data>(Data* dat = NULL, string val = "root", int akey = 0)
	{
		key = akey;
		d = dat;
		value = val;
		next = NULL;
		son = NULL;
	}
};