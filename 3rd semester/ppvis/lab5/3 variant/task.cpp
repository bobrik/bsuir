#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;


enum incidency_type {EMPTY, DIRECT, INVERTED};

class Graph
{
	private:
		vector< vector<short int> * > * incidency;
		bool _hasPath(short int, short int);
		map<short int, bool> * _getAcessible(short int, short int = -1);
	public:
		Graph(vector< vector<short int> * > *);
		bool isBlah();
};

Graph::Graph(vector< vector<short int> * > * _incidency)
{
	// external - edges
	// internal - vertices
	incidency = _incidency;
}

bool Graph::isBlah()
{
	map<short int, bool> * marked = _getAcessible(0);
	bool answer = true;
	int verticesCount = (*(incidency->begin()))->size();
	for (int distance = 0; distance < verticesCount; ++distance)
	{
		if ((*marked)[distance] == false && !this->_hasPath(distance, 0))
		{
			answer = false;
			break;
		}
	}
	
	delete marked;
	
	return answer;
}

map<short int, bool> * Graph::_getAcessible(short int start, short int end)
{
	map<short int, bool> * marked = new map<short int, bool>;
	queue<short int> * vertices = new queue<short int>;
	vector< vector<short int> * >::iterator i;
	vector<short int>::iterator j;
	
	int distance;
	int verticesCount = (*(incidency->begin()))->size();
	for (distance = 0; distance < verticesCount; ++ distance)
	{
		(*marked)[distance] = false;
	}
	(*marked)[start] = true;
	
	if (verticesCount > start)
	{
		vertices->push(start);
	}
	
	short int vertex;
	while (!vertices->empty())
	{
		vertex = vertices->front();
		vertices->pop();
		for (i = incidency->begin(); i < incidency->end(); ++i)
		{
			if ((*i)->at(vertex) == INVERTED)
			{
				// vertex hast edge starting from it and not yet marked
				distance = 0;
				for (j = (*i)->begin(); j < (*i)->end(); ++j, ++distance)
				{
					if (*j == DIRECT && vertex != distance)
					{
						vertices->push(distance);
						if (end == distance)
						{
							(*marked)[end] = true;
							while (!vertices->empty())
							{
								vertices->pop();
							}
							break;
						}
					}
				}
			}
		}
		(*marked)[vertex] = true;
	}
	
	delete vertices;
	
	return marked;
}

bool Graph::_hasPath(short int first, short int second)
{
	map<short int, bool> * marked = _getAcessible(first, second);
	
	bool answer = false;
	if ((*marked)[second])
	{
		answer = true;
	}
	
	delete marked;
	return answer;
}


int main()
{
	vector< vector<short int> * > * incidency = new vector< vector<short int> * >;
	vector<short int> * edge_0 = new vector<short int>;
	edge_0->push_back(INVERTED);
	edge_0->push_back(DIRECT);
	edge_0->push_back(EMPTY);
	vector<short int> * edge_1 = new vector<short int>;
	edge_1->push_back(EMPTY);
	edge_1->push_back(INVERTED);
	edge_1->push_back(DIRECT);
	incidency->push_back(edge_0);
	incidency->push_back(edge_1);
	Graph graf(incidency);
	cout << "ololo: " << graf.isBlah() << endl;
	return 0;
}