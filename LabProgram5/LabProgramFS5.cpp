
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string>
using namespace std;
fstream sfile, ifile;
int mode = 0, ind, i;
char buffer[80];
class student
{
	char usn[15], name[15], branch[15], sem[5];
public:void add();
	  void remove(int);
	  void recDisp(int);
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
void opener(fstream& file, string fname, int mode)
{
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
	ifile.close();
}
void index::write()
{
	opener(ifile, "ifile.txt", ios::out);
	for (i = 0; i < ind; i++)
		ifile << in1[i].iusn << "|" << in1[i].addr << endl;
	ifile.close();
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
	sfile.close();
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
void student::remove(int pos)
{
	opener(sfile, "sfile.txt", ios::in | ios::out);
	sfile.seekg(atoi(in1[pos].addr), ios::beg);
	sfile.put('$');
	for (i = pos; i < ind; i++)
		in1[i] = in1[i + 1];
	ind--;
	sfile.close();
	in.write();
}
void student::recDisp(int pos)
{
	opener(sfile, "sfile.txt", ios::in);
	sfile.seekg(atoi(in1[pos].addr), ios::beg);
	unpack();
	cout << "The searched details are:\nUSN: " << usn << "\nName: " << name << "\nBranch: " << branch << "\nSem: " << sem << endl;
	sfile.close();
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
	sfile.close();
}

void main()
{
	int flag, ch;
	char susn[15];
	student s;
	in.init();
	for (;;)
	{
		cout << "1.Enter record\n2.Display records\n3.Search record\n4.Delete record\n0.Exit: ";
		cin >> ch;
		switch (ch)
		{
		case 0:exit(0);
		case 1:cout << "Enter student details:" << endl;
			s.add();
			in.write(); break;
		case 2:cout << "The student record details are: " << endl;
			s.dispAll();
			cout << "The index record details are: " << endl;
			for (i = 0; i < ind; i++)
				cout << in1[i].iusn << "|" << in1[i].addr << endl;
			break;
		case 3:cout << "Enter USN: ";
			cin >> susn;
			flag = search(susn);
			if (flag == -1)
				cout << "Record does not exist" << endl;
			else s.recDisp(flag);
			break;
		case 4:cout << "Enter USN: ";
			cin >> susn;
			flag = search(susn);
			if (flag == -1)
				cout << "Record does not exist" << endl;
			else s.remove(flag);
			break;
		}
	}
}
