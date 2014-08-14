// Base.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include "Data.h"
#include "Database.cpp"

#pragma once

using namespace std;

void Test()
{
	ifstream in("input.txt");
	int MapSize;
	in >> MapSize;
	Database<Data> *dat = new Database<Data>(MapSize);
	Data d;
	while (!in.eof())
	{
		in >> d;
		dat->Add(d, d.Phone, d.FirstName);
	}
	cout << "Test!" << endl << endl;
	dat->PrintByKeyI("Original list");
	dat->PrintByKeyS("Original list");
	dat->Delete(888230);
	dat->Delete("Woman");
	dat->PrintByKeyI("After deleting keys: 888230 and Woman");
	d = Data(442342, "Mike", "Shugar", "dajkljkda 030 jdjk 2", "<><><>");
	dat->Add(d, d.Phone, d.FirstName);
	dat->PrintByKeyI("After adding key: 442342");
	cout << "Find item (key - Mike):" << endl;
	dat->Find("Mike");
	cout << "Find item 442321:" << endl;
	dat->Find(442321);
	dat->WriteF("output.txt");
	dat->ReadF("input.txt");
	dat->PrintByKeyI("After reading from file input.txt");
	delete dat;
}

int _tmain(int argc, _TCHAR* argv[])
{
//	Test();
	int Size;
	int Type = 0;
	int key;
	string skey;
	Data d;
	cout << "Enter size of the hash map: ";
	cin >> Size;
	if (Size <= 0) return 0;
	Database<Data>* dat = new Database<Data>(Size);
	while (Type!=7)
	{
		cout << "1: Add " << " 2: Delete " << " 3: Find " << " 4: Print " << " 5: Read from file " << " 6: Write to file " << " 7: Exit " << endl;
		cin >> Type;
		switch (Type)
		{
		case 1:
			{
				cin >> d;
				cout << endl;
				dat->Add(d, d.Phone, d.FirstName);
				break;
			}
		case 2:
			{			
				cout << "Enter key: ";
				cin >> key;
				cout << endl;
				dat->Delete(key);
				break;
			}
		case 3:
			{
				cout << "Enter key: ";
				cin >> key;
				cout << endl;
				Node<Data>* p = dat->Find(key);
				break;
			}
		case 4:
			{
				dat->PrintByKeyI("List");
				break;
			}
		case 5:
			{
				cout << "Enter file name: ";
				cin >> skey;
				cout << endl;
				dat->ReadF(skey);
				break;
			}
		case 6:
			{
				cout << "Enter file name: ";
				cin >> skey;
				cout << endl;
				dat->WriteF(skey);
				break;
			}
		case 7:
			{
				delete dat;
				return 0;
			}
		default:
			{
				cout << "Wrong Type! " << endl;
				Type = 0;
			}
		}
	}
	getchar();
	return 0;
}

