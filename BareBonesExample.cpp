#include <iostream>
#include "Graph.h"

using namespace std;


int main()
{
	char values[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
	Graph<char> gr(10, values);
	
	gr.addEdge('A', 'F', 1);
	gr.addEdge('A', 'B', 2);
	gr.addEdge('A', 'E', 3);
	gr.addEdge('F', 'B', 4);
	gr.addEdge('F', 'G', 1);
	gr.addEdge('F', 'C', 6);
	gr.addEdge('B', 'H', 7);
	gr.addEdge('G', 'C', 5);
	gr.addEdge('G', 'D', 6);
	gr.addEdge('C', 'B', 4);
	gr.addEdge('C', 'D', 1);
	gr.addEdge('D', 'I', 2);
	gr.addEdge('I', 'H', 2);
	gr.addEdge('I', 'J', 5);
	gr.addEdge('H', 'J', 3);
	gr.addEdge('H', 'E', 2);
	
	cout << "Which node to go to? ";
	char inVal;
	cin >> inVal;
	gr.findShortestPath(inVal);
	
	
	return 0;
}