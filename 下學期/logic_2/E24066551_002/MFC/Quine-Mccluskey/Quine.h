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
	vector<vector<vector<Implicant>>>state_temp;/*�sQuine McClusky Procedure�U��round���U��column(round,column,No.)*/
	vector<vector<vector<int>>> group_choose;/*�x�sQuine McClusky Procedure�U��column�����զX�O�_�Q��L(����1,�S����0)*/
	vector<int>dont_care;/*�x�sŪ�i��minterm�O�_��dontcare(�O��1,���O��0)*/
	vector<int>essential_temp;/*�ΨӰOminterm�Q�ϥιL������,��1���ܾ֦���minterm��implicant��essential*/

	vector<Implicant>petrick_input;/*�ΨӦs�Ҧ��ѤU�S�Q���Ī�Implicant*/
	vector<Implicant>petrick_input_essential;/*�ΨӦsessential��Implicant�A�γo��vector���ˬd����minterm�w�g�Q�]�t��F*/
	vector<Implicant>petrick_input_prime;/*�ΨӦs�ǶiPetrick Method��prime Implicant*/
	vector<int>petrick_input_minterms;/*�ΨӦs�ǶiPetrick Method��minterms*/
	vector<vector<int>>petrick_input_minterms_include;/*�N�n�ǶiPetrick Method����ƾ�z��minterm�Q�]�t�b���X�Ӧ��l�̭����Φ�*/
	void Petrick(int, vector<int>);/*�ΨӰ�Petrick Method�����j*/
	vector<vector<int>>answer_mul;/*�ΨӦsPetrick Method���ۭ����i�}�᪺�U�زզX*/
	vector<vector<Implicant>>answers;/*�ΨӦs����*/
private:
};
#endif