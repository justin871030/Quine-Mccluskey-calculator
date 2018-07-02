#include<iostream>
#include<fstream>
#include"Quine.h"
using namespace std;

int main()
{
	string input_name="input2.txt";
	string output_name;
	cout << "Please enter the input data name:";
	/*cin >> input_name;*/
	/*cout << "Please enter the output data name:";
	cin >> output_name;*/
	Quine quine(input_name, output_name,10);
	system("pause");
}