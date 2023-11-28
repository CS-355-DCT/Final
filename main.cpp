// CS 355
// Final Project
// Drew Clark, Thomas Bendall, Christelle Mbemba
// 11/27/2023

#include <iostream>
#include <string>
#include "NewGraph.h"

using namespace std;


int main()
{
    // DC
    // This is simply a static text display to add to the program's interface.
    const string line = "-------------------------------------------------------------------------------------------------------";
    const string shortline = "----------------";
    cout << line << endl << endl;
    cout << "  00000     0000   00000   00  00000      00000    00000   00000   00000  00   00  00000      00    " << endl;
    cout << "  00  00   00  00  00  00  00  00  00     00  00   00     00      00      00   00  00         00    " << endl;
    cout << "  0000000  000000  00000   00  00  00     0000000  0000   000000  00      00   00  0000    00000000 " << endl;
    cout << "  00   00  00  00  00      00  00  00     00   00  00         00  00      00   00  00         00    " << endl;
    cout << "  00   00  00  00  00      00  00000      00   00  00000  00000    00000   00000   00000      00    " << endl << endl;
    cout << line << endl << endl;

    // DC
    // Creating Metrocity as an object of the "Graph" class
	Graph Metrocity;

	// TB
    // String for user input of destination.
	string inName;
	//end TB

    // DC

    // These locations are akin to the alphabetic labels given in the example graph.
    // The letters here are purely symbolic.

    // A: Station
    // B: Church
    // C: CFA
    // D: Utilities
    // E: Gas Station
    // F: Town Hall
    // G: Post Office
    // H: Lowes
    // I: Sonic
    // J: Verizon

    // DC
    // A: Station
    // Initializing Station Node and connecting Its Neighbors
    Metrocity.addRoad("Station","Avalon","Town Hall",1);
    Metrocity.addRoad("Station","Long","Church",2);
    Metrocity.addRoad("Station","Prime","Gas Station",3);

    // DC
    // F: Town Hall
    // Initializing Town Hall Node and connecting Its Neighbors
    Metrocity.addRoad("Town Hall","Avalon","Post Office",1);
    Metrocity.addRoad("Town Hall","State","Church",4);
    Metrocity.addRoad("Town Hall","Iron","CFA",6);

    // DC
    // G: Post Office
    // Initializing Post Office Node and connecting Its Neighbor
    Metrocity.addRoad("Post Office","Avalon","Utilities",6);
    Metrocity.addRoad("Post Office","Wood","CFA",5);

    // DC
    // C: CFA
    // Initializing CFA Node and connecting Its Neighbors
    Metrocity.addRoad("CFA","Silver","Utilities",1);
    Metrocity.addRoad("CFA","Trout","Church",4);

    // DC
    // B: Church
    // Initializing Church Node and connecting Its Neighbors
    Metrocity.addRoad("Church","Lime","Lowes",7);

    // DC
    // D: Utilities
    // Initializing Utilities Node and connecting Its Neighbors
    Metrocity.addRoad("Utilities","Avalon","Sonic",2);

    // DC
    // I: Sonic
    // Initializing Sonic Node and connecting Its Neighbors
    Metrocity.addRoad("Sonic","Avalon","Verizon",5);
    Metrocity.addRoad("Sonic","Sixth","Lowes",2);

    // DC
    // H: Lowes
    // Initializing Lowes Node and connecting Its Neighbors
    Metrocity.addRoad("Lowes","Seventh","Gas Station",2);
    Metrocity.addRoad("Lowes","Eighth","Verizon",3);
    // end DC


    // TB and DC
    // This Do While loop takes in user input for example "Sonic"
    // and validates the user input before exiting the loop and calling
    // the getShortestPath method to run Dijkstra's algorithm and display
    // the route.

    bool exitLoop;
    do
    {
        exitLoop = true;

	    cout << "Here is a list of available locations:" << endl << endl;
        cout << shortline << endl << endl;
	    Metrocity.printNodes();
        cout << endl;
        cout << shortline << endl << endl;
	    cout << "Please enter the location nearest of the emergency, and we will tell you the fastest route!" << endl;
	    getline(cin, inName);

	    if(!(Metrocity.validateName(inName)))
	    {
		    cout << "Please enter a valid name! note: all names are currently case sensitive!" << endl;
		    exitLoop = false;
	    }

    } while(!exitLoop);

    Metrocity.getShortestPath(inName);


    return 0;
//end TB
}
