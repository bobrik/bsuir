#include <fstream>

using namespace std;

struct trect
{
	int x1;
	int y1;
	int x2;
	int y2;
};

int min(int x, int y)
{
	if (x < y)
		return x;
	else
		return y;
}

int max(int x, int y)
{
	if (x > y)
		return x;
	else
		return y;
}

void readRect(trect * rect, ifstream & in)
{
	int x1, y1, x2, y2;
	
	in >> x1 >> y1 >> x2 >> y2;
	
	rect->x1 = min(x1, x2);
	rect->x2 = max(x1, x2);
	rect->y1 = min(y1, y2);
	rect->y2 = max(y1, y2);
}

void sort(int * tarr, int count)
{
	int buf;
	
	for (int i = 0; i < count; ++i)
		for (int j = 0; j < count; ++j)
			if (i < j && tarr[i] > tarr[j])
			{
				buf     = tarr[i];
				tarr[i] = tarr[j];
				tarr[j] = buf;
			}
}

void killDups(int * tarr, int * count)
{
	int to = 0;
	for (int from = 1; from < *count; ++from)
		if (tarr[from] != tarr[from-1])
		{
			++to;
			tarr[to] = tarr[from];
		}
	*count = to+1;
}

bool belongs(int x, int y, trect r)
{
	return (r.x1 <= x) && (x < r.x2) && (r.y1 <= y) && (y < r.y2);
}

int main()
{
	trect r[100];
	int n;
	
	ifstream in("rectarea.in");
	
	in >> n;
	
	for (int i = 0; i < n; ++i)
	{
		readRect(&r[i], in);
	}
	
	in.close();
	
	int xcount = 0, ycount = 0;
	int x[200], y[200];
	
	for (int i = 0; i < n; ++i)
	{
		x[xcount++] = r[i].x1;
		x[xcount++] = r[i].x2;
		y[ycount++] = r[i].y1;
		y[ycount++] = r[i].y2;
	}
	
	
	sort(x, xcount);
	killDups(x, &xcount);
	sort(y, ycount);
	killDups(y, &ycount);
	
	unsigned int area = 0;
	bool painted;
	for (int i = 0; i < xcount-1; ++i)
		for (int j = 0; j < ycount-1; ++j)
		{
			painted = false;
			for (int k = 0; k < n; ++k)
				if (belongs(x[i], y[j], r[k]))
				{
					painted = true;
					break;
				}
			if (painted)
				area += (x[i+1]-x[i])*(y[j+1]-y[j]);
		}
	
	ofstream out("rectarea.out");
	
	out << area << endl;
	
	out.close();
	
	return 0;
}