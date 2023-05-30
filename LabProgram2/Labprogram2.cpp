/*
2. Write a Program to read and write Students Objects with Fixed length records and the fields delimited by
"|". Implement pack(),unpack(),modify() and search() methods.
*/

#include<conio.h>
#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string>

using namespace std;

class student
{
public:char name[25], usn[15], branch[15], buffer[100];
}temp, s, s1[100];

char extra[45];
int i, no = 0, mode = 1;

void pack()
{
	fstream app;
	if (mode == 0)
		app.open("st1.txt", ios::app);
	else
		app.open("st1.txt", ios::out);
	if (!app)
	{
		cout << "cant open the file in output mode";
		_getch();
		exit(0);
	}
	strcpy_s(s.buffer, s.name);
	strcat_s(s.buffer, "|");
	strcat_s(s.buffer, s.usn);
	strcat_s(s.buffer, "|");
	strcat_s(s.buffer, s.branch);

	int count = strlen(s.buffer);

	for (int k = 0; k < 45 - count; k++)
		strcat_s(s.buffer, "|");
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
		cout << "cant open the file in input mode"; 
		_getch();
		exit(0);
	}
	while (!in.eof())
	{
		in.getline(s1[i].name, 15, '|');
		in.getline(s1[i].usn, 15, '|');
		in.getline(s1[i].branch, 15, '|');
		in.getline(extra, 45, '\n');
		no++;
		i++;
	}
	in.close();
}

void write()
{
	cout << "\n enter the student name\n";
	cin >> s.name;
	cout << "enter the student usn\n";
	cin >> s.usn;
	cout << "enter the student branch\n";
	cin >> s.branch;
	pack();
	mode = 0;
}


void display()
{
	cout << "name\t\t usn\t\t branch\n\n";
	unpack();
	for (int i = 0; i < no; i++)
		cout << "\n\n" << s1[i].name << "\t\t" << s1[i].usn << "\t\t" << s1[i].branch;
	_getch();
}

void search()
{
	char usn[15], extra[45];
	cout << "\nenter the usn to search=";
	cin >> usn;
	unpack();
	for (i = 0; i < no; i++)
	{
		if (strcmp(s1[i].usn, usn) == 0) {
			cout << "\nrecord found";
			cout << "\n" << s1[i].name << "\t" << s1[i].usn << "\t" << s1[i].branch;
			_getch();
			return;
		}
	}
	cout << "record not found";
	_getch();
	return;
}

void modify()
{
	char usn[15]; int j;
	cout << "enter the usn to search\n";
	cin >> usn;
	unpack(); no--;
	for (j = 0; j < no; j++)
	{
		if (strcmp(usn, s1[j].usn) == 0)
		{
			cout << "the old values of the record are with usn" << usn << "are";
			cout << "\nname=" << s1[j].name;
			cout << "\nusn=" << s1[j].usn;
			cout << "\nbranch=" << s1[j].branch;
			cout << "enter the new values\n";
			cout << "\nname=";
			cin >> s1[j].name;
			cout << "\nusn=";
			cin >> s1[j].usn;
			cout << "\nbranch=";
			cin >> s1[j].branch;
			break;
		}
	}
	if (j == no)
	{
		cout << "the record with usn is not present";
		_getch();
		return;
	}
	mode = 1;
	for (j = 0; j < no; j++)
	{
		strcpy_s(s.name, s1[j].name);
		strcpy_s(s.usn, s1[j].usn);
		strcpy_s(s.branch, s1[j].branch);
		pack();
		mode = 0;
	}
	cout << "record modified\n";
}

void main()
{
	int choice;
	for (;;)
	{
		cout << "\n0:exit";
		cout << "\n1:write";
		cout << "\n2:display";
		cout << "\n3:modify";
		cout << "\n4:search";
		cout << "\nenter u choice\n";
		cin >> choice;
		switch (choice)
		{
		case 1:write();
			break;
		case 2:display();
			break;
		case 3:modify();
			break;
		case 4:search();
			break;
		case 0: exit(0);
		default:cout << "\ninvalid input";
			break;
		}
	}
}

/*

In summary, the pack() function converts the student object's data into a fixed-length string format and 
saves it in a file,which allows for easy storage and retrieval of student records.

unpack() : function reads the content of a file that contains student records in a specific format,
extracts the data, and stores it into an array of student objects for further processing and manipulation.

*/
