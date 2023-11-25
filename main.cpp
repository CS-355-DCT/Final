#include <iostream>
#include <string>
#include "NewGraph.h"

using namespace std;


int main()
{
    // DC
	Graph Metrocity;

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
    Metrocity.addRoad("Station","Avalon","Town Hall",1);
    Metrocity.addRoad("Station","Long","Church",2);
    Metrocity.addRoad("Station","Prime","Gas Station",3);

    // DC
    // F: Town Hall
    Metrocity.addRoad("Town Hall","Avalon","Post Office",1);
    Metrocity.addRoad("Town Hall","State","Church",4);
    Metrocity.addRoad("Town Hall","Iron","CFA",6);

    // DC
    // G: Post Office
    Metrocity.addRoad("Post Office","Avalon","Utilities",6);
    Metrocity.addRoad("Post Office","Wood","CFA",5);

    // DC
    // C: CFA
    Metrocity.addRoad("CFA","Silver","Utilities",1);
    Metrocity.addRoad("CFA","Trout","Church",4);

    // DC
    // B: Church
    Metrocity.addRoad("Church","Lime","Lowes",7);

    // DC
    // D: Utilities
    Metrocity.addRoad("Utilities","Avalon","Sonic",2);

    // DC
    // I: Sonic
    Metrocity.addRoad("Sonic","Avalon","Verizon",5);
    Metrocity.addRoad("Sonic","Sixth","Lowes",2);

    // DC
    // H: Lowes
    Metrocity.addRoad("Lowes","Seventh","Gas Station",2);
    Metrocity.addRoad("Lowes","Eighth","Verizon",3);

    Metrocity.printNodes();
}
