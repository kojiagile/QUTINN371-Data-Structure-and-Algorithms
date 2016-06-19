#include "CityMap.h"
#include "FileController.h"

#include <map>
#include <iostream>
#include <fstream>
#include <cmath>
#include <cfloat> // for DBL_MIN and DBL_MAX
#include <cstdlib> // for system()

/** Add a city to the CityMap
 * \pre The CityMap does not contain a city with the name cityName
 * \post The CityMap now contains a city with the name cityName at the coordinates x, y
 *
 * \param cityName The name of the city to add
 * \param x The X coordinate (unit: km) of the city to add
 * \param y The Y coordinate (unit: km) of the city to add
 * \return void
 *
 */
void CityMap::AddCity(string cityName, double x, double y)
{
    // Attempt to add the city to the cities map
    if (!cities.insert(make_pair(cityName, City(x, y))).second)
    {
        // A city with the same name already exists, so display an error
        cerr << "ERROR: City \"" << cityName << "\" already exists." << endl;
    }
}

/** Add a road to the CityMap connecting firstCity and secondCity
 * \pre The CityMap contains cities firstCity and secondCity, but does not contain a road connecting them
 * \post The CityMap now contains a road connecting firstCity and secondCity
 *
 * \param firstCity One of the two cities being connected
 * \param secondCity The other of the two cities being connected
 * \return void
 *
 */
void CityMap::AddRoad(string firstCity, string secondCity)
{
    // First, verify that both cities exist
    if (cities.count(firstCity) == 0)
    {
        cerr << "ERROR: City \"" << firstCity << "\" does not exist." << endl;
        return;
    }

    if (cities.count(secondCity) == 0)
    {
        cerr << "ERROR: City \"" << secondCity << "\" does not exist." << endl;
        return;
    }

    // Attempt to add the road to the roads set
    if (!roads.insert(Road(firstCity, secondCity)).second)
    {
        // A road connecting these cities already exists
        cerr << "ERROR: The road connecting \"" << firstCity << "\" and \"" << secondCity << "\" already exists." << endl;
        return;
    }
}

/** Remove the road connecting firstCity and secondCity from the CityMap
 * \pre The CityMap contains a road connecting the cities firstCity and secondCity
 * \post The CityMap no longer contains a road connecting the cities firstCity and secondCity
 *
 * \param firstCity One of the two cities connected by the road being removed
 * \param secondCity The other of the two cities connected by the road being removed
 * \return void
 *
 */
void CityMap::RemoveRoad(string firstCity, string secondCity)
{
    // Find the road connecting the specified cities
    set<Road>::iterator road = roads.find(make_pair(firstCity, secondCity));
    // Check if the road was found
    if (road == roads.end())
    {
        // The road was not found, so display an error to the user
        cerr << "ERROR: No road connecting \"" << firstCity << "\" and \"" << secondCity << "\" could be found." << endl;
        return;
    }
    // Remove the road from the roads set
    roads.erase(road);
}

/** Remove the city, as well as any roads connecting that city, from the CityMap
 * \pre The CityMap contains a city with the name cityName
 * \post The CityMap no longer contains a city with the name cityName, nor any roads connecting to cityName
 *
 * \param cityName The name of the city to remove
 * \return void
 *
 */
void CityMap::RemoveCity(string cityName)
{
    // Find the named city
    map<string, City>::iterator city = cities.find(cityName);

    if (city == cities.end())
    {
        // The named city was not found, so display an error to the user
        cerr << "ERROR: City \"" << cityName << "\" not found." << endl;
        return;
    }
    // Remove this city
    cities.erase(city);
    // Remove all roads connecting this city
    for (set<Road>::iterator i = roads.begin(); i != roads.end(); i++)
    {
        if (i->first == cityName || i->second == cityName)
        {
            roads.erase(i);
        }
    }
}

/** Returns the distance of the shortest path between firstCity and secondCity
 * \pre The CityMap contains cities named firstCity and secondCity, as well as a valid path between them
 *
 * \param firstCity The name of the starting city
 * \param secondCity The name of the destination city
 * \return The distance of the shortest path between firstCity and secondCity
 *
 */
double CityMap::FindDistance(string firstCity, string secondCity)
{
    double totalDistance = 0.0;
    // Retrieve the shortest path between the two given cities
    deque<pair<string, double> > path = shortestPathHelper(firstCity, secondCity);
    for (deque<pair<string, double> >::iterator i = path.begin(); i != path.end(); i++)
    {
        // Add this distance to the running total
        totalDistance += i->second;
    }

    return totalDistance;
}

/** Returns the list of cities on the shortest path between firstCity and secondCity
 * \pre The CityMap contains cities named firstCity and secondCity, as well as a valid path between them
 *
 * \param firstCity The name of the starting city
 * \param secondCity The name of the destination city
 * \return The cities on the shortest path between firstCity and secondCity
 *
 */
 /*
vector<string> CityMap::ShortestPath(string firstCity, string secondCity)
{
    vector<string> cityPath;

    // Retrieve the shortest path between the two given cities
    deque<pair<string, double> > path = shortestPathHelper(firstCity, secondCity);
    for (deque<pair<string, double> >::iterator i = path.begin(); i != path.end(); i++)
    {
        // Add this city onto the end of the shortest path vector
        cityPath.push_back(i->first);
    }
    return cityPath;
}
*/

/** Prints (to the standard output stream) the list of cities and distances between them on the shortest path between firstCity and secondCity
 * \pre The CityMap contains cities named firstCity and secondCity, as well as a valid path between them
*
 * \param firstCity The name of the starting city
 * \param secondCity The name of the destination city
 * \return void
 *
 */
 /*
void CityMap::PrintPath(string firstCity, string secondCity)
{
    deque<pair<string, double> > path = shortestPathHelper(firstCity, secondCity);
    for (deque<pair<string, double> >::iterator pathNode = path.begin(); pathNode != path.end(); pathNode++)
    {
        // Only print distances for edges other than the first
        if (pathNode != path.begin())
        {
            cout << pathNode->second << "km" << endl;
        }
        cout << pathNode->first << endl;
    }
}
*/

/** Private helper function to calculate the Euclidean distance between the coordinates of firstCity and secondCity
 * \pre The CityMap contains cities named firstCity and secondCity
 *
 * \param firstCity The first of the two cities to return the distance between
 * \param secondCity The second of the two cities to return the distance between
 * \return The Euclidean distance between the two cities
 *
 */
double CityMap::getDistance(string firstCity, string secondCity)
{
    // Retrieve the city positions from the cities map
    City firstCityPos = cities[firstCity];
    City secondCityPos = cities[secondCity];

    // Calculate the X and Y deltas between the city coordinates
    double deltax = firstCityPos.first - secondCityPos.first;
    double deltay = firstCityPos.second - secondCityPos.second;

    // Calculate the Euclidean distance and return this value
    return sqrt(deltax * deltax + deltay * deltay);
}

/** Private helper function implementing Dijkstra's shortest path algorithm to return the shortest path between firstCity and secondCity in the form of a deque
 *
 * \param firstCity The name of the starting city
 * \param secondCity The name of the destination city
 * \return A deque containing the distance and city name of each city on the shortest path
 *
 */
deque<pair<string, double> > CityMap::shortestPathHelper(string firstCity, string secondCity)
{
    map<string, double> distances;
    set<string> visited;
    set<string> unvisited;
    map<string, string> fromCity;
    map<string, double> fromCityDistance;
    map<string, map<string, double> > neighbours;

    // Initialise all default distances to DBL_MAX and add all cities to the unvisited set
    for (map<string, City>::iterator i = cities.begin(); i != cities.end(); i++)
    {
        distances[i->first] = DBL_MAX;
        unvisited.insert(i->first);
    }

    // Create neighbour distance mappings for each city
    for (set<Road>::iterator i = roads.begin(); i != roads.end(); i++)
    {
        neighbours[i->first][i->second] = getDistance(i->first, i->second);
        neighbours[i->second][i->first] = getDistance(i->second, i->first);
    }

    distances[firstCity] = 0.0;

    while (!unvisited.empty())
    {
        // Find closest unvisited city
        string currentCity = *unvisited.begin();
        for (set<string>::iterator i = unvisited.begin(); i != unvisited.end(); i++)
        {
            if (distances[*i] < distances[currentCity])
                currentCity = *i;
        }

        // Visit this city, adding it to the visited set and removing it from the unvisited set
        visited.insert(currentCity);
        unvisited.erase(unvisited.find(currentCity));

        // Assign distances to this city's neighbours
        for (map<string, double>::iterator i = neighbours[currentCity].begin(); i != neighbours[currentCity].end(); i++)
        {
            string otherCity = i->first;
            double distance = i->second + distances[currentCity];

            if (distance < distances[otherCity])
            {
                fromCity[otherCity] = currentCity;
                fromCityDistance[otherCity] = i->second;
                distances[otherCity] = distance;
            }
        }
    }

    // Create the shortest path deque by reversing through the fromCity map
    string currentCity = secondCity;
    deque<pair<string, double> > path;
    while (currentCity != firstCity)
    {
        // Add the distance and city name to the shortest path deque
        double dist = fromCityDistance[currentCity];
        path.push_front(make_pair(currentCity, dist));

        currentCity = fromCity[currentCity];
    }

    // Add the first city to the deque with a distance of 0 to ensure that all cities along the path appear in the deque
    path.push_front(make_pair(currentCity, 0.0));

    return path;
}


vector<string> CityMap::GetAllCityNames()
{
    vector<string> ret;
    map<string, City>::iterator it;
    for(it = this->cities.begin(); it != this->cities.end(); it++)
    {
        ret.push_back(it->first);
    }
    return ret;

}









