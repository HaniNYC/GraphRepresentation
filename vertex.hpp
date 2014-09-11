#include <vector>
#include <limits>
struct vertex
{
    double 		distanceFromStart;
    int 		previousID;
    int 		ID;
    bool 		isKnown;
    std::vector<int> 	adjList;
    std::vector<double> distances;
    vertex() : distanceFromStart(std::numeric_limits< double >::max()), isKnown(false), previousID(0), adjList(), distances(), ID(0){}
};
