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
	
	ofstream file_out;//输出文件
	ifstream file_src;//源文件
	map<string,int>::iterator it_var;
	map<string,int> totalVar;
	map<string,int> keyword;//保留字
	TYPE sym[32];
	TYPE nsym;//当前类型
	string nsym_str;
	char *buf;
	void Init();
	void HandleLines(char *str);
public:
	Syntax();
	ERROR Process(string filename);
	~Syntax();

};