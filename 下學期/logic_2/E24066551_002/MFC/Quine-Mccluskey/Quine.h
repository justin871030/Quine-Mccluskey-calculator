#pragma once
#include "stdafx.h"
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include"Implicant.h"
using namespace std;

#ifndef QUINE_H
#define QUINE_H
class Quine
{
public:
	Quine(string = "input.txt",string = "output.txt",int = 10);
	vector<Minterm>minterms;
	vector<int>minterms_no;
	vector<vector<vector<Implicant>>>state_temp;/*存Quine McClusky Procedure各個round的各個column(round,column,No.)*/
	vector<vector<vector<int>>> group_choose;/*儲存Quine McClusky Procedure各個column中的組合是否被選過(有為1,沒有為0)*/
	vector<int>dont_care;/*儲存讀進的minterm是否為dontcare(是為1,不是為0)*/
	vector<int>essential_temp;/*用來記minterm被使用過的次數,為1的話擁有該minterm的implicant為essential*/

	vector<Implicant>petrick_input;/*用來存所有剩下沒被打勾的Implicant*/
	vector<Implicant>petrick_input_essential;/*用來存essential的Implicant，用這個vector來檢查哪些minterm已經被包含到了*/
	vector<Implicant>petrick_input_prime;/*用來存傳進Petrick Method的prime Implicant*/
	vector<int>petrick_input_minterms;/*用來存傳進Petrick Method的minterms*/
	vector<vector<int>>petrick_input_minterms_include;/*將要傳進Petrick Method的資料整理成minterm被包含在哪幾個式子裡面的形式*/
	void Petrick(int, vector<int>);/*用來做Petrick Method的遞迴*/
	vector<vector<int>>answer_mul;/*用來存Petrick Method中相乘式展開後的各種組合*/
	vector<vector<Implicant>>answers;/*用來存答案*/
private:
};
#endif