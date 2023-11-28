// CS 355
// Final Project
// Thomas Bendall, Drew Clark, Christelle Mbemeba
// 11/27/2023

#include "NewGraph.h"


//TB
//Constructor that initializes the first node of the graph
//Takes in no values and returns no values
Graph::Graph()
{
	Station.name = "Station";
	points.push_front(Station);
}

//TB
//function that takes in a string variable 'poiName'
//Searches for a POI with the same string value for its name as poiName
//Returns said index if it is found, otherwise it returns -1
int Graph::findPOIIndex(string poiName)
{
 	for(int i = 0; i < points.size(); i++)
	{
		if(points[i].name == poiName)
			return i;
	}
	//poi is not in graph, return -1
	return -1;
}

//TB
//takes in a pointer to a POI
//gets the Roads vector that is assigned to each POI, and iterates through each Road
//updates the length value if it is less than its original length
//returns no values
void Graph::findDistanceFromStart(POI* point)
{
	for(auto & i : point->Roads)
	{
		double testLength = point->lengthFromStart + i.second.length;
		POI currentNode = *(i.first);
		if(testLength < currentNode.lengthFromStart)
		{
			i.first->lengthFromStart = testLength;
			i.first->lastNode = point;
		}
	}
}

//TB
//takes in a string value
//iterates through the points deque and checks each POI in points for a matching name equal to 'inName'
//returns true if a matching value is found, returns false if not found
bool Graph::validateName(const string inName)
{
	for(auto i : points)
	{
		if(i.name == inName)
			return true;
	}
	return false;
}

//TB
//takes in a string for the name of the POI to create
//uses the findPOIIndex function to make sure the POI doesn't already exist
//if it doesn't it creates a new POI and adds to to the points deque
//it returns no values
void Graph::addPOI(const string inPOI)
{
	int inIndex = findPOIIndex(inPOI);
	if(inIndex == -1)
	{
		POI newPOI;
		newPOI.name = inPOI;
		points.push_back(newPOI);
	}
	else
		cout << "POI is already in the graph" << endl;
}


//TB
//takes in three strings, and a double for the new Road's length
//searches for the POI of both startPOI, and linkedPOI if it doesn't find one, it makes one
//it creates a new Road and adds it to the POI with the name 'startPOI' Roads vector 
void Graph::addRoad(const string startPOI, const string roadName, const string linkedPOI, double length)
{
	int  linkedI = findPOIIndex(linkedPOI);
	int startI = findPOIIndex(startPOI);
	if(linkedI == -1)
	{
		addPOI(linkedPOI);
		//it will be the last index, so size - 1 :)
		linkedI = points.size() - 1;
	}

	if(startI == -1)
	{
		addPOI(startPOI);
		//same as before :D
		startI = points.size() - 1;
	}

	Road newRoad;
	newRoad.length = length;
	newRoad.name = roadName;

	if(startPOI == "Station")
		points[0].Roads.push_back(make_pair(&points[linkedI], newRoad));
	else
		points[startI].Roads.push_back(make_pair(&points[linkedI], newRoad));
	
}

//TB
//takes in two POI elements
//searches through startPOI's Roads vector, and checks to see if one of them is linked to endPOI
//if it is, it returns the road's name, if not it returns "No Road Found"
string Graph::findRoadName(POI endPOI, POI startPOI)
{
	for(int i = 0; i < startPOI.Roads.size(); i++)
	{
		string currName = startPOI.Roads[i].first->name;
		if(currName == endPOI.name)
		{
			return startPOI.Roads[i].second.name;
		}
	}
	return "No Road Found";
}


//CM
//takes in a POI element
//initializes a string deque to get all the names of the POI's and Roads that will be traversed
//prints out the values of the string deque until its final element
void Graph::printShortestPath(const POI& finalDestination)
{

   POI* curr = finalDestination.lastNode;

   cout << "Fastest Route to " << finalDestination.name << " is: ";

    deque<string> names;
    // TB & DC
    names.push_front(findRoadName(finalDestination,*curr));
    names.push_front(finalDestination.name);
    // end TB & DC

    while (curr != nullptr)
    {
    //TB
	if(curr->lastNode != nullptr)
	   names.push_front(findRoadName(*curr, *(curr->lastNode)));

       names.push_front(curr->name);
	//end TB

        curr = curr->lastNode;
    }


    //TB
    cout << "Starting at the " << names.front() << " ";
    names.pop_front();

    while(!(names.empty()))
    {
		cout << "then drive to " << names.front();
		names.pop_front();
		cout << " on " << names.front() << endl;
		names.pop_front();

    }	//end TB

    // DC
    cout << "Total Mileage: " << finalDestination.lengthFromStart << " miles." << endl;
    cout << endl << "Thank you for using RAPID RESCUE! Have a nice day!" << endl;

    cout << endl;
    // end DC
}

//TB
//takes in a string value
//ensure the inserted string is a valid name for a POI
//if it is, it initializes values, and makes to POI pointer deques
//it adds values to unvisited by checking the nodes closes to the start, and going out until all nodes are found
//iterates through the unvisited deque and calls findShortestDistance()
//once the loop is finished it calls printShortestPath()
void Graph::getShortestPath(const string destination)
{
	int destinationI = findPOIIndex(destination);
	if(destinationI < 0)
		cout << "Invalid Destination" << endl;
	else
	{
		const double INF = 100000;

		points[0].lengthFromStart = 0;
		points[0].lastNode = nullptr;
		for(int i = 1; i < points.size(); i++)
		{
			points[i].lengthFromStart = INF;
			points[i].lastNode = nullptr;
		}
		
		deque<POI*> unvisited;
		int iterator = 0;
		unvisited.push_back(&points[0]);
		
		//Initialize unvisited
		while(points.size()  > unvisited.size())
		{
			for(int i = 0; i < unvisited[iterator]->Roads.size(); i++)
			{
				bool contains = false;
				POI currentNode = *(unvisited[iterator]->Roads[i].first);
				for(int j = 0; j < unvisited.size(); j++)
				{
					if(currentNode.name == unvisited[j]->name)
					{
						contains = true;
						break;
					}
				}
				if(!contains)
					unvisited.push_back(unvisited[iterator]->Roads[i].first);
			}
			iterator++;
		}

		deque<POI*> visited;
		visited.push_back(unvisited.front());
		unvisited.pop_front();


		do
		{

			findDistanceFromStart(visited.back());
			visited.push_back(unvisited.front());
			unvisited.pop_front();

		} while(!(unvisited.empty()));


         //CM
         printShortestPath(points[destinationI]);

	}
}

// DC
// prints out each POI in the graph
// takes in no elements and returns no elements
void Graph::printNodes() const
{

    for(const auto& i : points){
        cout << i.name << endl;
    }
}
