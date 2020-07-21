#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

//what first
//what we have
//	we have 9 9
//  each got its state
//how it run
//	fill?
//	autofill?

//try to write all without debug, 1 time finish, but i cant do it..., logic error occur, i was shocked when debug

//sad me, i fail, i rewrite better

int const outer = 9;
int const inner = 9;
int totalFixed = 0;
int o = 0;
int i = 0;
struct possibleNumber{
	int possibleValue = 0;
	possibleNumber *next = NULL;
};

struct box {
	bool fixed = false;
	int value = 0;
	int totalPossibleNumber = 0;
	possibleNumber *head = NULL;
	possibleNumber *curr = NULL;
	possibleNumber *prev = NULL;
	possibleNumber *scan = NULL;
	bool scanExist(int check)
	{
		scan = head;
		for (int z = 0; z < totalPossibleNumber; z++)
		{
			if (scan->possibleValue == check)
			{
				return true;
			}
			else
			{
				scan = scan->next;
			}
		}
		return false;
	}
	void addPossibleNumber(int number) {
		possibleNumber *pNew = new possibleNumber;
		pNew->possibleValue = number;
		if (totalPossibleNumber == 0)
		{
			head = pNew;
			curr = pNew;
		}
		else
		{
			prev = curr;
			curr->next = pNew;
			curr = pNew;
		}
		totalPossibleNumber++;
	}
	void delPossibleNumber(int number)
	{
		scan = head;
		prev = head;
		for (int z = 0; z < totalPossibleNumber; z++)
		{
			if (scan->possibleValue == number)
			{
				if (scan == head)
				{
					head = head->next;
				}
				else
				{
					prev->next = scan->next;
				}
				totalPossibleNumber--;
				break;
			}
			else
			{
				prev = scan;
				scan = scan->next;
			}
		}
	}
};

void print(box sudoku[outer][inner])
{
	int a = 0;
	int b = 0;
	a = 0;
	b = 0;
	for (int d = 0; d < 3; d++)
	{
		for (int c = 0; c < 3; c++)
		{
			for (o = a; o < a + 3; o++)
			{
				for (i = b; i < b + 3; i++)
				{
					cout << sudoku[o][i].value << " ";
				}
				cout << "| ";
			}
			b += 3;
			cout << endl;
		}
		b = 0;
		cout << endl;
		a += 3;
	}
}

void questionRead(box sudoku[outer][inner])
{
	ifstream openfile;
	openfile.open("question.txt");
	int value = 0;
	for (o = 0; o < outer; o++)
	{
		for (i = 0; i < inner; i++)
		{
			openfile >> value;
			sudoku[o][i].value = value;
			if (sudoku[o][i].value == 0)
			{
				sudoku[o][i].fixed = false;
			}
			else
			{
				sudoku[o][i].fixed = true;
				totalFixed++;
			}
		}
	}
	openfile.close();
}

bool checkExistInnerBox(box sudoku[outer][inner], int number)
{
	for (int s = 0; s < inner ; s++)
	{
		if (s != i )
		{
			if (sudoku[o][s].value == number)
			{
				//cout << o << s << sudoku[o][s].value << number << "true" << endl;
				return true;
			}
		}
		//cout << o << s << sudoku[o][s].value << number << "false" << endl;
	}
	return false;
}

bool checkExistOuterXBox(box sudoku[outer][inner], int number)
{
	for (int b = (o / 3) * 3; b < (o / 3) * 3 + 3 ; b++)
	{
		for (int s = (i / 3) * 3; s < (i / 3) * 3 + 3; s++)
		{
			if (b != o && s != i)
			{
				if (sudoku[b][s].value == number)
				{
					//cout << b << s << sudoku[b][s].value << number << "true" << endl;
					return true;
				}
				//cout << b << s << sudoku[b][s].value << number << "false" << endl;
			}
		}
	}
	return false;
}

bool checkExistOuterYBox(box sudoku[outer][inner],int number)
{
	for (int b = o % 3; b < outer; b+=3)
	{
		for (int s = i % 3; s < inner; s += 3)
		{
			if (b != o && s != i)
			{
				if (sudoku[b][s].value == number)
				{
					//cout << b << s << sudoku[b][s].value << number << "true" << endl;
					return true;
				}
				//cout << b << s << sudoku[b][s].value << number << "false" << endl;
			}
		}
	}
	return false;
}

void fillAllPossibleValue(box sudoku[outer][inner])
{
	int value = 0;
	for (value = 1; value <= 9; value++)
	{
		for (o = 0; o < outer; o++)
		{
			for (i = 0; i < inner;)
			{
				if (sudoku[o][i].fixed == false)
				{
					if (checkExistInnerBox(sudoku, value))
					{
						i = 0;
						break;
					}
					else
					{
						if (checkExistOuterXBox(sudoku, value))
						{
							i = ((i / 3) + 1) * 3;
							cout << i << endl;
						}
						else
						{
							if (checkExistOuterYBox(sudoku, value))
							{
								i++;
							}
							else
							{
								sudoku[o][i].addPossibleNumber(value);
								i++;
							}
							//else cant skip next 1 but want to skip next 2
						}
					}
				}
			}
		}
	}
}

void delOtherBoxPossibleValue(box sudoku[outer][inner], int value)
{
	for (int s = 0; s < inner ; s++)
	{
		if (s != i)
		{
			if (sudoku[o][s].fixed == false)
			{
				sudoku[o][s].delPossibleNumber(value);
			}
		}
	}
	for (int b = (o / 3) * 3; b < (o / 3) * 3 + 3 ; b++)
	{

		for (int s = (i / 3) * 3; s < (i / 3) * 3 + 3; s++)
		{
			if (b != o)
			{
				if (sudoku[b][s].fixed == false)
				{
					sudoku[b][s].delPossibleNumber(value);
				}
			}
		}
	}
	for (int b = o % 3; b < outer ; b += 3)
	{
		for (int s = i % 3; s < inner; s += 3)
		{
			if (b != o)
			{
				if (sudoku[b][s].fixed == false)
				{
					sudoku[b][s].delPossibleNumber(value);
				}
			}
		}
	}
}

void fixTheOnlyPossibleValue(box sudoku[outer][inner])
{
	bool found = true;
	bool repeat = false;
	do
	{
		repeat = false;
		for (o = 0; o < outer; o++)
		{
			for (i = 0; i < inner; i++)
			{
				if (sudoku[o][i].fixed == false)
				{
					sudoku[o][i].curr = sudoku[o][i].head;
					for (int g = 0; g < sudoku[o][i].totalPossibleNumber; g++)
					{
						found = true;
						if (found == true)
						{
							for (int s = 0; s < inner; s++)
							{
								if (s != i)
								{
									if (sudoku[o][s].fixed == false && sudoku[o][s].scanExist(sudoku[o][i].curr->possibleValue))
									{
										found = true;
										break;
									}
									found = false;
								}
							}
						}
						if (found == true)
						{
							for (int b = (o / 3) * 3; b < (o / 3) * 3 + 3; b++)
							{
								for (int s = (i / 3) * 3; s < (i / 3) * 3 + 3; s++)
								{
									if (b != o && s != i)
									{
										if (sudoku[b][s].fixed == false && sudoku[b][s].scanExist(sudoku[o][i].curr->possibleValue))
										{
											found = true;
											break;
										}
										found = false;
									}
								}
								if(found)
								{
									break;
								}
							}
						}
						if (found == true)
						{
							for (int b = o % 3; b < outer; b += 3)
							{
								for (int s = i % 3; s < inner; s += 3)
								{
									if (b != o && s != i)
									{
										if (sudoku[b][s].fixed == false && sudoku[b][s].scanExist(sudoku[o][i].curr->possibleValue))
										{
											found = true;
											break;
										}
										found = false;
									}
								}
								if (found)
								{
									break;
								}
							}
						}
						if (found == false)
						{
							sudoku[o][i].value = sudoku[o][i].curr->possibleValue;
							sudoku[o][i].fixed = true;
							repeat = true;
							totalFixed++;
							delOtherBoxPossibleValue(sudoku, sudoku[o][i].value);
							break;
						}
						else
						{
							sudoku[o][i].curr = sudoku[o][i].curr->next;
						}
					}
				}
			}
		}
	} while (repeat == true);
}

void fixMorePossibleValue(box sudoku[outer][inner])
{
	for (o = 0; o < outer; o++)
	{
		for (i = 0; i < inner;)
		{
			if (sudoku[o][i].fixed == true)
			{
				i++;
			}
			else
			{
				sudoku[o][i].value ++;
				print(sudoku);
				if (sudoku[o][i].value >= 10)
				{
					sudoku[o][i].value = 0;
					do
					{
						i--;
						if (i<0)
						{
							o--;
							if (o<0)
							{
								cout << "\n\nNo solution\n";
								system("pause");
							}
							else
							{
								i = 8;
							}
						}
					}
					while (sudoku[o][i].fixed == true);
				}
				else
				{
					if (!checkExistInnerBox(sudoku, sudoku[o][i].value))
					{
						if (!checkExistOuterXBox(sudoku, sudoku[o][i].value) && !checkExistOuterYBox(sudoku, sudoku[o][i].value))
						{
							i++;
						}
					}
				}
			}
		}
	}
}



//int main()
//{
//	cout << "=== Sudoku Autofill ===\n\n";
//	box sudoku[outer][inner];
//	questionRead(sudoku);
//	print(sudoku);
//	system("pause");
//	fillAllPossibleValue(sudoku);
//	fixTheOnlyPossibleValue(sudoku);
//	print(sudoku);
//	system("pause");
//	fixMorePossibleValue(sudoku);
//	print(sudoku);
//	system("pause");
//	return 0;
//}