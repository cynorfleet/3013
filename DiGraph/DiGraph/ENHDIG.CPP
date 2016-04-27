/*
UNIT NAME :		EnhDiGraph.cpp
PURPOSE   :		Enhanced DiGraph Operations Specifications
WRITTEN FOR :	CS 3013
WRITTEN BY :	Christian Norfleet
DATE :			4/25/2016
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "ENHDIG.h"
using namespace std;

void ReadDiGraph(ifstream & InFile, ofstream & OutFile, DiGraph & G)
// PreCondition : G is created.  The first line of InFile contains the
//                number of vertices in the graph,, the following lines
//                are the edges (vertex pairs) of the Graph
// PostCondition : Graph G is the DiGraph specified by InFile
// ErrorCondition : Error if the size is invalid, or if there are invalid edges
{
	int GSize;
	int X;
	int Y;

	//read in # of verticies and change size of graph to reflect verticies
	InFile >> GSize;
	G.ResizeGraph(GSize);

	do {
		// read data into graph
		InFile >> X;
		InFile >> Y;

		if ((X >= 0) && (X < G.GetNumberOfVertices()) && (Y >= 0) && (Y < G.GetNumberOfVertices()))
		{
			//If X and Y are verticies in graph
			if ((X >= 0) && (X < G.GetNumberOfVertices()) && (Y >= 0) && (Y < G.GetNumberOfVertices()))
			{
				//Check to see if in array already
				if (G.IsEdge(X, Y))
					cout << "\nERROR: CANNOT ADD EDGE. ALREADY IN GRAPH\n";
				//Check if not distinct
				else if (X == Y)
					cout << "\nERROR: CANNOT ADD EDGE. X AND Y MUST BE DISTINCT\n";
				//If valid, add edge to graph
				else
					G.AddEdge(X, Y);
			}
			//If X and Y are NOT verticies in graph print error
			else
				cout << "\nERROR: CANNOT ADD EDGE. X or Y not a vertex in Graph\n";
		}
		//reset temp edges for next vertex input
		X = NULL;
		Y = NULL;
	} while (!(InFile.eof()));
}

void PrintDiGraph(ofstream & OutFile, DiGraph & G, bool Compl)
// PreCondition  : G is created
// PostCondition : outfile"s first line is the size of the graph, the
//                 succeeding lines contain a list of vertices and the
//                 vertices to which they are adjacent
// ErrorCondition : none
{
	string output = "";
	OutFile << "\nThere are " << G.GetNumberOfVertices() << " verticies in the Graph";

	//if printing complement add appropriate string
	if (Compl)
		OutFile << "'s complement";

	OutFile << ".\n";
	OutFile << "The edges are as follows:\n";

	//Grab data from graph object
	G.ToString(output, G);
	OutFile << output;
}

void PrintDegree(ofstream & outfile, DiGraph & g, bool outdegree)
{
	//if computing out-degree
	if (outdegree)
	{
		outfile << "\nThe out-degrees are as follows:";
		//traverse the verticies while calling the in-degree function to find sum
		//i will be used as an index counter
		for (int i = 0; i < g.GetNumberOfVertices(); i++)
			outfile << "\nFrom vertex " << i << " is:\t" << g.OutDegree(g, i);
		cout << "\n\n";
	}

	//if computing in-degree
	else
	{
		outfile << "\n\nThe in-degrees are as follows: ";
		//traverse the verticies while calling the out-degree function to find sum
		//i will be used for matching edge list of all verticies
		for (int i = 0; i < g.GetNumberOfVertices(); i++)
			outfile << "\nFrom vertex " << i << " is:\t" << g.InDegree(g, i);
		outfile << "\n\n";
	}
}

void Complement(DiGraph & G, DiGraph & GComp)
// PreCondition : G and GComp are created
// PostCondition : G = #G, GComp is the same size as G and has edges between
//                 exactly those pairs of vertices not directly
//                 connected in G
// ErrorCondition : none
{
	//crop GComp to # of vertices in G
	GComp.ResizeGraph(G.GetNumberOfVertices());

	//Traverse verticies
	for (int i = 0; i < G.GetNumberOfVertices(); i++)
	{
		//Traverse edges
		for (int z = 0; z < G.GetNumberOfVertices(); z++)
		{
			//if edge is not found and vertex is distinct add edge-complement
			if (!(G.IsEdge(i, z)) && (i != z))
				GComp.AddEdge(i, z);
		}
	}
}

/*
void DoLinearOrder(DiGraph & G, int Course, Stack & PreReq, ControlData & Visited)
// requires : G is created, PreReq is created, Course is a valid course
// ensures : G is unchanged; PreReq contains the sequence of courses that
//           have to be taken before Course, with Course itself at the top
// checks : Course is a valid course
{
  int i;

  // start at vertex <course>, mark vertex <course> as visited

	 // for (each vertex in G which has not already been visited

	  //if (there is an edge between <course> and <i>, recursively
	  // call  LinearOrder for (vertex <i>

	  // with each return (backtrack) from a call to  LinearOrder,
	  // add the vertex (for (which that call was made) to PreReq

// }        LinearOrder
*/

/*
void FindLinearOrder(DiGraph & G, int Course, Stack & Prerequisites)
// requires : G is created, Prerequisites is created, Course is a valid course
// ensures : G = #G; Prerequisites contains the sequence of courses that have
//           to be taken before Course, with Course itself at the top
// checks : Course is a valid course
{
	ControlData Visited;
	int i;
	// Find Linear Order

	// initialize array Visited

	// clear stack Prerequisites

	// checkif (Course is valid course number
}  //Find Linear Order
/*

/*
void PrintLinearOrder (ofstream & OutFile, Stack & PreReq)
// requires : OutFile has been opened for (output; PreReq is created,
//            and its top item is the "target course" for (which the rest
//            of the items on the stack are prerequisites
// checks : none
{
}
*/