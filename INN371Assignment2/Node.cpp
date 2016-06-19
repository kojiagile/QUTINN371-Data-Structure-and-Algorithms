#include "Node.h"


/**
 * Constructor
 * @param name: The node name.
 */
Node::Node(string name)
{
    this->name = name;
    //this->isMedoid = false;
}

/**
 * Destructor
 */
Node::~Node()
{

}

/**
 * Get distance from the node to each city.
 * @return A map object containing distance from the node to each city.
 */
map<string, double> Node::GetCostToCities()
{
    return this->distToCities;
}

/**
 * Get the node name.
 * @return string The node name.
 */
string Node::GetName()
{
    return this->name;
}

/**
 * Set the distance between the node to another.
 * @param nodeName: The node name that connected to the node.
 * @param distance: distance between the node and the one specified at the first parameter.
 */
void Node::SetDistanceTo(string nodeName, double distance)
{
    if(this->distToCities.find(nodeName) != this->distToCities.end())
    {
        //distance already exist
        return;
    }
    this->distToCities[nodeName] = distance;
}
