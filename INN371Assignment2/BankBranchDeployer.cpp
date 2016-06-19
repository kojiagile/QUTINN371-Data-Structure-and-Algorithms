#include "BankBranchDeployer.h"
#include "FileController.h"
#include "CityMap.h"
#include "Node.h"
#include "CityCombination.h"

#include <iostream>
#include <map>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <cfloat>
#include <queue>

using namespace std;


///
/// Seed value
///
const unsigned int BankBranchDeployer::SEED_VALUE = 1434206378;



/**
 * Constructor
 */
BankBranchDeployer::BankBranchDeployer()
{
    this->citymap = CityMap();
}

/**
 * Destructor
 */
BankBranchDeployer::~BankBranchDeployer()
{
    map<string, Node*>::iterator it = this->allNodes.begin();
    Node *med;
    while(it != this->allNodes.end())
    {
        // free allocated memory
        med = it->second;
        delete med;
        med = NULL;
        it++;
    }

    //for task 2
    for(int i = 0; i < this->cityCombos.size(); i++)
    {
        CityCombination *cc = this->cityCombos[i];
        delete cc;
        cc = NULL;
    }
}


/**
 * Find out cities where bank branches are to be placed, as well as display those.
 * @param int argc: The number of arguments.
 * @param char **argv: Arguments from command line.
 */
void BankBranchDeployer::Deploy(int argc, char **argv)
{
    if(!CheckArgs(argc, argv))
    {
        return;
    }
    if(!ImportCityMapData(argv[1], argv[2]))
    {
        //cerr << "----- ERROR ----- Data import error has occured." << endl;
        return;
    }
    //create Nodes
    CreateNodes();

    if(!this->isQOS)
    {
        //Check args for task 1
        if(this->numOfBranches > this->allNodes.size())
        {
            cerr << "----- ERROR ----- The number of K specified exceeds the number of cities." << endl;
            return;
        }
        else if(this->numOfBranches == 0)
        {
            cerr << "----- ERROR ----- Cannot specify 0 as K." << endl;
            return;
        }
    }
    else
    {
        //Check args for task 2
        if(this->QOSDistance < 0)
        {
            cerr << "----- ERROR ----- Distance cannot be below 0." << endl;
            return;
        }
    }
    //Find distance from a city to other cities in advance
    FindAllDistance();

    if(this->isQOS)
    {
        DeployByQOSDistance();
        return;
    }

    vector<string> medoidNames;
    map<string, vector<Node*> > clusters;
    double shortestDist = -1;

    //Initial medoids and clusters
    medoidNames = SelectInitialMedoids();
    clusters = CreateClusters(medoidNames);

    //After optimization
    medoidNames = GetNewMedoids(medoidNames, &clusters);
    clusters = CreateClusters(medoidNames);

    cout << "--------- Cities where bank branches are placed (Mean squared distance) --------" << endl;
    map<string, vector<Node*> >::iterator itc;
    for(itc = clusters.begin(); itc != clusters.end(); itc++)
    {
        vector<Node*> nodes = itc->second;
        Node *medoid;
        double dist = GetMeanSquaredDist(nodes, itc->first, medoid);
        cout << medoid->GetName() << "(" << dist << ")" << endl;
    }

    cout << "---------------------------------------------------------" << endl;
}

/**
 * Check if a target node is a medoid.
 * @param vector<string> medoidNames: Medoid names.
 * @param string target: A target node name.
 * @return bool: Returns true if target is a medoid.
 */
bool BankBranchDeployer::IsMedoid(vector<string> medoidNames, string target)
{
    for(int i = 0; i < medoidNames.size(); i++)
    {
        if(target == medoidNames[i])
        {
            return true;
        }
    }
    return false;
}


/**
 * Check if a target node is a medoid.
 * @param vector<string> medoidNames: Medoid names in (initial) cluster.
 * @param map<string, vector<Node*> > *clusters: (initial) cluster.
 * @return vector<string>: New medoid names.
 */
vector<string> BankBranchDeployer::GetNewMedoids(vector<string> medoidNames, map<string, vector<Node*> > *clusters)
{
    double currentDist = GetTotalMeanSquaredDist(clusters);
    double newDist = 0;
    vector<string> result;

    map<string, Node*>::iterator it;
    map<string, vector<Node*> >::iterator itc;
    vector<string>::iterator itMed;
    bool isSwapped = false;
    vector<string> oldMedoidNames;

    for(int i = 0; i < medoidNames.size(); i++)
    {
        //keep medoid names to compare with new ones
        oldMedoidNames.push_back(medoidNames[i]);
    }

    do
    {
        for(itMed = medoidNames.begin(); itMed != medoidNames.end(); itMed++)
        {

            string medName = "";
            vector<string> newMedoidNames;
            string excludedMed = *itMed;
            for(it = this->allNodes.begin(); it != this->allNodes.end(); it++)
            {
                Node *node = it->second;

                //To select non-medoid node, ignore medoids
                if(IsMedoid(medoidNames, node->GetName()))
                {
                    continue;
                }

                //Create new medoids combination which might provide shorter mean squared distance.
                newMedoidNames.push_back(node->GetName());
                for(int j = 0; j < medoidNames.size(); j++)
                {
                    if(excludedMed != medoidNames[j])
                    {
                        //Put medoids except for "excludedMed"
                        newMedoidNames.push_back(medoidNames[j]);
                    }
                }

                //To calculate total mean squared distance, create clusters with the combination above.
                map<string, vector<Node*> > newClusters = CreateClusters(newMedoidNames);
                newDist = GetTotalMeanSquaredDist(&newClusters);

                //cout << "current dist: " << currentDist << ", " << "new dist: " << newDist << endl;
                //if new distance is shorter than the current one, medoid is to be swapped
                if(newDist < currentDist)
                {
                    currentDist = newDist;
                    //keep the node name for inserting it to current medoidName vector ("medoidNames").
                    medName = node->GetName();
                    //keep new combination
                    result.clear();
                    result.swap(newMedoidNames);
                }
                //Clean has to be done for next loop
                newMedoidNames.clear();
            }
            //The node is going to be swapped and become a new medoid
            if(medName != "")
            {
                vector<string>::iterator itErasedPos = medoidNames.erase(itMed);
                medoidNames.insert(itErasedPos, medName);
                medName = "";
            }

        }
        if(result.size() == 0)
        {
            isSwapped = false;
        }
        else
        {
            isSwapped = IsMedoidsSwapped(oldMedoidNames, medoidNames);
        }

        if(result.size() != 0)
        {
            //medoidNames.swap(result);
            oldMedoidNames.clear();
            //oldMedoidNames.swap(result);
            for(int i = 0; i < result.size(); i++)
            {
                oldMedoidNames.push_back(result[i]);
            }
        }
        else
        {
            for(int i = 0; i < medoidNames.size(); i++)
            {
                result.push_back(medoidNames[i]);
            }
        }

        map<string, vector<Node*> > newClusters = CreateClusters(medoidNames);
        clusters = &newClusters;

    } while(isSwapped);

    return result;
}


/**
 * Comparing old medoid names and the current ones, find if the medoids are swapped.
 * @param vector<string> oldMedoidNames: Old medoid names.
 * @param vector<string> medoidNames: Current medoid names.
 * @return bool: Returns true if medoids are swapped.
 */
bool BankBranchDeployer::IsMedoidsSwapped(vector<string> oldMedoidNames, vector<string> medoidNames)
{
    bool found = false;
    for(int i = 0; i < oldMedoidNames.size(); i++)
    {
        int j = 0;
        found = false;
        for(j; j < medoidNames.size(); j++)
        {
            if(oldMedoidNames[i] == medoidNames[j])
            {
                found = true;
                break;
            }
        }
        if(!found)
        {
            return true;
        }
    }
    return false;
}


/**
 * Get mean squared distance of all clusters. (Add up all mean squared distance of each cluster)
 * @param map<string, vector<Node*> > *clusters: Clusters for calculating the distance
 * @return double: Total mean squared distance
 */
double BankBranchDeployer::GetTotalMeanSquaredDist(map<string, vector<Node*> > *clusters)
{
    double ret = 0;
    map<string, vector<Node*> >::iterator it;

    for(it = clusters->begin(); it != clusters->end(); it++)
    {
        vector<Node*> nodes = it->second;
        //temp = GetMeanSquaredDist(nodes, it->first);
        Node *medoid;
        ret += GetMeanSquaredDist(nodes, it->first, medoid);
    }

    return ret;
}


/**
 * Get mean squared distance of a cluster.
 * @param vector<Node*>: Pointers of nodes (non-medoids) in a cluster.
 * @param medoidNames: Current medoid name.
 * @param Node*& medoid: New medoid object
 * @return double: Mean squared distance of the cluster
 */
double BankBranchDeployer::GetMeanSquaredDist(vector<Node*> nodes, string medoidName, Node*& medoid)
{
    double ret = 0;
    vector<Node*> allMembers;
    for(int i = 0; i < nodes.size(); i++)
    {
        allMembers.push_back(nodes[i]);
    }
    allMembers.push_back(this->allNodes[medoidName]);
    ret = GetMinimumDistanceInCluster(allMembers, medoid);

    return ret / allMembers.size();
}

/**
 * Get total distance from the medoid in the cluster.
 * @param vector<Node*>: Pointers of nodes (non-medoids) in a cluster.
 * @param medoidNames: medoid name.
 * @return double: A mean squared distance of a cluster.
 */
double BankBranchDeployer::GetTotalDist(vector<Node*> nodes, string medoidName)
{
    double ret = 0;
    for(int i = 0; i < nodes.size(); i++)
    {
        map<string, double> distToCities = nodes[i]->GetCostToCities();
        //ret += distToCities[medoidName] * distToCities[medoidName];
        ret += distToCities[medoidName];
    }

    return ret;
}


/**
 * Create clusters.
 *  A map object holds medoid name as a key, and pointers of other nodes in its cluster as value.
 * @param medoidNames: medoid names.
 * @return map<string, vector<Node*> >: Clusters created.
 */
map<string, vector<Node*> > BankBranchDeployer::CreateClusters(vector<string> medoidNames)
{
    bool isChanged = false;
    map<string, Node*>::iterator it;

    //To store clusters. key is the name of a medoid, value is members of its cluster.
    map<string, vector<Node*> > clusters;
    for(int i = 0; i < medoidNames.size(); i++)
    {
        vector<Node*> nodes;
        clusters[medoidNames[i]] = nodes;
    }

    for(it = this->allNodes.begin(); it != this->allNodes.end(); it++)
    {
        //Find out which node belongs to which medoid.
        Node *node = it->second;

        //if(node->IsMedoid())
        if(clusters.find(node->GetName()) != clusters.end())
        {
            continue;
        }

        double minDist = DBL_MAX;
        Node *med;
        //for(itMed = this->medoidNames.begin(); itMed != medoidNames.end(); itMed++)
        for(int i = 0; i < medoidNames.size(); i++)
        {
            //Check distance between the node and each medoid to find out the closest medoid
            map<string, double> distToCities = node->GetCostToCities();
            if(minDist > distToCities[medoidNames[i]])
            {
                //keep (temporary) shortest distance and the medoid
                minDist = distToCities[medoidNames[i]];
                med = this->allNodes[medoidNames[i]];
            }
        }

        vector<Node*> members = clusters[med->GetName()];
        members.push_back(node);
        clusters[med->GetName()] = members;
    }

    return clusters;
}



/**
 * Select initial medoids using random function with seed.
 * @return vector<string>: A vector object containing initial medoid names.
 */
vector<string> BankBranchDeployer::SelectInitialMedoids()
{
    vector<string> medoidNames;
    vector<string> allCities = citymap.GetAllCityNames();
    int maxIndex = allCities.size();

    //For random number creation
    //srand(SEED_VALUE + SEED_OFFSET);
    srand(SEED_VALUE);
    //SEED_OFFSET++;

    //cout << "SEED_VALUE" << SEED_VALUE << endl;

    set<int> randomSet;
    while(randomSet.size() != this->numOfBranches)
    {
        int index = rand() % maxIndex;
        //If a number exist in the set object, get a new one to get distinct numbers.
        if(!randomSet.empty() && randomSet.find(index) != randomSet.end())
        {
            continue;
        }
        randomSet.insert(index);
    }

    for(set<int>::iterator it = randomSet.begin(); it != randomSet.end(); it++)
    {
        //The node is selected as initial medoid where a bank branch is installed.
        Node *node = this->allNodes.find(allCities[*it])->second;
        medoidNames.push_back(node->GetName());
    }

    return medoidNames;
}


/**
 * Find distance to each city from a city and store them into each city node.
 */
void BankBranchDeployer::FindAllDistance()
{
    vector<string> allCityName = citymap.GetAllCityNames();

    for(int i = 0; i < allCityName.size(); i++)
    {
        Node *node = this->allNodes.find(allCityName[i])->second;
        for(int j = i + 1; j < allCityName.size(); j++)
        {
            //Get distance from the node to any other node and store it in the node
            double dist = citymap.FindDistance(node->GetName(), allCityName[j]);
            if(dist != -1)
            {
                //If distance A to B, then B to A is the same distance.
                //Distance A to B
                node->SetDistanceTo(allCityName[j], dist);
                //Distance B to A
                Node *secondNode = this->allNodes[allCityName[j]];
                secondNode->SetDistanceTo(node->GetName(), dist);
            }
        }
    }
}


/**
 * Import files to get city and road information.
 * @param cityFileName: A file name containing city name and its coordinate.
 * @param roadFileName: A file name containing information about connection between a city and another.
 * @return Returns true if both files are correctly imported.
 */
bool BankBranchDeployer::ImportCityMapData(string cityFileName, string roadFileName)
{
    FileController fc = FileController(cityFileName, roadFileName);
    if(!fc.ReadFiles())
    {
        cerr << "----- ERROR ----- File read error" << endl;
        return false;
    }
    //Cities contains city name, coordinate-x and coordinate-y respectively and repeatedly.
    //Similarly, roads contains first city name and second city name respectively and repeatedly.
    //e.g. [0] = Brisbane [1] = 100 [2] = 100 [3] = Sydney [4] = 500 [5] = 500 .....
    vector<string> cities = fc.GetCities();
    vector<string> roads = fc.GetRoads();
    int i = 0;
    string firstCity;
    string secondCity;
    double x;
    double y;

    while(i < cities.size())
    {
        firstCity = cities[i++];
        x = atof(cities[i++].c_str());
        y = atof(cities[i++].c_str());
        this->citymap.AddCity(firstCity, x, y);
    }

    i = 0;
    while(i < roads.size())
    {
        firstCity = roads[i++];
        secondCity = roads[i++];
        this->citymap.AddRoad(firstCity, secondCity);
    }

    return true;
}


/**
 * Create nodes (city) and store them.
 */
void BankBranchDeployer::CreateNodes()
{
    vector<string> allCities = citymap.GetAllCityNames();
    Node *med;
    for(int i = 0; i < allCities.size(); i++)
    {
        //All cities are stored in allNodes.
        med = new Node(allCities[i]);
        this->allNodes[allCities[i]] = med;
    }
}


/**
 * Check arguments.
 * @param int argc: The number of arguments.
 * @param char **argv: Arguments from command line.
 * @return Returns true if all arguments are appropriate for the application.
 */
bool BankBranchDeployer::CheckArgs(int argc, char **argv)
{
    if(argc != 4)
    {
        cerr << "----- ERROR ----- Argument is missing or too many." << endl;
        return false;
    }
    //Convert the number of branches to be placed
    char *endp = '\0';
    string thirdArg = argv[3];
    int numOfBranches = (int)strtol(thirdArg.c_str(), &endp, 10);

    double distance = 0;
    string unit = "km";
    bool isQOS = false;

    //If conversion is not complete successfully
    if(*endp != '\0')
    {
        //param not containing "km" has to be rejected
        if(thirdArg.find("km") == std::string::npos)
        {
            cerr << "----- ERROR ----- Invalid argument." << endl;
            return false;
        }

        //replace "km" with empty so it can be converted to a number.
        thirdArg = thirdArg.replace(thirdArg.size() - 2, unit.size(), "");

        *endp = NULL;
        distance = strtod(thirdArg.c_str(), &endp);
        if(*endp != '\0')
        {
            //The third arg is invalid.
            cerr << "----- ERROR ----- Invalid argument (cannot converted to a number.)" << endl;
            return false;
        }
        isQOS = true;
    }

    this->numOfBranches = numOfBranches;
    this->isQOS = isQOS;
    this->QOSDistance = distance;

    return true;

}

/**
 * Get all members in the cluster.
 * @param vector<Node*> firstMembers: Members in the first cluster.
 * @param vector<Node*> secondMembers: Members in the second cluster.
 * @param string first: A medoid name in the first cluster.
 * @param string second: A medoid name in the second cluster.
 * @return vector<Node*> All nodes in both clusters.
 */
vector<Node*> BankBranchDeployer::GetAllMembersInCluster(
    vector<Node*> firstMembers, vector<Node*> secondMembers, string first, string second)
{
    vector<Node*> allMembers;
    Node *firstNode = this->allNodes[first];
    Node *secondNode = this->allNodes[second];

    allMembers.push_back(firstNode);
    allMembers.push_back(secondNode);
    for(int i = 0; i < firstMembers.size(); i++)
    {
        allMembers.push_back(firstMembers[i]);
    }
    for(int i = 0; i < secondMembers.size(); i++)
    {
        allMembers.push_back(secondMembers[i]);
    }

    return allMembers;
}


/**
 * Deploy bank branches based on QOS distance and display the result.
 */
void BankBranchDeployer::DeployByQOSDistance()
{
    CreateCombinations();
    FindPlaceByQOS();

    cout << "------ Cities where bank branches are placed based on QOS distance(" << this->QOSDistance << "km)------" << endl;
    cout << "City: City Name(Mean squared distance)" << endl;
    cout << "--------------------------------------" << endl;

    map<string, vector<Node*> >::iterator itq;
    for(itq = this->QOSClusters.begin(); itq != this->QOSClusters.end(); itq++)
    {
        vector<Node*> nodes = itq->second;
        vector<Node*> allMembers;
        allMembers.push_back(this->allNodes[itq->first]);
        for(int i = 0; i < nodes.size(); i++)
        {
            allMembers.push_back(nodes[i]);
        }

        Node *medoid;
        double dist = GetMinimumDistanceInCluster(allMembers, medoid);
        dist = dist / allMembers.size();
        //double dist = GetMeanSquaredDist(nodes, itq->first);

        cout << "City: "  << medoid->GetName() << "(" << dist << ")" << endl;
    }
    cout << "----------------------------------------------------------------------------" << endl;
}


/**
 * Merge clusters.
 * @param string first: A key city name in the first cluster.
 * @param string second: A key city name in the second cluster.
 */
void BankBranchDeployer::MergeClusters(string first, string second)
{
    map<string, vector<Node*> >::iterator itFirst = this->QOSClusters.find(first);
    map<string, vector<Node*> >::iterator itSecond = this->QOSClusters.find(second);
    Node *firstMed = this->allNodes.find(first)->second;
    Node *secondMed = this->allNodes.find(second)->second;
    vector<Node*> secondMember = itSecond->second;

    //Merge second cluster to first
    vector<Node*> nodes = itFirst->second;
    nodes.push_back(secondMed);
    for(int i = 0; i < secondMember.size(); i++)
    {
        nodes.push_back(secondMember[i]);
    }
    this->QOSClusters[firstMed->GetName()] = nodes;
    this->QOSClusters.erase(itSecond);
}

/**
 * Find out cities to place bank branches.
 */
void BankBranchDeployer::FindPlaceByQOS()
{
    priority_queue<CityCombination, vector<CityCombination>, greater<CityCombination> > pq;
    for(int i = 0; i < this->cityCombos.size(); i++)
    {
        CityCombination *temp = this->cityCombos[i];
        pq.push(*temp);
    }

    CityCombination cc;

    //priority queue always pops shorter distance between cities.
    while(!pq.empty())
    {
        cc = pq.top();

        //this->QOSClusters contains all clusters.
        //Initially, all cities are added in it as clusters independently.
        map<string, vector<Node*> >::iterator itFirst = this->QOSClusters.find(cc.GetFirstCity());
        map<string, vector<Node*> >::iterator itSecond = this->QOSClusters.find(cc.GetSecondCity());

        Node *first = this->allNodes.find(cc.GetFirstCity())->second;
        Node *second = this->allNodes.find(cc.GetSecondCity())->second;

        double dist = 0;
        double shorter = DBL_MAX;
        //When both city remain in the clusters object as medoids
        if(itFirst != this->QOSClusters.end() && itSecond != this->QOSClusters.end())
        {
            //Add second to first as a member of the cluster
            vector<Node*> firstMember = itFirst->second;
            vector<Node*> secondMember = itSecond->second;
            vector<Node*> allMembers;
            allMembers = GetAllMembersInCluster(firstMember, secondMember, first->GetName(), second->GetName());
            Node *medoid;
            dist = GetMinimumDistanceInCluster(allMembers, medoid);
            dist = dist / allMembers.size();

            //cout << "mean: " << dist << endl;
            if(dist > this->QOSDistance)
            {
                pq.pop();
                continue;
            }

            //Merge second cluster to first
            MergeClusters(first->GetName(), second->GetName());
        }
        else if(itFirst != this->QOSClusters.end())
        {
            //When second has been combined to another cluster

            //Look for second node in the cluster
            //Node *medoid;
            map<string, vector<Node*> >::iterator it;
            for(it = this->QOSClusters.begin(); it != this->QOSClusters.end(); it++)
            {
                vector<Node*> nodes = it->second;
                for(int i = 0; i < nodes.size(); i++)
                {
                    if(second->GetName() == nodes[i]->GetName())
                    {
                        //keep medoid the second node belongs to
                        second = this->allNodes[it->first];
                        break;
                    }
                }
            }

            //when two nodes are in the same cluster
            if(first->GetName() == second->GetName())
            {
                pq.pop();
                continue;
            }

            itSecond = this->QOSClusters.find(second->GetName());
            vector<Node*> firstMember = itFirst->second;
            vector<Node*> secondMember = itSecond->second;
            vector<Node*> allMembers = GetAllMembersInCluster(firstMember, secondMember, first->GetName(), second->GetName());

            Node *newMed;
            dist = GetMinimumDistanceInCluster(allMembers, newMed);
            dist = dist / allMembers.size();

            //cout << "mean: " << dist << endl;
            if(dist > this->QOSDistance)
            {
                pq.pop();
                continue;
            }

            //Merge second cluster
            MergeClusters(first->GetName(), second->GetName());
        }
        else if(itSecond != this->QOSClusters.end())
        {
            //When first has been combined to another cluster

            //Look for first node in the cluster
            //Node *medoid;
            map<string, vector<Node*> >::iterator it;
            for(it = this->QOSClusters.begin(); it != this->QOSClusters.end(); it++)
            {
                vector<Node*> nodes = it->second;
                for(int i = 0; i < nodes.size(); i++)
                {
                    if(first->GetName() == nodes[i]->GetName())
                    {
                        //keep medoid the first node belongs to
                        first = this->allNodes[it->first];
                        break;
                    }
                }
            }

            //when two nodes are in the same cluster
            if(second->GetName() == first->GetName())
            {
                pq.pop();
                continue;
            }

            itFirst = this->QOSClusters.find(first->GetName());
            vector<Node*> firstMember = itFirst->second;
            vector<Node*> secondMember = itSecond->second;
            vector<Node*> allMembers = GetAllMembersInCluster(firstMember, secondMember, first->GetName(), second->GetName());

            Node *newMed;
            dist = GetMinimumDistanceInCluster(allMembers, newMed);
            dist = dist / allMembers.size();

            //cout << "mean: " << dist << endl;
            if(dist > this->QOSDistance)
            {
                pq.pop();
                continue;
            }

            //Merge first cluster
            MergeClusters(first->GetName(), second->GetName());
        }
        else
        {
            //When first and second node have been combined to other clusters
            map<string, vector<Node*> >::iterator it;
            for(it = this->QOSClusters.begin(); it != this->QOSClusters.end(); it++)
            {
                vector<Node*> nodes = it->second;
                for(int i = 0; i < nodes.size(); i++)
                {
                    if(first->GetName() == nodes[i]->GetName())
                    {
                        first = this->allNodes[it->first];
                        break;
                    }
                }
            }
            for(it = this->QOSClusters.begin(); it != this->QOSClusters.end(); it++)
            {
                vector<Node*> nodes = it->second;
                for(int i = 0; i < nodes.size(); i++)
                {
                    if(second->GetName() == nodes[i]->GetName())
                    {
                        second = this->allNodes[it->first];
                        break;
                    }
                }
            }

            //when two nodes are in the same cluster
            if(first->GetName() == second->GetName())
            {
                pq.pop();
                continue;
            }

            itFirst = this->QOSClusters.find(first->GetName());
            itSecond = this->QOSClusters.find(second->GetName());
            vector<Node*> firstMember = itFirst->second;
            vector<Node*> secondMember = itSecond->second;
            vector<Node*> allMembers = GetAllMembersInCluster(firstMember, secondMember, first->GetName(), second->GetName());

            Node *newMed;
            dist = GetMinimumDistanceInCluster(allMembers, newMed);
            dist = dist / allMembers.size();

            //cout << "mean: " << dist << endl;
            if(dist > this->QOSDistance)
            {
                pq.pop();
                continue;
            }

            //Merge second cluster
            MergeClusters(first->GetName(), second->GetName());
        }

        pq.pop();
    }
}



/**
 * Get all members in the cluster.
 * @param vector<Node*> members: Members in a cluster.
 * @param Node*& medoid: New medoid object
 * @return double: Minimum distance in the cluster.
 */
double BankBranchDeployer::GetMinimumDistanceInCluster(vector<Node*> members, Node*& medoid)
{
    string newMedName = "";
    double distance = DBL_MAX;
    for(int i = 0; i < members.size(); i++)
    {
        Node *node = members[i];
        double temp = 0;
        map<string, double> distToCities = node->GetCostToCities();
        //map<string, double>::iterator it;
        for(int j = 0; j < members.size(); j++)
        {
            //ignore if the medoid is found
            if(node->GetName() == members[j]->GetName())
            {
                continue;
            }
            map<string, double>::iterator itTo = distToCities.find(members[j]->GetName());
            temp += itTo->second;
        }
        if(distance > temp)
        {
            //newMedName = node->GetName();
            distance = temp;
            medoid = node;
        }
    }

    return distance;
}

/**
 * Create city combination
 *  This method create a CityCombination object for finding out which cities have shorter distance.
 */
void BankBranchDeployer::CreateCombinations()
{
    map<string, Node*>::iterator it;
    //int i = 0;
    for(it = this->allNodes.begin(); it != this->allNodes.end(); it++)
    {
        Node *node = it->second;
        map<string, double> distTo = node->GetCostToCities();
        map<string, double>::iterator itDistTo;
        CityCombination *cc;
        for(itDistTo = distTo.begin(); itDistTo != distTo.end(); itDistTo++)
        {
            if(this->QOSClusters.find(itDistTo->first) == this->QOSClusters.end())
            {
                cc = new CityCombination(node->GetName(), itDistTo->first, itDistTo->second);
                //cc = new CityCombination(node->GetName(), itDistTo->first, i++);
                this->cityCombos.push_back(cc);
            }
        }
        //create initial cluster, which doesn't have any other nodes in it
        vector<Node*> vec;
        this->QOSClusters[node->GetName()] = vec;
    }

}





