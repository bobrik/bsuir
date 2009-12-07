#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <fstream>

using namespace std;


enum incidency_type {EMPTY, DIRECT, INVERTED};

class Graph
{
    private:
        vector< vector<short int> * > * incidency;
        bool _hasPath(short int, short int);
        map<short int, bool> * _getAcessible(short int, short int = -1);
    public:
        Graph(string);
        bool atLeastOneWayConnected();
        int getVerticesCount();
        set<int> * getIncident(int);
};

class GraphTasks
{
    public:
        static bool hasPath(Graph *, int, int);
        static map<int, bool> * getAcessible(Graph *, int, int = -1);
        static bool isAtLeastOneWayConnected(Graph *);
};

Graph::Graph(string filename)
{
    // external - edges
    // internal - vertices
    int vertices, edges;
    ifstream in(filename.c_str());
    in >> vertices >> edges;
    // filling with «zeros»
    incidency = new vector< vector <short int> * >;
    for (int i = 0; i < edges; ++i)
    {
        vector<short int> * edge = new vector<short int>;
        for (int j = 0; j < vertices; ++j)
            edge->push_back(EMPTY);
        incidency->push_back(edge);
    }
    // reading edges
    int from, to;
    vector< vector<short int> * >::iterator i;
    for (i = incidency->begin(); i < incidency->end(); ++i)
    {
        in >> from >> to;
        (*i)->at(from) = INVERTED;
        (*i)->at(to)   = DIRECT;
    }
}

int Graph::getVerticesCount()
{
    return (*(incidency->begin()))->size();
}

set<int> * Graph::getIncident(int vertex)
{
    vector< vector<short int> * >::iterator i;
    vector<short int>::iterator j;
    set<int> * incident = new set<int>;
    for (i = incidency->begin(); i < incidency->end(); ++i)
    {
        if ((*i)->at(vertex) == INVERTED)
        {
            int vertexTo = 0;
            for (j = (*i)->begin(); j < (*i)->end(); ++j, ++vertexTo)
            {
                if (*j == DIRECT)
                {
                    incident->insert(vertexTo);
                }
            }
        }
    }
    return incident;
}

bool GraphTasks::isAtLeastOneWayConnected(Graph * graph)
{
    bool answer = true;
    int verticesCount = graph->getVerticesCount();
    map<int, bool> * marked;
    for (int current = 0; current < verticesCount; ++current)
    {
        marked = GraphTasks::getAcessible(graph, current);
        for (int distance = 0; distance < verticesCount; ++distance)
        {
            if (distance == current)
                continue;
            if ((*marked)[distance] == false && !GraphTasks::hasPath(graph, distance, current))
            {
                answer = false;
                break;
            }
        }

        delete marked;

        if (!answer)
            break;
    }

    return answer;
}

map<int, bool> * GraphTasks::getAcessible(Graph * graph, int start, int end)
{
    map<int, bool> * marked = new map<int, bool>;
    queue<int> * vertices = new queue<int>;
    set<int> * incident;
    set<int>::iterator i;
    
    int distance;
    int verticesCount = graph->getVerticesCount();
    for (distance = 0; distance < verticesCount; ++ distance)
    {
        (*marked)[distance] = false;
    }
    (*marked)[start] = true;
    
    vertices->push(start);
    
    short int vertex;
    while (!vertices->empty())
    {
        vertex = vertices->front();
        vertices->pop();
        incident = graph->getIncident(vertex);
        for (i = incident->begin(); i != incident->end(); ++i)
        {
            if (!(*marked)[(*i)])
            {
                if (end == (*i))
                {
                    (*marked)[end] = true;
                    while (!vertices->empty())
                    {
                        vertices->pop();
                    }
                    break;
                } else
                {
                    vertices->push(*i);
                }
            }
        }
        delete incident;
        (*marked)[vertex] = true;
    }
    
    delete vertices;
    
    return marked;
}

bool GraphTasks::hasPath(Graph * graph, int start, int end)
{
    map<int, bool> * marked = GraphTasks::getAcessible(graph, start, end);
    
    bool answer = false;
    if ((*marked)[end])
    {
        answer = true;
    }
    
    delete marked;
    return answer;
}


int main()
{
    Graph graph("task.in");
    
    cout << "isAtLeastOneWayConnected: " << GraphTasks::isAtLeastOneWayConnected(&graph) << endl;
    return 0;
}