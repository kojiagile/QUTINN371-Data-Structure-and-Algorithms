#pragma once

#ifndef TESTCITYMAP_H_INCLUDED
#define TESTCITYMAP_H_INCLUDED


#include "CityMap.h"

using namespace std;

class TestCityMap
{

    public:
        /// Test city name
        static const string STR_TEST_CITY_NAME;
        /// Test next city name
        static const string STR_TEST_NEXT_CITY_NAME;
        /// The number of cities to be created: 100
        static const double NUM_HUNDRED;
        /// The number of cities to be created: 1000
        static const double NUM_THOUSAND;
        /// The number of cities to be created: 10000
        static const double NUM_TEN_THOUSAND;

        /// Test AddCity() method.
        void TestAddCity();
        /// Test AddRoad() method.
        void TestAddRoad();
        /// Test RemoveCity() method part 1
        void TestRemoveCity1();
        /// Test RemoveCity() method part 2
        void TestRemoveCity2();
        /// Test RemoveRoad() method.
        void TestRemoveRoad();
        /// Test to add many cities to ensure that the application does not hang up.
        void TestAddManyCities();
        /// Test to add many roads to ensure that the application does not hang up.
        void TestAddManyRoads();

        /// Test if the CityMap class works when int is specified to it.
        void TestCityMapWithInt();
        /// Test if the CityMap class works when float is specified to it.
        void TestCityMapWithFloat();
        /// Test if the CityMap class works when double is specified to it.
        void TestCityMapWithDouble();

        /// Test FindDistance() method.
        void TestFindDistance();
        /// Test ShortestPath() method.
        void TestShortestPath();
        /// Test PrintPath() method.
        void TestPrintPath();

        /// Check the shortest path case 1:
        void TestStartGoalConnectedDirectly();
        /// Check the shortest path case 2:
        void TestStartGoalNotConnectedDirectly();
        /// Check the shortest path case 3:
        void TestGoalIsolated();

        /// Check the shortest path case 4:
        void TestRouteChangeLater();
        /// Check the shortest path case 5:
        void TestPathChangeByRemovingCity();
        /// Check the shortest path case 6:
        void TestPathChangeByRemovingRoad();
        /// Check the shortest path case 7:
        void TestPathChangeByAddingCity();
        /// Check the shortest path case 8:
        void TestPathChangeByAddingRoad();
        /// Check the shortest path case 9:
        void TestAllSameCost();
        /// Check if the shortest distance is correct.
        void TestDistance();

        ///
        /// Display all cities added.
        /// @param CityMap<T> *cmap: CityMap object
        ///
        template <typename T>
        void ShowAllCities(CityMap<T> *cmap);

        ///
        /// Display all cities added and next cities connected to the current city.
        /// @param CityMap<T> *cmap: CityMap object
        ///
        template <typename T>
        void ShowAllNextCities(CityMap<T> *cmap);

        ///
        /// Join a string with number converted to a string.
        /// @param string str: A string value.
        /// @param int number: A number to be converted to a string.
        string JoinStringWithNumber(string str, int number);

    private:

};

#include "TestCityMap.cpp"

#endif // TESTCITYMAP_H_INCLUDED
