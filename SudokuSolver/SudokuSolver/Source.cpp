#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

#include "state.h"

void print(state number[9][9])
{
	for (int e = 0; e < 9; e += 3)
	{
		for (int d = 0; d < 9; d += 3)
		{
			for (int i = 0; i < 3; i++)
			{
				cout << " | ";
				for (int j = 0; j < 3; j++)
				{
					cout << number[i + e][j + d].num << " ";
				}
			}
			cout << endl;
		}
		cout << " -------------------------" << endl;
	}
}

int filldata(state number[9][9],string filename)
{
	int finalnum = 0;
	ifstream openfile;
	openfile.open(filename + ".txt");
	int data = 0;
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
		{
			openfile >> data;
			number[i][j].num = data;
			if (number[i][j].num == 0)
				number[i][j].final = false;
			else
			{
				number[i][j].final = true;
				finalnum++;
			}
		}
	openfile.close();
	return finalnum;
}

void main()
{
	state number[9][9];
	int finalnum = filldata(number,"question");
	int c = 0;
	int ctempnum = 0;
	stringstream tempnum;
	bool reload;
	do
	{
		reload = false;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				number[i][j].posnum.numofposnum = 0;
				for (int k = 1; k <= 9; k++)
				{
					if (!number[i][j].final && !number[i][j].checkinbox(number, i, k) && !number[i][j].checkincol(number, i, j, k) && !number[i][j].checkinrow(number, i, j, k))
					{
						number[i][j].posnum.adddata(k);
					}
				}
			}
		}
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (((c == 3)|| (c==5)) && ctempnum != 0)
				{
					stringstream tempnum;
					tempnum << ctempnum;
					string temp = "temp" + tempnum.str();

					//cout << " return " << temp << " ctemp is " << ctempnum << endl;
					ctempnum--;
					//system("pause");

					finalnum = filldata(number, temp);
					
					if (c == 5)
						c--;
					reload = true;
					break;
				}
				if (!number[i][j].final)
				{
					int m, n, o, p, q, r, s, t;
					number[i][j].rowchanger(i, m, n);
					number[i][j].rowchanger(j, o, p);
					number[i][j].colchanger(i, q, r);
					number[i][j].colchanger(j, s, t);
					for (int a = 1; (a <= number[i][j].posnum.numofposnum) && (!number[i][j].final); a++)
					{
						if (number[i][j].posnum.numofposnum == 1)
						{
							c = 0;
							number[i][j].posnum.cinposdata(number, i, j);
							reload = true;
							finalnum++;
							break;
						}
						
						int z = number[i][j].posnum.returnposnum(a);

						bool posnuminrow1 = (!number[m][j].posnum.check(z, number[m][j].posnum.numofposnum));
						bool posnuminrow2 = (!number[m][o].posnum.check(z, number[m][o].posnum.numofposnum));
						bool posnuminrow3 = (!number[m][p].posnum.check(z, number[m][p].posnum.numofposnum));
						bool posnuminrow4 = (!number[n][j].posnum.check(z, number[n][j].posnum.numofposnum));
						bool posnuminrow5 = (!number[n][o].posnum.check(z, number[n][o].posnum.numofposnum));
						bool posnuminrow6 = (!number[n][p].posnum.check(z, number[n][p].posnum.numofposnum));
						bool posnuminrowinbox1 = (!number[i][o].posnum.check(z, number[i][o].posnum.numofposnum));
						bool posnuminrowinbox2 = (!number[i][p].posnum.check(z, number[i][p].posnum.numofposnum));
						bool posnuminrow = (posnuminrow1 && posnuminrow2 && posnuminrow3 && posnuminrow4 && posnuminrow5 && posnuminrow6);
						bool posnuminrowinbox = (posnuminrowinbox1 && posnuminrowinbox2);

						bool posnumincol1 = (!number[q][j].posnum.check(z, number[q][j].posnum.numofposnum));
						bool posnumincol2 = (!number[q][s].posnum.check(z, number[q][s].posnum.numofposnum));
						bool posnumincol3 = (!number[q][t].posnum.check(z, number[q][t].posnum.numofposnum));
						bool posnumincol4 = (!number[r][j].posnum.check(z, number[r][j].posnum.numofposnum));
						bool posnumincol5 = (!number[r][s].posnum.check(z, number[r][s].posnum.numofposnum));
						bool posnumincol6 = (!number[r][t].posnum.check(z, number[r][t].posnum.numofposnum));
						bool posnumincolinbox1 = (!number[i][s].posnum.check(z, number[i][s].posnum.numofposnum));
						bool posnumincolinbox2 = (!number[i][t].posnum.check(z, number[i][t].posnum.numofposnum));
						bool posnumincol = (posnumincol1 && posnumincol2 && posnumincol3 && posnumincol4 && posnumincol5 && posnumincol6);
						bool posnumincolinbox = (posnumincolinbox1 && posnumincolinbox2);

						bool posnumincolinboxxor = (!posnumincolinbox && (posnumincolinbox1 || posnumincolinbox2));
						bool posnuminrowinboxxor = (!posnuminrowinbox && (posnuminrowinbox1 || posnuminrowinbox2));
						bool posnuminboxxor = (!(posnumincolinboxxor && posnuminrowinboxxor) && (posnumincolinboxxor || posnuminrowinboxxor));
						if (((c == 2) || (c == 4)) && number[i][j].posnum.numofposnum == 2)
						{
							if (c == 4)
							{
								z = number[i][j].posnum.returnposnum(a+1);
								//cout << "retry " << c << " posnumis " << z << endl;
								//system("pause");
							}
							else
							{
								ctempnum++;
								stringstream tempnum;
								tempnum << ctempnum;
								string temp = "temp" + tempnum.str();
								//cout << tempnum.str() << "try " << c << " file created " << temp << " ctemp " << ctempnum << endl;
								//system("pause");
								ofstream writefile;
								writefile.open(temp + ".txt");
								for (int i = 0; i < 9; i++)
									for (int j = 0; j < 9; j++)
										writefile << number[i][j].num << endl;
								writefile.close();
							}
							c = 0;
							number[i][j].num = z;
							number[i][j].final = true;
							number[i][j].posnum.numofposnum = 0;
							finalnum++;

							reload = true;
							/*int y = 0;
							for (int b = 0; b < 9; b++)
							{
								if (!number[i][b].final && number[i][b].posnum.check(z, number[i][b].posnum.numofposnum) && number[i][b].posnum.numofposnum == 2 && j != b)
								{
									y++;
								}
							}
							if (!posnuminrow1)
							{
								if (number[m][j].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnuminrow2)
							{
								if (number[m][o].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnuminrow3)
							{
								if (number[m][p].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnuminrow4)
							{
								if (number[n][j].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnuminrow5)
							{
								if (number[n][o].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnuminrow6)
							{
								if (number[n][p].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnumincol1)
							{
								if (number[q][j].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnumincol2)
							{
								if (number[q][s].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnumincol3)
							{
								if (number[q][t].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnumincol4)
							{
								if (number[r][j].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnumincol5)
							{
								if (number[r][s].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (!posnumincol6)
							{
								if (number[r][t].posnum.numofposnum == 2)
								{
									y++;
								}
							}
							if (y == 1)
							{
								c = 0;
								number[i][j].num = z;
								number[i][j].final = true;
								number[i][j].posnum.numofposnum = 0;
								finalnum++;

								reload = true;
							}*/
						}
						else if ((posnumincol && posnumincolinbox) || (posnuminrow && posnuminrowinbox))
						{
							c = 0;
							number[i][j].num = z;
							number[i][j].final = true;
							number[i][j].posnum.numofposnum = 0;
							finalnum++;

							reload = true;
						}
						else
						{
							int y = 0;
							for (int b = 0; b < 9; b++)
							{
								if (!number[i][b].final && number[i][b].posnum.check(z, number[i][b].posnum.numofposnum))
								{
									y++;
								}
							}
							if (y == 1)
							{
								c = 0;
								number[i][j].num = z;
								number[i][j].final = true;
								number[i][j].posnum.numofposnum = 0;
								finalnum++;

								reload = true;
							}
						}
					}
					if (reload)
						break;
				}
				if (reload)
					break;
			}
			if (reload)
				break;
		}
		c++;
		//print(number);
		//system("pause");
	} while (finalnum != 81 && c != 6);
	if ( c == 6 )
		cout << "cannnot solve" << endl;
	print(number);
	system("pause");
}
