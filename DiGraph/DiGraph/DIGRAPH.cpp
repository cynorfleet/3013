/*---------------------------------------------------------------------------
UNIT NAME :   DiGraph.cpp
PURPOSE   :   Directed Graph / Adjacency Matrix Implementation
WRITTEN FOR : Data Structures
WRITTEN BY :  Christian Norfleet and Catherine Stringfellow
DATE :
---------------------------------------------------------------------------*/
#include "digraph.H"
#include <iostream>
#include <string>
using namespace std;

DiGraph::DiGraph(int n)
// PreCondition :    Graph has not been created and 0 <= n < MaxVertices
// PostCondition :   Graph is created and has n vertices and no edges
// Error Condition : Error if n < 0 or n >+ MaxVertices
{
	//initialize vector
	adjList.resize(n);
}

DiGraph::DiGraph(DiGraph & other)
// Requires : other has been created and initialized
// Ensures :  other is copied to this graph
// Checks :   none
{
	adjList = other.adjList;
}

DiGraph::~DiGraph()
// PreCondition :   Graph is created
// PostCondition :  Graph is not created
// ErrorCondition : none
{
	//deletes edges. Use size_t for unsigned variable
	for (size_t i = 0; i < adjList.size(); i++)
	{
		adjList[i].clearList();
	}
	//deletes Vertex Vector
	adjList.clear();
}

void DiGraph::SwapDiGraphs(DiGraph & other)
// PreCondition :   this graph and other are created and initialized
// PostCondition :  this = #other and other = #this
// ErrorCondition : none
{
	adjList.swap(other.adjList);
}

void DiGraph::AddEdge(int X, int Y)
// PreCondition :   Graph is created, X and Y are distinct vertices in Graph, and
//				    edge (X,Y) not in Graph
// PostCondition :  Graph is the same except an edge (X,Y) now exists
// ErrorCondition : Error if X or Y is not
//                  a vertex in Graph or if X and Y are not distinct or if
//                  edge (X,Y) is already in Graph
{
	//Check to see if in array already
	if (adjList.at(X).searchitem(Y))
		cout << "\nERROR: CANNOT ADD EDGE. ALREADY IN GRAPH\n";
	//Check if not distinct
	else if (X == Y)
		cout << "\nERROR: CANNOT ADD EDGE. X AND Y MUST BE DISTINCT\n";
	//If valid, add edge to graph
	else
		adjList.at(X).insertitem(Y);
}

void DiGraph::RemoveEdge(int X, int Y)
// Requires : Graph is created, X and Y are distinct vertices in Graph and
//            edge (X,Y) is in Graph
// Ensures :  Graph is the same except edge (X,Y) no longer exists
// Checks :   Error if X or Y is not
//            a vertex in Graph or if X and Y are not distinct or
//            if edge (X,Y) is not in Graph
{
	//If there is a vertex at X
	if ((adjList.at(X).isEmpty()) || (adjList.at(Y).isEmpty()))
		cout << "\nERROR: CANNOT DELETE EDGE. VERTEX DOES NOT EXIST\n";
	//Check to see if in array already
	else if (adjList.at(X).searchitem(Y))
		cout << "\nERROR: CANNOT DELETE EDGE. ALREADY IN GRAPH\n";
	//Check if not distinct
	else if (X == Y)
		cout << "\nERROR: CANNOT DELETE EDGE. X AND Y MUST BE DISTINCT\n";
	//If valid, add edge to graph
	else
		adjList.at(X).removeitem(Y);
}

bool DiGraph::IsEdge(int X, int Y)
// PreCondition :   Graph is created, X and Y are vertices in Graph
// PostCondition :  Graph is unchanged, IsEdge is true if (f edge (X,Y) is in Graph
// ErrorCondition : X or Y is not a vertex in Graph
{
	//Check if X is a vertex
	if (adjList.at(X).isEmpty())
	{
		cout << "\nERROR: (X) VERTEX DOES NOT EXIST\n";
		return false;
	}
	//Check if Y is a vertex
	else if (adjList.at(Y).isEmpty())
	{
		cout << "\nERROR: (Y) VERTEX DOES NOT EXIST\n";
		return false;
	}
	else
		return (adjList.at(X).searchitem(Y));
}

int DiGraph::GetNumberOfVertices() const
// PreCondition :  Graph is created
// PostCondition : Graph is unchanged, GetNumberofVertices is the number of
//                 vertices in Graph
// ErrorCondition : none
{
	return int (adjList.size());
}

void DiGraph::ToString(string & output, DiGraph & graph)
{
	int temp = 0;

	//go through specified graph's rows
	for (size_t i = 0; i < graph.adjList.size(); i++)
	{
		output += "From vertex " + to_string(i) + " to:\t";
		//reset list for next row
		graph.adjList[i].resetList();
		do
		{
			//If there is a edge store it in output
			if (!graph.adjList.at(i).isEmpty())
			{
				graph.adjList[i].retrieveNextitem(temp);
				output += to_string(temp) + "\t";
			}
			//keep going until end of the list
		} while (!graph.adjList[i].atEnd());
		output += "\n";
	}
}

void DiGraph::Complement(DiGraph & GComp)
{
	//Traverse Verticies
	for (int i = 0; i < GetNumberOfVertices(); i++)
	{
		//Traverse edges
		for (int z = 0; z < GetNumberOfVertices(); z++)
		{
			//if edge is not found and vertex is distinct add edge-complement
			if ((!adjList.at(i).searchitem(z)) && i != z)
				GComp.AddEdge(i, z);
		}
	}
}

void DiGraph::ResizeGraph(int n)
{
	//Change size of adjecentcy list to represent # of verticies
	adjList.resize(n);
}