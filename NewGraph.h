#ifndef H_GRAPH
#define H_GRAPH

#include <iostream>
#include <list>
#include "POI.h"

using namespace std;

//TB
class Graph
{
	private:
		list<POI> points;
		//the station, starting point for all cases, will always be named "Station"
		POI Station;
	public:
		Graph();
		void addRoad(const string, const string, const string);
		void getShortestPath(const string);		
};

#endif