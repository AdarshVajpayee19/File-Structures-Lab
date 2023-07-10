/*
1. Write a program to read series of names,one per line, from standard input and write these names
spelled in reverse order to standard output using I/O redirection pipes.
Repeat the exercise using an input file specified by the user instead of the standard input and using an output
file specified by the user instead of the standard output.
*/

#include <iostream>
#include <conio.h>  // Console Input/Output.
#include <process.h> // Used for Menu driven programs.
#include <string>
#include <fstream> 
#include <algorithm> // calculations, data processing, and automated reasoning.
#include <cstring> // to manipulate C strings and arrays. Functions. Copying: memcpy: Copy block of memory (function).Strcpy · Strcmp · Strcat ·Strncpy

using namespace std;

class names
{
public: char name[50];
};
void main()
{
	names n[10];
	ifstream in;
	ofstream out;
	out.open("file1.txt", ios::out);
	int m;
	cout << "Enter the number of names to be entered : ";
	cin >> m;
	for (int i = 0; i < m; i++)
	{
		cout << "Enter name : ";
		cin >> n[i].name;
		_strrev(n[i].name);
		cout << "The name in reverse order is " << n[i].name << endl;
		out << n[i].name << "\n";
	}
	out.close();
	in.open("file1.txt", ios::in);
	out.open("f1.txt", ios::out);
	char ch[10];
	cout << "Names from files\n";
	while (!(in.eof()))
	{
		in >> ch;
		if (in)
			_strrev(ch);
		out << ch << endl;
		cout << ch << endl;
	}
	cout << endl;
	in.close();
	out.close();
	string line;
	in.open("f1.txt", ios::in);
	out.open("f2.txt", ios::out);
	cout << "Reverse order from files" << endl;
	while (in)
	{
		getline(in, line);
		cout << line << endl;
		reverse(line.begin(), line.end());
		out << line << endl;
		cout << line << endl;
	}
	in.close();
	out.close();
}
