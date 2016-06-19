//#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "City.h"
#include "CityMap.h"
//#include "TestCityMap.h"

using namespace std;

#ifdef TESTCITYMAP_H_INCLUDED

    /// Test city name
    const string TestCityMap::STR_TEST_CITY_NAME = "Test City";
    /// Test next city name
    const string TestCityMap::STR_TEST_NEXT_CITY_NAME = "Test Next";
    /// The number of cities to be created: 100
    const double TestCityMap::NUM_HUNDRED = 100;
    /// The number of cities to be created: 1000
    const double TestCityMap::NUM_THOUSAND = 1000;
    /// The number of cities to be created: 10000
    const double TestCityMap::NUM_TEN_THOUSAND = 10000;


    ///
    /// Test AddCity() method.
    ///
    void TestCityMap::TestAddCity()
    {
        cout << "======================== TestAddCity() Start ========================" << endl;
        CityMap<double> cmap;

        //1. no errors
        //  The method will finish with no errors
        cout << "[Case 1] Add a city with correct name." << endl;
        cmap.AddCity(cmap.BRI, 100.50, 100.70);
        City<double> *city;
        city = cmap.GetCityByName(cmap.BRI);
        cout << "--- Show added city ---" << endl;
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        cout << "-----------------------" << endl;

        //2. Add a city with no name
        //  The method will show error
        cout << "[Case 2] Add a city with empty name.(city name is empty string)" << endl;
        cmap.AddCity("", 100.0, 100.5);

        //3. Add the same city again
        //  The method will show an error message and will not add the city.
        cout << "[Case 3] Add the same city (Brisbane) again." << endl;
        cmap.AddCity(cmap.BRI, 200.77, 300.88);
        city = cmap.GetCityByName(cmap.BRI);
        cout << "--- Show added city ---" << endl;
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        cout << "-----------------------" << endl;

        map<string, City<double>* > cities = cmap.GetCities();
        map<string, City<double>* >::iterator it = cities.begin();
        cout << endl;

        //The number of cities added is 1, and the city is Brisbane, 200.77, 300.88
        cout << "=== Result ===" << endl;
        cout << "The number of cities added: " << cmap.GetCities().size() << endl;
        while(it != cities.end())
        {
            city = it->second;
            cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
            it++;
        }
        cout << "======================================================================" << endl;
        cout << endl;
        cmap.ClearAllCities();
    }

    ///
    /// Test AddRoad() method.
    ///
    void TestCityMap::TestAddRoad()
    {
        cout << "======================== TestAddRoad() Start ========================" << endl;
        CityMap<double> cmap;

        //Brisbane and Cairns
        cmap.AddCity(cmap.BRI, 100.10, 100.20);
        cmap.AddCity(cmap.CAI, 200.30, 100.40);

        //1. Normal case
        //  The method will finish with no errors
        cout << "[Case 1] Add a road with correct cities." << endl;
        cmap.AddRoad(cmap.BRI, cmap.CAI);
        cout << endl;
        //Brisbane and Cairn are shown, and both city has one next city, Brisbane and Cairns.
        this->ShowAllNextCities(&cmap);

        //2~4 Add a road with no name
        //  The method will show error
        cout << "[Case 2] Add a road with wrong city name (both start and goal city name are empty)" << endl;
        cmap.AddRoad("", "");
        cout << "[Case 3] Add a road with wrong city name (start city name is empty)" << endl;
        cmap.AddRoad("", cmap.CAI);
        cout << "[Case 4] Add a road with wrong city name (goal city name is empty)" << endl;
        cmap.AddRoad(cmap.BRI, "");

        //5. Add the same road again
        //  The method will finish with no errors (simply updated.)
        cout << "[Case 5] Add the same road again." << endl;
        cmap.AddRoad(cmap.BRI, cmap.CAI);
        this->ShowAllNextCities(&cmap);

        //6~8 Specify an unregistered city
        //  The method will show error
        cout << "[Case 6] Specify wrong city names (both start and goal)." << endl;
        cmap.AddRoad("TestCity", "TestCity2");
        cout << "[Case 7] Specify wrong city name (goal city)" << endl;
        cmap.AddRoad(cmap.BRI, "TestCity2");
        cout << "[Case 8] Specify wrong city names (start city)" << endl;
        cmap.AddRoad("TestCity", cmap.CAI);

        //9. Specify two same cities
        cout << "[Case 9] Add a road with same cities." << endl;
        cmap.AddRoad(cmap.BRI, cmap.BRI);

        cout << endl;
        cout << "======================================================================" << endl;
        cmap.ClearAllCities();

    }

    ///
    /// Test to add many cities to ensure that the application does not hang up.
    ///
    void TestCityMap::TestAddManyCities()
    {
        cout << "======================== TestAddManyCities() Start ========================" << endl;
        CityMap<double> cmap;

        cout << "[Case 1] Add 1,000 cities " << endl;
        string ret;
        int x = 0;
        int y = 0;
        for(int i = 0; i < TestCityMap::NUM_THOUSAND; i++)
        {
            ret = this->JoinStringWithNumber(TestCityMap::STR_TEST_CITY_NAME, i);
            cmap.AddCity(ret, x, y);
            x++;
            if(i % 1000 == 0)
            {
                x = 0;
                y++;
            }
        }
        cout << "=== Result ===" << endl;
        this->ShowAllCities(&cmap);
        cmap.ClearAllCities();

        Sleep(10000);

        x = 0;
        y = 0;
        cout << "[Case 2] Add 10,000 cities " << endl;
        for(int i = 0; i < TestCityMap::NUM_TEN_THOUSAND; i++)
        {
            ret = this->JoinStringWithNumber(TestCityMap::STR_TEST_CITY_NAME, i);
            cmap.AddCity(ret, x, y);
            x++;
            if(i % 1000 == 0)
            {
                x = 0;
                y++;
            }
        }
        cout << "=== Result ===" << endl;
        this->ShowAllCities(&cmap);
        cmap.ClearAllCities();
        cout << "===========================================================================" << endl;
    }

    ///
    /// Test to add many roads to ensure that the application does not hang up.
    ///
    void TestCityMap::TestAddManyRoads()
    {
        cout << "======================== TestAddManyRoads() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.BRI, 500, 500);

        cout << "[Case 1] A city is connected to 1,000 cities " << endl;
        string ret;
        int x = 0;
        int y = 0;
        for(int i = 0; i < TestCityMap::NUM_THOUSAND; i++)
        {
            ret = this->JoinStringWithNumber(TestCityMap::STR_TEST_NEXT_CITY_NAME, i);
            cmap.AddCity(ret, x, y);
            x++;
            y++;
        }
        //add roads
        for(int i = 0; i < TestCityMap::NUM_THOUSAND; i++)
        {
            ret = this->JoinStringWithNumber(TestCityMap::STR_TEST_NEXT_CITY_NAME, i);
            cmap.AddRoad(cmap.BRI, ret);
        }
        cout << "=== Result ===" << endl;
        this->ShowAllNextCities(&cmap);
        cmap.ClearAllCities();

        Sleep(10000);

        cout << "[Case 2] A city is connected to 10,000 cities " << endl;
        x = 0;
        y = 0;
        cmap.AddCity(cmap.BRI, 500, 500);
        for(int i = 0; i < TestCityMap::NUM_TEN_THOUSAND; i++)
        {
            ret = this->JoinStringWithNumber(TestCityMap::STR_TEST_NEXT_CITY_NAME, i);
            cmap.AddCity(ret, x, y);
            x++;
            if(i % 1000 == 0)
            {
                x = 0;
                y++;
            }
        }
        //add roads
        for(int i = 0; i < TestCityMap::NUM_TEN_THOUSAND; i++)
        {
            ret = this->JoinStringWithNumber(TestCityMap::STR_TEST_NEXT_CITY_NAME, i);
            cmap.AddRoad(cmap.BRI, ret);
        }
        cout << "=== Result ===" << endl;
        this->ShowAllNextCities(&cmap);
        cmap.ClearAllCities();
        cout << "==========================================================================" << endl;
    }

    ///
    /// Test RemoveCity() method part 1
    ///
    void TestCityMap::TestRemoveCity1()
    {
        //2. no errors 2
        //  multiple cities exist, and remove one of them.
        cout << "======================== TestRemoveCity()1 Start ========================" << endl;
        CityMap<double> cmap;
        //City<double> *city;

        //add city first
        cout << "[Case 1] Remove a city with correct name." << endl;
        cout << "Add Brisbane, Cairn, Alice Spring, Sydney..." << endl;
        cmap.AddCity(cmap.BRI, 100.50, 100.70);
        cmap.AddCity(cmap.CAI, 200.50, 200.70);
        cmap.AddCity(cmap.ALI, 300.50, 300.70);
        cmap.AddCity(cmap.SYD, 400.50, 400.70);

        //remove city, then show the result
        cout << "Remove Brisbane..." << endl;
        cmap.RemoveCity(cmap.BRI);
        cout << "=== Result === " << endl;
        this->ShowAllCities(&cmap);

        cout << "[Case 2] Remove a city with correct name, and make sure all roads connected to the city are deleted." << endl;
        cout << "Add Brisbane, Cairn, Alice Spring, Sydney..." << endl;
        cmap.AddRoad(cmap.CAI, cmap.ALI);
        cmap.AddRoad(cmap.CAI, cmap.SYD);
        cmap.AddRoad(cmap.SYD, cmap.ALI);
        cout << "Show all cities and the roads." << endl;
        this->ShowAllNextCities(&cmap);

        //remove city, then show the result
        cout << "Remove Sydney..." << endl;
        cmap.RemoveCity(cmap.SYD);
        cout << "=== Result === " << endl;
        this->ShowAllNextCities(&cmap);
        cmap.ClearAllCities();
        cout << endl;

    }


    ///
    /// Test RemoveCity() method part 2
    ///
    void TestCityMap::TestRemoveCity2()
    {
        cout << "======================== TestRemoveCity()2 Start ========================" << endl;
        CityMap<double> cmap;
        City<double> *city;

        //add city first
        cout << "[Case 1] Remove a city with wrong name" << endl;
        cmap.AddCity(cmap.BRI, 100.50, 100.70);
        city = cmap.GetCityByName(cmap.BRI);
        cout << "--- Show added city ---" << endl;
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        cout << "-----------------------" << endl;

        cout << "Specify empty name..." << endl;
        cmap.RemoveCity("");

        cout << "Remove city Wrong Name City..." << endl;
        cmap.RemoveCity("Wrong Name City");
        this->ShowAllCities(&cmap);

        cmap.ClearAllCities();
        cout << endl;
    }


    ///
    /// Test RemoveRoad() method.
    ///
    void TestCityMap::TestRemoveRoad()
    {
        cout << "======================== TestRemoveRoad() Start ========================" << endl;
        CityMap<double> cmap;

        //1. Remove a road with correct city names.
        //  The method will finish with no errors
        cout << "[Case 1] Remove road out of multiple roads added with no errors." << endl;
        cmap.AddCity(cmap.BRI, 100.50, 100.70);
        cmap.AddCity(cmap.CAI, 200.50, 300.70);
        cmap.AddCity(cmap.SYD, 300.50, 500.70);
        cmap.AddCity(cmap.CAN, 400.50, 700.70);
        cmap.AddRoad(cmap.BRI, cmap.CAI);
        cmap.AddRoad(cmap.BRI, cmap.SYD);
        cmap.AddRoad(cmap.BRI, cmap.CAN);

        //remove road, then show the result
        cout << "Remove Brisbane - Sydney road." << endl;
        cmap.RemoveRoad(cmap.BRI, cmap.SYD);
        cout << "=== Result ===" << endl;
        this->ShowAllNextCities(&cmap);
        cmap.ClearAllCities();


        //add city and road first
        cmap.AddCity(cmap.BRI, 100.50, 100.70);
        cmap.AddCity(cmap.CAI, 200.50, 300.70);
        cmap.AddRoad(cmap.BRI, cmap.CAI);
        cout << endl;

        //remove road, then show the result
        //  The method will show an error message each time.
        cout << "[Case 2] Specify wrong city name (both start and goal city)" << endl;
        cmap.RemoveRoad("Wrong City Name", "Wrong City Name");
        cout << "[Case 3] Specify wrong city name (start city)" << endl;
        cmap.RemoveRoad("Wrong City Name", cmap.CAI);
        cout << "[Case 4] Specify wrong city name (goal city)" << endl;
        cmap.RemoveRoad(cmap.BRI, "Wrong City Name");
        cout << "[Case 5] Specify same name at start and goal city." << endl;
        cmap.RemoveRoad(cmap.BRI, cmap.BRI);

        cout << "=== Result ===" << endl;
        this->ShowAllNextCities(&cmap);
        cmap.ClearAllCities();

    }

    ///
    /// Test if the CityMap class works when int is specified to it.
    ///
    void TestCityMap::TestCityMapWithInt()
    {
        cout << "======================== TestCityMapWithInt() Start ========================" << endl;
        cout << "CityMap instance was created with int." << endl;
        cout << "Specify floating point numbers... " << endl;
        CityMap<int> cmap;
        cmap.AddCity(cmap.BRI, 100.15, 100.56);
        cmap.AddCity(cmap.SYD, 200.450, 300.0);
        cmap.AddCity(cmap.CAI, 300.69, 480.2);
        cmap.AddRoad(cmap.BRI, cmap.SYD);
        cmap.AddRoad(cmap.BRI, cmap.CAI);
        cmap.AddRoad(cmap.CAI, cmap.SYD);

        cout << "--- Show added city ---" << endl;
        City<int> *city;
        city = cmap.GetCityByName(cmap.BRI);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        city = cmap.GetCityByName(cmap.SYD);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        city = cmap.GetCityByName(cmap.CAI);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        cout << "-----------------------" << endl;

        //find shortest way
        cout << "[Case 1]" << endl;
        cout << "Distance between Brisbane to Sydney: " << endl;
        cmap.PrintPath(cmap.BRI, cmap.SYD);
        cout << "[Case 2]" << endl;
        cout << "Distance between Brisbane to Cairns: " << endl;
        cmap.PrintPath(cmap.BRI, cmap.CAI);
        cout << "[Case 3]" << endl;
        cout << "Distance between Cairns to Sydney: " << endl;
        cmap.PrintPath(cmap.CAI, cmap.SYD);

        //this->ShowAllCities(cmap);
        cmap.ClearAllCities();
        cout << "===========================================================================" << endl;
    }



    ///
    /// Test if the CityMap class works when float is specified to it.
    ///
    void TestCityMap::TestCityMapWithFloat()
    {
        cout << "======================== TestCityMapWithFloat() Start ========================" << endl;
        CityMap<float> cmap;
        cout << "CityMap instance was created with float." << endl;
        cout << "Specify floating point numbers... " << endl;
        cmap.AddCity(cmap.BRI, 1000000000.123456789, 1000000000.123456789);
        cmap.AddCity(cmap.SYD, 2000000000.123456789, 3000000000.123456789);
        cmap.AddCity(cmap.CAI, 3000000000.123456789, 8000000000.123456789);
        cmap.AddRoad(cmap.BRI, cmap.SYD);
        cmap.AddRoad(cmap.BRI, cmap.CAI);
        cmap.AddRoad(cmap.CAI, cmap.SYD);

        cout << "--- Show added city ---" << endl;
        City<float> *city;
        city = cmap.GetCityByName(cmap.BRI);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        city = cmap.GetCityByName(cmap.SYD);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        city = cmap.GetCityByName(cmap.CAI);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        cout << "-----------------------" << endl;

        //find shortest way
        cout << "[Case 1]" << endl;
        cout << "Distance between Brisbane to Sydney: " << endl;
        cmap.PrintPath(cmap.BRI, cmap.SYD);
        cout << "[Case 2]" << endl;
        cout << "Distance between Brisbane to Cairns: " << endl;
        cmap.PrintPath(cmap.BRI, cmap.CAI);
        cout << "[Case 3]" << endl;
        cout << "Distance between Cairns to Sydney: " << endl;
        cmap.PrintPath(cmap.CAI, cmap.SYD);

        //this->ShowAllCities(cmap);
        cmap.ClearAllCities();
        cout << "===========================================================================" << endl;
    }


    ///
    /// Test if the CityMap class works when double is specified to it.
    ///
    void TestCityMap::TestCityMapWithDouble()
    {
        cout << "======================== TestCityMapWithDouble() Start ========================" << endl;
        cout << "CityMap instance was created with double." << endl;
        cout << "Specify floating point numbers... " << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.BRI, 1000000000.123456789, 1000000000.123456789);
        cmap.AddCity(cmap.SYD, 2000000000.123456789, 3000000000.123456789);
        cmap.AddCity(cmap.CAI, 3000000000.123456789, 8000000000.123456789);
        cmap.AddRoad(cmap.BRI, cmap.SYD);
        cmap.AddRoad(cmap.BRI, cmap.CAI);
        cmap.AddRoad(cmap.CAI, cmap.SYD);

        cout << "--- Show added city ---" << endl;
        City<double> *city;
        city = cmap.GetCityByName(cmap.BRI);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        city = cmap.GetCityByName(cmap.SYD);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        city = cmap.GetCityByName(cmap.CAI);
        cout << "City Name: " << city->GetName() << ", X: " << city->GetX() << ", Y: " << city->GetY() << endl;
        cout << "-----------------------" << endl;

        //find shortest way
        cout << "[Case 1]" << endl;
        cout << "Distance between Brisbane to Sydney: " << endl;
        cmap.PrintPath(cmap.BRI, cmap.SYD);
        cout << "[Case 2]" << endl;
        cout << "Distance between Brisbane to Cairns: " << endl;
        cmap.PrintPath(cmap.BRI, cmap.CAI);
        cout << "[Case 3]" << endl;
        cout << "Distance between Cairns to Sydney: " << endl;
        cmap.PrintPath(cmap.CAI, cmap.SYD);

        //this->ShowAllCities(cmap);
        cmap.ClearAllCities();
        cout << "===========================================================================" << endl;
    }

    ///
    /// Test FindDistance() method.
    ///
    void TestCityMap::TestFindDistance()
    {
        cout << "======================== TestFindDistance() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.BRI, 100, 100);
        cmap.AddCity(cmap.PER, 200, 500);
        cmap.AddRoad(cmap.BRI, cmap.PER);
        cout << "Brisbane and Perth have been added." << endl;

        //specify empty name
        cout << "[Case 1] Specify empty city names ( both start and goal city )" << endl;
        double dist = -1;
        dist = cmap.FindDistance("", "");
        cout << "Distance between (empty) to (empty): " << dist << "km." << endl << endl;

        cout << "[Case 2] Specify empty city names ( start city )" << endl;
        dist = -1;
        dist = cmap.FindDistance("", cmap.PER);
        cout << "Distance between (empty) to Perth: " << dist << "km." << endl << endl;

        cout << "[Case 3] Specify empty city names ( goal city )" << endl;
        dist = -1;
        dist = cmap.FindDistance(cmap.BRI, "");
        cout << "Distance between Brisbane to (empty): " << dist << "km." << endl << endl;

        //specify wrong name
        cout << "[Case 4] Specify wrong city names ( both start and goal city )" << endl;
        dist = -1;
        dist = cmap.FindDistance("Wrong Name City1", "Wrong Name City2");
        cout << "Distance between Wrong Name City1 to Wrong Name City2: " << dist << "km." << endl << endl;

        cout << "[Case 5] Specify wrong city name ( start city )" << endl;
        dist = -1;
        dist = cmap.FindDistance("Wrong Name City", cmap.PER);
        cout << "Distance between Wrong Name City to Perth: " << dist << "km." << endl << endl;

        cout << "[Case 6] Specify wrong city names ( goal city )" << endl;
        dist = -1;
        dist = cmap.FindDistance(cmap.BRI, "Wrong Name City");
        cout << "Distance between Brisbane to Wrong Name City: " << dist << "km." << endl << endl;

        cout << "[Case 7] Specify correct city name" << endl;
        dist = -1;
        dist = cmap.FindDistance(cmap.BRI, cmap.PER);
        cout << "Distance between Brisbane to Perth: " << dist << "km." << endl << endl;

        cout << "[Case 8] Specify the same city name at start and goal" << endl;
        dist = -1;
        dist = cmap.FindDistance(cmap.BRI, cmap.BRI);
        cout << "Distance between Brisbane to Brisbane: " << dist << "km." << endl << endl;

        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();

    }

    ///
    /// Test ShortestPath() method.
    ///
    void TestCityMap::TestShortestPath()
    {
        cout << "======================== TestShortestPath() Start ========================" << endl;
        CityMap<double> cmap;
        vector<string> path;
        vector<string>::iterator it;
        cmap.AddCity(cmap.BRI, 100, 100);
        cmap.AddCity(cmap.SYD, 200, 500);
        cmap.AddCity(cmap.CAN, 300, 800);
        cmap.AddCity(cmap.MEL, 500, 150);
        cmap.AddCity(cmap.ADE, 930, 200);
        cmap.AddCity(cmap.PER, 1030, 800);

        cmap.AddRoad(cmap.BRI, cmap.SYD);
        cmap.AddRoad(cmap.SYD, cmap.CAN);
        cmap.AddRoad(cmap.CAN, cmap.MEL);
        cmap.AddRoad(cmap.MEL, cmap.ADE);
        cmap.AddRoad(cmap.ADE, cmap.PER);
        cout << "Brisbane, Sydney, Canberra, Melbourne, Adelaide and Perth are added." << endl;

        //specify empty name
        double dist = 0;
        int i = 0;
        dist = cmap.FindDistance(cmap.BRI, cmap.PER);
        cout << "Distance between Brisbane to Perth: " << dist << "km." << endl << endl;

        cout << "[Case 1] Specify empty city names ( both start and goal city )" << endl;
        path = cmap.ShortestPath("", "");
        it = path.begin();
        cout << "Shortest Path: ";
        while(it != path.end())
        {
            cout << *it;
            if(i != (int)(path.size() - 1))
            {
                 cout << " -> ";
            }
            it++;
        }
        cout << endl;

        i = 0;
        cout << "[Case 2] Specify empty city names ( start city )" << endl;
        path = cmap.ShortestPath("", cmap.PER);
        it = path.begin();
        cout << "Shortest Path: ";
        while(it != path.end())
        {
            cout << *it;
            if(i != (int)(path.size() - 1))
            {
                 cout << " -> ";
            }
            it++;
        }
        cout << endl;

        i = 0;
        cout << "[Case 3] Specify empty city names ( goal city )" << endl;
        path = cmap.ShortestPath(cmap.BRI, "");
        it = path.begin();
        cout << "Shortest Path: ";
        while(it != path.end())
        {
            cout << *it;
            if(i != (int)(path.size() - 1))
            {
                 cout << " -> ";
            }
            it++;
        }
        cout << endl;

        //specify wrong name
        i = 0;
        cout << "[Case 4] Specify wrong city names ( both start and goal city )" << endl;
        path = cmap.ShortestPath("Wrong Name City", "Wrong Name City");
        it = path.begin();
        cout << "Shortest Path: ";
        while(it != path.end())
        {
            cout << *it;
            if(i != (int)(path.size() - 1))
            {
                 cout << " -> ";
            }
            it++;
        }
        cout << endl;

        i = 0;
        cout << "[Case 5] Specify wrong city names ( start city )" << endl;
        path = cmap.ShortestPath("Wrong Name City", cmap.PER);
        it = path.begin();
        cout << "Shortest Path: ";
        while(it != path.end())
        {
            cout << *it;
            if(i != (int)(path.size() - 1))
            {
                 cout << " -> ";
            }
            it++;
        }
        cout << endl;

        i = 0;
        cout << "[Case 6] Specify wrong city names ( goal city )" << endl;
        path = cmap.ShortestPath(cmap.BRI, "Wrong Name City");
        it = path.begin();
        cout << "Shortest Path: ";
        while(it != path.end())
        {
            cout << *it;
            if(i != (int)(path.size() - 1))
            {
                 cout << " -> ";
            }
            it++;
        }
        cout << endl;

        i = 0;
        cout << "[Case 7] Specify correct city name" << endl;
        path = cmap.ShortestPath(cmap.BRI, cmap.PER);
        it = path.begin();
        cout << "Shortest Path: ";
        while(it != path.end())
        {
            cout << *it;
            if(i != (int)(path.size() - 1))
            {
                 cout << " -> ";
            }
            i++;
            it++;
        }
        cout << endl;

        i = 0;
        cout << "[Case 8] Specify the same city name at start and goal" << endl;
        path = cmap.ShortestPath(cmap.BRI, cmap.BRI);
        it = path.begin();
        cout << "Shortest Path: ";
        while(it != path.end())
        {
            cout << *it;
            if(i != (int)(path.size() - 1))
            {
                 cout << " -> ";
            }
            i++;
            it++;
        }
        cout << endl;
        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }

    ///
    /// Test PrintPath() method.
    ///
    void TestCityMap::TestPrintPath()
    {
        cout << "======================== TestPrintPath() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.BRI, 100, 100);
        cmap.AddCity(cmap.SYD, 200, 500);
        cmap.AddCity(cmap.CAN, 300, 800);
        cmap.AddCity(cmap.MEL, 500, 150);
        cmap.AddCity(cmap.ADE, 930, 200);
        cmap.AddCity(cmap.PER, 1030, 800);

        cmap.AddRoad(cmap.BRI, cmap.SYD);
        cmap.AddRoad(cmap.SYD, cmap.CAN);
        cmap.AddRoad(cmap.SYD, cmap.MEL);
        cmap.AddRoad(cmap.CAN, cmap.MEL);
        cmap.AddRoad(cmap.CAN, cmap.ADE);
        cmap.AddRoad(cmap.MEL, cmap.ADE);
        cmap.AddRoad(cmap.MEL, cmap.PER);
        cmap.AddRoad(cmap.ADE, cmap.PER);
        cout << "Brisbane, Sydney, Canberra, Melbourne, Adelaide and Perth are added." << endl;

        //specify empty name
        double dist = 0;
        dist = cmap.FindDistance(cmap.BRI, cmap.PER);
        cout << "Distance between Brisbane to Perth: " << dist << "km." << endl << endl;


        cout << "[Case 1] Specify empty city names ( both start and goal city )" << endl;
        cmap.PrintPath("", "");
        cout << endl;

        cout << "[Case 2] Specify empty city names ( start city )" << endl;
        cmap.PrintPath("", cmap.PER);
        cout << endl;

        cout << "[Case 3] Specify empty city names ( goal city )" << endl;
        cmap.PrintPath(cmap.BRI, "");
        cout << endl;

        //specify wrong name
        cout << "[Case 4] Specify wrong city names ( both start and goal city )" << endl;
        cmap.PrintPath("Wrong Name City", "Wrong Name City");
        cout << endl;

        cout << "[Case 5] Specify wrong city names ( start city )" << endl;
        cmap.PrintPath("Wrong Name City", cmap.PER);
        cout << endl;

        cout << "[Case 6] Specify wrong city names ( goal city )" << endl;
        cmap.PrintPath(cmap.BRI, "Wrong Name City");
        cout << endl;

        cout << "[Case 7] Specify correct city name" << endl;
        cmap.PrintPath(cmap.BRI, cmap.PER);
        cout << endl;

        cout << "[Case 8] Specify the same city name at start and goal" << endl;
        cmap.PrintPath(cmap.BRI, cmap.BRI);
        cout << endl;
        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();

    }

    ///
    /// Check the shortest path case 1:
    ///      When start city and goal city are connected directly.
    ///
    void TestCityMap::TestStartGoalConnectedDirectly()
    {
        cout << "======================== TestStartGoalConnectedDirectly() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.BRI, 500, 500);
        cmap.AddCity(cmap.PER, 100, 100);
        cmap.AddRoad(cmap.BRI, cmap.PER);
        cout << "Brisbane and Perth are added." << endl;

        //find shortest way
        cout << "=== Result ===" << endl;
        //cout << "Distance between Brisbane to Perth: " << cmap.FindDistance(cmap.BRI, cmap.PER) << "km." << endl;
        cmap.PrintPath(cmap.BRI, cmap.PER);
        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }


    ///
    /// Check the shortest path case 2:
    ///      When start city and goal city are not directly connected but can be reached passing other cities.
    ///
    void TestCityMap::TestStartGoalNotConnectedDirectly()
    {
        cout << "======================== TestStartGoalNotConnectedDirectly() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.BRI, 100, 100);
        cmap.AddCity(cmap.SYD, 1200, -200);
        cmap.AddCity(cmap.CAN, -700, 5000);
        cmap.AddCity(cmap.PER, -4000, -800);
        cmap.AddRoad(cmap.BRI, cmap.SYD);
        cmap.AddRoad(cmap.SYD, cmap.CAN);
        cmap.AddRoad(cmap.CAN, cmap.PER);
        cout << "Brisbane, Sydeney, Canberra and Perth are added." << endl;

        //find shortest way
        cout << "=== Result ===" << endl;
        //cout << "Distance between Brisbane to Perth: " << cmap.FindDistance(cmap.BRI, cmap.PER) << "km." << endl;
        cmap.PrintPath(cmap.BRI, cmap.PER);
        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }

    ///
    /// Check the shortest path case 3:
    ///      When goal city is unreachable.
    ///
    void TestCityMap::TestGoalIsolated()
    {
        cout << "======================== TestGoalIsolated() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.BRI, 100, 100);
        cmap.AddCity(cmap.SYD, 1200, -200);
        cmap.AddCity(cmap.CAN, -700, 5000);
        cmap.AddCity(cmap.PER, -4000, -800);
        cmap.AddRoad(cmap.BRI, cmap.SYD);
        cmap.AddRoad(cmap.SYD, cmap.CAN);
        //cmap.AddRoad(cmap.CAN, cmap.PER);
        cout << "Brisbane, Sydney, Canberra and Perth are added." << endl;
        cout << "Perth is isolated. Now find distance from Brisbane to Perth..." << endl;

        //find shortest way
        cout << "=== Result ===" << endl;
        //cout << "Distance between Brisbane to Perth: " << cmap.FindDistance(cmap.BRI, cmap.PER) << "km." << endl;
        cmap.PrintPath(cmap.BRI, cmap.PER);
        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }


    ///
    /// Check the shortest path case 4:
    ///   Cities 1,2,3 are connected. 3-4, 2-4 are connected.
    ///   When the algorithm calculate the cost to 2 and 3,
    ///   it will calculate the cost to 1 and 2 from the city 3 since 3 is closer to 1 than 2.
    ///   This test checks if it eventually finds out that 1-2 is the shortest path.
    ///
    /// [Start] 1 [Goal] 2
    ///
    ///  1(Per)                     2(Bri)
    ///
    ///
    ///     3(Ade)
    ///
    ///      4(Hob)
    ///
    void TestCityMap::TestRouteChangeLater()
    {

        cout << "======================== TestRouteChangeLater() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.PER, 100, -1000);
        cmap.AddCity(cmap.BRI, 10000, 2000);
        cmap.AddCity(cmap.ADE, 1000, -1500);
        cmap.AddCity(cmap.HOB, 2000, -2500);
        cmap.AddRoad(cmap.BRI, cmap.PER);
        cmap.AddRoad(cmap.BRI, cmap.ADE);
        cmap.AddRoad(cmap.ADE, cmap.PER);
        cmap.AddRoad(cmap.ADE, cmap.HOB);
        cmap.AddRoad(cmap.HOB, cmap.BRI);
        cout << "Brisbane, Adelaide, Hobart and Perth are added." << endl;

        cout << "=== Result ===" << endl;
        //cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);
        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }


    ///
    /// Check the shortest path case 5:
    /// [Start] 1 [Goal] 3
    ///
    /// Connection:
    ///      1-2, 2-3, 1-4, 4-3, 4-5, 5-3
    /// Current shortest path is 1-2-3.
    /// When 2(Alice Spring) is deleted, the shortest path will be 1-4-3.
    /// This test checks if the algorithm finds out a new shortest path with no error when one of cities that passes through is removed.
    ///
    ///  1(Per)        2(Alice)       3(Bri)
    ///
    ///
    ///     4(Ade)
    ///
    ///      5(Hob)
    ///
    void TestCityMap::TestPathChangeByRemovingCity()
    {

        cout << "======================== TestPathChangeByRemovingCity() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.PER, 100, 1000);
        cmap.AddCity(cmap.ALI, 5000,1000);
        cmap.AddCity(cmap.BRI, 10000, 1000);
        cmap.AddCity(cmap.ADE, 1000, -1500);
        cmap.AddCity(cmap.HOB, 2000, -2500);
        cmap.AddRoad(cmap.PER, cmap.ALI);
        cmap.AddRoad(cmap.PER, cmap.ADE);
        cmap.AddRoad(cmap.ALI, cmap.BRI);
        cmap.AddRoad(cmap.ADE, cmap.ALI);
        cmap.AddRoad(cmap.ADE, cmap.BRI);
        cmap.AddRoad(cmap.ADE, cmap.HOB);
        cmap.AddRoad(cmap.HOB, cmap.BRI);
        cout << "Brisbane, Adelaide, Hobart, Alice Springs and Perth are added." << endl;

        cout << "=== Current shortest path ===" << endl;
        cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);
        cout << endl;

        //remove a road
        cout << "Remove Alice Springs..." << endl;
        cmap.RemoveCity(cmap.ALI);

        cout << "=== New shortest path ===" << endl;
        cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);

        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }


    ///
    /// Check the shortest path case 6:
    /// [Start] 1 [Goal] 3
    ///
    /// Connection:
    ///      1-2, 2-3, 1-4, 4-3, 4-5, 5-3
    /// Current shortest path is 1-2-3.
    /// When a road between 1-2 is deleted, the shortest path will be 1-4-3.
    /// This test checks if the algorithm finds out a new shortest path with no error when part of current shortest path is removed.
    ///
    ///  1(Per)        2(Alice)       3(Bri)
    ///
    ///
    ///     4(Ade)
    ///
    ///      5(Hob)
    ///
    void TestCityMap::TestPathChangeByRemovingRoad()
    {
        cout << "======================== TestPathChangeByRemovingRoad() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.PER, 100, 1000);
        cmap.AddCity(cmap.ALI, 5000,1000);
        cmap.AddCity(cmap.BRI, 10000, 1000);
        cmap.AddCity(cmap.ADE, 1000, -1500);
        cmap.AddCity(cmap.HOB, 2000, -2500);
        cmap.AddRoad(cmap.PER, cmap.ALI);
        cmap.AddRoad(cmap.PER, cmap.ADE);
        cmap.AddRoad(cmap.ALI, cmap.BRI);
        cmap.AddRoad(cmap.ADE, cmap.ALI);
        cmap.AddRoad(cmap.ADE, cmap.BRI);
        cmap.AddRoad(cmap.ADE, cmap.HOB);
        cmap.AddRoad(cmap.HOB, cmap.BRI);
        cout << "Brisbane, Adelaide, Hobart, Alice Springs and Perth are added." << endl;

        cout << "=== Current shortest path ===" << endl;
        cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);
        cout << endl;

        //remove a road
        cout << "Remove a road between Perth and Alice Springs..." << endl;
        cmap.RemoveRoad(cmap.PER, cmap.ALI);

        cout << "=== New shortest path ===" << endl;
        cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);

        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }


    ///
    /// Check the shortest path case 7:
    ///
    /// [Start] 1 [Goal] 3
    ///
    /// Connection:
    ///      1-4, 4-5, 5-3
    /// Current shortest path is 1-4-5-3.
    /// When a city 2 is added, the shortest path will be 1-2-3.
    /// This test checks if the algorithm finds out a new shortest path with no error when a new city is added.
    ///
    ///  1(Per)        2(Alice)       3(Bri)
    ///
    ///
    ///     4(Ade)
    ///
    ///      5(Hob)
    ///
    void TestCityMap::TestPathChangeByAddingCity()
    {
        cout << "======================== TestPathChangeByAddingCity() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.PER, 100, 1000);
        cmap.AddCity(cmap.BRI, 10000, 1000);
        cmap.AddCity(cmap.ADE, 1000, -1500);
        cmap.AddCity(cmap.HOB, 2000, -2500);
        cmap.AddRoad(cmap.PER, cmap.ADE);
        cmap.AddRoad(cmap.ADE, cmap.HOB);
        cmap.AddRoad(cmap.HOB, cmap.BRI);
        cout << "Brisbane, Adelaide, Hobart and Perth are added." << endl;

        cout << "=== Current shortest path ===" << endl;
        cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);
        cout << endl;

        //Add city
        cout << "Add Alice Springs and roads to Perth, Brisbane, Adelaide to Alice Springs and Brisbane..." << endl;
        cmap.AddCity(cmap.ALI, 5000,1000);
        cmap.AddRoad(cmap.PER, cmap.ALI);
        cmap.AddRoad(cmap.ALI, cmap.BRI);
        cmap.AddRoad(cmap.ADE, cmap.ALI);
        cmap.AddRoad(cmap.ADE, cmap.BRI);

        cout << "=== New shortest path ===" << endl;
        cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);

        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }


    ///
    /// Check the shortest path case 8:
    ///
    /// [Start] 1 [Goal] 3
    ///
    /// Connection:
    ///      1-4, 4-5, 5-3, 4-2, 2-3
    /// Current shortest path is 1-4-2-3.
    /// When a road between 1-2 is added, the shortest path will be 1-2-3.
    /// This test checks if the algorithm finds out a new shortest path with no error when a new road is added.
    ///
    ///  1(Per)        2(Alice)       3(Bri)
    ///
    ///
    ///     4(Ade)
    ///
    ///      5(Hob)
    ///
    void TestCityMap::TestPathChangeByAddingRoad()
    {
        cout << "======================== TestPathChangeByAddingRoad() Start ========================" << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.PER, 100, 1000);
        cmap.AddCity(cmap.ALI, 5000,1000);
        cmap.AddCity(cmap.BRI, 10000, 1000);
        cmap.AddCity(cmap.ADE, 1000, -1500);
        cmap.AddCity(cmap.HOB, 2000, -2500);
        cmap.AddRoad(cmap.PER, cmap.ADE);
        cmap.AddRoad(cmap.ADE, cmap.ALI);
        cmap.AddRoad(cmap.ADE, cmap.BRI);
        cmap.AddRoad(cmap.ALI, cmap.BRI);
        cmap.AddRoad(cmap.ADE, cmap.HOB);
        cmap.AddRoad(cmap.HOB, cmap.BRI);
        cout << "Brisbane, Adelaide, Hobart, Alice Springs and Perth are added." << endl;

        cout << "=== Current shortest path ===" << endl;
        cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);
        cout << endl;

        //remove a road
        cout << "Add a road between Perth to Alice Springs..." << endl;
        cmap.AddRoad(cmap.PER, cmap.ALI);

        cout << "=== New shortest path ===" << endl;
        cout << "Distance between Perth to Brisbane: " << cmap.FindDistance(cmap.PER, cmap.BRI) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.BRI);

        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }


    ///
    /// Check the shortest path case 9:
    ///
    /// [Start] 1 [Goal] 4
    ///
    /// Connection:
    ///      1-2, 1-3, 2-4, 3-4
    /// This test checks if the algorithm finds out a shortest path with no error when all distances are the same.
    ///
    ///  1(Per)        2(Alice)
    ///
    ///
    ///
    ///  3(Ade)        4(Can)
    ///
    void TestCityMap::TestAllSameCost()
    {
        cout << "======================== TestAllSameCost() Start ========================" << endl;
        cout << "Add Perth, Alice Springs, Adelaide, Canberra..." << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.PER, 100, 100);
        cmap.AddCity(cmap.ALI, 500, 100);
        cmap.AddCity(cmap.ADE, 100, -500);
        cmap.AddCity(cmap.CAN, 500, -500);
        cmap.AddRoad(cmap.PER, cmap.ALI);
        cmap.AddRoad(cmap.PER, cmap.ADE);
        cmap.AddRoad(cmap.ALI, cmap.CAN);
        cmap.AddRoad(cmap.ADE, cmap.CAN);
        cout << "Adelaide, Canberra, Alice Springs and Perth are added." << endl;


        cout << "=== Current shortest path ===" << endl;
        cout << "Distance between Perth to Canberra: " << cmap.FindDistance(cmap.PER, cmap.CAN) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.CAN);
        cout << endl;
        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }

    ///
    /// Check the shortest path case 9:
    ///
    /// [Start] 1 [Goal] 4
    ///
    /// Connection:
    ///      1-2, 1-3, 2-4, 3-4
    /// This test checks if the algorithm finds out a shortest path with no error when all distances are the same.
    ///
    void TestCityMap::TestDistance()
    {
        cout << "======================== TestCost() Start ========================" << endl;
        cout << "Add Perth, Alice Springs, Adelaide, Canberra..." << endl;
        CityMap<double> cmap;
        cmap.AddCity(cmap.PER, 100, 100);
        cmap.AddCity(cmap.ALI, 500, 100);
        cmap.AddCity(cmap.ADE, 200, 500);
        cmap.AddCity(cmap.CAN, 500, 1000);
        cmap.AddRoad(cmap.PER, cmap.ALI);
        cmap.AddRoad(cmap.PER, cmap.ADE);
        cmap.AddRoad(cmap.ALI, cmap.CAN);
        cmap.AddRoad(cmap.ADE, cmap.CAN);
        cout << "Adelaide, Canberra, Alice Springs and Perth are added." << endl;
        this->ShowAllNextCities(&cmap);

        cout << "=== Current shortest path ===" << endl;
        cout << "Distance between Perth to Canberra: " << cmap.FindDistance(cmap.PER, cmap.CAN) << "km." << endl;
        cmap.PrintPath(cmap.PER, cmap.CAN);
        cout << endl;
        cout << "===========================================================================" << endl;
        cmap.ClearAllCities();
    }

    ///
    /// Display all cities added.
    /// @param CityMap<T> *cmap: CityMap object
    ///
    template <typename T>
    void TestCityMap::ShowAllCities(CityMap<T> *cmap)
    {
        map<string, City<T>* > cities = cmap->GetCities();
        cout << "The number of cities: " << cities.size() << endl;

        typename map<string, City<T>* >::iterator it = cities.begin();
        int mod = 5;
        int i = 1;
        City<T> *city;
        while(it != cities.end())
        {
            city = it->second;
            cout << city->GetName();
            if(i++ % mod == 0)
            {
                cout << endl;
            }
            else
            {
                cout << ", ";
            }

            it++;
        }
        cout << endl;
    }


    ///
    /// Display all cities added and next cities connected to the current city.
    /// @param CityMap<T> *cmap: CityMap object
    ///
    template <typename T>
    void TestCityMap::ShowAllNextCities(CityMap<T> *cmap)
    {
        map<string, City<T>* > cities = cmap->GetCities();
        typename map<string, City<T>* >::iterator it = cities.begin();

        map<string, City<T>* > nextCities;
        typename map<string, City<T>* >::iterator itNext;

        cout << "The number of cities: " << cities.size() << endl;
        int mod = 5;
        int i = 1;
        City<T> *city;
        City<T> *nextCity;
        while(it != cities.end())
        {
            city = it->second;
            cout << "City: " << city->GetName() << endl;
            nextCities = city->GetNextCities();
            itNext = nextCities.begin();
            cout << "--- Next Cities ----" << endl;
            map<string, T> costs = city->GetCostsToNextCities();
            while(itNext != nextCities.end())
            {
                nextCity = itNext->second;
                //cout << nextCity->GetName() << endl;
                cout << "cost to " << nextCity->GetName() << " = ";
                cout << costs[nextCity->GetName()] << endl;
                if(i++ % mod == 0)
                {
                    cout << endl;
                }
                itNext++;
            }
            cout << "--------------------" << endl;
            it++;
        }
    }

    ///
    /// Join a string with number converted to a string.
    /// @param string str: A string value.
    /// @param int number: A number to be converted to a string.
    string TestCityMap::JoinStringWithNumber(string str, int number)
    {
        ostringstream oss;
        oss << str << number;
        return oss.str();
    }



#endif // TESTCITYMAP_H_INCLUDED
