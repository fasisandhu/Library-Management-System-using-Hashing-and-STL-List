#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
using namespace std;



class record {
	int issn;
	string title;
	list<string> authors;
	int no_of_refer;
	int no_of_copies;
public:
	record()
	{
		issn = 0; title = " ";
		no_of_copies = no_of_refer = 0;
	}
	record(int i,string t,list<string>a,int r,int c )
	{
		issn = i; title = t;
		no_of_refer = r;
		no_of_copies = c; 
		authors = a;
	}
	record(int i, string t, int r, int c)
	{
		issn = i; title = t;
		no_of_refer = r;
		no_of_copies = c;
	}

	const record& operator=(record& obj)
	{
		issn = obj.issn;
		title = obj.title;
		no_of_copies = obj.no_of_copies;
		no_of_refer = obj.no_of_refer;
		if (!obj.authors.empty())
		{
			list<string>::iterator it1 = obj.authors.begin();
			list<string>::iterator it2 = obj.authors.end();;
			if (!obj.authors.empty())
			{
				while (it1 != it2)
				{
					authors.push_back(*it1);
					it1++;
				}
			}
		}
		return *this;
	}
	void addauthor(string t)
	{
		authors.push_back(t);
	}
	~record()
	{
		//cout << "dest" << endl;
		//nothing dynamic
	}
	void setissn(int i)
	{
		issn = i;
	}
	void settitle(string t)
	{
		title = t;
	}
	void setcopies(int c)
	{
		no_of_copies = c;
	}
	void setrefer(int r)
	{
		no_of_refer = r;
	}
	void setauthors(list<string>a)
	{
		if (authors.empty())//empty
			authors = a;
		else
		{
			authors.clear();
			authors = a;
		}

	}
	int getissn()
	{
		return issn;
	}
	int getcopies()
	{
		return no_of_copies;
	}
	int getrefer()
	{
		return no_of_refer;
	}
	string gettile()
	{
		return title;
	}
	list<string> getauthors()
	{
		return authors;
	}

	bool operator ==(const record& obj)const
	{
		return issn == obj.issn;
	}
	
	bool operator !=(const record& obj)const
	{
		return issn != obj.issn;
	}
	
	friend ostream& operator<<(ostream& out, record& obj);
};
ostream& operator<<(ostream& out, record& obj)
{
	out << "ISSN::" << obj.issn << endl;
	out << "Title::" << obj.title << endl;
	out << "No of copies::" << obj.no_of_copies << endl;
	out << "No of reference books::" << obj.no_of_refer << endl;
	out << "--List of Authors--" << endl;
	list<string>::iterator it1=obj.authors.begin();
	list<string>::iterator it2 = obj.authors.end();
	if(!obj.authors.empty())
	{
		while (it1 != it2)
		{
			cout << *it1 << endl;
			it1++;
		}

	}
	return out;
}


class lms {
	vector<list<record>> hashtable;
	int currbooks;
	int tablesize;
public:
	lms(int m=1009)
	{
		currbooks = 0;
		tablesize = m;
		hashtable = vector <list<record>>(m);	//max size 1009 a prime number
	}

	int hashfunc(int key)
	{
		//p is set 1013 as t.size is 1009 so nearest prime is 1013
		//i have passed key as seed to srand so seq of random numbers is same
		// for a specific key and so a and b are diff for each key making it universal func
		///hash func=(((a*key)+b)%p)%table size---1<a,b<p
		//p is prime num nearest to table size

		srand(key);
		int p = 1013;
		int a = rand()%p;
		int b = rand()%p;
		int index = (((a * key) + b) % p) % tablesize;
		return index;
	}

	void createbkrc()
	{
		int i, c, r; string t; int count;
		cout << "Enter ISSN:" << endl;
		cin >> i;
		int index = hashfunc(i);	//getting index
		//first search
		int chk = 0;
		list<record>::iterator it1 = hashtable[index].begin();
		list<record>::iterator it2 = hashtable[index].end();
		while (it1 != it2)//this loop runs only 1 iteration mostly making the func o(1)
		{
			if (it1->getissn() == i)
			{
				chk = 1;
				break;
			}
			it1++;
		}
		if (chk == 1)
		{
			cout << "Already Exists" << endl;
			return;
		}
		cin.ignore();
		cout << "Enter Title:" << endl;
		cout << "After input press enter 2 times due to cin.ignore()" << endl;
		getline(cin, t);
		cin.ignore();
		cout << "Enter No of COPIES:" << endl;
		cin >> c;
		cout << "Enter No of Reference Books:" << endl;
		cin >> r;
		cout << "Enter NO of authors:" << endl;
		cin >> count;
		
		record objofrecod(i, t, r, c);
		for (int i = 0; i < count; i++)
		{
			//string name;
			cin.ignore();
			cout << "Enter author's name" << endl;
			cout << "After input press enter 2 times due to cin.ignore()" << endl;
			getline(cin, t);
			//cin.ignore();
			cin.clear();
			objofrecod.addauthor(t);
		}

		//inserting
		hashtable[index].push_back(objofrecod); currbooks++;
		//collision is dealt as there is list at each index
		//of hashtable simple every new obj is getting inserted in list
		//in case of collsion which has negligible chances due to
		//universal hash function
	}
	//======================================================================================
	//have used loop for traversing the list at an index but loop mostly runs only 1 times =
	//due to hash func so making it o(1) avg time                                          =
	//======================================================================================
	void reviewbkrc()
	{
		int issn;
		cout << "Enter ISSN:" << endl;
		cin >> issn;
		int index = hashfunc(issn);	//getting index
		list<record> temp = hashtable[index];
		list<record>::iterator it1 = temp.begin();
		list<record>::iterator it2 = temp.end();
		while (it1 != it2)//this loop runs only 1 iteration mostly making the func o(1)
		{
			record temprecord = *it1;
			if (temprecord.getissn() == issn)
			{
				cout << temprecord;
				return;	//so func ends
			}
			it1++;
		}
		cout << "Not Found" << endl;	//if it gets out of loop so it hasnt found
	}

	void updatebkrc()
	{
		int issn;
		cout << "Enter ISSN:" << endl;
		cin >> issn;
		int index = hashfunc(issn);	//getting index
		//first search
		int chk = 0;
		list<record>::iterator it1 = hashtable[index].begin();
		list<record>::iterator it2 = hashtable[index].end();
		while (it1 != it2)//this loop runs only 1 iteration mostly making the func o(1)
		{
			if (it1->getissn() == issn)
			{
				chk = 1;
				break;
			}
			it1++;
		}
		if (chk == 0)
		{
			cout << "Not Found" << endl;
			return;
		}

		int c, r; string t; int count;
		cin.ignore();
		cout << "Enter Title:" << endl;
		cout << "After input press enter 2 times due to cin.ignore()" << endl;
		getline(cin, t);
		cin.ignore();
		cout << "Enter No of COPIES:" << endl;
		cin >> c;
		cout << "Enter No of Reference Books:" << endl;
		cin >> r;
		cout << "Enter NO of authors:" << endl;
		cin >> count;
		it1->settitle(t);
		it1->setcopies(c);
		it1->setrefer(r);
		list<string> names;
		for (int i = 0; i < count; i++)
		{
			cin.ignore();
			cout << "Enter author's name" << endl;
			cout << "After input press enter 2 times due to cin.ignore()" << endl;
			getline(cin, t);
			//cin.ignore();
			cin.clear();
			names.push_back(t);
		}
		it1->setauthors(names);
		cout << "Updated" << endl;
	}

	void deletebkrc()
	{
		int issn;
		cout << "Enter ISSN:" << endl;
		cin >> issn;

		record tobj; tobj.setissn(issn);
		int index = hashfunc(issn);	//getting index

		//first search
		int chk = 0;
		list<record> temp = hashtable[index];
		list<record>::iterator it1 = temp.begin();
		list<record>::iterator it2 = temp.end();
		while (it1 != it2 )//this loop runs only 1 iteration mostly making the func o(1)
		{
			record temprecord = *it1;
			if (temprecord.getissn() == issn)
			{
				chk = 1;
				break;
			}
			it1++;
		}
		if (chk == 0)
		{
			cout << "Not Found" << endl;
			return;
		}
		hashtable[index].remove(*it1); currbooks--;
		//hashtable[index].erase(it1);
		//record *t1;
		//t1 = new record; t1->setissn(issn);
		//record obj; obj.setissn(issn);
		//hashtable[index].remove(obj);
		//hashtable[index].
		//globalissn = issn;
		//hashtable[index].remove_if(checkissn);
		cout << "Deleted" << endl;
	}

	void printwholehash()
	{
		cout << "Total Records::" << currbooks << endl;
		list<record>::iterator it1;
		list<record>::iterator it2;
		//will be a long loop due to large size
		for (int i = 0; i < hashtable.size(); i++)
		{
			it1 = hashtable[i].begin();
			it2 = hashtable[i].end();
			while (it1 != it2)
			{
				cout << *it1 << endl;
				it1++;
			}
		}
	}

	void printspecificindex()
	{
		int i;
		cout << "Input index::" << endl;
		cin >> i;
		if (i >= hashtable.size())
		{
			cout << "out of bound" << endl;
			return;
		}
		list<record>::iterator it1;
		list<record>::iterator it2;
		it1 = hashtable[i].begin();
		it2 = hashtable[i].end();
		while (it1 != it2)
		{
			cout << *it1 << endl;
			it1++;
		}
	
	}

	void menu()
	{
		int choice = -1;
		while (1)
		{
			cout << "---------LMS-------" << endl;
			cout << "1:Create Record" << endl;
			cout << "2:Review Record" << endl;
			cout << "3:Update Record" << endl;
			cout << "4:Delete Record" << endl;
			cout << "5:Print Whole Hashtable(All Entries)" << endl;
			cout << "6:Print Hastable's specific index" << endl;
			cout << "7:Exit" << endl;
			cout << "Enter choice:" << endl;
			cin >> choice;
			while (!(choice >= 1 && choice <= 7))
			{
				cout << "Enter choice:" << endl;
				cin >> choice;
			}
			if (choice == 1)
			{
				createbkrc();
			}
			else if (choice == 2)
			{
				reviewbkrc();
			}
			else if (choice == 3)
			{
				updatebkrc();
			}
			else if (choice == 4)
			{
				deletebkrc();
			}
			else if (choice == 5)
			{
				printwholehash();
			}
			else if (choice == 6)
			{
				printspecificindex();
			}
			else if (choice == 6)
			{
				printspecificindex();
			}
			else if (choice == 7)
			{
				break;
			}
			system("pause");
			system("cls");
		}
	}


};


int main()
{
	lms obj;
	obj.menu();
	
	//obj.createbkrc();
	////obj.createbkrc();
	////obj.reviewbkrc();
	//obj.reviewbkrc();
	//obj.updatebkrc();
	////obj.deletebkrc();
	//obj.reviewbkrc();
	//obj.createbkrc();
	//obj.reviewbkrc();
	//obj.reviewbkrc();


	//record a1, a2;
	//a1 == a2;

	//list<int> tt;
	//tt.remove()

	//record obj;
	//obj.setissn(123);
	//obj.settitle("test");
	//obj.setrefer(2);
	//obj.setcopies(3);
	//obj.addauthor("a 1");
	//obj.addauthor("a 2");
	//cout << obj;

	/*int m;
	cin >> m;
	vector<list<record>> hashtable(m);
	cout << hashtable.size();*/


	system("pause");
	return 0;
}