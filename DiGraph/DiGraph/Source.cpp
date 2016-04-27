/*---------------------------------------------------------------------------
UNIT NAME :   Source.cpp
PURPOSE   :   Creates adjacency list for provided verticies with in/outdegree
WRITTEN FOR : Data Structures
WRITTEN BY :  Christian Norfleet and Catherine Stringfellow
DATE :		  4/25/2016
---------------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <string>
#include "DiGraph.h"
#include "SortedList.h"
using namespace std;

//Temp container that holds # of verticies and edge inputs
struct specifcations
{
	int size;
	pair <int, int> edge;

	//Default Constructor
	specifcations()
	{
		//initialize variables
		size = NULL;
		edge = make_pair(NULL, NULL);
	}

	//Parameterized Constructor
	specifcations(int x, int y)
	{
		size = 0;
		edge = make_pair(x, y);
	}
};

// PreCondition	:	in and outfiles initialized, specif container allocated
// PostCondition :	in/outfiles are opened. # of vertices are read
// Error Condition :if incorrect infile name reenter
void OpenFiles(ifstream &, ofstream &, specifcations &);

// PreCondition	:	in and outfile initialized, specif container and graph allocated
// PostCondition :	graph is changed to include edges. Vector index rep verticies
// Error Condition :NONE
void ReadFile(ifstream &, specifcations &, DiGraph &);

// PreCondition	:	outfile and graph allocated
// PostCondition :	will display graph w/ edges by default. Displays compl if true is
//					passed as additional argument
// Error Condition :NONE
void PrintList(ofstream &, DiGraph &, bool = false);

// PreCondition	:	outfile and graph allocated
// PostCondition :	will display in-degree and out-degree
// Error Condition :NONE
void PrintDegree(ofstream &, DiGraph &, bool = false);

int main()
// PreCondition : none
// PostCondition : The prerequisites for the courses in a program of study
//                 are read from an input file, and the prerequisites for
//                 each course selected by the user are found and sent to
//                 the output file.  The process is repeated  until the user
//                 decides to stop looking for prerequisites
// ErrorCondition : none
{
	//VARIABLES
	ifstream infile;
	ofstream outfile;
	specifcations vertex;
	DiGraph graph, graphcomp;

	// open input & output files
	OpenFiles(infile, outfile, vertex);

	//crop Vector to # of vertices
	graph.ResizeGraph(vertex.size);
	graphcomp.ResizeGraph(vertex.size);

	//keep reading in vertices into graph until end of file
	do
	{
		// read data into graph
		ReadFile(infile, vertex, graph);
		//reset temp edges for next vertex
		vertex.edge.first = NULL;
		vertex.edge.second = NULL;
	} while (!(infile.eof()));

	//5A find complement
	graph.Complement(graphcomp);

	//print graph and print complement graph, and in/out degree of verticies
	PrintList(outfile, graph);
	PrintList(outfile, graphcomp, true);
	PrintDegree(outfile, graph);
	PrintDegree(outfile, graph, true);

	// 5B find, and print to outfile, prerequisites for selected courses

	// while user selects courses to process
	//get valid course
	//find linear order
	//print linear order

	//do you want to go again?

	//5A and 5B close files
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}

void OpenFiles(ifstream & infile, ofstream & outfile, specifcations & temp)
{
	//HEADING
	cout << "This program will read infile and process verticies into graph.\n";
	cout << "It will then output the edges found and their complements.\n\n";

	// VARIABLES
	char infileName[40], outfileName[40];

	do
	{
		//get name of infile
		cout << "Enter name of data file> ";
		cin >> infileName;
		infile.open(infileName);

		//get name of infile
		cout << "Enter name of output file > ";
		cin >> outfileName;
		outfile.open(outfileName);

		//if invalid filename prompt reenter
		if (!infile)
		{
			cout << "\nERROR: Infile could not be opened.\n";
			cout << "Please reenter correct infile name.\n";
			system("pause");
			outfile << endl;
		}
		//loop until valid filename
	} while (!infile);
	//read in list size and allocate memory for degree vector
	infile >> temp.size;
}

void ReadFile(ifstream & infile, specifcations & temp, DiGraph & graph)
{
	infile >> temp.edge.first;
	infile >> temp.edge.second;
	//add edge and degree to graph
	graph.AddEdge(temp.edge.first, temp.edge.second);
}

void PrintList(ofstream & outfile, DiGraph & g, bool complement)
{
	string output = "";
	outfile << "\nThere are " << g.GetNumberOfVertices() << " verticies in the Graph";

	//if printing complement add appropriate string
	if (complement)
		outfile << "'s complement";

	outfile << ".\n";
	outfile << "The edges are as follows:\n";

	//Grab data from graph object
	g.ToString(output, g);
	outfile << output;
}

void PrintDegree(ofstream & outfile, DiGraph & g, bool outdegree)
{
	//if computing in-degree
	if (!outdegree)
	{
		outfile << "\nThe in-degrees are as follows:";
		//traverse the verticies while calling the in-degree function to find sum
		//i will be used as an index counter
		for (int i = 0; i < g.GetNumberOfVertices(); i++)
			outfile << "\nFrom vertex " << i << " is:\t" << g.InDegree(g, i);
		cout << "\n\n";
	}

	//if computing out-degree
	else
	{
		outfile << "\n\nThe out-degrees are as follows: ";
		//traverse the verticies while calling the out-degree function to find sum
		//i will be used for matching edge list of all verticies
		for (int i = 0; i < g.GetNumberOfVertices(); i++)
			outfile << "\nFrom vertex " << i << " is:\t" << g.OutDegree(g, i);
		outfile << "\n\n";
	}
}