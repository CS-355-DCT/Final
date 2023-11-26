#ifndef H_GRAPH
#define H_GRAPH

#include <iostream>
#include <deque>
#include "POI.h"
#include "road.h"

using namespace std;

//TB
class Graph
{
	private:
		deque<POI> points;
		//the station, starting point for all cases, will always be named "Station"
		POI Station;
		int findPOIIndex(string);
		void findDistanceFromStart(POI*);
		void printShortestPath(const POI&);
	public:
		Graph();
		bool validateName(const string);
		void addPOI(const string);
		void addRoad(const string, const string, const string, int);
		void getShortestPath(const string);
	       	void printNodes();
};

#endif
