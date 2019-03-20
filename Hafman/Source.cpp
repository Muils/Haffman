#include "List.h"

List Build(char *s, int TAB[])		//построение упорядоченного по частоте встречаемости списка символов
{
	int i;
	for (i = 0; s[i]; i++)
		TAB[s[i]]++;
	List L;
	L.Type() = 0;
	char ch[2];
	for (i = 0; i<256; i++)
		if (TAB[i])
		{
			ch[0] = i;
			ch[1] = '\0';
			if (L.Head() == 0)
			{
				Node *p = new Node(ch, TAB[i]);
				L.Head() = p;
			}
			else
			{
				if (L.Head()->Freq()>TAB[i])
					L.AddToHead(ch, TAB[i]);
				else
				{
					Node *t = L.Head();
					while (t->Next() && t->Next()->Freq() < TAB[i])
						t = t->Next();
					if (t->Next() == 0)
						L.AddToTail(ch, TAB[i]);
					else
						L.AddAfter(ch, TAB[i], t);
				}
			}


		}
	return L;
}

void BuildTree(List &L)		// перестройка списка в дерево
{
	Node *t1, *t2, *t, *q;
	t1 = L.Head();
	int n1, n2, fr;
	while (t1->Next())
	{
		t2 = t1->Next();
		n1 = strlen(t1->STR());
		n2 = strlen(t2->STR());
		char *s = new char[n1 + n2 + 1];
		strcpy_s(s, strlen(s), t1->STR());
		strcpy_s(s, strlen(s), t2->STR());
		fr = t1->Freq() + t2->Freq();
		t = t2->Next();
		t1->Next() = 0;
		t2->Next() = 0;
		q = new Node(s, fr, 0, t1, t2);

		if (t == 0) L.Head() = q;
		else
		{
			L.Head() = t;
			if (t->Freq()>fr)	L.AddToHead(q);
			else
			{
				while (t->Next() && t->Freq()<fr)
					t = t->Next();
				if (t->Next() == 0)	L.AddToTail(q);
				else L.AddAfter(q, t);
			}
		}
		t1 = L.Head();
		delete[] s;
	}
	L.Type() = 1;
}

bool Find(char ch, char p[])		// поиск символа в строке
{
	for (int i = 0; i < strlen(p); i++) {
		if (p[i] == ch)
			return true;
	}
	return false;
}

void BuildCodeTAB(char CodeTAB[][10], int TAB[], List &L)
{
	int i;
	for (i = 0; i<256; i++)
		if (TAB[i])
		{
			Node *t = L.Head();
			while (t->Left())
				if (Find(i, t->Left()->STR()))
				{
					strcat_s(CodeTAB[i], "0");
					t = t->Left();
				}
				else
				{
					strcat_s(CodeTAB[i], "1");
					t = t->Right();
				}
		}
}

int main()
{
	int TAB[256] = { 0 };
	char s[80];
	puts("input s: ");
	gets_s(s);

	List L;
	L = Build(s, TAB);
	BuildTree(L);

	char CodeTAB[256][10];
	for (int i = 0; i<256; i++)
		CodeTAB[i][i] = '\0';
	BuildCodeTAB(CodeTAB, TAB, L);

	system("PAUSE");
	return 0;
}