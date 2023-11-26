#include "NewGraph.h"


//TB
Graph::Graph()
{
	Station.name = "Station";
	points.push_front(Station);
}

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
void Graph::findDistanceFromStart(POI* point)
{
	for(auto & i : point->Roads)
	{
		double testLength = point->lengthFromStart + i.second.length;
		POI currentNode = *(i.first);
	//	cout << currentNode.name << ":" << testLength << "vs" << currentNode.lengthFromStart << endl;
		if(testLength < currentNode.lengthFromStart)
		{
			i.first->lengthFromStart = testLength;
			i.first->lastNode = point;
		}
	}
}

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


string findRoadName(POI endPOI, POI startPOI)
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
void Graph::printShortestPath(const POI& finalDestination)
{

   POI* curr = finalDestination.lastNode;

   cout << "Fastest Route to " << finalDestination.name << " is: ";

    deque<string> names;
    names.push_front(finalDestination.name);

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
	if(names.front() == names.back())
	{
		cout << "bringing you to " << names.front();
		names.pop_front();
	}
	else
	{
		cout << "then turn by " << names.front();
		names.pop_front();
		cout << " on " << names.front() << endl;
		names.pop_front();
	}

    }	//end TB   

    cout << endl;
}

//TB
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
		
               /* for (int i =0; i< visited.size(); i++)
                 {
                         cout << visited[i]->name << ": ";
                         cout << visited[i]->lengthFromStart << ": ";
                         if(visited[i]->lastNode != nullptr)
                                 cout << visited[i]->lastNode->name << endl;
                         else
                                 cout<< "nullptr" <<endl;
                 }*/	

         //CM
         printShortestPath(points[destinationI]);	
	
		
	}		
}

// DC
void Graph::printNodes(){

    for(const auto& i : points){
        cout << i.name << endl;
    }
}
