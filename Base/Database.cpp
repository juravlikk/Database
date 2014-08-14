#include "stdafx.h"
#include "Database.h"

template <class Data> Database<Data>::~Database()
{
	delete m;
	delete t;
}

template <class Data> Database<Data>::Database()
{
	Size = 0;
	numb = -1;
}

template <class Data> Database<Data>::Database(int Size)
{
	m = new HashMap<Data>(Size);
	t = new Tree<Data>();
	this->Size = Size;
}

template <class Data> void Database<Data>::Add(Data d, int key, string skey)
{
	Node<Data>* p = m->Add(d, key, skey);
	t->Add(&(p->d), skey, key);
}

template <class Data> bool Database<Data>::Delete(int key)
{
	Node<Data> *p = m->Find(key);
	if (p)
	{
		Top<Data> * pp = t->Find(p->skey);
		if (pp)
		{
			t->Delete(p->skey);
			m->Delete(key);
			return true;
		}
		return false;
	}
	return false;
}

template <class Data> bool Database<Data>::Delete(string key)
{
	Top<Data> * pp = t->Find(key);
	if (pp)
	{
		Node<Data> *p = m->Find(pp->key);
		if (p)
		{
			m->Delete(pp->key);
			t->Delete(key);
			return true;
		}
		return false;
	}
	return false;
}

template <class Data> void Database<Data>::PrintByKeyI(std::string s)
{
	cout << s << ":" << endl;
	m->Print();
}

template <class Data> void Database<Data>::PrintByKeyS(std::string s)
{
	cout << s << ":" << endl;
	t->Print();
}

template <class Data> Node<Data>* Database<Data>::Find(int key)
{
	Node<Data> *p = m->Find(key);
	if (p) cout << p->d << endl;
	return p;
}

template <class Data> Top<Data>* Database<Data>::Find(string key)
{
	Top<Data> *p = t->Find(key);
	if (p) cout << *p->d << endl;
	return p;
}

template <class Data> void Database<Data>::ReadF(string s)
{
	const char* str = s.c_str();
	ifstream in(str);
	if (!in)
	{
		cout << "Cann't open file " << s << "for reading!" << endl;
		return;
	}
	this->~Database();
	int MapSize;
	in >> MapSize;
	Data d;
	this->m = new HashMap<Data>(MapSize);
	this->t = new Tree<Data>();
	this->Size = MapSize;
	while (!in.eof())
	{
		in >> d;
		this->Add(d, (int)d, (string)d);
	}
}

template <class Data> void Database<Data>::WriteF(std::string s)
{
	const char* str = s.c_str();
	ofstream out(str, ios::out);
	if (!out)
	{
		cout << "Cann't open file " << s << " for writing!" << endl;
		return;
	}
	out << Size << endl;
	for (int i = 0; i < Size; i++)
	{
		m->Map[i]->PrintF(s);
	}
	out.close();
}
