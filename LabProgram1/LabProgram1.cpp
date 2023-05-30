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

class names {
public:char name[50];
};

int main()
{
    names n[10];
    ofstream out;
    out.open("file.txt", ios::out); //to create files and to write data to files.

    int m;
    cout << "Enter the no. of names to be entered\n";
    cin >> m;

    for (int i = 0;i < m;i++)
    {
        cout << "Enter Name: ";
        cin >> n[i].name;
        cout << "The name in reverse order\n";
        _strrev(n[i].name);
        cout << n[i].name << "\n";
        out << n[i].name;
        out << "\n";
    }
    out.close();

    ifstream in, in2;
    in.open("file.txt", ios::in);
    ofstream outf;
    outf.open("f1.txt", ios::out);

    char ch[10];
    cout << "Names from files\n";

    while (in)
    {
        in >> ch;
        if (in)
        _strrev(ch);
        outf << ch;
        outf << "\n";
        cout << ch << "\n";
    }
    cout << endl;
    in.close();
    outf.close();

    string line;
    in2.open("f1.txt", ios::in);
    outf.open("f2.txt", ios::out);
    cout << "Reverse order from files\n";

    while (in2)
    {
        getline(in2, line);
        cout << line << "\n";
        reverse(line.begin(), line.end());
        outf << line;
        outf << "\n";
        cout << line << "\n";
    }
    in.close();
    outf.close();
    _getch();
    return 0;
}

