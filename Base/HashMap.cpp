#include "stdafx.h"
#include "HashMap.h"
#include <string>

#pragma once

using namespace std;

template <class Data> HashMap<Data>::~HashMap()
{
	for (int i = 0; i < MapSize; i++)
	{
		if (Map[i]) delete Map[i];
	}
}

template <class Data> HashMap<Data>::HashMap()
{
	MapSize = 0;
}

template <class Data> HashMap<Data>::HashMap(int Size)
{
	MapSize = Size;
	Map = new List<Data>* [Size];
	for (int i = 0; i < Size; i++)
	{
		Map[i] = new List<Data>();
	}
}

template <class Data> int HashMap<Data>::HF(int key)
{
	return key%MapSize;
}

template <class Data> Node<Data>* HashMap<Data>::Find(int key)
{
	Node<Data>* p = Map[HF(key)]->Find(key);
	if (p == NULL) cout << "This record ( key - " << key << " ) doesn't exist!" << endl << endl; 
	return p;
}

template <class Data> Node<Data>* HashMap<Data>::Add(Data d, int key, string skey)
{
	Node<Data>* p = Map[HF(key)]->Add(d, key, skey);
	if (!p)
	{
		cout << "This record ( key - " << key << " ) is already exist!" << endl;
		return NULL;
	}
	return p;
}

template <class Data> bool HashMap<Data>::Delete(int key)
{
	bool state = Map[HF(key)]->Delete(key);
	if (!state) cout << "This record ( key - " << key << " ) doesn't exist!" << endl << endl;
	return state;
}

template <class Data> void HashMap<Data>::Print()
{
	for (int i = 0; i < MapSize; i++)
	{
		Map[i]->Print();
	}
}