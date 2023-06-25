/*
Program 7: Write a program to read two lists of names and then match the names in the two lists using
Cosequential Match based on a single loop. Output the names common to both the lists.
*/

#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<string>

using namespace std;

fstream f1, f2, op;

void sort(char arr[100][20], int n)
{
	char temp[20];
	for (int i = 0;i <= n - 1;i++)
		for (int j = 0;j <= n - 1 - i;j++)
			if (strcmp(arr[j], arr[j + 1]) > 0)
			{
				strcpy_s(temp, arr[j]);
				strcpy_s(arr[j], arr[j + 1]);
				strcpy_s(arr[j + 1], temp);
			}
}

void match(char l1[100][20], char l2[100][20], int n1, int n2)
{
	int i = 0, j = 0;
	while ((i <= n1) && (j <= n2))
	{
		if (strcmp(l1[i], l2[j]) == 0)
		{
			cout << "Matched : " << l1[i] << endl;
			op << l1[i] << endl;
			i++;
			j++;
		}
		else if (strcmp(l1[i], l2[j]) > 0)
			j++;
		else
			i++;
	}
}

int main()
{
	char l1[100][20], l2[100][20];
	f1.open("file1.txt", ios::in);
	f2.open("file2.txt", ios::in);

	if (!f1 || !f2)
	{
		cout << "Could not open file " << endl;
		exit(0);
	}

	int n1 = -1, n2 = -1;

	while (!f1.eof())
		f1.getline(l1[++n1], 20, '\n');
	while (!f2.eof())
		f2.getline(l2[++n2], 20, '\n');

	sort(l1, n1);
	sort(l2, n2);

	op.open("output.txt", ios::out);
	match(l1, l2, n1, n2);
	f1.close();
	f2.close();
	op.close();
	return 0;
}

