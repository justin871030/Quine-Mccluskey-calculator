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

	vector<Minterm>minterms;/*�s�o��Implicant�]�t��minterms(�H����Φ�)*/
	vector<int>minterms_no;/*�s�o��Implicant�]�t��minterms(�H�Ʀr�Φ�)*/
	int minterm_num;/*�֦�minterms���ƶq*/
	bool addable(Implicant&);/*�P�_���Implicant�O�_�i�H�ۥ[*/
	bool operator==(Implicant&);/*�P�_���Implicant�O�_�ۦP*/
};



#endif
