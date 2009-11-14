#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class MSD
{
	protected:
		static unsigned int _getElementSize(int);
		static unsigned int _getElementSize(string &);
		static char _getElementDigit(int, int);
		static char _getElementDigit(string &, int);
		template<class T> static void _sort(vector<T *> *, unsigned int);
		template<class T> static vector<T *> * _getElementsPtrsVector(T *, int);
		template<class T> static vector<T *> * _getElementsPtrsVector(vector<T> &);
	public:
		template<class T> static void sort(T *, int);
		template<class T> static void sort(vector<T> &);
};


unsigned int MSD::_getElementSize(int number)
{
	int size = 0;
	
	do {
		number = number/10;
		++size;
	} while (number > 0);
	
	return size;
}

unsigned int MSD::_getElementSize(string & str)
{
	return str.length();
}

char MSD::_getElementDigit(int number, int digit)
{
	int length = MSD::_getElementSize(number);
	while(length > digit+1)
	{
		number = number/10;
		length--;
	}
	
	return number%10;
}

char MSD::_getElementDigit(string & str, int digit)
{
	return str[digit];
}

template<class T>
void MSD::_sort(vector<T *> * basket = NULL, unsigned int position = -1)
{
	if (basket->size() < 2)
		return; // basket have no need to be sorted
	
	bool stop = true;
	typename vector<T *>::iterator i;
	for (i = basket->begin(); i != basket->end()-1; ++i)
	{
		if (**i != **(i+1))
		{
			stop = false;
			break;
		}
	}
	if (stop)
		return;
	
	map< char, vector<T *> * > * baskets = new map< char, vector<T *> * >;
	typename map< char, vector<T *> * >::iterator iter;
	vector<T *> * sorted = new vector<T *>;
	
	(*baskets)[0] = new vector<T *>;
	for (i = basket->begin(); i != basket->end(); ++i)
	{
		if (MSD::_getElementSize(**i) < position)
		{
			(*baskets)[0]->push_back((*i));
		} else
		{
			if (baskets->find(MSD::_getElementDigit(**i, position)) == baskets->end())
			{
				(*baskets)[MSD::_getElementDigit(**i, position)] = new vector<T *>;
			}
			(*baskets)[MSD::_getElementDigit(**i, position)]->push_back((*i));
		}
	}
	
	for (iter = baskets->begin(); iter != baskets->end(); ++iter)
	{
		MSD::_sort(iter->second, position+1);
		for (i = iter->second->begin(); i != iter->second->end(); ++i)
		{
			sorted->push_back(*i);
		}
		baskets->erase(iter);
	}
	delete baskets;
	
	int ii = 0;
	for (i = sorted->begin(); i != sorted->end(); ++ii)
	{
		basket->at(ii) = *i;
		sorted->erase(i);
	}
	delete sorted;
}

template<class T>
vector<T *> * MSD::_getElementsPtrsVector(T * array, int size)
{
	vector<T *> * elementsPtrs = new vector<T *>;
	for (int i = 0; i < size; ++i)
		elementsPtrs->push_back(&array[i]);
	return elementsPtrs;
}

template<class T>
vector<T *> * MSD::_getElementsPtrsVector(vector<T> & initialVector)
{
	vector<T *> * elementsPtrs = new vector<T *>;
	typename vector<T>::iterator i;
	for (i = initialVector.begin(); i != initialVector.end(); ++i)
		elementsPtrs->push_back(&(*i));
	return elementsPtrs;
}

template<class T>
void MSD::sort(T * array, int size)
{
	vector<T *> * elementsPtrs = MSD::_getElementsPtrsVector(array, size);
	typename vector<T *>::iterator i;
	
	MSD::_sort(elementsPtrs, 0);
	
	T * sorted = new T[size];
	int ii = 0;
	for (i = elementsPtrs->begin(); i != elementsPtrs->end(); ++i, ++ii)
	{
		sorted[ii] = (**i);
	}
	
	for (ii = 0; ii < size; ++ii)
		array[ii] = sorted[ii];
	
// 	delete sorted;
	delete elementsPtrs;
}

template<class T>
void MSD::sort(vector<T> & unsorted)
{
	vector<T *> * elementsPtrs = MSD::_getElementsPtrsVector(unsorted);
	typename vector<T *>::iterator i;
	vector<T> * sorted = new vector<T>;
	typename vector<T>::iterator ii;
	
	MSD::_sort(elementsPtrs, 0);
	
	for (i = elementsPtrs->begin(); i != elementsPtrs->end(); ++i)
	{
		sorted->push_back(**i);
	}
	
	for (ii = unsorted.begin(); ii != unsorted.end();)
	{
		unsorted.erase(ii);
	}
	
	for (ii = sorted->begin(); ii != sorted->end();)
	{
		unsorted.push_back(*ii);
		sorted->erase(ii);
	}
	
	delete elementsPtrs;
	delete sorted;
}



int main()
{
	string a[5];
	a[0] = "ez25";
	a[1] = "ololo!";
	a[2] = "efrololo";
	a[3] = "hell";
	a[4] = "efck";
	
	cout << "Unsorted array of strings:" << endl;
	for (int i = 0; i < 5; ++i)
		cout << a[i] << endl;
	cout << endl;
	
	MSD::sort(a, 5);
	
	cout << "Sorted out array of strings:" << endl;
	for (int i = 0; i < 5; ++i)
		cout << a[i] << endl;
	cout << endl;
	
	int aa[8] = {56,67,43,54,325,325,35,235};
	
	cout << "Unsorted array of integers:" << endl;
	for (int i = 0; i < 8; ++i)
		cout << aa[i] << endl;
	cout << endl;
	
	MSD::sort(aa, 8);
	
	cout << "Sorted out array of integers:" << endl;
	for (int i = 0; i < 8; ++i)
		cout << aa[i] << endl;
	cout << endl;
	
	vector<string> trololo;
	trololo.push_back("one");
	trololo.push_back("twe");
	trololo.push_back("tno");
	trololo.push_back("2one");
	trololo.push_back("ole");
	
	cout << "Unsorted vector of strings:" << endl;
	vector<string>::iterator iii;
	for (iii = trololo.begin(); iii != trololo.end(); ++iii)
		cout << *iii << endl;
	cout << endl;
	
	MSD::sort(trololo);
	
	cout << "Sorted out vector of strings:" << endl;
	for (iii = trololo.begin(); iii != trololo.end(); ++iii)
		cout << *iii << endl;
	cout << endl;
	
	vector<int> ololo;
	ololo.push_back(56);
	ololo.push_back(56);
	ololo.push_back(13);
	ololo.push_back(42);
	ololo.push_back(0);
	
	cout << "Unsorted vector of integers:" << endl;
	vector<int>::iterator ii;
	for (ii = ololo.begin(); ii != ololo.end(); ++ii)
		cout << *ii << endl;
	cout << endl;
	
	MSD::sort(ololo);
	
	cout << "Sorted out vector of integers:" << endl;
	for (ii = ololo.begin(); ii != ololo.end(); ++ii)
		cout << *ii << endl;
	
	return 0;
}