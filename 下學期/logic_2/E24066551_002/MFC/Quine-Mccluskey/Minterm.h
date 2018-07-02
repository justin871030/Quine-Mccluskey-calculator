#pragma once
#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

#ifndef MINTERM_H
#define MINTERM_H
class Minterm
{
public:
	int no;
	vector<int>bit;/*�H�Ʀr�Φ��simplicant (EX.abc'=(1,1,0,-1))*/
	string bit_name;/*�^���r�Φ����W��*/
	string bit_name_base;/*bit_name_base="dcba" �զ�implicant���^���r*/
	int one_num=0;/*�֦�"1"���Ӽ�(EX.ab'cd��3��)*/
	int _num=0;/*�֦�"-"���Ӽ�(EX.ab'c��1��)*/
	void show_2bit();/*�H�Ʀr�Φ��L�X*/
	void output_2bit(fstream&);
	void show_en();/*�H�^��Φ��L�X*/
	void output_en(fstream&);
	Minterm(int=0, int=10);/*Minterm(int)����l��function*/
	void setup();
	bool addable(Minterm&);
	bool addable(vector<Minterm>&);
	bool operator==(Minterm&);
private:
};
#endif