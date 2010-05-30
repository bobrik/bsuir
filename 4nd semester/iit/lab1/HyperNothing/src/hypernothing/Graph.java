/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


package hypernothing;

import java.util.Stack;
import java.util.Vector;
import java.util.HashMap;

/**
 * Graph representation class
 * @author bobrik
 */
public class Graph
{
    /**
     * Nodes list
     */
    private Vector<String>  nodes;
    /**
     * Connections map
     */
    private HashMap< String, Vector<String> > nodeConnections;

    /**
     * Create constant Graph object with prefilled elements and connections
     * @param elements vector of elements
     * @param elementConnections hash of connections
     */
    public Graph(Vector elements, HashMap elementConnections)
    {
	this.nodes = elements;
	this.nodeConnections = elementConnections;
    }

    /**
     * Calculate max distance bewteen vertices
     * @param start first vertex name
     * @param end last vertex name
     * @return path length
     */
    public String maxDistance(String start, String end)
    {
	// NP-complete task
	if (!nodes.contains(start) || !nodes.contains(end))
	{
	    return "No path";
	}

	Vector<Integer> nodeWeights = new Vector<Integer>();
	for (int i = 0; i < nodes.size(); ++i)
	{
	    nodeWeights.addElement(0);
	}

	Stack<String> currentPath = new Stack<String>();

	currentPath.addElement(start);

	_maxDistanceHelper(currentPath, nodeWeights, end);

	int maxNodeWeight = new Integer(nodeWeights.elementAt(nodes.indexOf(end)).toString());

	Vector<String> path = new Vector<String>();

	path.add(end);

	while (true)
	{
	    try
	    {
		path.add(nodes.elementAt(_prevStepNodeNumber(path.lastElement() , nodeWeights)));
	    } catch (Exception e)
	    {
		break;
	    }
	}

	String result = new String("\n");

	for (int i = path.size()-1; i > 0; --i)
	{
	    result += path.elementAt(i) + " -(1)> \n";
	}

	if (path.size() > 0)
	{
	    result += path.elementAt(0);
	}

	return result;
    }

    private int _prevStepNodeNumber(String node, Vector<Integer> nodeWeights) throws Exception
    {
	for (int i = 0; i < nodes.size(); ++i)
	{
	    Vector<String> connections = (Vector) nodeConnections.get(nodes.elementAt(i));
	    for (int j = 0; j < connections.size(); ++j)
	    {
		String currentNode = connections.elementAt(j);
		if (!currentNode.equals(node))
		{
		    continue;
		}
		if (nodeWeights.elementAt(i) == nodeWeights.elementAt(nodes.indexOf(node))-1)
		{
		    return i;
		}
	    }
	}
	throw new Exception("No way back!");
    }

    private void _maxDistanceHelper(Stack<String> currentPath, Vector<Integer> nodeWeights, String end)
    {
	String currentNode = currentPath.peek();
	for (int i = 0; i < nodeConnections.get(currentNode).size(); ++i)
	{
	    String nodeConnection = nodeConnections.get(currentNode).elementAt(i);
	    if (!currentPath.contains(nodeConnection))
	    {
		if (nodeWeights.elementAt(nodes.indexOf(nodeConnection)) < currentPath.size())
		{
		    nodeWeights.setElementAt(currentPath.size(), nodes.indexOf(nodeConnection));

		    if (!nodeConnection.equals(end))
		    {
			currentPath.push(nodeConnection);
			_maxDistanceHelper(currentPath, nodeWeights, end);
		    }
		}
	    }
	}
	//nodeWeights.setElementAt(0, nodes.indexOf(currentNode)); // let's give that node another chanse
	currentPath.pop();
    }
}
