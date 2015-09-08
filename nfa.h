

#include "helper.h"
#include "Stack.h"

extern int Nstate = 0;

struct state
{
	int c;
	state *out;
	state *out1;//用作回溯
	int n;
	state(int c, state *out, state *out1) {
		this->c = c;
		this->out = out;
		this->out1 = out1;
		n = ++Nstate;
	}
};

union ptrlist
{
	ptrlist *next;
	state *s;
};

struct frag
{

	state *start;

	ptrlist *out;

	frag(state *s, ptrlist *n) {
		this->start = s;
		this->out = n;
	}
	frag(){}

};

void
patch(ptrlist *l, state *s)
{
	ptrlist *n;

	while (l) {
		n = l->next;
		l->s = s;
		l = n;
	}
}

ptrlist*
append(ptrlist *l1, ptrlist *l2)
{
	ptrlist *oldl;
	oldl = l1;
	
	while (l1)
		l1 = l1->next;

	l1 = l2;

	return oldl;
}

ptrlist*
listcreate(state **s) 
{
	ptrlist *l;
	l = (ptrlist *)s;
	l->next = NULL;

	return l;
}

state *
post2nfa(char *p)
{
	frag e1, e2, e;
	Stack<frag> stack;
	while (*p)
	{
		switch (*p)
		{
		case '.':
			e2 = stack.pop();
			e1 = stack.pop();
			patch(e1.out, e2.start);
//		e1.out->s = e2.start;
			stack.push(frag(e1.start, e2.out));
			break;
		case '|':
		{
			e2 = stack.pop();
			printf("pop %d\n", e2.start->c);
			e1 = stack.pop();
			printf("pop %d\n", e1.start->c);
			state *s;
			s = new state(SPLITE, e1.start, e2.start);
			stack.push(frag(s, append(e1.out, e2.out)));

			break;
		}
		case '?':
		{
			e = stack.pop();
			state *s;
			s = new state(SPLITE, e.start, NULL);
			stack.push(frag(s, append(e1.out, listcreate(&s->out1) ) ) );
			break;
		}
		case '+':
		{
			e = stack.pop();
			state *s;
			s = new state(SPLITE, e.start, NULL);
			patch(e.out, s);
			stack.push(frag(e.start, listcreate(&s->out1) ) );

			break;
		}
		case '*':
		{
			e = stack.pop();
			printf("pop %d\n", e.start->c);

			state *s;
			s = new state(SPLITE, e.start, NULL);
			patch(e.out, s);
			stack.push(frag(s, listcreate(&s->out1) ) );
			break;
		}
		default:
		{
			state *s;
			s = new state(*p, NULL, NULL);
			stack.push(frag(s, NULL));
			printf("push %d\n", stack.Top().start->c);

			break;
		}
		}
		p++;
	}
	state *matchstate;
	matchstate = new state(MATCH, NULL, NULL);
	e = stack.pop();
	//printf("%d\n", e.start->n);
	state *f = e.start;
	patch(e.out, matchstate);

	//while (f)
	//{
	//	printf("state %d is %d\n", f->n, f->c);PAUSE;
	//	f = f->out;
	//}
	return e.start;
}

void
verify(char *p)
{
	state *e;

	e = post2nfa(p);

	//printf("number of state is %d\n-------------------\n", Nstate);

	//while (e) {
	//	
	//	printf("state %d is %c\n", e->n, e->c);PAUSE;
	//	e = e->out;
	//}
		
}

//void
//print(state *s)
//{
//	
//}
