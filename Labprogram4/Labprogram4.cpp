/*
4. Write a program to write student objects with variable length records using any suitable record structure and read 
to read from a file using relative record number (RRN).
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

int mode = 1, no = 0, i = 0;

void pack()
{
	fstream app;
	if (mode == 0)
		app.open("st1.txt", ios::app);
	else
		app.open("st1.txt", ios::out);
	if (!app)
	{
		cout << "\nCan't Open file in input mode";
		_getch();
		exit(0);
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
	in.open("st1.txt", ios::in);
	i = 0, no = 0;

	if (!in)
	{
		cout << "\nCan't open file in input mode.";
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

void search()
{
	int rrn;
	cout << "\nEnter the rrn value : ";
	cin >> rrn;
	unpack();
	no--;

	for (i = 0;i < no;i++)
	{
		if (rrn == i)
		{
			cout << "\nRecord Found.";
			cout << "\n" << s1[i].name << "\t\t" << s1[i].usn << "\t\t" << s1[i].branch<<"\n";
			_getch();
			return;
		}
	}
	cout << "\nRecord not Found.";
	_getch();
	return;
}

void main()
{
	int choice;
	for (;;)
	{
		cout << "\n0 : Exit\n1 : Write\n2 : Search\nEnter Your Choice : ";
		cin >> choice;
		switch (choice)
		{
		case 0:exit(0);
		case 1:write();break;
		case 2:search();break;
		default:cout << "\nInvalid Input.";break;
		}
	}
}
