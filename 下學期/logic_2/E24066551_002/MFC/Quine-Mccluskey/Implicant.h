#pragma once
#include "stdafx.h"
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
	Implicant(Minterm&);
	Implicant(Minterm&, Minterm&);
	Implicant(Implicant&, Implicant&);
	vector<Minterm>minterms;
	vector<int>minterms_no;
	int minterm_num;
	bool addable(Implicant&);
	bool operator==(Implicant&);
};



#endif
