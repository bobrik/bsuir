#include <fstream>
#include <iostream>

#define s 100

using namespace std;

bool isCorrect(int day, int month, int *dates)
{
	if (month < 0 || month > 11)
		return false;
	if (day < 0 || day > dates[month]-1)
		return false;
	return true;
}

int main()
{
	int dates[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	bool wins[31][12];
	int day = 0;
	int month = 0;
	ifstream in("dategame.in");
	in >> day >> month;
	in.close();
	for (int i = 11; i >= 0; --i)
		for (int j = dates[i]-1; j >= 0; --j)
			if (j != 30 || month != 11)
			{
				wins[j][i] = false;
				if (isCorrect(j+1, i, dates))
					if (!wins[j+1][i])
						wins[j][i] = true;
				if (isCorrect(j+2, i, dates))
					if (!wins[j+2][i])
						wins[j][i] = true;
				if (isCorrect(j, i+1, dates))
					if (!wins[j][i+1])
						wins[j][i] = true;
				if (isCorrect(j, i+2, dates))
					if (!wins[j][i+2])
						wins[j][i] = true;
			}
	/* for (int i = 0; i < 12; ++i)
	{
		for (int j = 0; j < dates[i]; ++j)
		{
			cout << (wins[j][i] ? 1 : 2) << (day == j+1 && month == i+1 ? "<" : " ");
		}
		cout << endl;
	} */
	ofstream out("dategame.out");
	if (wins[day-1][month-1])
		out << 1 << endl;
	else
		out << 2 << endl;
	out.close();
	return 0;
}
