# solarsales

This program is the final project for CIS-7: Discrete Structures in C++.  It demonstrates the use of graphs and adjancency matrices to connect a map of four cities. Each city is connected to another city with a respective distance.  This reflects the edges between the vertices in a graph and their weight. 

![image](https://github.com/davastor/solarsales/assets/25750009/c1c605e2-2149-4c41-9de3-6cdd3c5f2cfa)

The project scenario surrounds a solar marketing specialist that is required to travel through the four cities to market their product.  The program is designed to facilitate efficient travel by determining all the possible variations of paths and their respective distances.  It also implements Dijkstra's algorithm to determine the shortest path from one city to another city.  

The adjacency list is implemented in multiple different ways in each of the user options.  

The cities are implemented as Node objects, with pointers to another Node (adjacent cities), with integer data members to also reflect weight.  The program can iterate through the adjacency list by assigning a temporary pointer to each Node's ptr->next value, which is the adjacent Node object.  

Another implementation is to split the Node object's integer data members (value and cost) and insert them into a map of vectors of pairs.  The key value of the map represents the source node.  The mapped values are vectors that store the pairs of integers that store the adjacent Node's value and the cost to get there.  The result is a two-dimensional structure that represents the chain of adjacent cities connected to the source node.  

For Dijkstra's algorithm, the weighted adjancency matrix is programmed into a two-dimensional array.  

To use this program, input an integer from 1-3 into the console, based on the options:

1. Trip Planner (Trip Representation)
2. Roads (Adjacencies)
3. Map (Matrix)
