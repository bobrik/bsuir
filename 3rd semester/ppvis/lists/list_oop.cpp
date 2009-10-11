#include <iostream>

using namespace std;

class Element;

class List
{
	private:
		Element * start;
		Element * end;
	public:
		List(int);
		void insert(int, Element *);
		void add(int);
		Element * getStart();
		Element * getEnd();
		Element * getElement(int);
		void show();
};

class Element
{
	public:
		Element(int);
		int data;
		Element * next;
		Element * prev;
};

List::List(int number)
{
	start = new Element(number);
	end = start;
}

void List::insert(int number, Element * after)
{
	Element * next = new Element(number);
	Element * cur = start;
	while (cur != NULL)
	{
		if (cur == after)
		{
			if (cur->next == NULL)
			{
				cur->next = next;
				next->prev = cur;
				next->next = NULL;
				end = next;
			} else
			{
				next->next = cur->next;
				next->next->prev = next;
				cur->next = next;
				next->prev = cur;
			}
			break;
		}
		cur = cur->next;
	}
}

void List::add(int number)
{
	Element * next = new Element(number);
	if (end->prev == NULL)
	{
		next->prev = start;
		start->next = next;
	} else
	{
		next->prev = end;
		end->next = next;
	}
	end = next;
}

Element * List::getStart()
{
	return start;
}

Element * List::getEnd()
{
	return end;
}

void List::show()
{
	Element * cur = start;
	while (cur != NULL)
	{
		cout << cur->data << " ";
		cur = cur->next;
	}
	cout << endl;
}

Element::Element(int number)
{
	data = number;
	prev = NULL;
	next = NULL;
}

int main()
{
	List * list = new List(5);
	for (int i = 7; i < 10; ++i)
		list->add(i);
	list->insert(100500, list->getStart()->next->next);
	list->show();

	return 0;
}