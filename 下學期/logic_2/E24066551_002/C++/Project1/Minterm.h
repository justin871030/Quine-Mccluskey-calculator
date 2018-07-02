#pragma once
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
	/*constructor*/
	Minterm(int = 0, int = 10);
	int no;/*minterm的編號*/
	vector<int>bit;/*以數字形式存implicant (EX.abc'=(1,1,0,-1))*/
	string bit_name;/*英文單字形式的名稱*/
	string bit_name_base;/*bit_name_base="dcba" 組成implicant的英文單字*/
	int one_num=0;/*擁有"1"的個數(EX.ab'cd有3個)*/
	int _num=0;/*擁有"-"的個數(EX.ab'c有1個)*/
	void show_2bit();/*以數字形式印出*/
	void output_2bit(fstream&);/*協助輸出txt的function*/
	void show_en();/*以英文形式印出*/
	void output_en(fstream&);/*協助輸出txt的function*/
	void setup();/*Minterm(int)的初始化function*/
private:
};
#endif