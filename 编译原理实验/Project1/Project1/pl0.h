#pragma once

const int NUM_RESERVED = 13;
const int BUF_SIZE = 100;//���ж�ȡ��BUF��С
enum TYPE
{
	nul, ident, number, _plus, _minus,
	times, slash, oddsym, eql, neq, 
	lss, leq, gtr, geq, lparen, 
	rparen, comma, semicolon, period,
	becomes,
	//����Ϊ������
	beginsym,endsym, ifsym, thensym, whilesym,
	writesym, readsym, dosym, callsym, constsym,
	varsym, procsym
};

//��������
enum ERROR
{
	FAILED_OPEN_FILE,
	NOT_A_IDENTIFIER,
	SUCESSED
};

#define white_blank (now == ' ' || now == 10 || now == 9)

#define tolower_case(x) x-'A'+'a'
#define s_isupper(x) x>='A' && x<= 'Z'
#define get_next now=buf[++index]
#define print file_out << "(" << Type2String(nsym) << ", "<< nsym_str << " )" << endl;

void s_tolower(char *, char *);//תСд
bool check_ident(char s);//����ʶ��


