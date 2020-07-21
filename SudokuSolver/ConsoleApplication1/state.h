#ifndef STATE_H
#define STATE_H

class state
{
public:

	int num;
	bool final;
	class posnum
	{
	private:
		class list
		{
		public:
			int data;
			list *link;
		};
		list *pHead;
		list *pCurr;
		list *pPrev;

	public:
		posnum();
		~posnum();
		int returnposnum(int a);
		bool check(int data,int a);
		void adddata(int k);
		void deletedata();
		void cinposdata(state number[9][9], int i, int j);
		int numofposnum;
	};
	posnum posnum;
	state();
	~state();
	//bool checkposnum(int i,int a);
	bool checkinbox(state number[9][9], int i, int k);
	bool checkinrow(state number[9][9], int i, int j, int k);
	bool checkincol(state number[9][9], int i, int j, int k);
	void colchanger(int &l, int &m, int &n);
	void rowchanger(int &l, int &m, int &n);
};


#endif