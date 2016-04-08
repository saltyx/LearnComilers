//�������ڴ���
#include "syntax.h"
//#define DEBUG_1_1

string Type2String(TYPE type);
bool Check_Separator(char c);

typedef pair<string, int> new_pair;

Syntax::Syntax() {
	Init();

	buf = new char[BUF_SIZE];
}
void Syntax::Init() {
	//TODO: ��ʼ����ʶ��
	keyword.clear();

	keyword.insert(new_pair("begin", 0));		sym[0] = beginsym;
	keyword.insert(new_pair("call", 1));		sym[1] = callsym;
	keyword.insert(new_pair("const", 2));		sym[2] = constsym;
	keyword.insert(new_pair("do", 3));			sym[3] = dosym;
	keyword.insert(new_pair("end", 4));			sym[4] = endsym;
	keyword.insert(new_pair("if", 5));			sym[5] = ifsym;
	keyword.insert(new_pair("odd", 6));			sym[6] = oddsym;
	keyword.insert(new_pair("procedure", 7));	sym[7] = procsym;
	keyword.insert(new_pair("read", 8));		sym[8] = readsym;
	keyword.insert(new_pair("then", 9));		sym[9] = thensym;
	keyword.insert(new_pair("var", 10));		sym[10] = varsym;
	keyword.insert(new_pair("while", 11));		sym[11] = whilesym;
	keyword.insert(new_pair("write", 12));		sym[12] = writesym;
}
Syntax::~Syntax() {
	delete[] buf;
}
ERROR Syntax::Process(string filename) {

	file_src.open(filename);
	file_out.open("2.txt");

	while (file_src.getline(buf, BUF_SIZE)) {
		//���ж�ȡ
#ifdef DEBUG_MODE
		std::cout << "debug info:\n lines string===>" << buf << endl;
#endif // DEBUG
		s_tolower(buf, buf);
		char *str = new char[BUF_SIZE];//��ʱbuf
		HandleLines(str);
		delete[] str;
	}
	if (file_src.is_open())
		file_src.close();
	else
		return FAILED_OPEN_FILE;
	if (file_out.is_open())
		file_out.close();
	else
		return FAILED_OPEN_FILE;
	return SUCESSED;
}
//����buf
void Syntax::HandleLines(char *str) {
	int index = 0;
	char now = buf[index];//��ǰ���ڴ�����ַ�
	int k = 0;//��ʱbuf���±�
	string s;
	do {
		while (white_blank)
		{//���Կո�TAB�س�
			get_next;
			k = 0;//���¹�0
			continue;
		}
		if (check_ident(now)) {
			//������ַ����ʾ�п��ܳ��ֱ�ʶ���Լ������ֻ��߷Ƿ��ַ���
			do {
				str[k++] = now;
				get_next;
			} while (check_ident(now) || isdigit(now));//�������ĸ��������
			if (!Check_Separator(now) && !white_blank)
			{
				k = 0; continue;
			}
			str[k] = '\0';
			k = 0;
			string stmp(str); nsym_str = stmp;
			if ((it_var = keyword.find(stmp)) != keyword.end()) {
#ifdef DEBUG_MODE
			std::cout << "debug info :\n============keyword========\n" << str << "#" << endl;
#endif // DEBUG				//�Աȳɹ�
				nsym = sym[it_var->second];//������
				print;
				str[0] = '\0';
				stmp = "";
			}
			else {
				nsym = ident;
				print;
				//�Ա�ʧ��,����map���Ƿ���ڸ�ֵ
				if ((it_var = totalVar.find(stmp)) != totalVar.end())
				{
					//����
					it_var->second++;
				}
				else {
					totalVar.insert(new_pair(stmp, 1));
				}
#ifdef DEBUG_MODE
				std::cout << "debug info :\n============Ident========\n"
					<< stmp << endl;
#endif // DEBUG
			}
		}
		else {
			//����ĸ���ǵ���
			if (isdigit(now)) {
				//�����ǰ�ַ������֣��п�����֮����ַ�������
				k = 0; str[k++] = now;
				get_next;

				bool flag_number = true;//�ж��Ƿ�Ϊ�Ƿ���ʶ��
				while (now != '\0'
					&& (isdigit(now) || isalpha(now))) {
					if (isalpha(now)) {
						flag_number = false;
						while (now &&
							((isalpha(now)) || isdigit(now))) get_next;
#ifdef DEBUG
						cout << "��ʶ������\n";
						cout << "\n��������˳�\n";
						system("pause");
						exit(0);
#endif // DEBUG		
						//�����Ժ��������ĸ�����ַ�
					}
					else {
						str[k++] = now;
						get_next;
					}
				}
				//ѭ���������ж�
				if (flag_number) {
					str[k] = '\0';	k = 0;
					nsym = number;
					string str_(str);
					nsym_str = str;
#ifdef DEBUG_MODE
					std::cout << "debug info :\n============Num========\n"
						<< str_ << endl;
#endif // DEBUG					
					print;
				}
			}
			else {
				k = 0;
#ifdef DEBUG_1
				cout << "==========sym==========\n" << now << endl;
#endif // DEBUG_MODE				
				switch (now)
				{
				case '(':
					nsym = lparen;
					nsym_str = "(";
					print; get_next;
					break;
				case ')':
					nsym = rparen;
					nsym_str = ")";
					print; get_next;
					break;
				case ':':
					get_next;
					if (now == '=') {
						nsym = becomes;
						nsym_str = ":=";
						print; get_next;
					}
					else {
						nsym = nul;//δ֪
						nsym_str = ":" + now;
						print;
					}
					break;
				case '>':
					get_next;
					if (now == '=') {
						nsym = geq;
						nsym_str = ">=";
						print; get_next;
					}
					else {
						nsym = gtr;
						nsym_str = ">";
						print;
					}
					break;
				case '<':
					get_next;
					if (now == '=') {
						nsym = leq;
						nsym_str = "<=";
						print; get_next;
					}
					else {
						nsym = lss;
						nsym_str = "<";
						print;
					}
					break;
				case '=':
					nsym = eql;
					nsym_str = "=";
					print; get_next;
					break;
				case '*':
					nsym = times;
					nsym_str = "*";
					print; get_next;
					break;
				case '+':
					nsym = _plus;
					nsym_str = "+";
					print; get_next;
					break;
				case '-':
					nsym = _minus;
					nsym_str = "-";
					print; get_next;
					break;
				case ',':
					nsym = comma;
					nsym_str = ",";
					print; get_next;
					break;
				case ';':
					nsym = semicolon;
					nsym_str = ";";
					print; get_next;
					break;
				case '.':
					nsym = period;
					nsym_str = ".";
					print; get_next;
					break;
				case '/':
					nsym = slash;
					nsym_str = "/";
					print; get_next;
					break;
				default:
#ifdef DEBUG_1_1
					cout << now << endl;
#endif					
					get_next;
					while (now != '\0' && (isalpha(now) || isdigit(now)))get_next;
					//����֮���������ĸ�������ַ�
					break;
				}
			}
		
		}
	} while (now != '\0');
}


void s_tolower(char *src, char *dst)
{
	while (*src) {
		if (s_isupper(*src))
			*dst++ = tolower_case(*src++);
		else
			*dst++ = *src++;
	}
	*dst = '\0';
}

bool check_ident(char s) {//֧����ĸ���»���
	return (isalpha(s)) ? true : false;
}

string Type2String(TYPE type) {
	string ans = "";
	switch (type)
	{
	case nul:ans = "nul";
		break;
	case ident:ans = "ident";
		break;
	case number:ans = "number";
		break;
	case _plus:ans = "plus";
		break;
	case _minus:ans = "minus";
		break;
	case times:ans = "times";
		break;
	case slash:ans = "slash";
		break;
	case oddsym:ans = "oddsym";
		break;
	case eql:ans = "eql";
		break;
	case neq:ans = "neq";
		break;
	case lss:ans = "lss";
		break;
	case leq:ans = "leq";
		break;
	case gtr:ans = "gtr";
		break;
	case geq:ans = "geq";
		break;
	case lparen:ans = "lparen";
		break;
	case rparen:ans = "rparen";
		break;
	case comma:ans = "comma";
		break;
	case semicolon:ans = "semicolon";
		break;
	case period:ans = "period";
		break;
	case becomes:ans = "becomes";
		break;
	case beginsym:ans = "beginsym";
		break;
	case endsym:ans = "endsym";
		break;
	case ifsym:ans = "ifsym";
		break;
	case thensym:ans = "thensym";
		break;
	case whilesym:ans = "whilesym";
		break;
	case writesym:ans = "writesym";
		break;
	case readsym:ans = "readsym";
		break;
	case dosym:ans = "dosym";
		break;
	case callsym:ans = "callsym";
		break;
	case constsym:ans = "constsym";
		break;
	case varsym:ans = "varsym";
		break;
	case procsym:ans = "procsym";
		break;
	default:
		break;
	}
	return ans;
}
bool Check_Separator(char c) {
//����Ƿ�Ϊ�ָ���
	switch (c)
	{
	case '(':break;
	case ')':break;
	case ':':break;
	case '>':break;
	case '<':break;
	case '=':break;
	case '*':break;
	case '+':break;
	case '-':break;
	case ',':break;
	case ';':break;
	case '.':break;
	case '/':break;
	default:
		return false;
	}
	return true;
}


