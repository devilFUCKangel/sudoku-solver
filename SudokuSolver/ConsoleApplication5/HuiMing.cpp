#include <iostream>
#include <fstream>
using namespace std;

struct InnerBlock	//j
{
	bool status;
	int value;
};

struct OuterBlock	//i
{
	InnerBlock Inner[9];
};

char display(const int value)
{
	return ((value == 0) ? ' ' : static_cast<char>(value + 48));
}

void checky(const int no, int& no1, int& no2)
{
	if (no >= 0 && no <= 2)
	{
		no1 = no + 3;
		no2 = no + 6;
	}
	if (no >= 3 && no <= 5)
	{
		no1 = no - 3;
		no2 = no + 3;
	}
	if (no >= 6 && no <= 8)
	{
		no1 = no - 3;
		no2 = no - 6;
	}
}

void checkx(const int no, int& no1, int& no2)
{
	if (no == 0 || no == 3 || no == 6)
	{
		no1 = no + 1;
		no2 = no + 2;
	}
	if (no == 1 || no == 4 || no == 7)
	{
		no1 = no - 1;
		no2 = no + 1;
	}
	if (no == 2 || no == 5 || no == 8)
	{
		no1 = no - 1;
		no2 = no - 2;
	}
}

bool xy_valid(const OuterBlock Outer[9], const int j0, const int value, const int o1, const int o2, const int i1, const int i2)
{
	return ((Outer[o1].Inner[j0].value == value || Outer[o1].Inner[i1].value == value || Outer[o1].Inner[i2].value == value || Outer[o2].Inner[j0].value == value || Outer[o2].Inner[i1].value == value || Outer[o2].Inner[i2].value == value) ? false : true);
}

bool inner_valid(const OuterBlock Outer[9], const int i, const int skipped, const int value)
{
	for (int j = 0; j<9; j++)
	{
		if (Outer[i].Inner[j].value == value && j != skipped)
			return false;
	}
	return true;
}


void main()
{
	OuterBlock Outer[9];
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			Outer[i].Inner[j].status = false;
			Outer[i].Inner[j].value = 0;
		}
	}
	cout << "=== Sudoku Autofill ===\n\n";
	ifstream ind;
	ind.open("in.txt");
	bool next = true;
	do
	{
		int fixed, fixedi, fixedj;
		ind >> fixed >> fixedi >> fixedj;
		next = false;
		if (ind)
		{
			fixedi -= 1;
			fixedj -= 1;
			bool valid = inner_valid(Outer, fixedi, fixedj, fixed);
			int o1, o2, i1, i2;
			checky(fixedi, o1, o2);
			checky(fixedj, i1, i2);
			bool validy = xy_valid(Outer, fixedj, fixed, o1, o2, i1, i2);
			checkx(fixedi, o1, o2);
			checkx(fixedj, i1, i2);
			bool validx = xy_valid(Outer, fixedj, fixed, o1, o2, i1, i2);
			if ((validx && validy && valid) == true)
			{
				Outer[fixedi].Inner[fixedj].value = fixed;
				Outer[fixedi].Inner[fixedj].status = true;
			}
			else
				cout << "	" << fixed << " = " << fixedi << " " << fixedj << "	[Error]" << endl;
			next = true;
		}
	} while (next);
	ind.close();

	cout << "\n\nFixed number:\n";
	for (int i = 0; i<9; i++)
	{
		for (int j = 0; j<9; j++)
		{
			if (Outer[i].Inner[j].status)
				cout << "		" << Outer[i].Inner[j].value << " = " << i + 1 << " " << j + 1 << endl;
		}
	}

	cout << "\n\nQuestion:\n";

	for (int i = 0; i<9; i += 3)
	{
		for (int j = 0; j<9; j += 3)
		{
			if (j == 0 && i == 0)
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "| " << display(Outer[i].Inner[j].value) << " " << display(Outer[i].Inner[j + 1].value) << " " << display(Outer[i].Inner[j + 2].value) << " | " << display(Outer[i + 1].Inner[j].value) << " " << display(Outer[i + 1].Inner[j + 1].value) << " " << display(Outer[i + 1].Inner[j + 2].value) << " | " << display(Outer[i + 2].Inner[j].value) << " " << display(Outer[i + 2].Inner[j + 1].value) << " " << display(Outer[i + 2].Inner[j + 2].value) << " |" << endl;
			if (j == 6)
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
	}

	cout << endl << endl;
	system("pause");

	for (int i = 0; i<9; i++)
	{//1
		for (int j = 0; j<9;)
		{//2
			cout << i + 1 << j + 1 << "	";
			if (Outer[i].Inner[j].status)
				j++;
			else
			{//3
				Outer[i].Inner[j].value += 1;
				if (Outer[i].Inner[j].value >= 10)
				{//4
					Outer[i].Inner[j].value = 0;
					do
					{//5
						j--;
						if (j<0)
						{
							i--;
							if (i<0)
							{
								cout << "\n\nNo solution\n";
								system("pause");
								exit(0);
							}
							else
								j = 8;
						}
					}//5
					while (Outer[i].Inner[j].status);
				}//4
				else
				{//4
					bool valid = inner_valid(Outer, i, j, Outer[i].Inner[j].value);
					if (valid)
					{//5
					 //continue to outer x and y
						int o1, o2, i1, i2;
						checky(i, o1, o2);
						checky(j, i1, i2);
						bool validy = xy_valid(Outer, j, Outer[i].Inner[j].value, o1, o2, i1, i2);
						checkx(i, o1, o2);
						checkx(j, i1, i2);
						bool validx = xy_valid(Outer, j, Outer[i].Inner[j].value, o1, o2, i1, i2);
						if ((validx && validy) == true)
							j++;
					}//5
				}//4
			}//3
		}//2
	}
	cout << "\n\n\n\n";
	cout << "Solution:\n\n";

	for (int i = 0; i<9; i += 3)
	{
		for (int j = 0; j<9; j += 3)
		{
			if (j == 0 && i == 0)
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
			cout << "| " << Outer[i].Inner[j].value << " " << Outer[i].Inner[j + 1].value << " " << Outer[i].Inner[j + 2].value << " | " << Outer[i + 1].Inner[j].value << " " << Outer[i + 1].Inner[j + 1].value << " " << Outer[i + 1].Inner[j + 2].value << " | " << Outer[i + 2].Inner[j].value << " " << Outer[i + 2].Inner[j + 1].value << " " << Outer[i + 2].Inner[j + 2].value << " |" << endl;
			if (j == 6)
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		}
	}

	system("pause");
	exit(0);
}