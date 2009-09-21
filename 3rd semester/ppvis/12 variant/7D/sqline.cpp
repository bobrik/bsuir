#include <fstream>
#include <iostream>

#define s 100

using namespace std;

bool cross(int x1, int y1, int x2, int y2, int & n, int & w, int & e)
{
	x1 = x1*s;
	y1 = y1*s;
	x2 = x2*s;
	y2 = y2*s;
	int t = n*s;
	double s1 = t*(y1-w)-(e-w)*x1;
	double s2 = t*(y2-w)-(e-w)*x2;
	return (s1*s2 <= 0);
}

int main()
{
	int count = 0;
	int n, w, e;
	ifstream in("sqline.in");
	in >> n >> w >> e;
	in.close();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (cross(i, j, i+1, j, n, w, e)  || cross(i+1, j, i+1, j+1, n, w, e) ||
				cross(i, j, i, j+1, n, w, e) || cross(i+1, j+1, i, j+1, n, w, e))
				++count;
	ofstream out("sqline.out");
	out << count << endl;
	out.close();
	return 0;
}
