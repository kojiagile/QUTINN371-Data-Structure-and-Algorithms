#ifndef BANKBRANCHDEPLOYER_H_INCLUDED
#define BANKBRANCHDEPLOYER_H_INCLUDED

#include "CityMap.h"
#include "Node.h"
#include "CityCombination.h"

#include <string>
#include <map>

using namespace std;


/**
 * BankBranchDeployer class.
 *  The class is used to find out cities where bank branches is to be placed.
 *  Information about cities and connections between them are imported from
 *  two files whose names are supposed to be specified as command line arguments.
 *
 *  The third argument is used to specify either K, the number of cities where bank branches to be place, or QOS distance.
 *  Only digit(s) must be used when K is specified (e.g. 3)
 *  "km" must be added right after the QOS distance. (e.g. 100km)
 */
class BankBranchDeployer
{

public:


    /**
     * Constructor
     */
    BankBranchDeployer();

    /**
     * Destructor
     */
    ~BankBranchDeployer();

    /**
     * Find out cities where bank branches are to be placed, as well as display those.
     * @param int argc: The number of arguments.
     * @param char **argv: Arguments from command line.
     */
    void Deploy(int, char**);


    /**
     * Deploy bank branches based on QOS distance and display the result.
     */
    void DeployByQOSDistance();



private:

    ///
    /// The number of bank branches to be placed
    int numOfBranches;

    ///
    /// QOS distance
    ///
    double QOSDistance;

    ///
    /// Weather the application calculate based on QOS distance or not
    ///
    bool isQOS;

    ///
    /// Combinations of cities
    ///
    vector<CityCombination*> cityCombos;

    ///
    /// QOS clusters
    ///
    map<string, vector<Node*> > QOSClusters;


    ///
    /// CityMap object to obtain distance between cities.
    ///
    CityMap citymap;

    ///
    /// All nodes information
    ///
    map<string, Node*> allNodes;

    ///
    /// Seed value
    ///
    const static unsigned int SEED_VALUE;

    ///
    /// Seed Offset
    ///
    static unsigned int SEED_OFFSET;

    ///
    /// Loop counter
    ///
    const static int LOOPCOUNT;

    /**
     * Create nodes (city) and store them.
     */
    void CreateNodes();

    /**
     * Find distance to each city from a city and store them into each city node.
     */
    void FindAllDistance();

    /**
     * Import files to get city and road information.
     * @param cityFileName: A file name containing city name and its coordinate.
     * @param roadFileName: A file name containing information about connection between a city and another.
     * @return Returns true if both files are correctly imported.
     */
    bool ImportCityMapData(string, string);

    /**
     * Select initial medoids using random function with seed.
     * @return vector<string>: A vector object containing initial medoid names.
     */
    vector<string> SelectInitialMedoids();

    /**
     * Create clusters.
     *  A map object holds medoid name as a key, and pointers of other nodes in its cluster as value.
     * @param medoidNames: medoid names.
     * @return map<string, vector<Node*> >: Clusters created.
     */
    map<string, vector<Node*> > CreateClusters(vector<string>);

    /**
     * Get mean squared distance of a cluster.
     * @param vector<Node*>: Pointers of nodes (non-medoids) in a cluster.
     * @param medoidNames: Current medoid name.
     * @param Node*& medoid: New medoid object
     * @return double: Mean squared distance of the cluster
     */
    double GetMeanSquaredDist(vector<Node*>, string, Node*&);


    /**
     * Get mean squared distance of all clusters. (Add up all mean squared distance of each cluster)
     * @param map<string, vector<Node*> > *clusters: Clusters for calculating the distance
     * @return double: Total mean squared distance
     */
    double GetTotalMeanSquaredDist(map<string, vector<Node*> >*);

    /**
     * Check if a target node is a medoid.
     * @param vector<string> medoidNames: Medoid names.
     * @param string target: A target node name.
     * @return bool: Returns true if target is a medoid.
     */
    bool IsMedoid(vector<string>, string);

    /**
     * Comparing old medoid names and the current ones, find if the medoids are swapped.
     * @param vector<string> oldMedoidNames: Old medoid names.
     * @param vector<string> medoidNames: Current medoid names.
     * @return bool: Returns true if medoids are swapped.
     */
    bool IsMedoidsSwapped(vector<string>, vector<string>);


    /**
     * Check if a target node is a medoid.
     * @param vector<string> medoidNames: Medoid names in (initial) cluster.
     * @param map<string, vector<Node*> > *clusters: (initial) cluster.
     * @return vector<string>: New medoid names.
     */
    vector<string> GetNewMedoids(vector<string>, map<string, vector<Node*> >*);

    /**
     * Check arguments.
     * @param int argc: The number of arguments.
     * @param char **argv: Arguments from command line.
     * @return Returns true if all arguments are appropriate for the application.
     */
    bool CheckArgs(int, char**);

    /**
     * Create city combination
     *  This method create a CityCombination object for finding out which cities have shorter distance.
     */
    void CreateCombinations();

    /**
     * Find out cities to place bank branches.
     */
    void FindPlaceByQOS();

    /**
     * Get all members in the cluster.
     * @param vector<Node*> members: Members in a cluster.
     * @param Node*& medoid: New medoid object
     * @return double: Minimum distance in the cluster.
     */
    double GetMinimumDistanceInCluster(vector<Node*>, Node*&);

    /**
     * Get total distance from the medoid in the cluster.
     * @param vector<Node*>: Pointers of nodes (non-medoids) in a cluster.
     * @param medoidNames: medoid name.
     * @return double: A mean squared distance of a cluster.
     */
    double GetTotalDist(vector<Node*>, string);

    /**
     * Get all members in the cluster.
     * @param vector<Node*> firstMembers: Members in the first cluster.
     * @param vector<Node*> secondMembers: Members in the second cluster.
     * @param string first: A medoid name in the first cluster.
     * @param string second: A medoid name in the second cluster.
     * @return vector<Node*> All nodes in both clusters.
     */
    vector<Node*> GetAllMembersInCluster(vector<Node*>, vector<Node*>, string, string);

    /**
     * Merge clusters.
     * @param string first: A key city name in the first cluster.
     * @param string second: A key city name in the second cluster.
     */
    void MergeClusters(string, string);


};


#endif // BANKBRANCHDEPLOYER_H_INCLUDED
