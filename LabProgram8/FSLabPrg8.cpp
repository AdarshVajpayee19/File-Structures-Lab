/*
Program 8: K-way merge
*/

#include<iostream>
#include<fstream>
#include<stdlib.h>

using namespace std;

fstream f[8], f1, f2, out;

string ifiles[8] = {"1.txt","2.txt", "3.txt", "4.txt", "5.txt", "6.txt", "7.txt", "8.txt"};
string ofiles[7] = {"12.txt","34.txt", "56.txt", "78.txt", "1234.txt", "5678.txt", "12345678.txt"};

class records
{
	public:char name[15], usn[15];
}rec[20], temp;

void merge(string file1, string file2, string outfile)
{
	int k = -1;
	f1.open(file1, ios::in);
	f2.open(file2, ios::in);
	out.open(outfile, ios::out);

	while (!f1.eof())
	{
		f1.getline(rec[++k].name, 15, '|');
		f1.getline(rec[k].usn, 15, '\n');
	}
	while (!f2.eof())
	{
		f2.getline(rec[k].name, 15, '|');
		f2.getline(rec[k++].usn, 15, '\n');
	}
	k--;

	for (int i = 0;i < k - 1;i++)
	{
		for (int j = 0;j < k - 1 - i;j++)
		{
			if (strcmp(rec[j].name, rec[j + 1].name) > 0)
			{
				temp = rec[j];
				rec[j] = rec[j + 1];
				rec[j + 1] = temp;
			}
		}
	}
	for (int i = 0;i < k;i++)
		out << rec[i].name << "|" << rec[i].usn << endl;
	f1.close();
	f2.close();
	out.close();
}

void kway()
{
	int k = 0;
	for (int i = 0;i < 8;i+=2)
		merge(ifiles[i], ifiles[i + 1], ofiles[k++]);
	for (int i = 0;i < 4;i+=2)
		merge(ofiles[i], ofiles[i + 1], ofiles[k++]);
	merge(ofiles[4], ofiles[5], ofiles[6]);
}

int main()
{
	cout << "Enter the Number of records: ";
	int no;
	cin >> no;

	for (int i = 0;i < 8;i++)
		f[i].open(ifiles[i], ios::out);

	cout << "Enter records : " << endl;
	for (int i = 0;i < no;i++)
	{
		cout << "Enter Name: ";
		cin >> temp.name;
		cout << "Enter Usn: ";
		cin >> temp.usn;
		f[i % 8] << temp.name << "|" << temp.usn << endl;
	}

	for (int i = 0;i < 8;i++)
		f[i].close();

	kway();

	out.open(ofiles[6], ios::in);
	cout << "The Sorted data is : " << endl;
	for (int i = 0;i < no;i++)
	{
		out.getline(temp.name, 15, '|');
		out.getline(temp.usn, 15, '\n');
		cout << "Name : " << temp.name << "\tUsn : " << temp.usn << endl;
	}
	out.close();
}
