#pragma once

#include <string>
#include <iterator>
#include <map>
#include <iostream>
#include <cfloat>

//#include "City.h"

using namespace std;

#ifdef CITY_H_INCLUDED

    ///
    /// Constructor
    ///
    template <typename T>
    City<T>::City()
    {
        this->x = 0;
        this->y = 0;
        this->doneCalc = false;
        this->totalCost = DBL_MAX;
    }


    ///
    /// Constructor
    /// @param string name: City name
    /// @param T x: Coordinate X
    /// @param T y: Coordinate Y
    ///
    template <typename T>
    City<T>::City(string name, T x, T y)
    {
        this->name = name;
        this->x = x;
        this->y = y;
        this->doneCalc = false;
        this->totalCost = DBL_MAX;
    }

    ///
    /// Destructor
    ///
    template <typename T>
    City<T>::~City()
    {

    }

    ///
    /// Getter: Coordinate X
    /// @return T Coordinate X
    ///
    template <typename T>
    T City<T>::GetX()
    {
        return this->x;
    }

    ///
    /// Getter: Coordinate Y
    /// @return T Coordinate Y
    ///
    template <typename T>
    T City<T>::GetY()
    {
        return this->y;
    }

    ///
    /// Getter: City name
    /// @return string City name.
    ///
    template <typename T>
    string City<T>::GetName()
    {
        return this->name;
    }

    ///
    /// Getter: Total Cost
    /// @return T total cost
    ///
    template <typename T>
    T City<T>::GetTotalCost()
    {
        return this->totalCost;
    }

    ///
    /// Getter: doneCalc
    /// @return bool Flag that represent whether all costs to next cities have been calculated.
    ///
    template <typename T>
    bool City<T>::IsDoneCalc()
    {
        return this->doneCalc;
    }

    ///
    /// Getter: previous city
    /// @return City<T> Previous city
    ///
    template <typename T>
    City<T>* City<T>::GetPrevCity()
    {
        return this->prevCity;
    }

    ///
    /// Getter: All next cities (connected to this city.)
    /// @return map<string, City*> All next cities connected to the city.
    ///
    template <typename T>
    map<string, City<T>* > City<T>::GetNextCities()
    {
        return this->nextCities;
    }


    ///
    /// Setter: Coordinate X
    /// @param T x: Coordinate X
    ///
    template <typename T>
    void City<T>::SetX(T x)
    {
        this->x = x;
    }

    ///
    /// Setter: Coordinate Y
    /// @param T y: Coordinate Y
    ///
    template <typename T>
    void City<T>::SetY(T y)
    {
        this->y = y;
    }

    ///
    /// Setter: name
    /// @param string name: City name
    ///
    template <typename T>
    void City<T>::SetName(string name)
    {
        this->name = name;
    }

    ///
    /// Setter: Total cost
    /// @param T cost: Total cost
    ///
    template <typename T>
    void City<T>::SetTotalCost(T cost)
    {
        this->totalCost = cost;
    }

    ///
    /// Setter: Flag that represent whether all costs to next cities have been calculated.
    /// @param bool doneCalc: Flag that represent whether all costs to next cities have been calculated.
    ///
    template <typename T>
    void City<T>::SetDoneCalc(bool doneCalc)
    {
        this->doneCalc = doneCalc;
    }

    ///
    /// Setter: Previous city
    /// @param City city: Previous city
    ///
    template <typename T>
    void City<T>::SetPrevCity(City<T> *city)
    {
        this->prevCity = city;
    }

    ///
    /// Setter: Set next cities that connected to the city.
    /// @param string cityName: Next city name
    /// @param City nextCity: Next city
    ///
    template <typename T>
    void City<T>::SetNextCity(string cityName, City<T> *nextCity)
    {
        this->nextCities[cityName] = nextCity;
    }

    ///
    /// Get next city.
    /// @param string cityName: Next city name to be retrieved.
    ///
    template <typename T>
    City<T>* City<T>::GetNextCityByName(string cityName)
    {
        //If map instance is accessed with [] operator and the key doesn't exist,
        //a new element will automatically be created, thus use find() method to find it.
        if(this->nextCities.find(cityName) != this->nextCities.end())
        {
            return this->nextCities[cityName];
        }
        return NULL;
    }


    ///
    /// Get the cost to next city.
    /// @param string nextCity: Next city name to be retrieved.
    /// @return T cost to next city.
    ///
    template <typename T>
    T City<T>::GetCostToNextCityByName(string nextCity)
    {
        if(this->costsToNextCities.find(nextCity) != this->costsToNextCities.end())
        {
            return this->costsToNextCities[nextCity];
        }
        return 0.0;
    }

    ///
    /// Get all cost to next cities.
    /// @return map<string, T> All costs to next cities.
    ///
    template <typename T>
    map<string, T> City<T>::GetCostsToNextCities()
    {
        return this->costsToNextCities;
    }

    ///
    /// Set cost to next city.
    /// @param string nextCity: Next city
    /// @param T cost: Cost to the next city.
    ///
    template <typename T>
    void City<T>::SetCostToNextCityByName(string nextCity, T cost)
    {
        this->costsToNextCities[nextCity] = cost;
    }

    ///
    /// Erase next city.
    /// @param string cityName: Next city to be removed.
    ///
    template <typename T>
    void City<T>::EraseNextCityByName(string cityName)
    {
        this->nextCities.erase(cityName);
    }

    ///
    /// Erase cost to next city.
    /// @param string cityName: Next city to be removed.
    ///
    template <typename T>
    void City<T>::EraseCostToNextCityByName(string cityName)
    {
        this->costsToNextCities.erase(cityName);
    }

    ///
    /// Oveload method of "<" operator
    /// @param const City<T> &city1: City 1
    /// @param const City<T> &city2: City 2
    /// @return bool true when city1->totalCost is smaller than city1->totalCost.
    ///
    template <typename T>
    bool operator<(const City<T> &city1, const City<T> &city2)
    {
        return city1.totalCost < city2.totalCost;
    }

    ///
    /// Oveload method of ">" operator
    /// @param const City<T> &city1: City 1
    /// @param const City<T> &city2: City 2
    /// @return bool true when city1->totalCost is bigger than city1->totalCost.
    ///
    template <typename T>
    bool operator>(const City<T> &city1, const City<T> &city2)
    {
        return city1.totalCost > city2.totalCost;
    }

    template class City<int>;
    template class City<long>;
    template class City<float>;
    template class City<double>;
#endif // CITY_H
