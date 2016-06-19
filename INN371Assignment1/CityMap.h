#pragma once

#ifndef CITYMAP_H
#define CITYMAP_H

#include <string>
#include <vector>
#include <queue>
#include <math.h>
#include <cfloat>
#include <iostream>
#include <sstream>
#include <fstream>
#include <windows.h>
#include "City.h"


using namespace std;

///
/// CityMap class
///     The class is used to find the shortest distance and path using DijkstraÅfs algorithm between two cities.
///     The shortest path and the distance are shown on console,
///     and an .html file is generated for graphic representation.
///
template <typename T>
class CityMap
{
    public:

        /// City name: Adelaide
        const static string ADE;
        /// City name: Alice Springs
        const static string ALI;
        /// City name: Brisbane
        const static string BRI;
        /// City name: Canberra
        const static string CAN;
        /// City name: Cairns
        const static string CAI;
        /// City name: Darwin
        const static string DAR;
        /// City name: Hobart
        const static string HOB;
        /// City name: Melbourne
        const static string MEL;
        /// City name: Perth
        const static string PER;
        /// City name: Sydney
        const static string SYD;



        ///
        /// Constructor
        ///
        CityMap();

        ///
        /// Destructor
        ///
        ~CityMap();

        ///
        /// Add a city.
        ///     An error message will be show when an existing city is added.
        ///
        /// @param string cityName: City name.
        /// @param T x: Coordinate X
        /// @param T y: Coordinate Y
        ///
        void AddCity(string cityName, T x, T y);

        ///
        /// Add roads between two cities, both ways firstCity to secondCity and secondCity to firstCity.
        ///     An error message will be show when firstCity and/or secondCity do not exist.
        ///     An error message will be show when firstCity and secondCity are the same.
        ///
        /// @param string firstCity: First city.
        /// @param string secondCity: Second city.
        ///
        void AddRoad(string firstCity, string secondCity);

        ///
        /// Remove an existing city.
        ///     An error message will be show when the city does not exist.
        ///
        /// @param string cityName: City name.
        ///
        void RemoveCity(string cityName);

        ///
        /// Remove roads between two cities, both ways firstCity to secondCity and secondCity to firstCity.
        ///     An error message will be show when firstCity and/or secondCity do not exist.
        ///     An error message will be show when firstCity and secondCity are the same.
        ///
        /// @param string firstCity: First (start) city.
        /// @param string secondCity: Second (goal) city.
        ///
        void RemoveRoad(string firstCity, string secondCity);

        ///
        /// Find the shortest distance between two cities.
        ///     The method returns 0 when firstCity and secondCity are not connected.
        ///     An error message will be show when firstCity and/or secondCity do not exist.
        ///     An error message will be show when firstCity and secondCity are the same.
        ///
        /// @param string firstCity: First (start) city.
        /// @param string secondCity: Second (goal) city.
        /// @return T: The shortest distance between two cities.
        ///
        T FindDistance(string firstCity, string secondCity);

        ///
        /// Find the shortest path between two cities.
        ///     The return value contains 1 name when firstCity and secondCity are not connected.
        ///     An error message will be show when firstCity and/or secondCity do not exist.
        ///     An error message will be show when firstCity and secondCity are the same.
        ///
        /// @param string firstCity: First (start) city.
        /// @param string secondCity: Second (goal) city.
        /// @return vector<string>: All cities that are on the shortest path between two cities.
        ///
        vector<string> ShortestPath(string firstCity, string secondCity);

        ///
        /// Display the shortest path and distance between two cities.
        ///     The method show 0 as the shortest distance when firstCity and secondCity are not connected.
        ///     An error message will be show when firstCity and/or secondCity do not exist.
        ///     An error message will be show when firstCity and secondCity are the same.
        ///
        /// @param string firstCity: First (start) city.
        /// @param string secondCity: Second (goal) city.
        ///
        void PrintPath(string firstCity, string secondCity);

        ///
        /// Get All cities added
        /// @return map<string, City<T>*>: A map container that contains all cities added.
        ///
        map<string, City<T>*> GetCities();

        ///
        /// Get a city
        /// @return City<T>*: A pointer that points to a city.
        ///
        City<T> *GetCityByName(string target);

        ///
        /// Clear all cities added.
        ///
        void ClearAllCities();


    private:

        /// A value that represents that distance cannot be calculated (e.g. start and goal are not connected.)
        const static T NO_DISTANCE;
        /// A message type: INFO
        const static string MSG_TYPE_INFO;
        /// A message type: ERR
        const static string MSG_TYPE_ERR;

        /// A message when city name specified is empty.
        const static string MSG_EMPTY_NAME;
        /// A message when start city and goal city are the same.
        const static string MSG_SAME_CITY;
        /// A message when start city and goal city are not connected.
        const static string MSG_NOT_CONNECTED;
        /// A message when a city map has been generated.
        const static string MSG_MAP_GENERATED;

        //
        //For drawing city map
        //
        /// Template file name (for output an .html file)
        const static string STR_TEMP_FILE_NAME;
	    /// Output file name
        const static string STR_OUTPUT_FILE_NAME;
	    /// An Extension for output file
        const static string STR_EXTENTION;
	    /// Color: Ordinary city
        const static string STR_CITY_COLOR;
	    /// Color: City on the shortest path
        const static string STR_CITY_COLOR_SHORTEST;
	    /// Indent
        const static string STR_INDENT;
	    /// Key word in a template .html to find a line that Javascript codes are inserted to.
        const static string STR_CODE_DRAW_ALL;
	    /// Javascript array variables: coordinate X
        const static string STR_VAR_POS_X;
	    /// Javascript array variables: coordinate Y
        const static string STR_VAR_POS_Y;
        /// Javascript variable: proportion X
        const static string STR_VAR_PROP_X;
        /// Javascript variable: proportion Y
        const static string STR_VAR_PROP_Y;
	    /// Javascript function: drawCity()
        const static string STR_DRAW_CITY_FUNC;
	    /// Javascript function: drawTextCityName()
        const static string STR_DRAW_CITY_NAME_FUNC;
	    /// Javascript function: drawRoad()
        const static string STR_DRAW_ROAD_FUNC;
	    /// An error message : File read error.
        const static string MSG_FILE_READ_ERR;
	    /// An error message : No cities exist.
        const static string MSG_NO_CITIES;
        /// A map container that contains all cities added.
        map<string, City<T>*> cities;

	    /// Offset X
        const static T NUM_OFFSET_X;
        /// Offset Y
        const static T NUM_OFFSET_Y;


        ///
        /// Calculate cost to next city.
        /// @param City<T> *city1: A pointer that points to a city.
        /// @param City<T> *city2: A pointer that points to a next city.
        /// @return T: The cost between a city and a next city.
        ///
        T CalcCostToNextCity(City<T> *city1, City<T> *city2);

        ///
        /// Calculate cost to next city.
        /// @param T city1X: Corrdinate X of a city
        /// @param T city1Y: Corrdinate Y of a city
        /// @param T city2X: Corrdinate X of a next city
        /// @param T city2Y: Corrdinate Y of a next city
        /// @return T: The cost between a city and a next city.
        ///
        T CalcCostToNextCity(T city1X, T city1Y, T city2X, T city2Y);

        ///
        /// Initialise values that all cities contains.
        ///
        void InitializePathAndCost();

        ///
        /// Check if a city name is valid.
        /// @param string target: A city name.
        /// @return bool: True when a city name is valid.
        ///
        bool IsValidName(string target);

        ///
        /// Check if a city already exist.
        /// @param string cityName: A city name.
        /// @return bool: True when a city already exist
        ///
        bool ExistCity(string cityName);

        ///
        /// Check if a city name is valid and already exist.
        /// @param string firstCity: A city name.
        /// @param string secondCity: An another city name.
        /// @param bool checkSecond: True if the another city name needs to be checked.
        /// @return string: A message. An empty message when both names are valid and
        ///                 do not exist in A map container that contains all cities added.
        ///
        string CheckCities(string firstCity, string secondCity, bool checkSecond);

        ///
        /// Get a previous city name.
        /// @param City<T> *city: A pointer that points to a city.
        /// @param vector<string> *vecNames: A vector container that contains city names.
        /// @return string: A previous city name.
        ///
        string GetPreviCityName(City<T> *city, vector<string> *vecNames);

        //
        // For drawing city map
        //
        ///
        /// Generate a city map .html
        /// @param CityMap<T> *cmap: A pointer that points to the instance of this class.
        /// @param vector<string> path: The (shortest) path to be drawn.
        ///
        bool GenerateCityMap(CityMap<T> *cmap, vector<string> path);

        ///
        /// Write Javascript functions and variables to draw all cities and roads
        /// @param ifstream *ifs: A pointer of ifstream instance.
        /// @param ofstream *ofs: A pointer of ofstream instance.
        /// @param CityMap<T> *cmap: A pointer that points to the instance of this class.
        /// @param vector<string> path: The (shortest) path to be drawn.
        ///
        bool WriteAllCitiesAndRoads(ifstream *ifs, ofstream *ofs, CityMap<T> *cmap, vector<string> path);

        ///
        /// Write Javascript functions and variables to draw the shortest path with different colour.
        /// @param ifstream *ifs: A pointer of ifstream instance.
        /// @param ofstream *ofs: A pointer of ofstream instance.
        /// @param CityMap<T> *cmap: A pointer that points to the instance of this class.
        /// @param vector<string> path: The (shortest) path to be drawn.
        ///
        void WriteShortestPath(ifstream *ifs, ofstream *ofs, CityMap<T> *cmap, vector<string> path);

        ///
        /// Get Javascript functions and variables to draw cities.
        /// @param CityMap<T> *city: A pointer that points to the instance of this class.
        /// @param City<T> *city: A pointer that points to a city.
        /// @param string colour: A color that represent cities and roads.
        /// @param T maxX: A maximum value of coordinate X amongst all cities added.
        /// @param T maxY: A maximum value of coordinate Y amongst all cities added.
        /// @return string: Javascript functions and variables strings.
        ///
        string GetDrawCityFunction(CityMap<T> *cmap, City<T> *city, string color, T maxX, T maxY, T minX, T minY);

        ///
        /// Get Javascript functions and variables to draw city names.
        /// @param CityMap<T> *city: A pointer that points to the instance of this class.
        /// @param City<T> *city: A pointer that points to a city.
        /// @param string colour: A color that represent cities and roads.
        /// @param T maxX: A maximum value of coordinate X amongst all cities added.
        /// @param T maxY: A maximum value of coordinate Y amongst all cities added.
        /// @return string: Javascript functions and variables strings.
        ///
        string GetDrawCityNameFunction(CityMap<T> *cmap, City<T> *city, string color, T maxX, T maxY, T minX, T minY);

        ///
        /// Get Javascript functions and variables to draw all roads.
        /// @param CityMap<T> *city: A pointer that points to the instance of this class.
        /// @param City<T> *city: A pointer that points to a city.
        /// @param string colour: A color that represent cities and roads.
        /// @param T maxX: A maximum value of coordinate X amongst all cities added.
        /// @param T maxY: A maximum value of coordinate Y amongst all cities added.
        /// @return string: Javascript functions and variables.
        ///
        string GetDrawAllRoadFunction(CityMap<T> *cmap, City<T> *city, string color, T maxX, T maxY, T minX, T minY);

        ///
        /// Get Javascript functions and variables strings.
        /// @param CityMap<T> *city: A pointer that points to the instance of this class.
        /// @param City<T> *city: A pointer that points to a city.
        /// @param City<T> *secondCity: A pointer that points to an another city.
        /// @param string colour: A color that represent cities and roads.
        /// @param T maxX: A maximum value of coordinate X amongst all cities added.
        /// @param T maxY: A maximum value of coordinate Y amongst all cities added.
        /// @return string: Javascript functions and variables.
        ///
        string GetDrawRoadFunction(CityMap<T> *cmap, City<T> *city, City<T> *secondCity, string color, T maxX, T maxY, T minX, T minY);

        ///
        /// Find A maximum value of coordinate X and Y amongst all cities added.
        ///     Two parameters X and Y will be updated as a result.
        /// @param CityMap<T> *city: A pointer that points to the instance of this class.
        /// @param T maxX: A maximum value of coordinate X amongst all cities added.
        /// @param T maxY: A maximum value of coordinate Y amongst all cities added.
        ///
        void FindMaxXAndY(CityMap<T> *cmap, T *maxX, T *maxY, T *minX, T *minY);

        ///
        /// Get Javascript functions and variables strings.
        /// @param T maxX: A maximum value of coordinate X amongst all cities added.
        /// @param T maxY: A maximum value of coordinate Y amongst all cities added.
        /// @return string: Javascript functions and variables.
        ///
        string GetProportionFunc(T maxX, T maxY);

        ///
        /// Show a message.
        /// @param string msgType: A message type.(e.g. INFO, ERR)
        /// @param string message: A message to be displayed.
        ///
        void ShowMsg(string msgType, string message);


        ///
        /// Convert number to a string.
        /// @param T number: A number
        /// @return string: A string converted to a string.
        string ToString(T number);

};



//#include "CityMap.cpp"

    /// A value that represents that distance cannot be calculated (e.g. start and goal are not connected.)
    template <typename T>
    const T CityMap<T>::NO_DISTANCE = 0;
    /// A message type: INFO
    template <typename T>
    const string CityMap<T>::MSG_TYPE_INFO = "*** INFO  *** ";
    /// A message type: ERR
    template <typename T>
    const string CityMap<T>::MSG_TYPE_ERR = "*** ERROR *** ";

    /// A message when city name specified is empty.
    template <typename T>
    const string CityMap<T>::MSG_EMPTY_NAME = " --- Please specify correct city name. ";
    /// A message when start city and goal city are the same.
    template <typename T>
    const string CityMap<T>::MSG_SAME_CITY = " --- Two cities are same.";
    /// A message when start city and goal city are not connected.
    template <typename T>
    const string CityMap<T>::MSG_NOT_CONNECTED = " --- Two cities are not connected ";
    /// A message when a city map has been generated.
    template <typename T>
    const string CityMap<T>::MSG_MAP_GENERATED = "The city map has been generated.";
    /// City name: Adelaide
    template <typename T>
    const string CityMap<T>::ADE = "Adelaide";
    /// City name: Alice Springs
    template <typename T>
    const string CityMap<T>::ALI = "Alice Springs";
    /// City name: Brisbane
    template <typename T>
    const string CityMap<T>::BRI = "Brisbane";
    /// City name: Canberra
    template <typename T>
    const string CityMap<T>::CAN = "Canberra";
    /// City name: Cairns
    template <typename T>
    const string CityMap<T>::CAI = "Cairns";
    /// City name: Darwin
    template <typename T>
    const string CityMap<T>::DAR = "Darwin";
    /// City name: Hobart
    template <typename T>
    const string CityMap<T>::HOB = "Hobart";
    /// City name: Melbourne
    template <typename T>
    const string CityMap<T>::MEL = "Melbourne";
    /// City name: Perth
    template <typename T>
    const string CityMap<T>::PER = "Perth";
    /// City name: Sydney
    template <typename T>
    const string CityMap<T>::SYD = "Sydney";

    //
    // For drawing city map
    //
    /// Template file name (for output an .html file)
    template <typename T>
    const string CityMap<T>::STR_TEMP_FILE_NAME = "citymaptemp";
    /// Output file name
    template <typename T>
    const string CityMap<T>::STR_OUTPUT_FILE_NAME = "citymap_";
    /// An Extension for output file
    template <typename T>
    const string CityMap<T>::STR_EXTENTION = ".html";

    /// Color: Ordinary city
    template <typename T>
    const string CityMap<T>::STR_CITY_COLOR = "\"#000000\"";
    /// Color: City on the shortest path
    template <typename T>
    const string CityMap<T>::STR_CITY_COLOR_SHORTEST = "\"#C84B40\"";

    /// Indent
    template <typename T>
    const string CityMap<T>::STR_INDENT = "\n\t\t\t";
    /// Key word in a template .html to find a line that Javascript codes are inserted to.
    template <typename T>
    const string CityMap<T>::STR_CODE_DRAW_ALL = "\t\t\t//draw all cities and roads";

    /// Javascript array variable: coordinate X
    template <typename T>
    const string CityMap<T>::STR_VAR_POS_X = "posX = [";
    /// Javascript array variable: coordinate Y
    template <typename T>
    const string CityMap<T>::STR_VAR_POS_Y = "posY = [";

    /// Javascript variable: proportion X
    template <typename T>
    const string CityMap<T>::STR_VAR_PROP_X = "propX = width / ";
    /// Javascript variable: proportion Y
    template <typename T>
    const string CityMap<T>::STR_VAR_PROP_Y = "propY = height / ";

    /// Javascript function: drawCity()
    template <typename T>
    const string CityMap<T>::STR_DRAW_CITY_FUNC = "drawCity(ct, ";
    /// Javascript function: drawTextCityName()
    template <typename T>
    const string CityMap<T>::STR_DRAW_CITY_NAME_FUNC = "drawTextCityName(ct, ";
    /// Javascript function: drawRoad()
    template <typename T>
    const string CityMap<T>::STR_DRAW_ROAD_FUNC = "drawRoad(ct, posX, posY, ";

    /// An error message : File read error.
    template <typename T>
    const string CityMap<T>::MSG_FILE_READ_ERR = "File read error. (CityMap template file)";

    /// An error message : No cities exist.
    template <typename T>
    const string CityMap<T>::MSG_NO_CITIES = "No cities exist.";

    template <typename T>
    const T CityMap<T>::NUM_OFFSET_X = 30;

    template <typename T>
    const T CityMap<T>::NUM_OFFSET_Y = 15;

    //
    // Implementation
    //

    ///
    /// Constructor
    ///
    template <typename T>
    CityMap<T>::CityMap()
	{

	}

    ///
    /// Destructor
    ///
    template <typename T>
    CityMap<T>::~CityMap()
	{
	    typename map<string, City<T>*>::iterator it = this->cities.begin();
	    City<T> *city;
        while(it != this->cities.end())
        {
            // free allocated memory first
            city = it->second;
            delete city;
            city = NULL;
            it++;
        }
	}

    ///
    /// Add a city.
    ///     An error message will be show when an existing city is added.
    ///
    /// @param string cityName: City name.
    /// @param T x: Coordinate X
    /// @param T y: Coordinate Y
    ///
    template <typename T>
    void CityMap<T>::AddCity(string cityName, T x, T y)
	{
	    string msg = "City " + cityName + " has been added.";
	    if(!this->IsValidName(cityName))
        {
            ShowMsg(MSG_TYPE_ERR, "AddCity() failed" + MSG_EMPTY_NAME);
            return;
        }
        //when the city already exist
        if(this->ExistCity(cityName))
        {
            ShowMsg(MSG_TYPE_ERR, "AddCity() failed --- City " + cityName + " already exist. ");
            return;
        }

        City<T> *city = new City<T>(cityName, x, y);
        this->cities[cityName] = city;
        //ShowMsg(MSG_TYPE_INFO, msg);
	}

    ///
    /// Add roads between two cities, both ways firstCity to secondCity and secondCity to firstCity.
    ///     An error message will be show when firstCity and/or secondCity do not exist.
    ///     An error message will be show when firstCity and secondCity are the same.
    ///
    /// @param string firstCity: First city.
    /// @param string secondCity: Second city.
    ///
    template <typename T>
    void CityMap<T>::AddRoad(string firstCity, string secondCity)
	{
	    string errMsg = this->CheckCities(firstCity, secondCity, true);
	    if(errMsg != "")
        {
            ShowMsg(MSG_TYPE_ERR, "AddRoad() failed" + errMsg);
            return;
        }
        City<T> *start = this->GetCityByName(firstCity);
        City<T> *goal = this->GetCityByName(secondCity);

        //Two roads (first to second, second to first) are added.
        T cost = CalcCostToNextCity(start, goal);
        start->SetNextCity(goal->GetName(), goal);
        start->SetCostToNextCityByName(secondCity, cost);

        goal->SetNextCity(start->GetName(), start);
        goal->SetCostToNextCityByName(firstCity, cost);

        //debug code
	    //cout << this->MSG_TYPE_INFO << "Road " << firstCity << " - " << secondCity << "(" << cost << ")" << " has been added." << endl;
        //this->ShowRelationWithCost(firstCity, secondCity, cost);
	}

    ///
    /// Remove an existing city.
    ///     An error message will be show when the city does not exist.
    ///
    /// @param string cityName: City name.
    ///
    template <typename T>
    void CityMap<T>::RemoveCity(string cityName)
    {
        string errMsg = this->CheckCities(cityName, "", false);
	    if(errMsg != "")
        {
            ShowMsg(MSG_TYPE_ERR, "RemoveCity() failed" + errMsg);
            return;
        }
        City<T> *city = this->GetCityByName(cityName);
        City<T> *nextCity;
        map<string, City<T>*> nextCities = city->GetNextCities();
        map<string, T> costToNext = city->GetCostsToNextCities();
        typename map<string, City<T>*>::iterator itNext = nextCities.begin();
        typename map<string, T>::iterator itCost = costToNext.begin();

        //Two cities are connected each other,
        // thus the target city needs to be removed from next city's nextCities object
        // as well as the cost to target city from the next cities.
        while(itNext != nextCities.end())
        {
            nextCity = itNext->second;
            nextCity->EraseNextCityByName(cityName);
            nextCity->EraseCostToNextCityByName(cityName);
            itNext++;
        }

        //delete the target city in the map
        typename map<string, City<T>*>::iterator it = this->cities.find(cityName);
        if(it != this->cities.end())
        {
            this->cities.erase(it);
        }

        //free allocated memory
        delete city;
        city = NULL;
	    //this->ShowMsg(this->MSG_TYPE_INFO, cityName + " has been removed.");
	}

    ///
    /// Remove roads between two cities, both ways firstCity to secondCity and secondCity to firstCity.
    ///     An error message will be show when firstCity and/or secondCity do not exist.
    ///     An error message will be show when firstCity and secondCity are the same.
    ///
    /// @param string firstCity: First (start) city.
    /// @param string secondCity: Second (goal) city.
    ///
    template <typename T>
    void CityMap<T>::RemoveRoad(string firstCity, string secondCity)
	{
	    string errMsg = this->CheckCities(firstCity, secondCity, true);
	    if(errMsg != "")
        {
            ShowMsg(MSG_TYPE_ERR, "RemoveRoad() failed" + errMsg);
            return;
        }
        City<T> *start = this->GetCityByName(firstCity);
        City<T> *goal = this->GetCityByName(secondCity);

        //both citis are automatically connected each other when a road is added,
        //thus when second city does not exist in first city's nextCities object,
        //that means that two cities are not connected.
        map<string, City<T>*> nextCities = start->GetNextCities();
        if(nextCities.find(secondCity) == nextCities.end())
        {
            ShowMsg(MSG_TYPE_ERR, "RemoveRoad() failed" + MSG_NOT_CONNECTED);
            return;
        }

        //Two cities are connected each other, thus road needs to be deleted from both cities.
        start->EraseNextCityByName(secondCity);
        start->EraseCostToNextCityByName(secondCity);
        goal->EraseNextCityByName(firstCity);
        goal->EraseCostToNextCityByName(firstCity);
	}

    ///
    /// Find the shortest distance between two cities.
    ///     The method returns 0 when firstCity and secondCity are not connected.
    ///     An error message will be show when firstCity and/or secondCity do not exist.
    ///     An error message will be show when firstCity and secondCity are the same.
    ///
    /// @param string firstCity: First (start) city.
    /// @param string secondCity: Second (goal) city.
    /// @return T: The shortest distance between two cities.
    ///
    template <typename T>
    T CityMap<T>::FindDistance(string firstCity, string secondCity)
	{
        T newTotalCost = 0;
        string errMsg = this->CheckCities(firstCity, secondCity, true);
	    if(errMsg != "")
        {
            ShowMsg(MSG_TYPE_ERR, "FindDistance() failed" + errMsg);
            return newTotalCost;
        }
        priority_queue<City<T>*, vector<City<T>*>, greater<City<T>*> > pq;

        //initialise
        InitializePathAndCost();
        City<T> *city;
        City<T> *nextCity;

        //start city has no cost (zero).
        city = this->GetCityByName(firstCity);
        city->SetTotalCost(0);
        if(firstCity == secondCity)
        {
            city->GetTotalCost();
        }

        //push the first city to the queue.
        pq.push(city);

        //Get all next cities connected to the city.
        map<string, City<T>*> nextCities;
        map<string, T> costsToNextCities;
        typename map<string, City<T>*>::iterator itNextCities;
        while(!pq.empty())
        {
            city = pq.top();
            pq.pop();
            //when the flag is on, calculation is done, thus ignore it.
            if(city->IsDoneCalc())
            {
                continue;
            }

            city->SetDoneCalc(true);
            nextCities = city->GetNextCities();
            itNextCities = nextCities.begin();
            costsToNextCities = city->GetCostsToNextCities();

            //calculate total cost (cost from start city to current city + cost to next city)
            while(itNextCities != nextCities.end())
            {
                //get next city from iterator
                nextCity = itNextCities->second;
                newTotalCost = costsToNextCities[nextCity->GetName()];
                //if(city->GetTotalCost() != DBL_MAX && city->GetTotalCost() == INFINITY)
                if(city->GetTotalCost() != DBL_MAX)
                {
                    newTotalCost += city->GetTotalCost();
                }
                /*
                if(city->GetTotalCost() == DBL_MAX)
                {
                    newTotalCost = costsToNextCities[nextCity->GetName()];
                }
                else
                {
                    newTotalCost = city->GetTotalCost() + costsToNextCities[nextCity->GetName()];
                }
                */
                //if new total cost is smaller than current one, then it will be updated
                if(newTotalCost < nextCity->GetTotalCost())
                {
                    nextCity->SetTotalCost(newTotalCost);
                    //keep this city in next city's prevCity to retrieve the shortest path later on.
                    nextCity->SetPrevCity(city);
                    pq.push(nextCity);
                }

                itNextCities++;
            }
        }
        //if start and goal are not connected, return 0;
        city = this->GetCityByName(secondCity);
        if(INFINITY == city->GetTotalCost() || DBL_MAX == city->GetTotalCost())
        {
            return NO_DISTANCE;
        }
        return city->GetTotalCost();
	}

    ///
    /// Find the shortest path between two cities.
    ///     The return value contains 1 name when firstCity and secondCity are not connected.
    ///     An error message will be show when firstCity and/or secondCity do not exist.
    ///     An error message will be show when firstCity and secondCity are the same.
    ///
    /// @param string firstCity: First (start) city.
    /// @param string secondCity: Second (goal) city.
    /// @return vector<string>: All cities that are on the shortest path between two cities.
    ///
    template <typename T>
    vector<string> CityMap<T>::ShortestPath(string firstCity, string secondCity)
	{
        vector<string> paths;
        string errMsg = this->CheckCities(firstCity, secondCity, true);
	    if(errMsg != "")
        {
            ShowMsg(MSG_TYPE_ERR, "ShortestPath() failed" + errMsg);
            return paths;
        }

        //calculate the shortest distance
        this->FindDistance(firstCity, secondCity);
        string ret;
        City<T> *goalCity = this->GetCityByName(secondCity);
        ret = this->GetPreviCityName(goalCity, &paths);
        paths.push_back(ret);

        return paths;
	}


    ///
    /// Display the shortest path and distance between two cities.
    ///     The method show 0 as the shortest distance when firstCity and secondCity are not connected.
    ///     An error message will be show when firstCity and/or secondCity do not exist.
    ///     An error message will be show when firstCity and secondCity are the same.
    ///
    /// @param string firstCity: First (start) city.
    /// @param string secondCity: Second (goal) city.
    ///
    template <typename T>
    void CityMap<T>::PrintPath(string firstCity, string secondCity)
	{
        string errMsg = this->CheckCities(firstCity, secondCity, true);
	    if(errMsg != "")
        {
            ShowMsg(MSG_TYPE_ERR, "PrintPath() failed" + errMsg);
            return;
        }
        T dist = this->FindDistance(firstCity, secondCity);
        vector<string> paths = this->ShortestPath(firstCity, secondCity);

	    string path = "Shortest Path: ";
        //when no cities found or city names are not the same as the parameters
        if(paths.size() < 1 || (paths[0] != firstCity || paths[paths.size() - 1] != secondCity))
        {
            path = MSG_NOT_CONNECTED + "---";
        }
        else
        {
            //create a string that represent the shortest path
            vector<string>::iterator it = paths.begin();
            for(int i = 0; i < (int)paths.size(); i++)
            {
                path += *it;
                if(i != (int)(paths.size() - 1))
                {
                    path += " -> ";
                }
                it++;
            }
        }
        path += " (Distance = " + this->ToString(dist) + " km)";
        cout << path << endl;

        if(this->GenerateCityMap(this, paths))
        {
            this->ShowMsg(MSG_TYPE_INFO, MSG_MAP_GENERATED);
        }
	}

    ///
    /// Get All cities added
    /// @return map<string, City<T>*>: A map container that contains all cities added.
    ///
    template <typename T>
    map<string, City<T>*> CityMap<T>::GetCities()
    {
        return this->cities;
    }

    ///
    /// Get a city
    /// @return City<T>*: A pointer that points to a city.
    ///
    template <typename T>
    City<T>* CityMap<T>::GetCityByName(string cityName)
    {
        //If map instance is accessed with [] operator and the key doesn't exist,
        //a new element will automatically be created, thus use find() method to find it.
        if(this->cities.find(cityName) != this->cities.end())
        {
            return this->cities[cityName];
        }
        return NULL;
    }

    ///
    /// Calculate cost to next city.
    /// @param City<T> *city1: A pointer that points to a city.
    /// @param City<T> *city2: A pointer that points to a next city.
    /// @return T: The cost between a city and a next city.
    ///
    template <typename T>
    T CityMap<T>::CalcCostToNextCity(City<T> *city1, City<T> *city2)
    {
        return this->CalcCostToNextCity(
                    city1->GetX(), city1->GetY(),
                    city2->GetX(), city2->GetY() );
    }

    ///
    /// Calculate cost to next city.
    /// @param T city1X: Corrdinate X of a city
    /// @param T city1Y: Corrdinate Y of a city
    /// @param T city2X: Corrdinate X of a next city
    /// @param T city2Y: Corrdinate Y of a next city
    /// @return T: The cost between a city and a next city.
    ///
    template <typename T>
    T CityMap<T>::CalcCostToNextCity(T city1X, T city1Y, T city2X, T city2Y )
    {
        T distX = city2X - city1X;
        T distY = city2Y - city1Y;
        return sqrt(pow(distX, 2.0) + pow(distY, 2.0));
    }

    ///
    /// Initialise values that all cities contains.
    ///
    template <typename T>
    void CityMap<T>::InitializePathAndCost()
    {
        City<T> *city;
        map<string, City<T>*> allCities = this->GetCities();
        typename map<string, City<T>*>::iterator itAllCities = allCities.begin();
        while(itAllCities != allCities.end())
        {
            city = itAllCities->second;
            city->SetPrevCity(NULL);
            city->SetDoneCalc(false);
            city->SetTotalCost(DBL_MAX);
            itAllCities++;
        }
    }

    ///
    /// Check if a city name is valid.
    /// @param string target: A city name.
    /// @return bool: True when a city name is valid.
    ///
    template <typename T>
    bool CityMap<T>::IsValidName(string cityName)
    {
	    return cityName != "";
    }

    ///
    /// Check if a city already exist.
    /// @param string cityName: A city name.
    /// @return bool: True when a city already exist
    ///
    template <typename T>
    bool CityMap<T>::ExistCity(string cityName)
    {
        if(this->cities.find(cityName) == this->cities.end())
        {
            return false;
        }
        return true;
    }

    ///
    /// Check if a city name is valid and already exist.
    /// @param string firstCity: A city name.
    /// @param string secondCity: An another city name.
    /// @param bool checkSecond: True if the another city name needs to be checked.
    /// @return string: A message. An empty message when both names are valid and
    ///                 do not exist in A map container that contains all cities added.
    ///
    template <typename T>
    string CityMap<T>::CheckCities(string firstCity, string secondCity, bool checkSecond)
    {
        string msg = " --- City " + firstCity + " or " + secondCity + " does not exist.";
	    if(!this->IsValidName(firstCity))
        {
            return MSG_EMPTY_NAME;
        }
        if(!this->ExistCity(firstCity))
        {
            return msg;
        }

        if(checkSecond)
        {
            if(!this->IsValidName(secondCity))
            {
                return MSG_EMPTY_NAME;
            }
            if(!this->ExistCity(secondCity))
            {
                return msg;
            }
            if(firstCity == secondCity)
            {
                return MSG_SAME_CITY;
            }
        }
        return "";
    }


    ///
    /// Get a previous city name.
    /// @param City<T> *city: A pointer that points to a city.
    /// @param vector<string> *vecNames: A vector container that contains city names.
    /// @return string: A previous city name.
    ///
    template <typename T>
    string CityMap<T>::GetPreviCityName(City<T> *city, vector<string> *vecNames)
    {
        string ret;
        if(city->GetPrevCity() != NULL)
        {
            ret = this->GetPreviCityName(city->GetPrevCity(), vecNames);
            vecNames->push_back(ret);
        }
        ret = city->GetName();

        return ret;
    }

    ///
    /// Clear all cities added.
    ///
    template <typename T>
    void CityMap<T>::ClearAllCities()
    {
        this->cities.clear();
    }

    ///
    /// Show a message.
    /// @param string msgType: A message type.(e.g. INFO, ERR)
    /// @param string message: A message to be displayed.
    ///
    template <typename T>
    void CityMap<T>::ShowMsg(string msgType, string message)
    {
        cout << msgType << message << endl;
    }

    ///
    /// Convert number to a string.
    /// @param T number: A number
    /// @return string: A string converted to a string.
    template <typename T>
    string CityMap<T>::ToString(T number)
    {
        ostringstream oss;
        oss << number;
        return oss.str();
    }

    //
    // For drawing city map
    //

    ///
    /// Generate a city map .html
    /// @param CityMap<T> *cmap: A pointer that points to the instance of this class.
    /// @param vector<string> path: The (shortest) path to be drawn.
    ///
    template <typename T>
    bool CityMap<T>::GenerateCityMap(CityMap<T> *cmap, vector<string> path)
    {
        if(path.size() == 0)
        {
            cerr << MSG_NO_CITIES << endl;
            return false;
        }
        string start = path[0];
        string goal = "";
        if(path.size() > 1)
        {
            goal = path[path.size() - 1];
        }

        // Get template file name, output file name with current time.
        // To avoid that the same .html files are generated, each file name has current minute, second and millisecond.
        SYSTEMTIME st;
        GetSystemTime(&st);
        string tempFile = STR_TEMP_FILE_NAME + STR_EXTENTION;
        string outputFile = STR_OUTPUT_FILE_NAME + start + "_" + goal + "_" +
                            cmap->ToString(st.wMinute) + cmap->ToString(st.wSecond) +
                            cmap->ToString(st.wMilliseconds) + STR_EXTENTION;

        ifstream ifs(tempFile.c_str(), ios::in);
        ofstream ofs(outputFile.c_str(), ios::trunc);

        if (ifs.fail())
        {
            cerr << MSG_FILE_READ_ERR << endl;
            return false;
        }
        //generate an .html file
        bool ret = this->WriteAllCitiesAndRoads(&ifs, &ofs, cmap, path);
        ifs.close();
        ofs.close();
        return ret;
    }

    ///
    /// Write Javascript functions and variables to draw all cities and roads
    /// @param ifstream *ifs: A pointer of ifstream instance.
    /// @param ofstream *ofs: A pointer of ofstream instance.
    /// @param CityMap<T> *cmap: A pointer that points to the instance of this class.
    /// @param vector<string> path: The (shortest) path to be drawn.
    ///
    template <typename T>
    bool CityMap<T>::WriteAllCitiesAndRoads(ifstream *ifs, ofstream *ofs, CityMap<T> *cmap, vector<string> path)
    {
        string str;
        map<string, City<T>* > cities = cmap->GetCities();
        if(cities.size() == 0 )
        {
            return false;
        }
        typename map<string, City<T>* >::iterator it = cities.begin();
        string strProportionVar;
        string drawCityFunc;
        string drawCityNameFunc;
        string drawRoadFunc;
        City<T> *city;

        T maxX = 0;
        T maxY = 0;
        T minX = 0;
        T minY = 0;
        this->FindMaxXAndY(cmap, &maxX, &maxY, &minX, &minY);
        //cout << minX << endl;
        //cout << minY << endl;
        maxX = fabs(minX) + maxX;
        maxY = fabs(minY) + maxY;
        //cout << maxX << endl;
        //cout << maxY << endl;
        strProportionVar = this->GetProportionFunc(maxX, maxY);
        while (getline(*ifs, str))
        {
            if(str == STR_CODE_DRAW_ALL)
            {
                // Output draw functions and necessary variables to draw all cities and roads.
                // Definition of each functions already exist in the template file,
                // thus this method returns Javascript that calls the functions and
                // generate arrays to be passed to the functions.
                //
                // Example result:
                //  drawCity(ct, 100, 100, "#000000" );
                //  drawTextCityName(ct, 100, 100, "Brisbane", "#000000" );
                //  drawCity(ct, 200, 200, "#000000" );
                //  drawTextCityName(ct, 200, 200, "Sydney", "#000000" );
                //  posX = [100, 200];
                //  posY = [100, 200];
                //  drawRoad(ct, posX, posY, "#000000");
                //

                //write proportions first
                *ofs << strProportionVar + STR_INDENT << endl;

                while(it != cities.end())
                {
                    city = it->second;
                    drawCityFunc = this->GetDrawCityFunction(cmap, city, STR_CITY_COLOR, maxX, maxY, minX, minY);
                    drawCityNameFunc = this->GetDrawCityNameFunction(cmap, city, STR_CITY_COLOR, maxX, maxY, minX, minY);
                    drawRoadFunc = this->GetDrawAllRoadFunction(cmap, city, STR_CITY_COLOR, maxX, maxY, minX, minY);
                    *ofs << (drawCityFunc + STR_INDENT + drawCityNameFunc + STR_INDENT + drawRoadFunc) << endl;
                    it++;
                }
                *ofs << str << endl;
                //
                // draw the shortest path
                //
                this->WriteShortestPath(ifs, ofs, cmap, path);
            }
            else
            {
                *ofs << str << endl;
            }
        }
        //this->WriteShortestPath(ifs, ofs, cmap, path);
    }

    ///
    /// Write Javascript functions and variables to draw the shortest path with different colour.
    /// @param ifstream *ifs: A pointer of ifstream instance.
    /// @param ofstream *ofs: A pointer of ofstream instance.
    /// @param CityMap<T> *cmap: A pointer that points to the instance of this class.
    /// @param vector<string> path: The (shortest) path to be drawn.
    ///
    template <typename T>
    void CityMap<T>::WriteShortestPath(ifstream *ifs, ofstream *ofs, CityMap<T> *cmap, vector<string> path)
    {
        string str;
        vector<string>::iterator it;
        string drawCityFunc;
        string drawCityNameFunc;
        string drawRoadFunc;
        City<T> *city;
        City<T> *prevCity;

        //string goal = path[path.size() - 1];
        city = cmap->GetCityByName(path[path.size() - 1]);
        prevCity = city->GetPrevCity();
        T maxX = 0;
        T maxY = 0;
        T minX = 0;
        T minY = 0;
        this->FindMaxXAndY(cmap, &maxX, &maxY, &minX, &minY);
        maxX = fabs(minX) + maxX;
        maxY = fabs(minY) + maxY;

        // Tracking previous city, draw all cities and roads on the shortest path.
        while(prevCity != NULL)
        {
            drawCityFunc = this->GetDrawCityFunction(cmap, city, STR_CITY_COLOR_SHORTEST, maxX, maxY, minX, minY);
            drawCityNameFunc = this->GetDrawCityNameFunction(cmap, city, STR_CITY_COLOR_SHORTEST, maxX, maxY, minX, minY);
            drawCityFunc += this->GetDrawRoadFunction(cmap, city, prevCity, STR_CITY_COLOR_SHORTEST, maxX, maxY, minX, minY);
            *ofs << (drawCityFunc + STR_INDENT + drawCityNameFunc + STR_INDENT + drawRoadFunc) << endl;
            city = prevCity;
            prevCity = city->GetPrevCity();
        }
        //draw start city here
        drawCityFunc = this->GetDrawCityFunction(cmap, city, STR_CITY_COLOR_SHORTEST, maxX, maxY, minX, minY);
        drawCityNameFunc = this->GetDrawCityNameFunction(cmap, city, STR_CITY_COLOR_SHORTEST, maxX, maxY, minX, minY);
        *ofs << drawCityFunc + STR_INDENT + drawCityNameFunc << endl;
    }


    ///
    /// Get Javascript functions and variables to draw cities.
    /// @param CityMap<T> *city: A pointer that points to the instance of this class.
    /// @param City<T> *city: A pointer that points to a city.
    /// @param string colour: A color that represent cities and roads.
    /// @return string: Javascript functions and variables strings.
    ///
    template <typename T>
    string CityMap<T>::GetDrawCityFunction(CityMap<T> *cmap, City<T> *city, string color, T maxX, T maxY, T minX, T minY)
    {
        T x = city->GetX() + fabs(minX);
        T y = city->GetY() + fabs(minY);
        if(maxX == city->GetX())
        {
            x -= NUM_OFFSET_X;
        }
        if(minX == city->GetX())
        {
            x = NUM_OFFSET_X;
        }
        if(maxY == city->GetY())
        {
            y -= NUM_OFFSET_Y;
        }
        if(minY == city->GetY())
        {
            y = NUM_OFFSET_X;
        }

        string ret;
        //create drawCity function
        ret += STR_INDENT;
        ret += STR_DRAW_CITY_FUNC;
        ret += cmap->ToString(x) +
                        ", " + cmap->ToString(y) +
                        ", " + color +
                        " );";

        return ret;
    }

    ///
    /// Get Javascript functions and variables to draw city names.
    /// @param CityMap<T> *city: A pointer that points to the instance of this class.
    /// @param City<T> *city: A pointer that points to a city.
    /// @param string colour: A color that represent cities and roads.
    /// @return string: Javascript functions and variables strings.
    ///
    template <typename T>
    string CityMap<T>::GetDrawCityNameFunction(CityMap<T> *cmap, City<T> *city, string color, T maxX, T maxY, T minX, T minY)
    {
        T x = city->GetX() + fabs(minX);
        T y = city->GetY() + fabs(minY);
        if(maxX == city->GetX())
        {
            x -= NUM_OFFSET_X;
        }
        if(minX == city->GetX())
        {
            x = NUM_OFFSET_X;
        }
        if(maxY == city->GetY())
        {
            y -= NUM_OFFSET_Y;
        }
        if(minY == city->GetY())
        {
            y = NUM_OFFSET_X;
        }
        string ret;
        //create drawCity function
        ret += STR_INDENT;
        ret += STR_DRAW_CITY_NAME_FUNC;

        ret += cmap->ToString(x) +
                        ", " + cmap->ToString(y) +
                        ", \"" + city->GetName() +
                        "\", " + color +
                        " );";

        return ret;
    }


    ///
    /// Get Javascript functions and variables to draw all roads.
    /// @param CityMap<T> *city: A pointer that points to the instance of this class.
    /// @param City<T> *city: A pointer that points to a city.
    /// @param string colour: A color that represent cities and roads.
    /// @return string: Javascript functions and variables.
    ///
    template <typename T>
    string CityMap<T>::GetDrawAllRoadFunction(CityMap<T> *cmap, City<T> *city, string color, T maxX, T maxY, T minX, T minY)
    {
        T x = city->GetX() + fabs(minX);
        T y = city->GetY() + fabs(minY);
        if(maxX == city->GetX())
        {
            x -= NUM_OFFSET_X;
        }
        if(minX == city->GetX())
        {
            x = NUM_OFFSET_X;
        }
        if(maxY == city->GetY())
        {
            y -= NUM_OFFSET_Y;
        }
        if(minY == city->GetY())
        {
            y = NUM_OFFSET_X;
        }
        string ret;
        string roadPosX;
        string roadPosY;
        map<string, City<T>* > nextCities;
        typename map<string, City<T>* >::iterator itNext;
        //create drawRoad function
        roadPosX = STR_VAR_POS_X + cmap->ToString(x) + ", ";
        roadPosY = STR_VAR_POS_Y + cmap->ToString(y) + ", ";

        City<T> *nextCity;
        nextCities = city->GetNextCities();
        //if there are no roads
        if(nextCities.size() == 0)
        {
            return "";
        }

        itNext = nextCities.begin();
        while(itNext != nextCities.end())
        {
            nextCity = itNext->second;
            ret += this->GetDrawRoadFunction(cmap, city, nextCity, STR_CITY_COLOR, maxX, maxY, minX, minY);
            itNext++;
        }

        return ret;
    }

    ///
    /// Get Javascript functions and variables strings.
    /// @param CityMap<T> *city: A pointer that points to the instance of this class.
    /// @param City<T> *city: A pointer that points to a city.
    /// @param City<T> *secondCity: A pointer that points to an another city.
    /// @param string colour: A color that represent cities and roads.
    /// @return string: Javascript functions and variables.
    ///
    template <typename T>
    string CityMap<T>::GetDrawRoadFunction(CityMap<T> *cmap, City<T> *city, City<T> *secondCity,
                                           string color, T maxX, T maxY, T minX, T minY)
    {
        T x = city->GetX() + fabs(minX);
        T y = city->GetY() + fabs(minY);
        if(maxX == city->GetX())
        {
            x -= NUM_OFFSET_X;
        }
        if(minX == city->GetX())
        {
            x = NUM_OFFSET_X;
        }
        if(maxY == city->GetY())
        {
            y -= NUM_OFFSET_Y;
        }
        if(minY == city->GetY())
        {
            y = NUM_OFFSET_X;
        }

        string ret;
        string roadPosX;
        string roadPosY;
        map<string, City<T>* > nextCities;
        typename map<string, City<T>* >::iterator itNext;
        //create drawRoad function
        roadPosX = STR_VAR_POS_X + cmap->ToString(x) + ", ";
        roadPosY = STR_VAR_POS_Y + cmap->ToString(y) + ", ";

        x = secondCity->GetX() + fabs(minX);
        y = secondCity->GetY() + fabs(minY);
        if(maxX == secondCity->GetX())
        {
            x -= NUM_OFFSET_X;
        }
        if(minX == secondCity->GetX())
        {
            x = NUM_OFFSET_X;
        }
        if(maxY == secondCity->GetY())
        {
            y -= NUM_OFFSET_Y;
        }
        if(minY == secondCity->GetY())
        {
            y = NUM_OFFSET_X;
        }
        roadPosX += cmap->ToString(x);
        roadPosY += cmap->ToString(y);
        roadPosX += "];";
        roadPosY += "];";
        ret += STR_INDENT +
                roadPosX + STR_INDENT + roadPosY + STR_INDENT +
                STR_DRAW_ROAD_FUNC + color + ");";

        return ret;
    }

    ///
    /// Find A maximum value of coordinate X and Y amongst all cities added.
    ///     Two parameters X and Y will be updated as a result.
    /// @param CityMap<T> *city: A pointer that points to the instance of this class.
    /// @param T maxX: A maximum value of coordinate X amongst all cities added.
    /// @param T maxY: A maximum value of coordinate Y amongst all cities added.
    ///
    template <typename T>
    void CityMap<T>::FindMaxXAndY(CityMap<T> *cmap, T *maxX, T *maxY, T *minX, T *minY)
    {
        City<T> *city;
        map<string, City<T>* > cities = cmap->GetCities();
        typename map<string, City<T>* >::iterator it = cities.begin();
        while(it != cities.end())
        {
            city = it->second;
            if(*maxX < city->GetX())
            {
                *maxX = city->GetX();
            }
            if(*maxY < city->GetY())
            {
                *maxY = city->GetY();
            }
            if(*minX > city->GetX())
            {
                //cout << city->GetX() << endl;
                //cout << *minX << endl;
                *minX = city->GetX();
            }
            if(*minY > city->GetY())
            {
                //cout << *minY << endl;
                //cout << city->GetY() << endl;
                *minY = city->GetY();
            }
            it++;
        }

    }

    ///
    /// Get Javascript functions and variables strings.
    /// @param T maxX: A maximum value of coordinate X amongst all cities added.
    /// @param T maxY: A maximum value of coordinate Y amongst all cities added.
    /// @return string: Javascript functions and variables.
    ///
    template <typename T>
    string CityMap<T>::GetProportionFunc(T maxX, T maxY)
    {
        string ret = STR_INDENT + STR_VAR_PROP_X + ToString(maxX) + ";";
        return ret + STR_INDENT + STR_VAR_PROP_Y + ToString(maxY) + ";" + STR_INDENT;
    }


/*
template class CityMap<int>;
template class CityMap<float>;
template class CityMap<double>;
*/

#endif // CITYMAP_H
