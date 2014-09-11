#include <iostream>
#include "fileReader.hpp"

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <limits>
#include <vector>
#include <limits>
#include <stack>
#include "vertex.hpp"


#include "BinaryHeap.h"
typedef boost::tokenizer<boost::char_separator<char> >	tokenizer;

// this is Daniels function, If a non number was passed into it it will request reinput
// message to user will be preemptively passed to stdout.
// typing 'q' or 'Q' anywhere in the string will return a negative number
int recieveNaturalNum(std::string messageToUser);

// replaces tabs with spaces in the string. tokenizer seems to have a bug in 152.0 that doesn't tokenize tabs..
void tabReplacer(std::string & str);

//takes graph and computes distances using dijkstras algorithm
void dijkstras (int startingVertex, std::vector<vertex> & graph)
{ 
    BinaryHeap<int> myQueue; // start a mutable priority queue
    vertex * ver = &graph[startingVertex]; // pointer to the starting vertex (root)
    ver->previousID = startingVertex; // its previous ID is itself.
    ver->distanceFromStart = 0.0; // distance to the root from the root is zero
    myQueue.insert(ver->ID, ver->distanceFromStart);//queue the starting vertex (the vertex's id is queued, not the actual vertex)
    
    while(!myQueue.isEmpty()) // while the queue is not empty
    {
	ver = &graph[myQueue.findMin()];//pop the element with the smallest priority value (shortest distance from starting vertex) from the queue
	myQueue.deleteMin();

	for (int i =0; i< ver->adjList.size(); i++)//loop through the adjacency list for the popped vertex
	{
	    double distance_from_root_to_adj_vertex_through_this_ver = ver->distanceFromStart + ver->distances[i]; //calculate the distance from the root to the adjacent vertex through the popped vertex
	    if (distance_from_root_to_adj_vertex_through_this_ver < graph[ver->adjList[i]].distanceFromStart)//if this new distance is shorter than the previous distance, change the adjacent vertex's values to match the new shortest route.
	    {
		double variable_that_checks_if_this_node_has_been_queued = graph[ver->adjList[i]].distanceFromStart; //this variable will be max double if the node has never been queued
		graph[ver->adjList[i]].distanceFromStart = distance_from_root_to_adj_vertex_through_this_ver;
		graph[ver->adjList[i]].previousID = ver->ID;

		if (variable_that_checks_if_this_node_has_been_queued == std::numeric_limits< double >::max()){//queue the vertex if it has not been queued yet
		    myQueue.insert(graph[ver->adjList[i]].ID, graph[ver->adjList[i]].distanceFromStart);
		}
		else//if the node is in the queue, change its priority to match the new distance from the root
		{
		    myQueue.decreaseKey(variable_that_checks_if_this_node_has_been_queued-distance_from_root_to_adj_vertex_through_this_ver, ver->adjList[i]);
		}
	    } // end if 
	} // end for
	
    }// end while
    
} // end dijkstras

int main(int argc, char **argv) {

    if (argc < 3)
    {
	std::cerr << "Error: Format is (#exec PathToFile Number)\n";
	return -1;
    }
    
    if (argc > 3)
    {
	std::cerr << "Error: Too many Inputs\n";
	return -1;
    }
    
    std::vector<vertex> graph;
    int numberOfVertices(0);
    
    if (argc >= 2 && argc <= 3) // 2-3 parameters (need more than 1, no more than 3) // 1: exec 2: file 3: startpoint
    {
	fileReader fFile;
	fFile.openFile(argv[1]);
	std::string buffer;
	boost::char_separator<char> seperators("\t "); // \x09 existed in the pdf
	buffer = fFile.getLine();
	std::cout << buffer.size() << "\n";
	tokenizer tok(buffer, seperators);
	numberOfVertices = boost::lexical_cast<int>(*tok.begin());
	bool isVertex(true); 
	
	vertex ver;
	// ---------------------Read File ---------------------
	while (!fFile.eof()) 
	{
	    buffer = fFile.getLine();
	    tokenizer tokens(buffer, seperators);
	    tokenizer::iterator it = tokens.begin();
	    int nodeID = boost::lexical_cast<int>(*it);
	    ver = vertex(); // reset the values in advance
	    ver.ID = nodeID;
	    
	    it++;
	    while (*it != "-1" && it != tokens.end())
	    {
		if (isVertex) 
		{
		    ver.adjList.push_back(boost::lexical_cast<int>(*it)); 
		    isVertex = false;
		} // end if adjacent point section
		else 
		{
		    if (it->find_first_of("-") != std::string::npos)
		    {
			std::cerr << "WARNING: Dijkstras Algorithm doesn't work properly with negative inputs.\n"
				  << "Expect to see undefined behavior\n";
		    } // end if negative
		    ver.distances.push_back(boost::lexical_cast<double>(*it)); 
		    isVertex = true;

		} // end else distance section
		it++;
	    } // end while
// 	    graph.insert(graph.end(), ver);
	    graph.push_back(ver);
	    
	    if (!isVertex) // if false then there are problems with the file
		std::cerr << "WARNING: File has uneven inputs at line " << nodeID << ".\n";
		    
	    
	} // end while reading file

	// --------------------- confirm data  ---------------------

	for (int i = 0; i < graph.size(); i++)
	{
	    std::cout << graph[i].ID << " "; 
	    for (int j = 0; j < graph[i].distances.size(); j++)
	    {
		std::cout << "a: " << graph[i].adjList[j] << " d: " << graph[i].distances[j] << " ";
	    }
	    std::cout << "\n";
	    
	}
	std::cout << "------------------------------------------------------------\n";
	
    } // end if part A of assignemnt5
    
    // ----------start part 2-----------
    
    std::string startVec = argv[2]; // check if the 2nd parameter is a positive number
    if (startVec.find_first_not_of("0123456789") != std::string::npos) // if any of the characters inside are not present
    {
	std::cerr << "Error: starting vertex must be positive AND be a number\n"; 
	return -1;
    }
    
    int startingVertex = boost::lexical_cast<int>(argv[2]); // take 2nd argument 
    
    if (startingVertex >= numberOfVertices)
    {
	std::cerr << "ERROR: starting vertex (" << startingVertex << ") CAN'T be larger than " 
		  << numberOfVertices << ", #(number vertices in graph)\n";
	return -1;
    }
    dijkstras(startingVertex, graph);
    int targetVertex(0);
    
    for (int i = 0; i < graph.size(); i++)
    {
	std::cout << "graph ID: " << graph[i].ID << ", distance from start: " 
	      << graph[i].distanceFromStart << ", previous:" << graph[i].previousID << "\n"; 
 
    }// end for
	std::cout << "------------------------------------------------------------\n";
    

    
    while (targetVertex >= 0)
    {
	std::string stdOutput = "Input target vertex, (q or Q will terminate session), (0-";
	stdOutput += boost::lexical_cast<std::string>(numberOfVertices-1 );
	stdOutput += "): ";
	
	targetVertex = recieveNaturalNum(stdOutput);
	
	if (targetVertex < 0)
	{
	    std::cerr << "Terminating...\n";
	    break;
	} // end if end program
	
	if (targetVertex > numberOfVertices-1)
	{
	    std::cerr << "ERROR: target vertex (" << targetVertex << ") CAN'T be larger than " << numberOfVertices << ", (#number vertices in graph)\n";
	    continue;

	}
	std::stack<int> outputQueue;
	vertex * ver = &graph[targetVertex];
	if (ver->distanceFromStart != std::numeric_limits< double >::max()){ // bad things will happen if its max_double
		int x = targetVertex; 
		outputQueue.push(ver->ID);
		while (x != startingVertex)
		{
		    x = ver->previousID;
		    outputQueue.push(ver->previousID);
		    ver = &graph[ver->previousID];

		} // end while
		while (!outputQueue.empty())
		{
		    std::cout << outputQueue.top();
		    outputQueue.pop();
		    if (!outputQueue.empty()) // prevent printing an extra ->
			std::cout << "->";
		}
		std::cout <<"\nTotal distance: " <<graph[targetVertex].distanceFromStart <<"\n";
		
	    } // end while
    }
    return 0;
    
} // end main


int recieveNaturalNum(std::string messageToUser)
{
    std::string output;
    std::string numbers = "0123456789qQ"; // If Qs are intered -11 will be passed
    while(true) 
    {
	std::cout << messageToUser;
	std::cin >> output;
	// if an alien character was found, hiccup
	if (output.find_first_not_of(numbers) != std::string::npos ) 
	{
	std::cout << "Warning: cannot process non-natural-numbers!\n"; 
	continue;
	} // end if
	
    if (output.find_first_of("Qq") != std::string::npos)
	return -11;
    // else
    return boost::lexical_cast<int>(output);
    
    //return atoi(output.c_str());
    } // end while
} 


void tabReplacer(std::string& str)
{
    std::size_t loc;
    while ( (loc = str.find('\t') ) != std::string::npos)
    {
	str.replace(loc,1," ");
    }
}


