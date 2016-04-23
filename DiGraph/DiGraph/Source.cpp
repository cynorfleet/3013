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
	pair <int, int> vertex;

	//Default Constructor
	specifcations()
	{
		//initialize variables
		size = 0;
		vertex = make_pair(0, 0);
	}

	//Parameterized Constructor
	specifcations(int x, int y)
	{
		size = 1;
		vertex = make_pair(x, y);
	}
};

//******************************************************************************
// PreCondition	:
// PostCondition :
// Error Condition :
//******************************************************************************
void OpenFiles(ifstream & infile, ofstream & outfile);

//******************************************************************************
// PreCondition	:
// PostCondition :
// Error Condition :
//******************************************************************************
void ReadFile(ifstream & infile, specifcations & temp, DiGraph);

void PrintList(ofstream & outfile, DiGraph);

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
	DiGraph graph;

	// open input & output files
	OpenFiles(infile, outfile);
	// read data file into G
	ReadFile(infile, vertex, graph);

	//5A find complement

	//print graph and print complement graph
	PrintList(outfile, graph);

	// 5B find, and print to outfile, prerequisites for selected courses

	// while user selects courses to process
	//get valid course
	//find linear order
	//print linear order

	//do you want to go again?

	//5A and 5B close files

	return 0;
}

void OpenFiles(ifstream & infile, ofstream & outfile)
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
}

void ReadFile(ifstream & infile, specifcations & temp, DiGraph graph)
{
	//read in list size
	infile >> temp.size;

	//keep reading in vertices until end of file
	do
	{
		infile >> temp.vertex.first;
		infile >> temp.vertex.second;
		//add edge to graph
		graph.AddEdge(temp.vertex.first, temp.vertex.second);
	} while (!(infile.eof()));
}

void PrintList(ofstream & outfile, DiGraph graph)
{
	string output = "";

	//Grab data from graph object
	graph.ToString(output);
	cout << output;
}