/*
Program 6: Secondary Index.
*/

#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
using namespace std;
fstream sfile, ifile, sifile;
int mode = 0, ind, i, sind;
char buffer[80];
class student
{
	char usn[15], name[15], branch[15], sem[5];
public:void add();
	  void remove();
	  void ssearch();
	  void dispAll();
	  void pack();
	  void unpack();
	  friend int search(char*);
};
class index
{
public:char iusn[15], addr[5];
public:void write();
	  void init();
}in, in1[100];
class sindex
{
public:char susn[15], sname[15];
public:void swrite();
	  void sinit();
}sin1[100];
void opener(fstream& file, string fname, int mode)
{
	sfile.close();
	sifile.close();
	ifile.close();
	try
	{
		file.open(fname, mode);
	}
	catch (ios_base::failure& e)
	{
		cout << e.what() << endl;
	}
	if (!file)
	{
		cout << "Error opening file";
		exit(1);
	}
}
void sindex::sinit()
{
	sifile.open("sifile.txt", ios::in);
	if (!sifile)
	{
		sind = 0;
		return;
	}
	for (sind = 0;; sind++)
	{
		sifile.getline(sin1[sind].sname, 15, '|');
		sifile.getline(sin1[sind].susn, 15, '\n');
		if (sifile.eof())
			break;
	}
}
void sindex::swrite()
{
	opener(sifile, "sifile.txt", ios::out);
	for (i = 0; i < sind; i++)
		sifile << sin1[i].sname << "|" << sin1[i].susn << endl;
}
void index::init()
{
	ifile.open("ifile.txt", ios::in);
	if (!ifile)
	{
		ind = 0;
		return;
	}
	for (ind = 0;; ind++)
	{
		ifile.getline(in1[ind].iusn, 15, '|');
		ifile.getline(in1[ind].addr, 5, '\n');
		if (ifile.eof())
			break;
	}
}
void index::write()
{
	opener(ifile, "ifile.txt", ios::out);
	for (i = 0; i < ind; i++)
		ifile << in1[i].iusn << "|" << in1[i].addr << endl;
}
int search(char* fusn)
{
	int low = 0, high = ind - 1, mid;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (strcmp(fusn, in1[mid].iusn) == 0)
			return mid;
		else if (strcmp(fusn, in1[mid].iusn) > 0)
			low = mid + 1;
		else high = mid - 1;
	}
	return -1;
}
void student::add()
{
	cout << "Enter USN: ";
	cin >> usn;
	if (search(usn) != -1)
	{
		cout << "Duplicate records cannot be added" << endl;
		return;
	}
	for (i = ind; i > 0; i--)
	{
		if (strcmp(usn, in1[i - 1].iusn) < 0)
			in1[i] = in1[i - 1];
		else break;
	}
	if (mode)
		opener(sfile, "sfile.txt", ios::app);
	else
	{
		opener(sfile, "sfile.txt", ios::out);
		mode = 1;
	}
	cout << "Enter Name: ";
	cin >> name;
	cout << "Enter Branch: ";
	cin >> branch;
	cout << "Enter Sem: ";
	cin >> sem;
	pack();
	sfile.seekg(0, ios::end);
	_itoa_s(sfile.tellg(), in1[i].addr, 10);
	sfile << buffer << endl;
	strcpy_s(in1[i].iusn, usn);
	ind++;
	for (i = sind; i > 0; i--)
	{
		if (strcmp(name, sin1[i - 1].sname) < 0)
			sin1[i] = sin1[i - 1];
		else if ((strcmp(name, sin1[i - 1].sname) == 0) && (strcmp(usn, sin1[i - 1].susn) < 0))
			sin1[i] = sin1[i - 1];
		else break;
	}
	strcpy_s(sin1[i].sname, name);
	strcpy_s(sin1[i].susn, usn);
	sind++;
}
void student::pack()
{
	strcpy_s(buffer, usn);
	strcat_s(buffer, "|");
	strcat_s(buffer, name);
	strcat_s(buffer, "|");
	strcat_s(buffer, branch);
	strcat_s(buffer, "|");
	strcat_s(buffer, sem);
}
void student::unpack()
{
	sfile.getline(usn, 15, '|');
	sfile.getline(name, 15, '|');
	sfile.getline(branch, 15, '|');
	sfile.getline(sem, 5, '\n');
}
void student::remove()
{
	char skey[15], uusn[15];
	int flag = -1, pos, spos = -1;
	cout << "Enter secondary key to search: ";
	cin >> skey;
	cout << "The searched details are: " << endl;
	for (i = 0; i < sind; i++)
		if (strcmp(skey, sin1[i].sname) == 0)
		{
			cout << "Name: " << sin1[i].sname << "\nUSN: " << sin1[i].susn;
			flag = i;
		}
	if (flag == -1)
	{
		cout << "No records found" << endl;
		return;
	}
	cout << "Choose USN from the above list to delete: ";
	cin >> uusn;
	for (i = 0; i < sind; i++)
		if (strcmp(uusn, sin1[i].susn) == 0)
		{
			spos = i;
			break;
		}
	if (strcmp(skey, sin1[spos].sname) == 0)
	{
		pos = search(uusn);
		opener(sfile, "sfile.txt", ios::in | ios::out);
		sfile.seekg(atoi(in1[pos].addr), ios::beg);
		sfile.put('$');
		for (i = pos; i < ind; i++)
			in1[i] = in1[i + 1];
		ind--;
		for (i = spos; i < sind; i++)
			sin1[i] = sin1[i + 1];
		sind--;
	}
	else cout << "Name and USN dont match" << endl;
}
void student::dispAll()
{
	opener(sfile, "sfile.txt", ios::in);
	while (1)
	{
		unpack();
		if (sfile.eof())
			break;
		if (usn[0] == '$')
			cout << "This record has been deleted" << endl;
		else cout << "USN: " << usn << "\nName: " << name << "\nBranch: " << branch << "\nSem: " << sem << endl;
	}
}
void student::ssearch()
{
	cout << "Enter secondary key to search: ";
	char skey[15];
	cin >> skey;
	int flag = -1;
	opener(sfile, "sfile.txt", ios::in);
	for (int j = 0;j < sind;j++)
		if (strcmp(skey, sin1[j].sname) == 0)
			for (i = 0;i < ind;i++)
				if (strcmp(sin1[j].susn, in1[i].iusn) == 0)
				{
					flag = i;
					sfile.seekg(atoi(in1[i].addr), ios::beg);
					unpack();
					if (usn[0] == '$')
						cout << "Record has been deleted";
					else cout << "USN: " << usn << "\nName: " << name << "\nBranch: " << branch << "\nSem: " << sem << endl;
				}
	if (flag == -1)
		cout << "Record not found" << endl;
}
void main()
{
	int flag, ch;
	char susn[15];
	student s;
	sindex sin;
	in.init();
	sin.sinit();
	for (;;)
	{
		cout << "1.Enter record\n2.Display records\n3.Search record\n4.Delete record\n0.Exit: ";
		cin >> ch;
		switch (ch)
		{
		case 0:exit(0);
		case 1:cout << "Enter student details:" << endl;
			s.add();
			in.write();
			sin.swrite(); break;
		case 2:cout << "The student record details are: " << endl;
			s.dispAll();
			cout << "The index record details are: " << endl;
			for (i = 0; i < ind; i++)
				cout << in1[i].iusn << "|" << in1[i].addr << endl;
			cout << "The secondary index record details are: " << endl;
			for (i = 0; i < sind; i++)
				cout << sin1[i].sname << "|" << sin1[i].susn << endl;
			break;
		case 3:s.ssearch();
			break;
		case 4:s.remove();
			in.write();
			sin.swrite();
			break;
		}
	}
}
