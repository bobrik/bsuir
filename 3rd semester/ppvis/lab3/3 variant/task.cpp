#include <iostream>

using namespace std;

/*
 Наследование
 - Закрытое
 + Открытое
 - Защищённое
 
 + Виртуальные функции
 - using-директива
 + Виртуальное наследование
*/


class Shape
{
	public:
		virtual bool containsDot(int, int, int) = 0;
};

class Surface : virtual public Shape
{
	public:
		virtual int getPerimeter() = 0;
		bool containsDot(int, int, int);
};

bool Surface::containsDot(int x, int y, int z)
{
	return false;
}

class EmptyShape : virtual public Surface
{
	public:
		int getPerimeter();
};

int EmptyShape::getPerimeter()
{
	return 0;
}

class Volumetric : virtual public Shape
{
	public:
		virtual int getVolume() = 0;
};

class SolidOfRevolution : virtual public Shape
{
	protected:
	public:
		
};

class Parallelepiped : virtual public Volumetric
{
	public:
		int getVolume();
		virtual bool containsDot(int, int, int);
};

int Parallelepiped::getVolume()
{
	return 11;
}

bool Parallelepiped::containsDot(int x, int y, int z)
{
	return true;
}

class Cube : virtual public Parallelepiped
{
	public:
		int getVolume();
};

int Cube::getVolume()
{
	return 22;
}


class EmptyCube : public EmptyShape, public Cube
{
	public:
		// using не хочет, хоть убейся:
		//  task.cpp:116: ошибка: отсутствует уникальное переопределение ‘virtual bool Shape::containsDot(int, int, int)’ в ‘EmptyCube’
		//  task.cpp:116: ошибка: отсутствует уникальное переопределение ‘virtual bool Shape::containsDot(int, int, int)’ в ‘EmptyCube’
// 		using Surface::containsDot;
		bool containsDot(int x, int y, int z) { return Surface::containsDot(x,y,z); };
};




int main()
{
	Cube cube;
	Parallelepiped parallelepiped;
	EmptyCube emptycube;
	
	cout << "Parrallelepiped volume: "
		<< parallelepiped.getVolume() << endl
		<< "Cube volume: "
		<< cube.getVolume() << endl
		<< "Empty cube volume: "
		<< emptycube.getVolume() << endl
		<< "Empty cube have dot inside: "
		<< emptycube.containsDot(1,2,3)
		<< endl;
		
	
	return 0;
}