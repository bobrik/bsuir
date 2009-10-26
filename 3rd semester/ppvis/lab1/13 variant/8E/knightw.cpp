#include <iostream>
#include <fstream>
#include <queue>

#define MAXSIZE 50

using namespace std;

enum cell_status {FREE = 0, START = 1, FINISH = -1, PATH = -2, CUT = -3};
struct cell
{
	int i;
	int j;
};

bool isAccessable(int i, int j, int ** table, bool wayback = false)
{
	if (i < 0 || j < 0 || i > 49 || j > 49)
		return false;
	if (table[i][j] == FREE || table[i][j] == FINISH || (wayback == true && table[i][j] != CUT))
		return true;
	return false;
}

bool maybeUpdateQueue(int i, int j, int ** table, queue<cell> * cells, cell & finish, int step)
{
	if (isAccessable(i, j, table))
	{
		table[i][j] = step;
		if (i == finish.i && j == finish.j)
			return true;
		cell next;
		next.i = i;
		next.j = j;
		cells->push(next);
	}
	return false;
}

bool stepBackward(cell & finish, int i, int j, int ** table, int step)
{
	if (isAccessable(finish.i+i, finish.j+j, table, true) && table[finish.i+i][finish.j+j] == step-1)
	{
		finish.i = finish.i+i;
		finish.j = finish.j+j;
		table[finish.i][finish.j] = PATH;
		return true;
	}
	return false;
}


int main()
{
	ifstream in("knightw.in");
	int n = 0;
	int ** table = new int * [MAXSIZE];
	for (int i = 0; i < MAXSIZE; ++i)
	{
		table[i] = new int [MAXSIZE];
		for (int j = 0; j < MAXSIZE; ++j)
			table[i][j] = CUT;
	}

	in >> n;
	char cur;
	bool started = false;
	queue<cell> * cells = new queue<cell>;
	cell start, finish;
	// input
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
		{
			in >> cur;
			if (cur == '.')
			{
				table[i][j] = FREE;
			} else if (cur == '@')
			{
				if (!started)
				{
					started = true;
					start.i = i;
					start.j = j;
					cells->push(start);
					table[i][j] = START;
				} else
				{
					table[i][j] = FINISH;
					finish.i = i;
					finish.j = j;
				}
			}
		}

	// searching for way to
	while (!cells->empty())
	{
		cell current = cells->front();
		cells->pop();
		if (maybeUpdateQueue(current.i+1, current.j+2, table, cells, finish, table[current.i][current.j]+1))
			break;
		if (maybeUpdateQueue(current.i+1, current.j-2, table, cells, finish, table[current.i][current.j]+1))
			break;
		if (maybeUpdateQueue(current.i-1, current.j+2, table, cells, finish, table[current.i][current.j]+1))
			break;
		if (maybeUpdateQueue(current.i-1, current.j-2, table, cells, finish, table[current.i][current.j]+1))
			break;
		if (maybeUpdateQueue(current.i+2, current.j+1, table, cells, finish, table[current.i][current.j]+1))
			break;
		if (maybeUpdateQueue(current.i+2, current.j-1, table, cells, finish, table[current.i][current.j]+1))
			break;
		if (maybeUpdateQueue(current.i-2, current.j+1, table, cells, finish, table[current.i][current.j]+1))
			break;
		if (maybeUpdateQueue(current.i-2, current.j-1, table, cells, finish, table[current.i][current.j]+1))
			break;
	}

	while (!cells->empty())
		cells->pop();
	//delete cells;

	ofstream out("knightw.out");
	if (table[finish.i][finish.j] == FINISH)
	{
		out << "Impossible" << endl;
		out.close();
		return 0;
	}

	// find wayback
	cells->push(finish);
	int step = table[finish.i][finish.j];
	table[finish.i][finish.j] = PATH;
	while (!(finish.i == start.i && finish.j == start.j))
	{
		if (stepBackward(finish,  1,  2, table, step))
			continue;
		else if (stepBackward(finish,  1, -2, table, step))
			continue;
		else if (stepBackward(finish, -1,  2, table, step))
			continue;
		else if (stepBackward(finish, -1, -2, table, step))
			continue;
		else if (stepBackward(finish,  2,  1, table, step))
			continue;
		else if (stepBackward(finish,  2, -1, table, step))
			continue;
		else if (stepBackward(finish, -2,  1, table, step))
			continue;
		else if (stepBackward(finish, -2, -1, table, step))
			continue;
		--step;
	}

	// show wayback
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (table[i][j] == PATH)
				out << '@';
			else if (table[i][j] == CUT)
				out << '#';
			else
				out << '.';
		}
		out << endl;
	}
	out.close();
	
	return 0;
}