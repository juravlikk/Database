#include "stdafx.h"
#include "List.h"
#include <iomanip>
#include <iostream>

#pragma once

using namespace std;

template <class Data> List<Data>::List()
{
	Size = 0;
	pbeg = NULL;
	pend = NULL;
}

template <class Data> List<Data>::~List()
{
	if (pbeg!=0)
	{
		Node<Data> *pv = pbeg;
		while (pv)
		{
			pv = pv->next;
			delete pbeg;
			pbeg = pv;
		}
	}
}

template <class Data> Node<Data>* List<Data>::Add(Data d, int key, string skey)
{
	Node<Data> *pv = new Node<Data>(d, key, skey);
	Node<Data> *p = pbeg;
	Node<Data> *pp = pbeg;
	if (pbeg == NULL)
	{
		Size++;
		pbeg = pend = pv;
		return pv;
	}
	else
	{
		while (p)
		{
			if (p->key > pv->key) break;
			if (p->key == pv->key) 
			{
				return NULL;
			}
			p = p->next;
		}
		if (p == NULL)
		{
			pv->prev = pend;
			pend->next = pv;
			pend = pv;
			Size++;
			return pv;
		}
		else
		{
			if (p == pbeg)
			{
				pv->next = pbeg;
				pbeg->prev = pv;
				pbeg = pv;
				Size++;
				return pv;
			}
			else
			{
				pp = p->prev;
				pp->next = pv;
				pv->prev = pp;
				pv->next = p;
				p->prev = pv;
				Size++;
				return pv;
			}
		}
	}
}

template <class Data> Node<Data>* List<Data>::Find(int key)
{
	if (Size == 0) return NULL;
	Node<Data> *pv = pbeg;
	int size = Size;
	while (pv->key < key)
	{
		pv = pv->next;
	}
	if (pv->key == key)	return pv;
	else return NULL;
}

template <class Data> bool List<Data>::Delete(int key)
{
	if (Node<Data> *pv = Find(key))
	{
		if (Size > 1)
		{
			if (pv == pbeg)
			{
				pbeg = pbeg->next;
				pbeg->prev = NULL;
			}
			else
			{
				if (pv == pend)
				{
					pend = pend->prev;
					pend->next = NULL;
				}
				else
				{
					(pv->prev)->next = pv->next;
					(pv->next)->prev = pv->prev;
				}
			}
			delete pv;
			Size--;
			return true;
		}
		delete pv;
		Size = 0;
		pbeg = pend = NULL;
		return true;
	}
	return false;
}

template <class Data> void List<Data>::Print()
{
	Node<Data>* p = pbeg;
	while (p)
	{
		cout << p->d << endl;
		p = p->next;
	}
}

template <class Data> void List<Data>::PrintF(string s)
{
	const char* str = s.c_str();
	ofstream out(str, ios::app);
	Node<Data>* p = pbeg;
	while (p)
	{
		out << p->d;
		p = p->next;
	}
	out.close();
}