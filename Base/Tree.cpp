#include "stdafx.h"
#include <string>
#include <iostream>
#include "Tree.h"

using namespace std;

template <class Data> Tree<Data>::Tree()
{
	proot = new Top<Data>();
}

template <class Data> Tree<Data>::~Tree()
{
	if (proot->son)
	{
		DeleteTree(proot->son);
	}
	delete proot;
}

template <class Data> void Tree<Data>::DeleteTree(Top<Data> *&pcur)
{
	if ((pcur->son == NULL) & (pcur->next == NULL))
	{
		delete pcur;
		return;
	}
	if (pcur->son == NULL) DeleteTree(pcur->next);
	if (pcur->next = NULL) DeleteTree(pcur->son);
}

template <class Data> bool Tree<Data>::InsertTop(Top<Data> *&pcur, Top<Data> *pins)
{
	if (pcur == NULL)
	{
		pins->state = true;
		pcur = pins;
		return true;
	}
	else
	{
		if (pcur->value[0] < pins->value[0]) return InsertTop(pcur->next, pins);
		if (pcur->value[0] > pins->value[0])
		{
			pins->state = true;
			pins->next = pcur;
			pcur = pins;
			return true;
		}
		if (pcur->value[0] == pins->value[0])
		{
			if (pcur->value == pins->value)
			{
				if (pcur->state) return false;
				pins->state = true;
				pins->next = pcur->next;
				pins->son = pcur->son;
				pcur = pins;
				return true;
			}
			int i = 1;
			while ((pcur->value[i] == pins->value[i]) & (pcur->value.length() > i) & (pins->value.length() > i)) i++;
			if (i == pcur->value.length()) 
			{
				pins->value.erase(0, i);
				return InsertTop(pcur->son, pins);
			}
			else
			{
				string s = pcur->value;
				s.erase(0, i);
				Top<Data>* p = new Top<Data>(pcur->d, s, pcur->key);
				p->son = pcur->son;
				pcur->son = p;
				p->state = pcur->state;
				pcur->value.erase(i);
				pins->value.erase(0, i);
				if (pins->value.length() == 0)
				{
					pcur->state = true;
					pcur->d = pins->d;
					return true;
				}
				else
				{
					pcur->key = -1;
					pcur->d = NULL;
					pcur->state = false;
					return InsertTop(pcur->son, pins);
				}
			}
		}
	}
}

template <class Data> bool Tree<Data>::Add(Data* d, string key, int ikey)
{
	Top<Data> *pv = new Top<Data>(d, key, ikey);
	if (!InsertTop(proot->son, pv))
	{
		cout << "This record (" << key << ") is already exist!" << endl;
		delete pv;
		return false;
	}
	return true;
}

template <class Data> Top<Data>* Tree<Data>::FindTop(Top<Data> *&pcur, string key)
{
	if (pcur == NULL) return NULL;
	else
	{
		if (pcur->value[0] < key[0]) return FindTop(pcur->next, key);
		if (pcur->value[0] > key[0]) return NULL;
		if (pcur->value[0] == key[0])
		{
			if (pcur->value == key)
			{
				if (pcur->state) return pcur;
				return NULL;
			}
		}
		int i = 1;
		while ((pcur->value[i] == key[i]) & (pcur->value.length() > i) & (key.length() > i)) i++;
		if (i == pcur->value.length()) 
		{
			key.erase(0, i);
			return FindTop(pcur->son, key);
		}
		else return NULL;
	}
}

template <class Data> Top<Data>* Tree<Data>::Find(string key)
{
	Top<Data>* p = FindTop(proot->son, key);
	if (p == NULL) cout << "This record ( key - " << key << " ) doesn't exist!" << endl << endl; 
	return p;
}

template <class Data> void Tree<Data>::DeleteTop(Top<Data> *&pcur, string key, bool &ret)
{
	if (pcur == NULL) ret = false;
	else
	{
		if (pcur->value[0] < key[0]) 
		{
			DeleteTop(pcur->next, key, ret);
			return;
		}
		if (pcur->value[0] > key[0]) 
		{
			ret = false;
			return;
		}
		if (pcur->value[0] == key[0])
		{
			if (pcur->value == key)
			{
				if (pcur->son == NULL)
				{
					if (pcur->next == NULL)
					{
						delete pcur;
						pcur = NULL;
						ret = true;
						return;
					}
					Top<Data>* p = pcur->next;
					delete pcur;
					pcur = p;
					ret = true;
				}
				if (pcur->state) 
				{
					if (pcur->son->next)
					{
						pcur->state = false;
						pcur->d = 0;
						ret = true;
					}
					else
					{
						Top<Data>* p = pcur->son;
						p->next = pcur->next;
						p->value = pcur->value + p->value;
						delete pcur;
						pcur = p;
						ret = true;
					}
				}
				else ret = false;
			}
			else
			{			
				int i = 1;
				while ((pcur->value[i] == key[i]) & (pcur->value.length() > i) & (key.length() > i)) i++;
				if (i == pcur->value.length()) 
				{
					key.erase(0, i);
					DeleteTop(pcur->son, key, ret);
					if (ret)
					{
						if (!pcur->state)
						{
							if (pcur->son->next == NULL)
							{
								Top<Data> *p = pcur->son;
								p->next = pcur->next;
								p->value = pcur->value + p->value;
								delete pcur;
								pcur = p;
								return;
							}
							pcur->state = false;
							pcur->d = 0;
							return;
						}
					}
				}
				else ret = false;
			}
		}
	}
}

template <class Data> bool Tree<Data>::Delete(string key)
{
	bool ret = false;
	DeleteTop(proot->son, key, ret);
	return ret;
}

template <class Data> void Tree<Data>::PrintTop(Top<Data> *&pcur, string s)
{
	s+=pcur->value;
	if (pcur->state) 
	{
		cout << *pcur->d << endl;
	}
	if ((pcur->son == NULL) & (pcur->next == NULL))
	{
		return;
	}
	if (pcur->son) 
	{
		PrintTop(pcur->son, s);
	}
	if (pcur->next) 
	{
		s.erase(s.length() - pcur->value.length());
		PrintTop(pcur->next, s);
	}
}

template <class Data> void Tree<Data>::Print()
{
	if (proot->son)
	{
		PrintTop(proot->son, "");
		return;
	}
	cout << "Empty tree" << endl;
}