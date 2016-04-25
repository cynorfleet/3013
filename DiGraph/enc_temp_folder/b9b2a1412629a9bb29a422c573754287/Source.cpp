//              UNIT NAME :
//              PURPOSE   :
//              WRITTEN FOR :
//              WRITTEN BY :
//              DATE :

//#include <ctype>
#include <iostream>
#include <fstream>
#include <string>
#include "DiGraph.h"
#include "SortedList.h"
using namespace std;

struct specifcations
{
	int size;
	pair <int, int> edge;

	//Default Constructor
	specifcations()
	{
		//initialize variables
		size = 0;
		edge = make_pair(0, 0);
	}

	//Parameterized Constructor
	specifcations(int x, int y)
	{
		size = 1;
		edge = make_pair(x, y);
	}
};

//******************************************************************************
// PreCondition	:
// PostCondition :
// Error Condition :
//******************************************************************************
void OpenFiles(ifstream &, ofstream &, specifcations &);

//******************************************************************************
// PreCondition	:
// PostCondition :
// Error Condition :
//******************************************************************************
void ReadFile(ifstream &, specifcations &, DiGraph &);

void PrintList(ofstream &, bool, DiGraph &);

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
	bool wantcomplmt = false;
	DiGraph graph, graphcomp;

	// open input & output files
	OpenFiles(infile, outfile, vertex);

	//crop Vector to # of vertices
	graph.ResizeGraph(vertex.size);
	graphcomp.ResizeGraph(vertex.size);

	//keep reading in vertices into graph until end of file
	do
	{
		// read data file into graph
		ReadFile(infile, vertex, graph);
		vertex.edge.first = NULL;
		vertex.edge.second = NULL;
	} while (!(infile.eof()));

	//5A find complement
	graph.Complement(graphcomp);

	//print graph and print complement graph
	PrintList(outfile, wantcomplmt, graph);
	wantcomplmt = true;
	PrintList(outfile, wantcomplmt, graphcomp);

	// 5B find, and print to outfile, prerequisites for selected courses

	// while user selects courses to process
	//get valid course
	//find linear order
	//print linear order

	//do you want to go again?

	//5A and 5B close files

	system("pause");
	return 0;
}

void OpenFiles(ifstream & infile, ofstream & outfile, specifcations & temp)
{
	// VARIABLES
	char infileName[40], outfileName[40];

	//get name of infile
	cout << "Enter name of data file> ";
	cin >> infileName;
	infile.open(infileName);

	//get name of infile
	cout << "Enter name of output file > ";
	cin >> outfileName;
	outfile.open(outfileName);

	//read in list size
	infile >> temp.size;
}

void ReadFile(ifstream & infile, specifcations & temp, DiGraph & graph)
{
	infile >> temp.edge.first;
	infile >> temp.edge.second;
	//add edge to graph
	graph.AddEdge(temp.edge.first, temp.edge.second);
}

void PrintList(ofstream & outfile, bool whichone, DiGraph & g)
{
	string output = "";
	cout << "\nThere are " << g.GetNumberOfVertices() << " verticies in the Graph";

	//if printing complement add appropriate string
	if (whichone == true)
		cout << "'s complement";

	cout << ".\n";
	cout << "The edges are as follows:\n";

	//Grab data from graph object
	g.ToString(output, g);
	cout << output;
}