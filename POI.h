// CS 355
// Final Project
// Thomas Bendall
// 11/27/2023

#ifndef POI_H
#define POI_H

#include <string>
#include "road.h"
#include <vector>


//TB
//acts as nodes for the graph
//has a string for its name
//uses a vector to contain all of its 'edges' (called Roads)
//has lengthFromStart double and a POI* called lastNode to aid in the getShortestPath function
struct POI
{
	std::string name;
	std::vector<std::pair<POI*, Road>> Roads;
	double lengthFromStart;
	POI* lastNode;
};



#endif
