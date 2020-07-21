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
	//system("pause");
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

		for (int i = 0; i < 9; i++)
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
			}
		print(number);
		//int locicheck = 0;
		//int locjcheck = 0;
		//int keepinext = 0;
		//int keepjnext = 0;
		//int lowestposnum = 0;
		//int samei = 0;
		//int samej = 0;
		//int loci = 0;
		//int locj = 0;
		//bool fail = true;

		

		do
		{
			//lowestposnum = 0;
			//bool same = false;
			//int comparing = 0;
			for (int i = 0; i < 9; i++)
			{
				for (int j = 0; j < 9; j++)
				{
					//comparing++;
					//cout << comparing << endl;
					if (!number[i][j].final)
					{

						cout << "location" << i << " " << j << endl;
						cout << number[i][j].posnum.numofposnum << endl;
						cout << "step start" << endl;
						//system("pause");

						int m, n, o, p, q, r, s, t;

						number[i][j].rowchanger(i, m, n);
						number[i][j].rowchanger(j, o, p);
						cout << "step1" << i << m << n << j << o << p << endl;
						number[i][j].colchanger(i, q, r);
						number[i][j].colchanger(j, s, t);
						cout << "step2" << i << q << r << j << s << t << endl;

						for (int a = 1; a <= number[i][j].posnum.numofposnum && !number[i][j].final; a++)
						{
							int z = number[i][j].posnum.returnposnum(a);
							cout << "step3" << number[i][j].posnum.numofposnum << a << z << endl;
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
							cout << "check in col" << endl;
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
							cout << posnumincol1 << posnumincol2 << posnumincol3 << posnumincol4 << posnumincol5 << posnumincol6 << endl;
							bool posnumincolinboxxor = (!posnumincolinbox && (posnumincolinbox1 || posnumincolinbox2));
							bool posnuminrowinboxxor = (!posnuminrowinbox && (posnuminrowinbox1 || posnuminrowinbox2));
							bool posnuminboxxor = (!(posnumincolinboxxor && posnuminrowinboxxor ) && (posnumincolinboxxor || posnuminrowinboxxor));


							cout << "step4" << endl << posnuminrow << posnumincol << endl << posnuminrowinbox << posnumincolinbox << endl;
							//system("pause");
							/*if (posnuminrow || posnumincol)
							{
								//system("pause");
							}*/

							
							if ((posnumincol && posnumincolinbox)||(posnuminrow && posnuminrowinbox))
							{
								c = 0;
								number[i][j].num = z;
								number[i][j].final = true;
								number[i][j].posnum.numofposnum = 0;
								finalnum++;
								cout << "step 5.1 final num " << finalnum << " location " << i << j << "number" << z << endl;
								//system("pause");
								for (int b = 0; b < 9; b++)
								{
									if (!number[i][b].final)
									{
										//cout << "location " << i << b << "numofposnum is " << number[i][b].posnum.numofposnum << "ponum is " << number[i][b].posnum.returnposnum(a) << endl;
										//system("pause");
										if (number[i][b].posnum.check(z, number[i][b].posnum.numofposnum))
										{
											cout << "deleted" << endl;
											number[i][b].posnum.deletedata();
											//loci = 0;
											//locj = 0;
											//locicheck = 0;
											//locjcheck = 0;
										}

									}
								}
								if (!posnuminrow)
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
									cout << "step 5.2 final num " << finalnum << " location " << i << j << "number" << z << endl;
									//system("pause");
									if (!posnuminrow)
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
									}
									
								}
							}
					
						}
					}
					//if (number[i][j].posnum.numofposnum == 1)
					//{
					//	number[i][j].posnum.cinposdata(number, i, j);
					//	//lowestposnum = 0;
					//	finalnum++;
					//	//system("pause");
					//}


					/*if (lowestposnum == 0)
					{
						lowestposnum = number[i][j].posnum.numofposnum;
					}

					else if (lowestposnum > number[i][j].posnum.numofposnum)
					{
						lowestposnum = number[i][j].posnum.numofposnum;
						loci = i;
						locj = j;
						same = false;
						locicheck = i;
						locjcheck = j;
					}
					else if (lowestposnum == number[i][j].posnum.numofposnum )
					{
						if (fail && samei != i && samej != j && locicheck != i && locjcheck != j)
						{
							loci = i;
							loci = j;
							locicheck = i;
							locjcheck = j;
							break;
						}
						else
						{
							samei = i;
							samej = j;
						}
					}
					else
					{
						keepinext = i;
						keepjnext = j;
					}*/

				}
			}
			c++;
			cout << "retry" << c << endl;
			//print(number);

			//system("pause");
		
	} while (finalnum != 81 && c != 2);

	print(number);

}
