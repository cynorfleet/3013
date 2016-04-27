/*---------------------------------------------------------------------------
UNIT NAME :   DiGraph.cpp
PURPOSE   :   Directed Graph / Adjacency Matrix Implementation
WRITTEN FOR : Data Structures
WRITTEN BY :  Christian Norfleet and Catherine Stringfellow
DATE :		  4/25/2016
---------------------------------------------------------------------------*/
#include "digraph.H"
#include <iostream>
#include <string>
using namespace std;

DiGraph::DiGraph(int n)
// Requires :   Graph has not been created and 0 <= n < MaxVertices
// Ensures :	Graph is created and has n vertices and no edges
// Checks :		Error if n < 0 or n >+ MaxVertices
{
	//initialize vector
	adjList.resize(n);
}

DiGraph::DiGraph(DiGraph & other)
// Requires : other has been created and initialized
// Ensures :  other is copied to this graph
// Checks :   NONE
{
	adjList = other.adjList;
}

DiGraph::~DiGraph()
// Requires :   Graph is created
// Ensures :	Graph is not created
// Checks :		NONE
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
// Requires :   this graph and other are created and initialized
// Ensures :	this = #other and other = #this
// Checks :		NONE
{
	adjList.swap(other.adjList);
}

void DiGraph::AddEdge(int X, int Y)
// Requires :   Graph is created, X and Y are distinct vertices in Graph, and
//				edge (X,Y) not in Graph
// Ensures :	Graph is the same except an edge (X,Y) now exists
// Checks :		Error if X or Y is not
//              a vertex in Graph or if X and Y are not distinct or if
//              edge (X,Y) is already in Graph
{
	//If X and Y are verticies in graph
	if ((X >= 0) && (size_t(X) < adjList.size()) && (Y >= 0) && (size_t(Y) < adjList.size()))
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
	//If X and Y are NOT verticies in graph print error
	else
		cout << "\nERROR: CANNOT ADD EDGE. X or Y not a vertex in Graph\n";
}

void DiGraph::RemoveEdge(int X, int Y)
// Requires :	Graph is created, X and Y are distinct vertices in Graph and
//				edge (X,Y) is in Graph
// Ensures :	Graph is the same except edge (X,Y) no longer exists
// Checks :		Error if X or Y is not
//				a vertex in Graph or if X and Y are not distinct or
//				if edge (X,Y) is not in Graph
{
	//If X and Y are verticies in graph
	if (!(X >= 0) || !(size_t(X) < adjList.size()) || !(Y >= 0) || !(size_t(Y) < adjList.size()))
	{
		cout << "\nERROR: CANNOT DELETE EDGE. X or Y not a vertex in Graph\n";
	}
	//If X and Y are verticies in graph
	else if ((X >= 0) && (size_t(X) < adjList.size()) && (Y >= 0) && (size_t(Y) < adjList.size()))
	{
		//Check if vertex has edges
		if (adjList.at(X).isEmpty())
			cout << "\nERROR: CANNOT DELETE EDGE. EDGE DOES NOT EXIST\n";
		//Check to see if in edge is in graph
		else if (adjList.at(X).searchitem(Y))
			cout << "\nERROR: CANNOT DELETE EDGE. EDGE NOT IN GRAPH\n";
		//Check if not distinct
		else if (X == Y)
			cout << "\nERROR: CANNOT DELETE EDGE. X AND Y MUST BE DISTINCT\n";
	}

	//If valid, remove edge in graph
	else
		adjList.at(X).removeitem(Y);
}

bool DiGraph::IsEdge(int X, int Y)
// Requires :   Graph is created, X and Y are vertices in Graph
// Ensures :	Graph is unchanged, IsEdge is true if (f edge (X,Y) is in Graph
// Checks :		X or Y is not a vertex in Graph
{
	//Check if X is a vertex
	if (adjList.at(X).isEmpty())
	{
		return false;
	}
	//Check if Y is a vertex
	else if (adjList.at(Y).isEmpty())
	{
		return false;
	}
	else
		return (adjList.at(X).searchitem(Y));
}

int DiGraph::GetNumberOfVertices() const
// Requires :	Graph is created
// Ensures :	Graph is unchanged, GetNumberofVertices is the number of
//				vertices in Graph
// Checks :		NONE
{
	return int(adjList.size());
}

void DiGraph::ToString(string & output, DiGraph & graph)
// Requires :	Graph is created, a string is initialized
// Ensures :	Graph is unchanged, visual representation of graph sent to output
// Checks :		NONE
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

int DiGraph::OutDegree(DiGraph & g, int indexcounter)
// Requires :	Graph is created, list is initialized
// Ensures :	Graph is unchanged, adds  # verticies coming in to a vertex
// Checks :		NONE
{
	//"vertex", is the vertex being used for matching out-degree computation
	//initialize temp and #of out-degrees
	int degreecounter = 0;
	int temp;

	//reset cursor to head of edge list
	adjList.at(indexcounter).resetList();

	//if there is an edge
	if (!adjList.at(indexcounter).isEmpty())
		do
		{	//increment degree
			degreecounter++;
			//move to next item
			adjList.at(indexcounter).retrieveNextitem(temp);
			//keep going until end of edge list for vertex
		} while (!adjList.at(indexcounter).atEnd());
		return (degreecounter);
}

int DiGraph::InDegree(DiGraph & g, int vertex)
// Requires :	Graph is created, list is initialized
// Ensures :	Graph is unchanged, adds verticies, vertex points to
// Checks :		NONE
{
	//initialize temp and #of in-degrees
	int degreecounter = 0;
	int temp;
	//traverse the vertex list
	for (int i = 0; i < g.GetNumberOfVertices(); i++)
	{
		//reset cursor to head of edge list
		adjList.at(i).resetList();
		//if there is an edge
		if (!adjList.at(i).isEmpty())
			do
			{
				//store the edge in temp for comparison
				adjList.at(i).retrieveNextitem(temp);
				//if its the vertex we are looking for increment counter
				if (temp == vertex)
					degreecounter++;
				//do this until we get to end of the edge list for vertex
			} while (!adjList.at(i).atEnd());
	}
	return (degreecounter);
}

void DiGraph::ResizeGraph(int n)
// Requires :	Graph is created, list is initialized
// Ensures :	Graph is unchanged, size of adjacency list = n
// Checks :		NONE
{
	//Change size of adjacency list to represent # of verticies
	adjList.resize(n);
}