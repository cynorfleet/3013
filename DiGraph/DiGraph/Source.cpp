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
#include "ENHDIG.h"
#include "SortedList.h"
using namespace std;

// PreCondition	:	in and outfiles initialized, specif container allocated
// PostCondition :	in/outfiles are opened. # of vertices are read
// Error Condition :if incorrect infile name reenter
void OpenFiles(ifstream &, ofstream &);

// PreCondition	:	Graph is created
// PostCondition :	Will request user for course #, then verify it. Will change
//					coursenum, otherwise graph is unchanged.
// Error Condition :if course number (< 0) or (> |vertices) print error
bool GetCourse(DiGraph, int &);

// PreCondition	:	Graph is created
// PostCondition :	Will request user for course #, then verify it. Will change
//					coursenum, otherwise graph is unchanged.
// Error Condition :if course number (< 0) or (> |vertices) print error
bool GoAgain();

// PreCondition :	NONE
// PostCondition :	The prerequisites for the courses in a program of study
//					are read from an input file, and the prerequisites for
//					each course selected by the user are found and sent to
//					the output file.  The process is repeated  until the user
//					decides to stop looking for prerequisites
// ErrorCondition : NONE
int main()
{
	//VARIABLES
	ifstream infile;
	ofstream outfile;
	DiGraph graph, graphcomp;
	stack <int> req;
	int course = NULL;
	char choice = NULL;

	// open input & output files
	OpenFiles(infile, outfile);

	// read data into graph
	ReadDiGraph(infile, outfile, graph);

	//5A find complement
	Complement(graph, graphcomp);

	//print graph and print complement graph, and in/out degree of verticies
	PrintDiGraph(outfile, graph);
	PrintDiGraph(outfile, graphcomp, true);
	PrintDegree(outfile, graph);
	PrintDegree(outfile, graph, true);

	// 5B find, and print to outfile, prerequisites for selected courses

	// while user selects courses to process
	do
	{
		//get valid course
		if(GetCourse(graph, course));
		{
			//find linear order
			FindLinearOrder(graph, course, req);
			//print linear order
			PrintLinearOrder(outfile, req);
		}
		//do you want to go again?
	} while (GoAgain());
	//5A and 5B close files
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}

// PreCondition	:	in and outfiles initialized, specif container allocated
// PostCondition :	in/outfiles are opened. # of vertices are read
// Error Condition :if incorrect infile name reenter
void OpenFiles(ifstream & infile, ofstream & outfile)
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
}

bool GetCourse(DiGraph g, int & coursenum)
{
		do
		{
			cout << "Please enter desired course number: ";
			cin >> coursenum;

			//if course number is outside range print error
			if ((coursenum <= 0) && (coursenum <= g.GetNumberOfVertices()))
				cout << "\nERROR: Invalid course number\n";
			//loop until valid entry
		} while ((coursenum <= 0) && (coursenum <= g.GetNumberOfVertices()));
		if (g.OutDegree(g, coursenum) > 0)
			return true;
		else
		{
			cout << "\nThis course needs no prerequisisites.";
			return false;
		}
}

bool GoAgain()
{
	char choice = NULL;
	//Ask user to continue
	do 
	{
		cout << "\nDo you want to process a course for prerequisites: (Y/N)";
		cin >> choice;
		choice = tolower(choice);
		//if invalid input print error
		if (choice != 'y' && choice != 'n')
			cout << "\nERROR: Invalid choice. Please reenter.\n";
		//loop until valid choice
	} while (choice != 'y' && choice != 'n');
	//if they want to continue return true
	if (choice == 'y')
		return true;
	else
		return false;
}