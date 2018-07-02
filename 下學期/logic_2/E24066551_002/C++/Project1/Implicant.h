#pragma once
#include<iostream>
#include"Minterm.h"
#include<vector>
#include<string>
#include<fstream>
using namespace std;

#ifndef IMPLICANT_H
#define IMPLICANT_H
class Implicant:public Minterm
{
public:
	/*constructor*/
	Implicant(Minterm&);
	Implicant(Minterm&, Minterm&);
	Implicant(Implicant&, Implicant&);

	vector<Minterm>minterms;/*存這個Implicant包含的minterms(以物件形式)*/
	vector<int>minterms_no;/*存這個Implicant包含的minterms(以數字形式)*/
	int minterm_num;/*擁有minterms的數量*/
	bool addable(Implicant&);/*判斷兩個Implicant是否可以相加*/
	bool operator==(Implicant&);/*判斷兩個Implicant是否相同*/
};



#endif
