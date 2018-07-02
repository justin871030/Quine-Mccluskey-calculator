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
	vector<int>bit;/*计Αimplicant (EX.abc'=(1,1,0,-1))*/
	string bit_name;/*璣ゅ虫Α嘿*/
	string bit_name_base;/*bit_name_base="dcba" 舱Θimplicant璣ゅ虫*/
	int one_num=0;/*局Τ"1"计(EX.ab'cdΤ3)*/
	int _num=0;/*局Τ"-"计(EX.ab'cΤ1)*/
	void show_2bit();/*计Α*/
	void output_2bit(fstream&);
	void show_en();/*璣ゅΑ*/
	void output_en(fstream&);
	Minterm(int=0, int=10);/*Minterm(int)﹍てfunction*/
	void setup();
	bool addable(Minterm&);
	bool addable(vector<Minterm>&);
	bool operator==(Minterm&);
private:
};
#endif