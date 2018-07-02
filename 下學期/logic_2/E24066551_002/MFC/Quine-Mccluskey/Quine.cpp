#include "stdafx.h"
#include<iostream>
#include<vector>
#include<fstream>
#include"Quine.h"
#include<math.h>
#include<stdlib.h>
#include <iomanip> 
using namespace std;

int strnum(string a)/*str轉int*/
{
	int store = 0;
	for (int i = 0; i < a.size(); i++)
	{
		store += (a[i] - 48) *pow(10, a.size() - i - 1);
	}
	return store;
}
Quine::Quine(string address, string out,int bit_num)
{
	/*讀檔*/
	fstream data(address, ios::in);
	fstream output(out, ios::out);
	string temp;
	dont_care.resize(pow(2,10));
	while (getline(data,temp))
	{
		if (temp[0]=='(')
		{
			string change;
			for (int i = 1; i < temp.size()-1; i++)
			{
				change.push_back(temp[i]);
			}
			temp = change;
			dont_care[strnum(temp)] = 1;
		}
		minterms_no.push_back(strnum(temp));
		Minterm input(strnum(temp), bit_num);
		minterms.push_back(input);
	}
	/*把讀進的minterm存成implaicnat放到state_temp裡*/
	state_temp.resize(bit_num + 1);
	group_choose.resize(bit_num + 1);
	state_temp[0].resize(bit_num + 1);
	group_choose[0].resize(bit_num + 1);
	for (int i = 0; i <minterms.size(); i++)/*設定好第一排*/
	{
		for (int j = 0; j < bit_num + 1; j++)
		{
			if (minterms[i].one_num==j)
			{
				Implicant a(minterms[i]);
				state_temp[0][j].push_back(a);
				group_choose[0][j].resize(group_choose[0][j].size() + 1);
			}
		}
	}
	for (int i = 0; i < bit_num; i++)/*開始每個round的隔壁欄的互相比較*/
	{
		state_temp[i + 1].resize(bit_num+1 - i);
		group_choose[i + 1].resize(bit_num+1 - i);
		for (int j = 0; j < state_temp[i].size()-1; j++)
		{
			for (int k = 0; k < state_temp[i][j].size(); k++)
			{
				for (int l = k + 1; l < state_temp[i][j].size(); l++)
				{
					if (state_temp[i][j][k] == state_temp[i][j][l])
					{
						group_choose[i][j][l] = -1;
					}
				}
			}
			for (int k = 0; k < state_temp[i][j].size(); k++)
			{
				for (int l = 0; l < state_temp[i][j+1].size(); l++)
				{
					/*用addable這個funtion來檢查兩個implicant是否可結合*/
					if (state_temp[i][j][k].addable(state_temp[i][j + 1][l]) && group_choose[i][j][k] != -1 && group_choose[i][j + 1][l]!=-1)
					{
						group_choose[i][j][k] = 1;
						group_choose[i][j + 1][l] = 1;
						Implicant temp(state_temp[i][j][k], state_temp[i][j + 1][l]);
						state_temp[i + 1][j].push_back(temp);
						group_choose[i + 1][j].resize(group_choose[i + 1][j].size()+1);
					}
				}
			}
		}
	}
	essential_temp.resize(minterms_no.size());
	for (int i = 0; i < state_temp.size(); i++)/*印每欄每欄比較後的結果*/
	{
		int check=0;
		for (int j = 0; j < state_temp[i].size(); j++)
		{
			if (state_temp[i][j].size()==0)
			{
				check++;
			}
		}
		if (check != state_temp[i].size())
		{
			cout<<endl <<"======Round "<< i + 1 << "======" << endl;
			output << endl << "======Round " << i + 1 << "======" << endl;
		}
		for (int j = 0; j < state_temp[i].size(); j++)
		{
			for (int k = 0; k < state_temp[i][j].size(); k++)
			{
				if (group_choose[i][j][k]==1)
				{
					cout << "v ";
					output << "v ";
				}
				else if (group_choose[i][j][k] == -1)
				{
					cout << "x ";
					output << "x ";
				}
				else if (i == 0 && dont_care[state_temp[i][j][k].minterms_no[0]]==1)
				{
					cout << "d ";
					output << "d ";
				}
				else
				{
					cout << "  ";
					output << "  ";
					petrick_input.push_back(state_temp[i][j][k]);
					for (int x = 0; x < state_temp[i][j][k].minterms_no.size(); x++)
					{
						for (int y = 0; y < minterms_no.size(); y++)
						{
							if (minterms_no[y]== state_temp[i][j][k].minterms_no[x])
							{
								essential_temp[y]++;
							}
						}
					}
				}
				for (int f = state_temp[i][j][k].bit.size()-1; f >=0;  f--)
				{
					if (state_temp[i][j][k].bit[f] == -1)
					{
						cout << "-";
						output << "-";
					}
					else
					{
						cout << state_temp[i][j][k].bit[f];
						output << state_temp[i][j][k].bit[f];
					}
				}
				/*cout << " "<<state_temp[i][j][k].minterm_num<<" ";
				output << " " << state_temp[i][j][k].minterm_num << " ";*/
				cout << " : " ;
				output << " : " ;
				for (int x = 0; x < state_temp[i][j][k].minterm_num; x++)
				{
					cout << state_temp[i][j][k].minterms_no[x] ;
					output<< state_temp[i][j][k].minterms_no[x] ;
					if (x!= state_temp[i][j][k].minterm_num-1)
					{
						cout << ",";
						output << ",";
					}
				}
				cout << endl;
				output << endl;
			}
			if (state_temp[i][j].size()!=0)
			{
				cout << "-------------------" << endl;
				output << "-------------------" << endl;
			}
		}
	}
	for (int i = 0; i < petrick_input.size(); i++)
	{
		for (int j = 0; j < petrick_input[i].minterms_no.size(); j++)
		{
			int check = 0;
			for (int k = 0; k < minterms_no.size(); k++)
			{
				if (petrick_input[i].minterms_no[j] == minterms_no[k]&& essential_temp[k]==1 && dont_care[minterms_no[k]] != 1)
				{
					petrick_input_essential.push_back(petrick_input[i]);
					check = 1;
				}
			}
			if (check==1)
			{
				break;
			}
			if (j == petrick_input[i].minterms_no.size()-1)
			{
				petrick_input_prime.push_back(petrick_input[i]);
			}
		}
	}
	vector<int> include_check(minterms.size());
	for (int i = 0; i < petrick_input_essential.size(); i++)
	{
		for (int j = 0; j < petrick_input_essential[i].minterms_no.size(); j++)
		{
			for (int k = 0; k <minterms_no.size(); k++)
			{
				if (petrick_input_essential[i].minterms_no[j] == minterms_no[k])
				{
					include_check[k]++;
				}
			}
		}
	}
	for (int i = 0; i < include_check.size(); i++)
	{
		if (include_check[i]==0 && essential_temp[i] != 1&&dont_care[minterms_no[i]]!=1)
		{
			petrick_input_minterms.push_back(minterms_no[i]);
		}
	}
	petrick_input_minterms_include.resize(petrick_input_minterms.size());
	for (int i = 0; i < petrick_input_prime.size(); i++)
	{
		for (int j = 0; j < petrick_input_prime[i].minterms_no.size(); j++)
		{
			/*cout << petrick_input_prime[i].minterms_no[j];*/
			for (int k = 0; k < petrick_input_minterms.size(); k++)
			{
				if (petrick_input_prime[i].minterms_no[j] == petrick_input_minterms[k])
				{
					petrick_input_minterms_include[k].push_back(i);
				}
			}
		}
	}
	/*for (int i = 0; i < petrick_input_minterms_include.size(); i++)
	{
		cout << petrick_input_minterms[i] <<" ";
		for (int j = 0; j < petrick_input_minterms_include[i].size(); j++)
		{
			cout << petrick_input_minterms_include[i][j] << " ";
		}
		cout << endl;
	}*/
	vector<int>tempp;
	Petrick(0, tempp);
	int least_count = 999999;
	for (int i = 0; i < answer_mul.size(); i++)/*找Petrick Method 裡面包含最少Implicant的數量*/
	{
		if (answer_mul[i].size()<= least_count)
		{
			least_count = answer_mul[i].size();
		}
		/*cout << endl<<i << ":";*/
	}
	vector<Implicant>temp_imp=petrick_input_essential;
	for (int i = 0; i < answer_mul.size(); i++)/*輸出的組合等於最少的數量，存進答案的vector裡*/
	{
		if (answer_mul[i].size() == least_count)
		{
			vector<Implicant>temp_imp2= temp_imp;
			for (int j = 0; j < answer_mul[i].size(); j++)
			{
				temp_imp2.push_back(petrick_input_prime[answer_mul[i][j]]);
			}
			answers.push_back(temp_imp2);
		}
	}
	if (answers.size()==0)/*Petrick Method 沒有傳出任何答案代表答案為所有的Prime都是Essential,所有Prime組合起就是答案*/
	{
		answers.resize(1);
		for (int i = 0; i < petrick_input_essential.size(); i++)
		{
			answers[0].push_back(petrick_input_essential[i]);
		}
		/*for (int t = 0; t < answers.size(); t++)
		{

			for (int i = 0; i < petrick_input_essential.size(); i++)
			{
				answers[t].push_back(petrick_input_essential[i]);
			}
		}*/
	}
	cout << "(The implicants marked with \"ｅ\" are essential implicants , marked with \"ｖ\" are choosed implicants)";
	output << "(The implicants marked with \"ｅ\" are essential implicants , marked with \"ｖ\" are choosed implicants)";
	for (int i = 0; i < answers.size(); i++)/*印結果*/
	{
		/*印圖*/
		cout << endl << "======================Result"<<i+1<<"======================" << endl;
		output << endl << "======================Result" << i + 1 << "======================" << endl;
		cout << endl << "                    |";
		output << endl << "                    |";
		for (int i = 0; i < minterms_no.size(); i++)
		{
			if (dont_care[minterms_no[i]]!=1)
			{
				cout.width(4);
				cout.setf(ios::right);
				cout << minterms_no[i];
				cout.fill(' ');
				output.width(4);
				output.setf(ios::right);
				output << minterms_no[i];
				output.fill(' ');
				if (i != minterms_no.size() - 1)
				{
					cout << ",";
					output << ",";
				}
			}
		}
		cout << endl << "--------------------+-----------------------------";
		output << endl << "--------------------+-----------------------------";
		for (int j = 0; j < petrick_input.size(); j++)
		{
			cout << endl;
			cout.width(20);
			cout.setf(ios::left);
			output << endl;
			output.width(20);
			output.setf(ios::left);
			/*answers[i][j].show_en();
			output << answers[i][j].bit_name; */
			petrick_input[j].show_en();
			output << petrick_input[j].bit_name;
			cout.fill(' ');
			cout << "|";
			output.fill(' ');
			output << "|";
			/*minterm包含在implicant時打x*/
			for (int n = 0; n < minterms_no.size(); n++)
			{
				if (dont_care[minterms_no[n]] != 1)
				{
					if (n == 0)
					{
						cout.width(4);
						cout.setf(ios::right);
						output.width(4);
						output.setf(ios::right);
						int check = 0;
						for (int k = 0; k < petrick_input[j].minterms_no.size(); k++)
						{
							if (petrick_input[j].minterms_no[k] == minterms_no[n])
							{
								check = 1;
							}
						}
						if (check == 1)
						{
							cout << "x";
							output << "x";
						}
						else
						{
							cout << " ";
							output << " ";
						}
						cout.fill(' ');
						output.fill(' ');
					}
					else
					{
						cout.width(5);
						cout.setf(ios::right);
						output.width(5);
						output.setf(ios::right);
						int check = 0;
						for (int k = 0; k < petrick_input[j].minterms_no.size(); k++)
						{
							if (petrick_input[j].minterms_no[k] == minterms_no[n])
							{
								check = 1;
							}
						}
						if (check == 1)
						{
							cout << "x";
							output << "x";
						}
						else
						{
							cout << " ";
							output << " ";
						}
						cout.fill(' ');
						output.fill(' ');
					}
				}
			}
			for (int qq = 0; qq < answers[i].size(); qq++)
			{
				if (petrick_input[j] == answers[i][qq])
				{
					int check = 0;
					for (int qq = 0; qq < petrick_input_essential.size(); qq++)
					{
						if (petrick_input[j] == petrick_input_essential[qq])
						{
							cout << " ｅ";
							output << " ｅ";
							check = 1;
						}
					}
					if (check == 0)
					{
						cout << " ｖ";
						output << " ｖ";
					}
				}
			}
		}
		/*印算式*/
		cout << endl << "--------------------+-----------------------------";
		cout << endl << "F(";
		output << endl << "--------------------+-----------------------------";
		output << endl << "F(";
		Minterm aaaaa;
		for (int z = 0; z <bit_num; z++)
		{
			cout << aaaaa.bit_name_base[z];
			output << aaaaa.bit_name_base[z];
			if (z!= bit_num -1)
			{
				cout << ",";
				output << ",";
			}
		}
		cout << ")=";
		output << ")=";
		for (int q = 0; q <  answers[i].size(); q++)
		{
			answers[i][q].show_en();
			output << answers[i][q].bit_name;
			if (q!= answers[i].size()-1)
			{
				cout << "+";
				output << "+";
			}
		}
		cout << endl;
		output << endl;
	}
}
void Quine::Petrick(int step, vector<int>temp)
{
	if (step!= petrick_input_minterms.size())
	{
		for (int i = 0; i < petrick_input_minterms_include[step].size(); i++)
		{
			int check = 0;
			for (int j = 0; j < temp.size(); j++)
			{
				if (petrick_input_minterms_include[step][i]==temp[j])
				{
					check = 1;
				}
			}
			if (check==0)
			{
				vector<int>temp_tem = temp;
				temp_tem.push_back(petrick_input_minterms_include[step][i]);
				Petrick(step + 1, temp_tem);
			}
			else
			{
				Petrick(step + 1, temp);
			}
		}
	}
	else
	{
		answer_mul.push_back(temp);
	}
}