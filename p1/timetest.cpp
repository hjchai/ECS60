//author Huajun Chai, 998584845
#include <iostream>
#include "CPUTimer.h"
#include "dsexceptions.h"
#include "LinkedList.h"
#include "StackAr.h"
#include "CursorList.h"
#include "QueueAr.h"
#include "StackLi.h"
#include "vector.h"
#include "SkipList.h"
#include <fstream>
#include <string>

static const int Max_Num = 250000;

vector<CursorNode <int> > cursorSpace(Max_Num);

int getChoice();
void RunList(string s)
{
	ifstream in (s.c_str());
	string skip;
	char index;
	int number;
	getline(in,skip);
	List<int> llist;
	ListItr<int> itr = llist.zeroth();
	while(in >> index >> number)
	{
		if(index == 'i') 
		{
			llist.insert(number,itr);
		}
		else
			llist.remove(number);
	}		
}
void RunCursorList(string s)
{
	ifstream in (s.c_str());
	string skip;
	char index;
	int number;
	getline(in,skip);
	CursorList<int> cursel(cursorSpace);
	CursorListItr<int> itr = cursel.zeroth();
	while(in >> index >> number)
	{
		if(index == 'i') {
			cursel.insert(number,itr);
		}
		else
			cursel.remove(number);		
	}
}
void RunStackAr(string s)
{
	ifstream in (s.c_str());
	string skip;
	char index;
	int number;
	getline(in,skip);
	StackAr<int> stacka(Max_Num);
	while(in >> index >> number)
	{
		if(index == 'i') 
		{
			stacka.push(number);
		}
		else
			stacka.pop();		
	}
}
void RunStackLi(string s)
{
	ifstream in (s.c_str());
	string skip;
	char index;
	int number;
	getline(in,skip);
	StackLi<int> stackl;
	while(in >> index >> number)
	{
		if(index == 'i') 
		{
			stackl.push(number);
		}
		else
			stackl.pop();		
	}
}
void RunQueueAr(string s)
{
	ifstream in (s.c_str());
	string skip;
	char index;
	int number;
	getline(in,skip);
	Queue<int> queuear(Max_Num);
	while(in >> index >> number)
	{
		if(index == 'i') 
		{
			queuear.enqueue(number);
		}
		else
			queuear.dequeue();		
	}
}
void RunSkipList(string s)
{
	ifstream in (s.c_str());
	string skip;
	char index;
	int number;
	getline(in,skip);
	SkipList<int> skipl(1,Max_Num);
	while(in >> index >> number)
	{
		if(index == 'i') 
		{
			skipl.insert(number);
		}
		else
			skipl.deleteNode(number);		
	}
}

void menu()
{
	cout << "	ADT Menu" << endl;
	cout << "0. Quit" << endl;
	cout << "1. LinkedList" << endl;
	cout << "2. CursorList" << endl;
	cout << "3. StackAr" << endl;
	cout << "4. StackLi" << endl;
	cout << "5. QueueAr" << endl;
	cout << "6. SkipList" << endl;
}

using namespace std;

int main()
{
	int choice;
	string filename;
	cout << "Filename >> ";
	cin >> filename;
	CPUTimer ct;
	
	do
	{
		menu();
		choice = getChoice();
		ct.reset();

		switch (choice)
		{
			case 1: RunList(filename); break;
			case 2: RunCursorList(filename); break;
			case 3: RunStackAr(filename); break;
			case 4: RunStackLi(filename); break;
			case 5: RunQueueAr(filename); break;
			case 6: RunSkipList(filename); break; 
		}
		
		cout << "CPU time: " << ct.cur_CPUTime() << endl;
	} while(choice > 0);
	return 0;
}

int getChoice()
{
		cout << "Your choice >> ";
		int choice;
		cin >> choice;
		return choice;
}
