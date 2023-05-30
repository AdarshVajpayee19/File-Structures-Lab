/*

3. Write a Program to read and write Students Objects with variable length records and the fields delimited by
"|". Implement pack(),unpack(),modify() and search() methods.

*/

#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<process.h>

using namespace std;

class student {
	public:char name[25], usn[15], branch[15], buffer[100];
}s,s1[100];

int i = 0, mode = 1, no = 0;

void pack()
{
	fstream app;
	if (mode == 0)
		app.open("Stud details.txt", ios::app);
	else
		app.open("stud details.txt", ios::out);
	if (!app)
	{
		cout << "\nCan't open the file in output mode.";
		_getch();
		return;
	}
	strcpy_s(s.buffer, s.name);
	strcat_s(s.buffer, "|");
	strcat_s(s.buffer, s.usn);
	strcat_s(s.buffer, "|");
	strcat_s(s.buffer, s.branch);
	strcat_s(s.buffer, "\n");

	app << s.buffer;
	app.close();
}

void unpack() 
{
	fstream in;
	in.open("stud details.txt", ios::in);
	i = 0, no = 0;

	if (!in)
	{
		cout << "\nCan't Open file in input mode.";
		_getch();
		exit(0);
	}
	while (!in.eof())
	{
		in.getline(s1[i].name, 25, '|');
		in.getline(s1[i].usn, 15, '|');
		in.getline(s1[i].branch, 15, '\n');
		no++;
		i++;
	}
	in.close();
}

void write()
{
	cout << "\nEnter student name: ";
	cin >> s.name;
	cout << "\nEnter student usn: ";
	cin >> s.usn;
	cout << "\nEnter student branch: ";
	cin >> s.branch;
	pack();
	mode = 0;
}

void display()
{
	cout << "\nName\t\tUsn\t\tBranch\n";
	unpack();
	for (int i = 0;i < no;i++)
		cout << "\n" << s1[i].name << "\t\t" << s1[i].usn << "\t\t" << s1[i].branch;
	_getch();
}

void search()
{
	char usn[15];
	cout << "\nEnter usn to be searched: ";
	cin >> usn;
	unpack();

	for (i = 0;i < no;i++)
	{
		if (strcmp(s1[i].usn, usn) == 0)
		{
			cout << "\nRecord Found";
	        cout << "\n" << s1[i].name << "\t\t" << s1[i].usn << "\t\t" << s1[i].branch;
			return;
		}
	}
	cout << "\nRecord not Found\n";
	_getch();
	return;
}

void modify()
{
	char usn[15];int j;
	cout << "\nEnter usn to be searched: ";
	cin >> usn;
	unpack();
	no--;

	for (j = 0;j < no;j++)
	{
		if (strcmp(usn, s1[j].usn) == 0)
		{
			cout << "\nThe old values of the record with usn " << usn << " are";
			cout << "\nName : " << s1[j].name;
			cout << "\nusn : " << s1[j].usn;
			cout << "\nbranch : " << s1[j].branch;

			cout << "\nEnter new values of the record : ";
			cout << "\nName : ";   cin >> s1[j].name;
			cout << "\nusn : ";    cin >> s1[j].usn;
			cout << "\nbranch : "; cin >> s1[j].branch;
			break;
		}
	}
	if (j == no)
	{
		cout << "\nUsn is not present.";
		_getch();
		return;
	}
	mode = 1;
	for(j=0;j<no;j++)
	{
		strcpy_s(s.name, s1[j].name);
		strcpy_s(s.usn, s1[j].usn);
		strcpy_s(s.branch, s1[j].branch);
		pack();
		mode = 0;
	}
	cout << "\nRecord Modified.\n";
}

void main()
{
	int choice;
	for (;;)
	{
		cout<<"\n0 : Exit\n1 : Write\n2 : Display\n3 : Search\n4 : Modify\nEnter Your Choice : ";
		cin >> choice;
		switch (choice)
		{
		case 0: exit(0);
		case 1:write();
			break;
		case 2:display();
			break;
		case 3:search();
			break;
		case 4:modify();
			break;
		default:cout << "Invalid Input";
			break;
		}
	}
}
