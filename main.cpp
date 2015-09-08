//Supports only ( | ) * + ?
#include "Stack.h"
#include "nfa.h"
//#define TEST
#define DO
#define NFA
char* re2post(char *re);
void re2postfix(char *re, char *buf);
void predo(char *re, char *buf);
int getPrio(char c);


enum {
	LEFT = -1,
	OR = 0,
	STAR = 1,
	PLUS = 1,
	QUES = 1,
	CON = 1,
	NORMAL = 2
};

int 
main() {
	
	char *re = "(A|B)+*ABB|adad?|cd";
	
	char *buf;
	buf = new char[MAX_SIZE];
	predo(re, buf);
#ifndef NFA
#ifndef DO
	while (*buf) {

		printf("%c", *buf++);
	}
#endif 


#ifdef DO
	char *postfix;
	postfix = new char[MAX_SIZE];

	re2postfix(buf, postfix);

	printf("\n\nsaltyx程序结果:\n");
	while (*postfix != '\0')
		printf("%c", *postfix++);
#endif

#ifdef TEST
	printf("\n------------------------------------------\n\nRUSS COX的程序结果：\n");
	char *post = re2post(re);
	while (*post != '\0')
		printf("%c", *post++);
	printf("\n------------------------------------------\n\n");
#endif
#endif

#ifdef NFA
	char *p = "ab|*";
	post2nfa(p);
//	verify(p);
	printf("nstate :%d\n", Nstate);
#endif
	PAUSE;
	return 0;
}

//saltyx
void
predo(char *re, char *buf) {

	bool signal = false; // 上个是字符 or ')'
	int pos = 0;
	while (*re) {
		if (signal && isalpha(*re)) {//上个是字母，并且现在也是字母，或者上个是 '）'
			buf[pos++] = '.';
		}
		if (isalpha(*re) || *re == '*' || *re == '?' || *re == '+' || *re == ')')
		{
			signal = true;	
		}
		else signal = false;
		buf[pos++] = *re++;	
	}
	buf[pos] = '\0';
}
void 
re2postfix(char *re, char *buf) {
	Stack<char> stack;

	int pos = 0;

	while (*re) {
		switch (*re)
		{
		case '(':
			stack.push('(');
			re++;
			break;
		case '|':
			while (stack.Top() != NULL 
				&& getPrio(stack.Top()) >= getPrio('|')
				) 
			{

				buf[pos++] = stack.pop();
			}
			stack.push('|');
			re++;
			break;
		case ')':
			while ( stack.Top() != '(' && stack.Top()!=NULL )
			{
				buf[pos++] = stack.pop();
			}
			if (stack.Top() == '(')
				stack.pop();
			re++;
			break;
		case '.':
			while (stack.Top() != NULL
				&& getPrio(stack.Top()) >= getPrio('.')
				)
			{

				buf[pos++] = stack.pop();
			}
			stack.push('.');
			re++;
			break;
		default:
			buf[pos++] = *re++;
			break;
		}
	}
	while ((buf[pos++] = stack.pop()) != NULL);
	buf[pos] = '\0';
}

int 
getPrio(char c) {
	switch (c)
	{
	case '|':
		return OR;
	case '*':
		return STAR;
	case '+':
		return PLUS;
	case '?':
		return QUES;
	case '(':
		return LEFT;
	case '.':
		return CON;
	default:
		return NORMAL;
	}
}

//RUSS COX的程序
char*
re2post(char *re)
{
	int nalt, natom;
	static char buf[8000];
	char *dst;
	struct {
		int nalt;
		int natom;
	}  paren[100], *p;

	p = paren;
	dst = buf;
	nalt = 0;
	natom = 0;
	if (strlen(re) >= sizeof buf / 2)//状态数必然小于re的2倍
		return NULL;
	for (; *re; re++) {
		switch (*re) {
		case '(':
			if (natom > 1) {
				--natom;
				*dst++ = '.';
			}
			if (p >= paren + 100)
				return NULL;
			p->nalt = nalt;
			p->natom = natom;
			p++;
			nalt = 0;
			natom = 0;
			break;
		case '|':
			if (natom == 0)
				return NULL;
			while (--natom > 0)
				*dst++ = '.';
			nalt++;
			break;
		case ')':
			if (p == paren)
				return NULL;
			if (natom == 0)
				return NULL;
			while (--natom > 0)
				*dst++ = '.';
			for (; nalt > 0; nalt--)
				*dst++ = '|';
			--p;
			nalt = p->nalt;
			natom = p->natom;
			natom++;
			break;
		case '*':
		case '+':
		case '?':
			if (natom == 0)
				return NULL;
			*dst++ = *re;
			break;
		default:
			if (natom > 1) {
				--natom;
				*dst++ = '.';
			}
			*dst++ = *re;
			natom++;
			break;
		}
	}
	if (p != paren)
		return NULL;
	while (--natom > 0)
		*dst++ = '.';
	for (; nalt > 0; nalt--)
		*dst++ = '|';
	*dst = 0;
	return buf;
}
