#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED


#include <string>
#include <map>
#include <vector>

using namespace std;


/**
 * Node class.
 *  The class represents both medoid and non-medoid.
 *  The data is copied from CityMap class to facilitate the process of
 *  finding places where bank branches is to be placed.
 */
class Node
{

public:

    /**
     * Constructor
     * @param name: The node name.
     */
    Node(string);

    /**
     * Destructor
     */
    ~Node();

    /**
     * Get distance from the node to each city.
     * @return A map object containing distance from the node to each city.
     */
    map<string, double> GetCostToCities();

    /**
     * Get the node name.
     * @return string The node name.
     */
    string GetName();

    /**
     * Set the distance between the node to another.
     * @param nodeName: The node name that connected to the node.
     * @param distance: distance between the node and the one specified at the first parameter.
     */
    void SetDistanceTo(string, double);

private:

    ///
    /// Node name
    ///
    string name;

    ///
    /// Costs to get to cities connected.
    ///
    map<string, double> distToCities;
};


#endif // NODE_H_INCLUDED
