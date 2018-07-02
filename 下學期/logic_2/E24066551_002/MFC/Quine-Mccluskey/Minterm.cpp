#include "stdafx.h"
#include<iostream>
#include<vector>
#include<fstream>
#include"Minterm.h"
#include<math.h>
#include <iomanip> 
using namespace std;

string int_str(int input)
{
	string temp;
	string output;
	while (input >= 10)
	{
		temp.push_back(input % 10 + 48);
		input /= 10;
	}
	temp.push_back(input + 48);
	for (int i = temp.size() - 1; i >= 0; i--)
	{
		output.push_back(temp[i]);
	}
	return output;
}
/*bool operator=(vector<int>&b)
{
	if (&a==&b)
	{
		return true;
	}
	else if (a.size()!= b.size())
	{
		return false;
	}
	else
	{
		int check = 1;
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i]!=b[i])
			{
				check = 0;
			}
		}
		return check;
	}
}*/
/*bool operator==(Minterm&a, Minterm&b)
{
	int temp = 0;
	if (a.member.size()!=b.member.size())
	{
		return false;
	}
	vector<int>check;
	for (int i = 0; i < a.member.size(); i++)
	{
		for (int j = 0; j < b.member.size(); j++)
		{
			if (a.member[i]==b.member[j])
			{
				int check2=0;
				for (int h = 0; h< check.size(); h++)
				{
					if (a.member[i]==check[h])
					{
						check2 = 1;
					}
				}
				if (check2==0)
				{
					temp++;
					check.push_back(a.member[i]);
				}
			}
		}
	}
	if (temp==a.member.size())
	{
		return true;
	}
	else
	{
		return false;
	}
}*/
Minterm::Minterm(int num,int bit_num)
{
	_num = 0;
	no = num;
	bit_name_base="abcdefghij";
	bit.resize(bit_num);
	int count= 0;
	while (num>=2)
	{
		bit[count] = num % 2;
		count++;
		num = num / 2;
	}
	bit[count] = num;
	setup();
}
void Minterm::setup()
{
	bit_name.clear();
	one_num = 0;
	_num = 0;
	for (int i = bit.size() - 1; i >= 0; i--)
	{
		if (bit[i] != -1)
		{
			if (bit[i] == 1)
			{
				one_num += 1;
			}
			if (bit[i] == -1)
			{
				_num++;
			}
			bit_name.push_back(bit_name_base[bit.size() - 1 - i]);
			if (bit[i] == 0)
			{
				bit_name.push_back('\'');
			}
		}
	}
}
void Minterm::show_2bit()
{
	for (int i = bit.size()-1; i >=0; i--)
	{
		if (bit[i]==-1)
		{
			cout << "-";
		}
		else
		{
			cout << bit[i];
		}
	}
}
void Minterm::output_2bit(fstream& output)
{
	for (int i = bit.size() - 1; i >= 0; i--)
	{
		if (bit[i] == -1)
		{
			cout << "-";
			output<< "-";
		}
		else
		{
			cout << bit[i];
			output << bit[i];
		}
	}
}
void Minterm::show_en()
{
	cout << bit_name;
}
void Minterm::output_en(fstream& output)
{
	output << bit_name;
}
bool Minterm::addable(Minterm &input)
{
	if (bit.size()!=input.bit.size())
	{
		return false;
	}
	else
	{
		int count = 0;
		for (int i = 0; i < bit.size(); i++)
		{
			if (bit[i] != input.bit[i])
			{
				count++;
			}
		}
		if (count==1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool Minterm::addable(vector<Minterm> &input)
{
	double num = input.size();
	while (num >= 2)
	{
		num = num / 2;
	}
	if (num == 1)
	{
		int state = 0;
		for (int i = 0; i < input.size(); i++)
		{
			for (int j = i+1; j < input.size(); j++)
			{
				input[i].addable(input[j]);
			}
		}
	}
	else
	{
		return false;
	}
}
Minterm operator+(Minterm&a, Minterm&b)
{
	Minterm output(a.no);
	for (int i = 0; i < b.bit.size(); i++)
	{
		if (output.bit[i]!=b.bit[i])
		{
			output.bit[i] = -1;
		}
	}
	output.setup();
	return output;
}
bool Minterm::operator==(Minterm& data)
{
	if (bit==data.bit)
	{
		return true;
	}
	else
	{
		return false;
	}
}