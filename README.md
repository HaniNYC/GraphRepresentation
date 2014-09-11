                                            
                                          Graph Representation   
								   
								   
Description:
----------- 
The program will read a text file that contains a graph elements - vertices and weighted edges - as shown below. 
*******************************
5                       <--- number of total vertices in the graph                  
0 1 0.2 3 10.1 4 .5 -1  <-- a starting vertex(0) and its adjacent vertices followed by the edge weight ie: 0 ---0.2---> 1, 0 -----10.1---> 3  etc. 
1 0 1.5 -1
2 1 100 3 50.2 -1
3 -1
4 1 10.5 2 13.9 -1
*******************************
After the graph is implemented using the adjacency list,the program will find all the shortest paths- using Dijkstra's algorithm- to every vertex in the graph
when a starting vertex is giving. 
The idea is to traverse all vertices of graph using BreadthFirst Search and use a Mutable Priority queue to store the vertices not yet included in shortest Path Tree
or the vertices for which shortest distance is not finalized yet.Therefore, Mutable Priority Queue is used to store/get the minimum distance for vertices. 
Note :decreasekey() will be used to update the shortest distances for vertices.
 

Time Complexity Analysis:
-----------------------
The time complexity without using Mutable Priority Queue would be O(V^2) because there are two nested loops. But because Mutable Priority Queue was used , the inner loop  
are executed O(V+E)  times only -Breadth First Search -. The  decreaseKey() operation takes O(LogV)time.So overall time complexity is 
 O(E+V)*O(LogV) which is O((E+V)*LogV) = O(ELogV)
Files Included :
---------------
1- main.cpp                 - contains the graph adjacency list implementation and Dijkstra's algorithm for the shortest paths.
2- BinaryHeap.h             - From the group's fourth assignment.
3- QuadraticProbing.h       - From the group's fourth assignment. - One modification has been applied, the decreaskey() accepts doubles instead of integers.
4- QuadraticProbing.cpp     - From the group's fourth assignment.
5- fileReader.cpp           - Taken from Daniel's third assignment.Used for reading the file and checks for errors while reading.
6- fileReader.hpp           - Taken from Daniel's third assignment
7- vertex.hpp               - Contains vertex struct 
8- CMakeLists.txt
9- make file
10- ReadMe.txt
 
Important Functions :
-------------------
******************PUBLIC OPERATIONS*********************
 void insert( x )                     --> Insert x ( a node ) into the heap
 deleteMin( minItem )                 --> Remove (and optionally return) smallest item
 Comparable findMin( )                --> Return smallest item
 bool isEmpty( )                      --> Return true if empty; else false
 void makeEmpty( )                    --> Remove all items 
 void increaseKey(delta,key)          --> Increases delta value then percolate down 
 void decreaseKey(delta,key)          --> Decreases delta value then percolate up
 void removeKey(key)                  --> Assigning a minimum key value, Percolate up till root then delete
 void ds (int, vector<vertex>&)       --> The main function in the program, takes two arguments, the first is the starting vertex and the second is a vector representing the graph, 
                                         then applies Dijkstra's algorithm to all adjacent vertices and queue/ dequeue accordingly.If the current distance of a giving vertex is larger 
										 than the new distance to adjacent vertex + distance to starting vertex , then the vertex shortest distance is updated .
 void openFile(const string & file)   --> reads the input file( contains graph units) line by line into a string. - Found in fileReader-
 void removeSpecificChar(string&,char)-->  to remove specific chartype that maybe tainting the file.- Found in fileReader-
 void removeReturnCarraige(string&)   --> to remove any carrages found in file .- Found in fileReader-
 
 
Language Used: c++ 
------------- 
Compiling Instructions:
----------------------
                        In eniac,  use cmake "CMakeLists.txt" then run make
Running Instructions: 
--------------------- 
From command line window   : after make file is run, type      findPaths <GRAPH_FILE> <STARTING_VERTEX> 
where Graph_File is the text file that contains all the graph'e element as shown above , and the STARTING_VERTEX is the first vertex in the graph
                             
						   
Known Bugs:
----------   None; please let us know if you find any issues. 
Contacts:
--------
Hani Aboudeshisha                          Hani.Aboudeshisha44@myhunter.cuny.edu
Grigoriy Zhenein                           gregory.zhen@gmail.com 
Daniel Fialkouvskey                        falconoflegnds@gmail.com 


