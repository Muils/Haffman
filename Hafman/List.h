#pragma once
#include <iostream>

using namespace std;

class Node
{
	char *str;
	int freq;
	Node *next, *left, *right;

public:
	Node()
	{
		str = new char[1];
		str[0] = '\0';
		freq = 0;
		next = left = right = 0;
	}

	Node(char *s, int fr = 0, Node *nxt = 0, Node *l = 0, Node *r = 0)
	{
		str = new char[strlen(s) + 1];
		strcpy_s(str, strlen(str), s);
		freq = fr;
		next = nxt;
		left = l;
		right = r;
	}

	~Node()
	{
		delete[] str;
	}

	int Freq()
	{
		return freq;
	}

	char *STR()
	{
		return str;
	}

	Node *& Next()
	{
		return next;
	}

	Node *& Left()
	{
		return left;
	}

	Node *& Right()
	{
		return right;
	}

	friend class List;
};

class List
{
	Node *head;
	int type;	// type=0 - линейный список, type=1 - дерево

public:
	List()
	{
		head = 0;
		type = 0;
	}

	~List()
	{
		//Clear();
	}

	//List(List &L)
	//List &operator= (List &L)

	void AddToTail(char *s, int x);
	void AddToTail(Node *p);
	void AddToHead(char *s, int x);
	void AddToHead(Node *p);
	void AddAfter(char *s, int x, Node *pr);
	void AddAfter(Node *p, Node *pr);
	//void Clear();

	void DelHead();

	bool Empty();

	Node *&Head()
	{
		return head;
	}

	int &Type()
	{
		return type;
	}
};

void List::AddToTail(char *s, int x)
{
	Node *q = new Node(s, x);
	if (head == 0) head = q;
	else
	{
		Node *t = head;
		while (t->next) t = t->next;
		t->next = q;
	}
}

void List::AddToTail(Node *p)
{
	if (head == 0) head = p;
	else
	{
		Node *t = head;
		while (t->next) t = t->next;
		t->next = p;
	}
}

void List::AddToHead(char *s, int x)
{
	Node *q = new Node(s, x);
	if (head == 0) head = q;
	else
	{
		q->next = head;
		head = q;
	}
}

void List::AddToHead(Node *p)
{
	if (head == 0) head = p;
	else
	{
		p->next = head;
		head = p;
	}
}

void List::AddAfter(char *s, int x, Node *pr)
{
	Node *q = new Node(s, x);
	q->next = pr->next;
	pr->next = q;
}

void List::AddAfter(Node *p, Node *pr)
{
	p->next = pr->next;
	pr->next = p;
}

void List::DelHead()
{
	Node *t = head->next;
	delete head;
	head = t;
}

//void List::Clear() {
//
//	while (!Empty())
//		DelHead();
//}

bool List::Empty()
{
	if (head)	return false;
	return true;
}