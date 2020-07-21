#include <iostream>
#include "state.h"

using namespace std;

state::state()
{
	num = 0;
	final = false;
}

state::~state()
{}

bool state::checkinbox(state number[9][9], int i, int k)
{
	for (int j = 0; j < 9; j++)
	{
		if (number[i][j].num == k)
		{
			return true;
		}
	}
	return false;
}

void state::colchanger(int &l, int &m, int &n)
{
	if (l < 3)
	{
		m = l + 3;
		n = l + 6;
	}
	else if (l >= 3 && l < 6)
	{
		m = l - 3;
		n = l + 3;
	}
	else if (l >= 6)
	{
		m = l - 6;
		n = l - 3;
	}
}

void state::rowchanger(int &l, int &m, int &n)
{
	if (l == 0 || l == 3 || l == 6)
	{
		m = l + 1;
		n = l + 2;
	}
	else if (l == 1 || l == 4 || l == 7)
	{
		m = l - 1;
		n = l + 1;
	}
	else
	{
		m = l - 2;
		n = l - 1;
	}
}

bool state::checkincol(state number[9][9], int i, int j, int k)
{
	int a, b, c, d;
	colchanger(i, a, b);
	colchanger(j, c, d);
	if (number[a][j].num == k || number[a][c].num == k || number[a][d].num == k || number[b][j].num == k || number[b][c].num == k || number[b][d].num == k)
		return true;
	else
		return false;
}

bool state::checkinrow(state number[9][9], int i, int j, int k)
{
	int a, b, c, d;
	rowchanger(i, a, b);
	rowchanger(j, c, d);
	if (number[a][j].num == k || number[a][c].num == k || number[a][d].num == k || number[b][j].num == k || number[b][c].num == k || number[b][d].num == k)
		return true;
	else
		return false;
}


state::posnum::posnum()
{
	pHead = 0;
	numofposnum = 0;
	pCurr = 0;
	pPrev = 0;
}

state::posnum::~posnum()
{}

void state::posnum::adddata(int k)
{
	list *pNew = new list;
	pNew->data = k;
	if (numofposnum == 0)
	{
		pHead = 0;
		pNew->link = pHead;
		pHead = pNew;
		pCurr = pHead;
	}
	else
	{
		pNew->link = pCurr->link;
		pCurr->link = pNew;
		pCurr = pNew;
	}
	numofposnum++;
	cout << "numberofpossibledata  " << numofposnum << endl;
}

int state::posnum::returnposnum(int a)
{
	pCurr = pHead;
	for (int i = 1; i < a; i++)
	{
		pCurr = pCurr->link;
	}
	return pCurr->data;
}

bool state::posnum::check(int data, int a)
{
	if (a != 0)
	{
		pCurr = pHead;
		if (a == 1)
		{
			pPrev = pHead;
		}
		do
		{
			if (pCurr->data == data)
			{
				return true;
			}
			else
			{
				pPrev = pCurr;
				pCurr = pCurr->link;
			}
		} while (pCurr != 0);
		return false;
	}
	else
	{
		return false;
	}
}

void state::posnum::deletedata()
{
	if (pCurr == pHead)
	{
		pCurr = pHead->link;
		pPrev = pHead->link;
		pHead = pHead->link;
	}
	else
	{
		pPrev->link = pCurr->link;
	}
	numofposnum--;
}

void state::posnum::cinposdata(state number[9][9], int i, int j)
{
	number[i][j].num = pHead->data;
	number[i][j].final = true;
	numofposnum = 0;
}