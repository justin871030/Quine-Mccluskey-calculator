#include "stdafx.h"
#include<iostream>
#include<vector>
#include<fstream>
#include"Implicant.h"
#include<math.h>
#include <iomanip> 
using namespace std;

Implicant::Implicant(Minterm&a)
{
	minterms_no.push_back(a.no);
	minterms.push_back(a);
	minterm_num += 1;
	bit = a.bit;
	setup();
}
Implicant::Implicant(Minterm&a, Minterm&b)
{
	Minterm output(a.no);
	minterms_no.push_back(a.no);
	minterms_no.push_back(b.no);
	minterms.push_back(a);
	minterms.push_back(b);
	minterm_num += 2;
	for (int i = 0; i < b.bit.size(); i++)
	{
		if (output.bit[i] != b.bit[i])
		{
			output.bit[i] = -1;
		}
	}
	bit = output.bit;
	setup();
}
Implicant::Implicant(Implicant&a, Implicant&b)
{
	Minterm output;
	for (int i = 0; i < a.minterms_no.size(); i++)
	{
		minterms_no.push_back(a.minterms_no[i]);
		minterms.push_back(a.minterms[i]);
		minterms_no.push_back(b.minterms_no[i]);
		minterms.push_back(b.minterms[i]);
	}
	minterm_num += a.minterms_no.size() + b.minterms_no.size();
	output.bit = a.bit;
	for (int i = 0; i < a.bit.size(); i++)
	{
		if (output.bit[i] != b.bit[i])
		{
			output.bit[i] = -1;
		}
	}
	bit = output.bit;
	setup();
}
bool Implicant::addable(Implicant &input)
{
	if (bit.size() != input.bit.size())
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
		if (count == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool Implicant::operator==(Implicant& data)
{
	if (minterms_no.size()!= data.minterms_no.size())
	{
		return false;
	}
	else
	{
		int count = 0;
		for (int i = 0; i < minterms_no.size(); i++)
		{
			for (int j = 0; j < data.minterms_no.size(); j++)
			{
				if (minterms_no[i] == data.minterms_no[j])
				{
					/*cout << minterms_no[i];*/
					count++;
				}
			}
		}
		if (count == minterms_no.size())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}