#include <iostream>

using namespace std;

class Rectangle
{
	private:
		void _swap(int *, int *);
	public:
		int x1, x2, y1, y2;
		Rectangle(int, int, int, int);
		void setSize(int, int, int, int);
		void move(int, int);
		Rectangle * minFromTwo(Rectangle *);
		Rectangle * intersection(Rectangle *);
};

Rectangle::Rectangle(int _x1, int _y1, int _x2, int _y2)
{
	setSize(_x1, _y1, _x2, _y2);
}

void Rectangle::_swap(int * l, int * r)
{
	int t = *l;
	l = r;
	*r = t;
}

void Rectangle::setSize(int _x1, int _y1, int _x2, int _y2)
{
	if (x2 < x1)
	{
		int t = x2;
		x2 = x1;
		x1 = t;
	}
	if (y2 < y1)
	{
		int t = y2;
		y2 = y1;
		y1 = t;
	}
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;
}

void Rectangle::move(int _x, int _y)
{
	setSize(x1+_x, y1+_y, x2+_x, y2+_y);
}

Rectangle * Rectangle::intersection(Rectangle * right)
{
	Rectangle * trueLeft = this;
	Rectangle * trueRight = right;
	Rectangle * trueTop = this;
	Rectangle * trueBottom = right;
	// guaranted left
	if (this->x1 > right->x1)
	{
		trueLeft = right;
		trueRight = this;
	}
	int x1, y1, x2, y2;
	if (trueLeft->x2 > trueRight->x1)
	{
		x1 = trueRight->x1;
		if (trueLeft->x2 < trueRight->x2)
			x2 = trueLeft->x2;
		else
			x2 = trueRight->x2;
	} else
	{
		// no intersection by Ox
		return NULL;
	}
	if (this->y1 < right->y1)
	{
		trueTop = right;
		trueBottom = this;
	}
	if (trueBottom->y2 > trueTop->y1)
	{
		y1 = trueTop->y1;
		if (trueBottom->y2 < trueTop->y2)
			y2 = trueBottom->y2;
		else
			y2 = trueTop->y2;
	} else
	{
		// no intersection by Oy
		return NULL;
	}
	return new Rectangle(x1, y1, x2, y2);
}

Rectangle * Rectangle::minFromTwo(Rectangle * right)
{
	int _x1, _y1, _x2, _y2;
	if (this->x1 < right->x1)
		_x1 = this->x1;
	else
		_x1 = right->x1;
	if (this->y1 < right->y1)
		_y1 = this->y1;
	else
		_y1 = right->y1;
	if (this->x2 < right->x2)
		_x2 = right->x2;
	else
		_x2 = this->x2;
	if (this->y2 < right->y2)
		_y2 = right->y2;
	else
		_y2 = this->y2;
	return new Rectangle(_x1, _y1, _x2, _y2);
}

int main()
{
	Rectangle * one;
	Rectangle * two = new Rectangle(0,0,4,4);
	Rectangle * three;

	int x1, y1, x2, y2;
	cout << "Enter first rectangle x1 y1 x2 y2: ";
	cin >> x1 >> y1 >> x2 >> y2;
	one = new Rectangle(x1, y1, x2, y2);
	cout << "Enter second rectangle x1 y1 x2 y2: ";
	cin >> x1 >> y1 >> x2 >> y2;
	two = new Rectangle(x1, y1, x2, y2);


	char command = '$';

	while (command != '0')
	{
		if (command == '1')
		{
			three = one->intersection(two);
			if (NULL != three)
				cout << "Cooordinates x1 y1 x2 y2: " << three->x1 << " " << three->y1 << " " << three->x2 << " " << three->y2 << endl;
			else
				cout << "Sorry, there's no intersection" << endl;
			delete three;
		} else if (command == '2')
		{
			three = one->minFromTwo(two);
			cout << "Coordinates: x1 y1 x2 y2: " << three->x1 << " " << three->y1 << " " << three->x2 << " " << three->y2 << endl;
			delete three;
		} else if (command == '3' || command == '4')
		{
			cout << "Enter rectangle x1 y1 x2 y2: ";
			cin >> x1 >> y1 >> x2 >> y2;
			if (command == '3')
				one->setSize(x1, y1, x2, y2);
			else
				two->setSize(x1, y1, x2, y2);
		} else if (command == '5' || command == '6')
		{
			cout << "Enter difference for x and for y: ";
			cin >> x1 >> y1;
			if (command == '5')
				one->move(x1, y1);
			else
				two->move(x1, y1);
		} else if (command == '7')
		{
			cout << "First: " << one->x1 << " " << one->y1 << " " << one->x2 << " " << one->y2 << endl;
			cout << "Second: " << two->x1 << " " << two->y1 << " " << two->x2 << " " << two->y2 << endl;
		} else
		{
			cout << "Lol, what? Noone cares about that kind of troubles" << endl;
		}
		cout << endl;
		cout << "Enter number of the task what you want to do:" << endl;
		cout << " 0. Stop that shaitan-machine!!111" << endl;
		cout << " 1. Find intersection" << endl;
		cout << " 2. Find minimal containing two" << endl;
		cout << " 3. Change size of first" << endl;
		cout << " 4. Change size of second" << endl;
		cout << " 5. Move first" << endl;
		cout << " 6. Move second" << endl;
		cout << " 7. Print rectangle sizes" << endl;
		cout << "Task: ";	
		cin >> command;
		cout << endl;
	}

	return 0;
}
