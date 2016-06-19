#ifndef CITYMAP_H
#define CITYMAP_H

#include <string>
#include <vector>
#include <set>
#include <map>
#include <deque>
#include <utility> // For 'pair'

using namespace std;

class CityMap
{
public:
    void AddCity(string cityName, double x, double y);
    void AddRoad(string firstCity, string secondCity); // connect cities
    void RemoveCity(string cityName);
    void RemoveRoad(string firstCity, string secondCity); // disconnect cities
    double FindDistance(string firstCity, string secondCity); // Dijkstra
    //vector<string> ShortestPath(string firstCity, string secondCity); // cities on the path
    //void PrintPath(string firstCity, string secondCity); // display cities on the path and distances
    vector<string> GetAllCityNames();


private:
    // A city is represented by a pair of doubles indicating the city's X and Y coordinates
    typedef pair<double, double> City;

    // A road is represented by a pair of strings indicating the connected cities
    typedef pair<string, string> Road;

    set<Road> roads;
    map<string, City> cities;
    double getDistance(string firstCity, string secondCity); // returns the euclidean distance between cities
    deque<pair<string, double> > shortestPathHelper(string firstCity, string secondCity); // returns the shortest path between cities
};

#endif // CITYMAP_H
