/*

Calculates symmetric difference of any sets.
Input from file "collections.in".

Copyright 2009 Ivan Babroŭ (email : ibobrik@gmail.com)

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the license, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to
the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

// Brace types
enum brace_type {ORIENTED_OPEN = '<', ORIENTED_CLOSE = '>', REGULAR_OPEN = '{', REGULAR_CLOSE = '}'};
// Collection type: oriented or regular
enum collection_type {ORIENTED, REGULAR};
// Element type: single or collection
enum element_type {SINGLE, COLLECTION};

class Collection;
class Element;
class Operations;

class Element
{
	private:
		// element type
		element_type _type;
	public:
		// single element value
		string value;
		// collection element value
		Collection * collection;
		Element(element_type);
		~Element();
		const element_type type() const;
		void setValue(string &);
		void setValue(Collection *);
		string toString() const;
		bool operator<(const Element &) const;
};

class Collection
{
	private:
		// vector for collection elements
		vector<Element> elements;
		// collection type
		collection_type _type;
		Element * _getElementPtr(string &, unsigned int &, unsigned int);
		bool _checkBalance(string &);
	public:
		bool isSorted;
		bool isCorrect;
		Collection(collection_type);
		Collection(string &);
		~Collection();
		const collection_type type() const;
		void pushElement(Element *);
		void show(int);
		int size();
		void sort();
		string toString();
		bool hasElement(string &);
	friend class Operations;
};

class Operations
{
	public:
		Collection * symDifference(Collection *, Collection *);
};


Collection::Collection(collection_type t)
{
	// Collection constructor
	// t - collection type
	_type = t;
	isSorted = true;
}

Collection::Collection(string & line)
{
	// Collection constructor
	// line - collection line, type determined automatically
	_type = REGULAR;
	isSorted = true;
	isCorrect = true;
	if (!_checkBalance(line))
	{
		cerr << "Incorrect line (check braces balance): " << line << endl;
		isCorrect = false;
	} else
	{
		unsigned int start = 1;
		while (start < line.length()-1)
		{
			Element * el = _getElementPtr(line, start, line.length()-1);
			if (el != NULL)
				pushElement(el);
			else
				break;
		}
		if (line != toString())
		{
			cerr << "What the hell did you enered, dude?" << endl;
			cerr << " Got:           " << line << endl;
			cerr << " But parsed as: " << toString() << endl;
			isCorrect = false;
		}
	}
}

Collection::~Collection()
{
	// TODO: fix memleaks
// 	vector<Element>::iterator i;
// 	for (i = elements.begin(); i < elements.end(); ++i)
// 		elements.erase(i);
}

const collection_type Collection::type() const
{
	// returns collection type
	return _type;
}

bool Collection::_checkBalance(string & line)
{
	stack<char> braces;
	for (unsigned int i = 1; i < line.length()-1; ++i)
	{
		if (line[i] == REGULAR_OPEN)
		{
			braces.push(REGULAR_OPEN);
		} else if (line[i] == REGULAR_CLOSE)
		{
			if (braces.empty() || (!braces.empty() && braces.top() != REGULAR_OPEN))
				return false;
			else
				braces.pop();
		} else if (line[i] == ORIENTED_OPEN)
		{
			braces.push(ORIENTED_OPEN);
		} else if (line[i] == ORIENTED_CLOSE)
		{
			if (braces.empty() || (!braces.empty() && braces.top() != ORIENTED_OPEN))
				return false;
			else
				braces.pop();
		}
	}
	return braces.empty();
}

Element * Collection::_getElementPtr(string & line, unsigned int & start, unsigned int end)
{
	// Gets element pointer
	// start & end - line positons to get next element
	Collection * collection;
	if (line[start] == REGULAR_OPEN)
	{
		collection = new Collection(REGULAR);
	} else if (line[start] == ORIENTED_OPEN)
	{
		collection = new Collection(ORIENTED);
	}
	Element * element = NULL;
	if ((line[start] >= '0' && line[start] <= '9') || (line[start] >= 'A' && line[start] <= 'z'))
	{
		string child;
		while (line[start] != ',' && start < end)
		{
			child = child+line[start];
			++start;
		}
		++start; // finish element to comma after it
		element = new Element(SINGLE);
		element->setValue(child);
	} else if (line[start] == ORIENTED_OPEN)
	{
		unsigned int i = start;
		int braces = 0;
		while (line[i] != ORIENTED_CLOSE || braces != 1)
		{
			if (line[i] == ORIENTED_OPEN)
				++braces;
			else if (line[i] == ORIENTED_CLOSE)
				--braces;
			++i;
		}
		element = new Element(COLLECTION);
		Collection * collection;
		collection = new Collection(ORIENTED);
		++start;
		while (start < i)
			collection->pushElement(_getElementPtr(line, start, i));
		element->setValue(collection);
		start = i+2; // finish element to comma after it
	} else if (line[start] == REGULAR_OPEN)
	{
		unsigned int i = start;
		int braces = 0;
		while (line[i] != REGULAR_CLOSE || braces != 1)
		{
			if (line[i] == REGULAR_OPEN)
				++braces;
			else if (line[i] == REGULAR_CLOSE)
				--braces;
			++i;
		}
		element = new Element(COLLECTION);
		Collection * collection;
		collection = new Collection(REGULAR);
		++start;
		while (start < i)
			collection->pushElement(_getElementPtr(line, start, i));
		element->setValue(collection);
		start = i+2; // finish element to comma after it
	} else
	{
		start = end; // go away with your stupid input
	}
	return element;
}

void Collection::pushElement(Element * element)
{
	// Adds new element to collection
	// element - pointer to new element
	elements.push_back(*element);
	isSorted = false;
}

void Collection::show(int deep = 0)
{
	// Prints collection with deep level
	// deep - deep of subcollection
	vector<Element>::const_iterator i;
	for (i = elements.begin(); i != elements.end(); ++i)
	{
		for (int d = 0; d <= deep; ++d)
			cout << " ";
		if (i->type() == SINGLE)
		{
			cout << "Single: " << i->value << endl;
		} else
		{
			cout << "Collection (" <<
				(i->collection->type() == REGULAR ? "regular" : "oriented") <<
				", " << (i->collection->isSorted ? "sorted" : "unsorted") <<
				"): " << endl;
			i->collection->show(deep+1);
		}
	}
}

int Collection::size()
{
	// Returns collection size
	return elements.size();
}

void Collection::sort()
{
	// Sorts collection lexicographically
	if (isSorted)
		return;
	if (type() == REGULAR)
	{
		std::sort(elements.begin(), elements.end());
	} else
	{
		// sort recursively if oriented collection
		vector<Element>::iterator i;
		for (i = elements.begin(); i < elements.end(); ++i)
			if (i->type() == COLLECTION)
				i->collection->sort();
	}
	isSorted = true;
}

string Collection::toString()
{
	// Returns collection representation as string
	string collection = "";
	vector<Element>::iterator i;
	for (i = elements.begin(); i != elements.end(); ++i)
	{
		collection += i->toString();
		if (i+1 != elements.end())
			collection += ',';
	}
	if (type() == REGULAR)
		collection = (char) REGULAR_OPEN + collection + (char) REGULAR_CLOSE;
	else
		collection = (char) ORIENTED_OPEN + collection + (char) ORIENTED_CLOSE;
	return collection;
}

bool Collection::hasElement(string & element)
{
	// Checks element presence in collection
	// element - string representation to search for
	vector<Element>::iterator i;
	for (i = elements.begin(); i < elements.end(); ++i)
		if (i->toString() == element)
			return true;
	return false;
}


Element::Element(element_type t)
{
	// Element constructor
	// t - element type
	_type = t;
	value = "";
	collection = NULL;
}

Element::~Element()
{
// 	if (_type == COLLECTION)
// 		delete collection;;
}

void Element::setValue(string & val)
{
	// Sets element value for single element
	// val - string value
	value = val;
}

void Element::setValue(Collection * col)
{
	// Sets element value for collection
	// col - pointer to target collection
	collection = new Collection(col->type());
	*collection = *col;
}

const element_type Element::type() const
{
	// returns element type
	return _type;
}

string Element::toString() const
{
	// Returns element representation as string
	if (type() == SINGLE)
		return value;
	else
		return collection->toString();
}

bool Element::operator<(const Element & el) const
{
	// Operator to check is element less than another
	// el - link to rvalue
	if (type() == COLLECTION)
		collection->sort();
	if (el.type() == COLLECTION)
		el.collection->sort();
	if (type() == SINGLE && el.type() == SINGLE)
		return value < el.value;
	else if (type() == COLLECTION && el.type() == COLLECTION)
		return toString() < el.toString();
	else if (type() == SINGLE && el.type() == COLLECTION)
		return true;
	else
		return false;
}


Collection * Operations::symDifference(Collection * left, Collection * right)
{
	// Calculates symmetric difference of collections
	// left & right - pointers to two collections
	// in A but not in B plus not in A but in B
	// may be realized as two operations like A/B plus B/A
	// but who freakin' cares?
	left->sort();
	right->sort();
	vector<string> elements;
	vector<string>::iterator j;
	string result;
	vector<Element>::iterator i;
	string t = ""; // temp for toString resolving
	for(i = left->elements.begin(); i < left->elements.end(); ++i)
	{
		t = i->toString();
		if (!right->hasElement(t))
			elements.push_back(t);
	}
	bool already = false;
	for(i = right->elements.begin(); i < right->elements.end(); ++i)
	{
		t = i->toString();
		if (!left->hasElement(t))
		{
			for (j = elements.begin(); j < elements.end(); ++j)
				if (*j == t)
				{
					already = true;
					break;
				}
			if (!already)
				elements.push_back(t);
		}
	}
	result = (char) REGULAR_OPEN;
	for (j = elements.begin(); j < elements.end(); ++j)
		result += *j + ',';
	if (result.length() != 1) // if not {}
		result = result.substr(0, result.length()-1);
	result += REGULAR_CLOSE;
	Collection * collection = new Collection(result);
	return collection;
}

int main()
{
	ifstream in("collections.in");
	string collectionExpression;
	Operations * psycho = new Operations;
	Collection * result = new Collection(REGULAR);
	while (getline(in, collectionExpression))
	{
		unsigned int pos = collectionExpression.find("=");
		if (pos != string::npos)
		{
			collectionExpression = collectionExpression.substr(pos+1);
			Collection * collection = new Collection(collectionExpression);
			if (!collection->isCorrect)
			{
				cout << "Incorrect input, so terminating" << endl;
				return 0;
			}
			result = psycho->symDifference(result, collection);
			delete collection;
		}
	}
	cout << "Result: " << result->toString() << endl;
	return 0;
}
