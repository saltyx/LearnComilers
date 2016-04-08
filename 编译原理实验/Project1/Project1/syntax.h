#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <assert.h>
#include "pl0.h"
using namespace std;
typedef pair<string, int> new_pair;
typedef pair<TYPE, string> new_pair_T;
class Syntax {

private:
	
	ofstream file_out;//����ļ�
	ifstream file_src;//Դ�ļ�
	map<string,int>::iterator it_var;
	map<string,int> totalVar;
	map<string,int> keyword;//������
	TYPE sym[32];
	TYPE nsym;//��ǰ����
	string nsym_str;
	char *buf;
	void Init();
	void HandleLines(char *str);
public:
	Syntax();
	ERROR Process(string filename);
	~Syntax();

};