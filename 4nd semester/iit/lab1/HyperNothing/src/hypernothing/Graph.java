/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package hypernothing;

import java.util.Stack;
import java.util.Vector;
import java.util.HashMap;

/**
 *
 * @author bobrik
 */
public class Graph
{
    private Vector  nodes;
    private HashMap nodeConnections;

    public Graph(Vector elements, HashMap elementConnections)
    {
	this.nodes = elements;
	this.nodeConnections = elementConnections;
    }

    public int maxDistance(Object start, Object end)
    {
	// NP-complete task
	if (!nodes.contains(start) || !nodes.contains(end))
	{
	    return 0;
	}

	Vector<Integer> nodeWeights = new Vector<Integer>();
	for (int i = 0; i < nodes.size(); ++i)
	{
	    nodeWeights.addElement(0);
	}

	Stack currentPath = new Stack();

	currentPath.addElement(start);

	_maxDistanceHelper(currentPath, nodeWeights, end);

	return new Integer(nodeWeights.elementAt(nodes.indexOf(end)).toString());
    }

    private void _maxDistanceHelper(Stack currentPath, Vector<Integer> nodeWeights, Object end)
    {
	Object currentNode = currentPath.peek();
	for (int i = 0; i < ((Vector) nodeConnections.get(currentNode)).size(); ++i)
	{
	    Object nodeConnection = ((Vector) nodeConnections.get(currentNode)).elementAt(i);
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
	nodeWeights.setElementAt(0, nodes.indexOf(currentNode)); // let's give that node another chanse
	currentPath.pop();
    }
}
