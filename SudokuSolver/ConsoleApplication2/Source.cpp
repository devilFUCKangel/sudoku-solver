#include <iostream>
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
				for (int j = 0; j < 3; j++)
				{
					cout << number[i + e][j + d].num << "|";
				}
				cout << "\t";
			}
			cout << endl;
		}
	}
}

int filldata(state number[9][9])
{
	int finalnum = 0;
	ifstream openfile;
	openfile.open("question.txt");
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
	int finalnum = filldata(number);
	cout << finalnum << endl;
	int adding = 0;
	int c = 0;
	bool reload;
	do
	{
		reload = false;
		/*do
		{
			reload = false;*/
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					number[i][j].posnum.numofposnum = 0;
					for (int k = 1; k <= 9; k++)
					{
						adding++;
						cout << adding << endl;
						if (!number[i][j].final && !number[i][j].checkinbox(number, i, k) && !number[i][j].checkincol(number, i, j, k) && !number[i][j].checkinrow(number, i, j, k))
						{
							number[i][j].posnum.adddata(k);
							adding++;
							cout << adding << endl;
						}
					}
					/*if (number[i][j].posnum.numofposnum == 1)
					{
						number[i][j].posnum.cinposdata(number, i, j);
						finalnum++;
						reload = true;
						break;
					}*/
				}
				/*if (reload)
				{
					break;
				}*/
			}
		/*} while (reload);*/
		print(number);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
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
						int d = 0;
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

						if (c == 2)
						{
							print(number);
							int y = 0;
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
									cout << m << j << endl;
									y++;
									system("pause");
								}
							}
							if (!posnuminrow2)
							{
								if (number[m][o].posnum.numofposnum == 2)
								{
									cout << m << n << endl;
									y++;
									system("pause");
								}
							}
							if (!posnuminrow3)
							{
								if (number[m][p].posnum.numofposnum == 2)
								{
									cout << m << p << endl;
									y++;
									system("pause");
								}
							}
							if (!posnuminrow4)
							{
								if (number[n][j].posnum.numofposnum == 2)
								{
									cout << n << j << endl;
									y++;
									system("pause");
								}
							}
							if (!posnuminrow5)
							{
								if (number[n][o].posnum.numofposnum == 2)
								{
									cout << n << o << endl;
									y++;
									system("pause");
								}
							}
							if (!posnuminrow6)
							{
								if (number[n][p].posnum.numofposnum == 2)
								{
									cout << n << n << endl;
									y++;
									system("pause");
								}
							}
							if (!posnumincol1)
							{
								if (number[q][j].posnum.numofposnum == 2)
								{
									cout << q << j << endl;
									y++;
									system("pause");
								}
							}
							if (!posnumincol2)
							{
								if (number[q][s].posnum.numofposnum == 2)
								{
									cout << q << s << endl;
									y++;
									system("pause");
								}
							}
							if (!posnumincol3)
							{
								if (number[q][t].posnum.numofposnum == 2)
								{
									cout << q << t << endl;
									y++;
									system("pause");
								}
							}
							if (!posnumincol4)
							{
								if (number[r][j].posnum.numofposnum == 2)
								{
									cout << r << j << endl;
									y++;
									system("pause");
								}
							}
							if (!posnumincol5)
							{
								if (number[r][s].posnum.numofposnum == 2)
								{
									cout << r << s << endl;
									y++;
									system("pause");
								}
							}
							if (!posnumincol6)
							{
								if (number[r][t].posnum.numofposnum == 2)
								{
									cout << r << t << endl;
									y++;
									system("pause");
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
								break;
								//print(number);
								//system("pause");

								/*for (int b = 0; b < 9; b++)
								{
									if (!number[i][b].final && number[i][b].posnum.check(z, number[i][b].posnum.numofposnum))
									{
										number[i][b].posnum.deletedata();
									}
								}

								if (posnumincol && posnumincolinbox)
								{
									if (!posnuminrow1)
									{
										cout << m << j << endl;
										number[m][j].posnum.deletedata();
									}
									if (!posnuminrow2)
									{
										cout << m << o << endl;
										number[m][o].posnum.deletedata();
									}
									if (!posnuminrow3)
									{
										cout << m << p << endl;
										number[m][p].posnum.deletedata();
									}
									if (!posnuminrow4)
									{
										cout << n << j << endl;
										number[n][j].posnum.deletedata();
									}
									if (!posnuminrow5)
									{
										cout << n << o << endl;
										number[n][o].posnum.deletedata();
									}
									if (!posnuminrow6)
									{
										cout << n << p << endl;
										number[n][p].posnum.deletedata();
									}
								}
								if (posnuminrow && posnuminrowinbox)
								{
									if (!posnumincol1)
									{
										cout << q << j << endl;
										number[q][j].posnum.deletedata();
									}
									if (!posnumincol2)
									{
										cout << q << s << endl;
										number[q][s].posnum.deletedata();
									}
									if (!posnumincol3)
									{
										cout << q << t << endl;
										number[q][t].posnum.deletedata();
									}
									if (!posnumincol4)
									{
										cout << r << j << endl;
										number[r][j].posnum.deletedata();
									}
									if (!posnumincol5)
									{
										cout << r << s << endl;
										number[r][s].posnum.deletedata();
									}
									if (!posnumincol6)
									{
										cout << r << t << endl;
										number[r][t].posnum.deletedata();
									}
								}*/
							}
						
							/*if (!posnuminrow)
							{
								if (!posnuminrow1)
								{
									if (number[m][j].posnum.numofposnum == 2)
									{
										cout << m << j << endl;
										d++;
										system("pause");
									}
								}
								if (!posnuminrow2)
								{
									if (number[m][o].posnum.numofposnum == 2)
									{
										cout << m << n << endl;
										d++;
										system("pause");
									}
								}
								if (!posnuminrow3)
								{
									if (number[m][p].posnum.numofposnum == 2)
									{
										cout << m << p << endl;
										d++;
										system("pause");
									}
								}
								if (!posnuminrow4)
								{
									if (number[n][j].posnum.numofposnum == 2)
									{
										cout << n << j << endl;
										d++;
										system("pause");
									}
								}
								if (!posnuminrow5)
								{
									if (number[n][o].posnum.numofposnum == 2)
									{
										cout << n << o << endl;
										d++;
										system("pause");
									}
								}
								if (!posnuminrow6)
								{
									if (number[n][p].posnum.numofposnum == 2)
									{
										cout << n << n << endl;
										d++;
										system("pause");
									}
								}
							}
							if (!posnumincol)
							{
								if (!posnumincol1)
								{
									if (number[q][j].posnum.numofposnum == 2)
									{
										cout << q << j << endl;
										d++;
										system("pause");
									}
								}
								if (!posnumincol2)
								{
									if (number[q][s].posnum.numofposnum == 2)
									{
										cout << q << s << endl;
										d++;
										system("pause");
									}
								}
								if (!posnumincol3)
								{
									if (number[q][t].posnum.numofposnum == 2)
									{
										cout << q << t << endl;
										d++;
										system("pause");
									}
								}
								if (!posnumincol4)
								{
									if (number[r][j].posnum.numofposnum == 2)
									{
										cout << r << j << endl;
										d++;
										system("pause");
									}
								}
								if (!posnumincol5)
								{
									if (number[r][s].posnum.numofposnum == 2)
									{
										cout << r << s << endl;
										d++;
										system("pause");
									}
								}
								if (!posnumincol6)
								{
									if (number[r][t].posnum.numofposnum == 2)
									{
										cout << r << t << endl;
										d++;
										system("pause");
									}
								}
							}
							if (!posnuminrowinbox)
							{
								if (!posnuminrowinbox1)
								{
									if (number[i][o].posnum.numofposnum == 2)
									{
										cout << i << o << endl;
										d++;
										system("pause");
									}
								}
								if (!posnuminrowinbox2)
								{
									if (number[i][p].posnum.numofposnum == 2)
									{
										cout << i << p << endl;
										d++;
										system("pause");
									}
								}
							}
							if (!posnumincolinbox)
							{
								if (!posnumincolinbox1)
								{
									if (number[i][s].posnum.numofposnum == 2)
									{
										cout << i << s << endl;
										d++;
										system("pause");
									}
								}
								if (!posnumincolinbox2)
								{
									if (number[i][t].posnum.numofposnum == 2)
									{
										cout << i << t << endl;
										d++;
										system("pause");
									}
								}
							}
							if (d == 1)
							{
								c = 0;
								number[i][j].num = z;
								number[i][j].final = true;
								number[i][j].posnum.numofposnum = 0;
								finalnum++;
								for (int b = 0; b < 9; b++)
								{
									if (!number[i][b].final)
									{
										if (number[i][b].posnum.check(z, number[i][b].posnum.numofposnum))
										{
											number[i][b].posnum.deletedata();
										}
									}
								}
							}
							cout << i << j << z << d << endl;*/
							//system("pause");
						}
						else if ((posnumincol && posnumincolinbox) || (posnuminrow && posnuminrowinbox))
						{
							c = 0;
							number[i][j].num = z;
							number[i][j].final = true;
							number[i][j].posnum.numofposnum = 0;
							finalnum++;

							reload = true;
							break;

							for (int b = 0; b < 9; b++)
							{
								if (!number[i][b].final)
								{
									if (number[i][b].posnum.check(z, number[i][b].posnum.numofposnum))
									{
										number[i][b].posnum.deletedata();
									}
								}
							}
							if (posnumincol && posnumincolinbox)
							{
								if (!posnuminrow1)
								{
									cout << m << j << endl;
									number[m][j].posnum.deletedata();
								}
								if (!posnuminrow2)
								{
									cout << m << o << endl;
									number[m][o].posnum.deletedata();
								}
								if (!posnuminrow3)
								{
									cout << m << p << endl;
									number[m][p].posnum.deletedata();
								}
								if (!posnuminrow4)
								{
									cout << n << j << endl;
									number[n][j].posnum.deletedata();
								}
								if (!posnuminrow5)
								{
									cout << n << o << endl;
									number[n][o].posnum.deletedata();
								}
								if (!posnuminrow6)
								{
									cout << n << p << endl;
									number[n][p].posnum.deletedata();
								}
							}
							if (posnuminrow && posnuminrowinbox)
							{
								if (!posnumincol1)
								{
									cout << q << j << endl;
									number[q][j].posnum.deletedata();
								}
								if (!posnumincol2)
								{
									cout << q << s << endl;
									number[q][s].posnum.deletedata();
								}
								if (!posnumincol3)
								{
									cout << q << t << endl;
									number[q][t].posnum.deletedata();
								}
								if (!posnumincol4)
								{
									cout << r << j << endl;
									number[r][j].posnum.deletedata();
								}
								if (!posnumincol5)
								{
									cout << r << s << endl;
									number[r][s].posnum.deletedata();
								}
								if (!posnumincol6)
								{
									cout << r << t << endl;
									number[r][t].posnum.deletedata();
								}
							}
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
								break;

								/*if (!posnuminrow)
								{
									if (!posnuminrow1)
									{
										cout << m << j << endl;
										number[m][j].posnum.deletedata();
									}
									if (!posnuminrow2)
									{
										cout << m << o << endl;
										number[m][o].posnum.deletedata();
									}
									if (!posnuminrow3)
									{
										cout << m << p << endl;
										number[m][p].posnum.deletedata();
									}
									if (!posnuminrow4)
									{
										cout << n << j << endl;
										number[n][j].posnum.deletedata();
									}
									if (!posnuminrow5)
									{
										cout << n << o << endl;
										number[n][o].posnum.deletedata();
									}
									if (!posnuminrow6)
									{
										cout << n << p << endl;
										number[n][p].posnum.deletedata();
									}
								}
								if (!posnumincol)
								{
									if (!posnumincol1)
									{
										cout << q << j << endl;
										number[q][j].posnum.deletedata();
									}
									if (!posnumincol2)
									{
										cout << q << s << endl;
										number[q][s].posnum.deletedata();
									}
									if (!posnumincol3)
									{
										cout << q << t << endl;
										number[q][t].posnum.deletedata();
									}
									if (!posnumincol4)
									{
										cout << r << j << endl;
										number[r][j].posnum.deletedata();
									}
									if (!posnumincol5)
									{
										cout << r << s << endl;
										number[r][s].posnum.deletedata();
									}
									if (!posnumincol6)
									{
										cout << r << t << endl;
										number[r][t].posnum.deletedata();
									}
								}*/
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
		cout << c << endl;
		print(number);
		system("pause");
	} while (finalnum != 81 && c != 3);
	cout << "final"<<  endl;
	print(number);
	system("pause");
}
