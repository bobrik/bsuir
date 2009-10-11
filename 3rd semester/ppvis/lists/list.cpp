#include <iostream>

using namespace std;

struct Spis 
{
	int info;
	Spis *Next, *Prev;
} *t, *begin, *end;

void Make(int i)
{
	t = new Spis;
	t->info = i;
	t->Next = t->Prev = NULL;
	begin = end = t;
}

void AddEnd(int i)
{
	t = new Spis;
	t->info = i;
	t->Next = NULL;
	t->Prev = end;
	end->Next = t;
	end = t;
}

void Insert(Spis *k, int i)
{
	Spis * t = begin;
	while (t != NULL)
	{
		if (t == k)
			break;
		t = t->Next;
	}
	t = new Spis;
	t->info = i;
	t->Prev = k;
	t->Next = k->Next;
	k->Next = t;
}

void Show()
{
	if (begin == NULL)
	{
		cout << "empty list" << endl;
		return;
	}
	Spis * t = begin;
	while (t != NULL)
	{
		cout << t->info << " ";
		t = t->Next;
	}
	cout << endl;
}


int main()
{
	Make(1);
	for (int i = 6; i > -3; --i)
		AddEnd(i);
	Insert(end->Prev, 100500);
	Show();
	return 0;
}
