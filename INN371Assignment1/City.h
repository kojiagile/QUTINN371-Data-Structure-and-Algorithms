#pragma once

#ifndef CITY_H_INCLUDED
#define CITY_H_INCLUDED

#include <string>
#include <vector>
#include <map>

using namespace std;

/*
template<typename T> class City;
template<typename T> bool operator> (const City<T> &city1, const City<T> &city2);
template<typename T> bool operator< (const City<T> &city1, const City<T> &city2);
*/


///
/// City class
///     The class store city's name and its coordinate
///     as well as cities that connected to the city and cost from start city.
///
template <typename T>
class City
{
    public:

        ///
        /// Constructor
        ///
        City();

        ///
        /// Constructor
        /// @param string name: City name
        /// @param T x: Coordinate X
        /// @param T y: Coordinate Y
        ///
        City(string name, T x, T y);

        ///
        /// Destructor
        ///
        ~City();

        ///
        /// Getter: Coordinate X
        /// @return T Coordinate X
        ///
        T GetX();

        ///
        /// Getter: Coordinate Y
        /// @return T Coordinate Y
        ///
        T GetY();

        ///
        /// Getter: City name
        /// @return string City name.
        ///
        string GetName();

        ///
        /// Getter: Total Cost
        /// @return T total cost
        ///
        T GetTotalCost();

        ///
        /// Getter: doneCalc
        /// @return bool Flag that represent whether all costs to next cities have been calculated.
        ///
        bool IsDoneCalc();

        ///
        /// Getter: previous city
        /// @return City<T> Previous city
        ///
        City *GetPrevCity();

        ///
        /// Getter: All next cities (connected to this city.)
        /// @return map<string, City*> All next cities connected to the city.
        ///
        map<string, City*> GetNextCities();

        ///
        /// Setter: Coordinate X
        /// @param T x: Coordinate X
        ///
        void SetX(T x);

        ///
        /// Setter: Coordinate Y
        /// @param T y: Coordinate Y
        ///
        void SetY(T x);

        ///
        /// Setter: name
        /// @param string name: City name
        ///
        void SetName(string name);

        ///
        /// Setter: Total cost
        /// @param T cost: Total cost
        ///
        void SetTotalCost(T cost);

        ///
        /// Setter: Flag that represent whether all costs to next cities have been calculated.
        /// @param bool doneCalc: Flag that represent whether all costs to next cities have been calculated.
        ///
        void SetDoneCalc(bool doneCalc);

        ///
        /// Setter: Previous city
        /// @param City city: Previous city
        ///
        void SetPrevCity(City *city);

        ///
        /// Setter: Set next cities that connected to the city.
        /// @param string cityName: Next city name
        /// @param City nextCity: Next city
        ///
        void SetNextCity(string cityName, City *nextCity);

        ///
        /// Get next city.
        /// @param string cityName: Next city name to be retrieved.
        ///
        City* GetNextCityByName(string cityName);

        ///
        /// Get the cost to next city.
        /// @param string nextCity: Next city name to be retrieved.
        /// @return T cost to next city.
        ///
        T GetCostToNextCityByName(string nextCity);

        ///
        /// Get all cost to next cities.
        /// @return map<string, T> All costs to next cities.
        ///
        map<string, T> GetCostsToNextCities();

        ///
        /// Set cost to next city.
        /// @param string nextCity: Next city
        /// @param T cost: Cost to the next city.
        ///
        void SetCostToNextCityByName(string nextCity, T cost);

        ///
        /// Erase next city.
        /// @param string cityName: Next city to be removed.
        ///
        void EraseNextCityByName(string cityName);

        ///
        /// Erase cost to next city.
        /// @param string cityName: Next city to be removed.
        ///
        void EraseCostToNextCityByName(string cityName);

        ///
        /// Oveload method of "<" operator
        /// @param const City<T> &city1: City 1
        /// @param const City<T> &city2: City 2
        /// @return bool true when city1->totalCost is smaller than city1->totalCost.
        ///
        friend bool operator< (const City<T> &city1, const City<T> &city2);

        ///
        /// Oveload method of "<" operator
        /// @param const City<T> &city1: City 1
        /// @param const City<T> &city2: City 2
        /// @return bool true when city1->totalCost is bigger than city1->totalCost.
        ///
        friend bool operator> (const City<T> &city1, const City<T> &city2);

    private:

        ///
        /// Coordinate X
        ///
        T x;

        ///
        /// Coordinate Y
        ///
        T y;

        ///
        /// City name.
        ///
        string name;

        ///
        /// Total cost.
        ///     This stores minimum cost to reach this city(node) from start city(node).
        ///     When (new) smaller minimum cost is found, the cost will be stored in this variable.
        ///
        T totalCost;

        ///
        /// Flag that represent whether all costs to next cities have been calculated.
        ///     True:  All cost of the roads(edges) connected to this city has been calculated.
        ///     False: All cost of the roads(edges) connected to this city has not yet been calculated.
        ///
        bool doneCalc;

        ///
        /// Previous city.
        ///     Note: prevCity has to be updated when totalCost is updated
        ///           to save a city with the smallest cost.
        ///
        City *prevCity;

        ///
        /// Cities connected to this city.
        ///
        map<string, City*> nextCities;

        ///
        /// Costs to get to next cities.
        ///     This is simply the cost from this city to next cities.
        ///
        map<string, T> costsToNextCities;
};

#include "City.cpp"

#endif // CITY_H_INCLUDED
