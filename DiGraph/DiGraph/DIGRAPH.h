/*---------------------------------------------------------------------------
UNIT NAME :		DiGraph.h
PURPOSE   :		Directed Graph Specification
WRITTEN FOR :	Data Structures
WRITTEN BY :	Catherine Stringfellow & Christian Norfleet
DATE :			November 7, 1998
---------------------------------------------------------------------------*/
#pragma once

#include <iostream>
#include <vector>
#include "SortedList.h"

using namespace std;

static const int MAXVERTICES = 25;

class DiGraph
{
public:

	DiGraph(int n = MAXVERTICES);
	// Requires :	Graph has not been created and 0 <= n < MAXVERTICES
	// Ensures :	Graph is created and has n vertices and no edges
	// Checks :		Error if n < 0 or n >= MAXVERTICES

	DiGraph(DiGraph & other);
	// Requires :	Other has been created and initialized
	// Ensures :	Other is copied to this graph
	// Checks :		NONE

	~DiGraph();
	// Requires :	Graph is created
	// Ensures :	Graph is not created
	// Checks :		NONE

	void SwapDiGraphs(DiGraph & other);
	// Requires :	This graph and other are created and initialized
	// Ensures :	This = #other and other = #this
	// Checks :		NONE

	void AddEdge(int X, int Y);
	// Requires :	Graph is created, X and Y are distinct vertices in Graph, and
	//              edge (X,Y) not in Graph
	// Ensures :	Graph is the same except an edge (X,Y) now exists
	// Checks :		Error if X or Y is not
	//              a vertex in Graph or if X and Y are not distinct or if
	//              edge (X,Y) is already in Graph

	void RemoveEdge(int X, int Y);
	// Requires :	Graph is created, X and Y are distinct vertices in Graph and
	//              edge (X,Y) is in Graph
	// Ensures :	Graph is the same except edge (X,Y) no longer exists
	// Checks :		Error if X or Y is not
	//              a vertex in Graph or if X and Y are not distinct or
	//              if edge (X,Y) is not in Graph

	bool IsEdge(int X, int Y);
	// Requires :	Graph is created, X and Y are vertices in Graph
	// Ensures :	Graph is unchanged, IsEdge is true iff edge (X,Y) is in Graph
	// Checks :		X or Y is not a vertex in Graph

	int GetNumberOfVertices() const;
	// Requires :	Graph is created
	// Ensures :	Graph is unchanged, GetNumberofVertices is the number of
	//              vertices in Graph
	// Checks :		NONE

	void ToString(string & output, DiGraph & graph);
	// Requires :	Graph is created, a string is initialized
	// Ensures :	Graph is unchanged, visual representation of graph sent to output
	// Checks :		NONE

	void ResizeGraph(int n);
	// Requires :	Graph is created, list is initialized
	// Ensures :	Graph is unchanged, size of adjacency list = n
	// Checks :		NONE

	int InDegree(DiGraph & g, int indexcounter);
	// Requires :	Graph is created, list is initialized
	// Ensures :	Graph is unchanged, adds  # verticies coming in to a vertex
	// Checks :		NONE

	int OutDegree(DiGraph & g, int vertex);
	// Requires :	Graph is created, list is initialized
	// Ensures :	Graph is unchanged, adds # of vertices, vertex points to
	// Checks :		NONE

private:
	//define vector of edge lists
	vector <SortedList> adjList;
};
