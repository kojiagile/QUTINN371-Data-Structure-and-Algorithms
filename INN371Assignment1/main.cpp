#include <iostream>
#include <math.h>
#include "City.h"
#include "CityMap.h"
#include "TestCityMap.h"
//#include "CityMapGenerator.h"

//#include <opencv2/core/core.hpp>

using namespace std;



int main()
{

/*
    CityMap<double> cmap;

    cmap.AddCity(cmap.ALI, 500, 220);
    cmap.AddCity(cmap.ADE, 620, 460);
    cmap.AddCity(cmap.BRI, -900, 250);
    cmap.AddCity(cmap.CAI, 870, 120);
    cmap.AddCity(cmap.CAN, 850, 370);
    cmap.AddCity(cmap.DAR, 1500, 120);
    cmap.AddCity(cmap.HOB, 750, 510);
    cmap.AddCity(cmap.MEL, 720, 3000);
    cmap.AddCity(cmap.SYD, 920, -330);
    cmap.AddCity(cmap.PER, 50, 250);

    cmap.AddRoad(cmap.BRI, cmap.SYD);
    cmap.AddRoad(cmap.BRI, cmap.CAI);
    cmap.AddRoad(cmap.CAI, cmap.DAR);
    cmap.AddRoad(cmap.CAN, cmap.BRI);
    cmap.AddRoad(cmap.DAR, cmap.PER);
    cmap.AddRoad(cmap.PER, cmap.ADE);
    cmap.AddRoad(cmap.ADE, cmap.HOB);
    cmap.AddRoad(cmap.MEL, cmap.HOB);
    cmap.AddRoad(cmap.HOB, cmap.SYD);

    cmap.PrintPath(cmap.HOB, cmap.BRI);
*/

    TestCityMap tmap;


    /*
    tmap.TestAddCity();
    tmap.TestAddRoad();

    tmap.TestRemoveCity1();
    tmap.TestRemoveCity2();
    tmap.TestRemoveRoad();
    tmap.TestFindDistance();
    tmap.TestShortestPath();
    tmap.TestPrintPath();
    tmap.TestCityMapWithInt();
    tmap.TestCityMapWithFloat();
    tmap.TestCityMapWithDouble();
    tmap.TestStartGoalConnectedDirectly();
    tmap.TestStartGoalNotConnectedDirectly();
    tmap.TestGoalIsolated();
    tmap.TestRouteChangeLater();
    tmap.TestPathChangeByAddingCity();
    tmap.TestPathChangeByAddingRoad();
    tmap.TestPathChangeByRemovingCity();
    tmap.TestPathChangeByRemovingRoad();
    tmap.TestAllSameCost();
*/
    //tmap.TestAddManyCities();
    //tmap.TestAddManyRoads();
    //tmap.TestDistance();


/*

    CityMap<double> citymap;

    // City positions are only examples
    citymap.AddCity("Canberra", 1445, 849.8);
    citymap.AddCity("Sydney", 1649, 689.0);
    citymap.AddCity("Melbourne", 1035, 1128);
    citymap.AddCity("Brisbane", 1829, -21.78);
    citymap.AddCity("Perth", -1829, 476.9);
    citymap.AddCity("Adelaide", 409.3, 807.4);
    citymap.AddCity("Hobart", 1268, 1692);
    citymap.AddCity("Darwin", -355.6, -1692);
    //citymap.AddCity("Alice Springs", -56.56, -440.6);
    citymap.AddCity(citymap.CAI, 1745, -1503.4);



    citymap.AddRoad(citymap.ADE, citymap.MEL);
    citymap.AddRoad(citymap.ADE, citymap.ALI);
    citymap.AddRoad(citymap.ADE, citymap.SYD);
    citymap.AddRoad(citymap.ADE, citymap.HOB);
    citymap.AddRoad(citymap.ADE, citymap.CAN);

    citymap.AddRoad(citymap.ALI, citymap.DAR);
    citymap.AddRoad(citymap.ALI, citymap.ADE);
    citymap.AddRoad(citymap.ALI, citymap.SYD);

    citymap.AddRoad(citymap.CAN, citymap.SYD);
    citymap.AddRoad(citymap.CAN, citymap.MEL);
    citymap.AddRoad(citymap.CAN, citymap.BRI);

    citymap.AddRoad(citymap.CAI, citymap.BRI);
    citymap.AddRoad(citymap.CAI, citymap.DAR);
    citymap.AddRoad(citymap.CAI, citymap.SYD);

    citymap.AddRoad(citymap.BRI, citymap.DAR);
    citymap.AddRoad(citymap.BRI, citymap.ALI);
    citymap.AddRoad(citymap.BRI, citymap.CAI);
    citymap.AddRoad(citymap.BRI, citymap.SYD);

    citymap.AddRoad(citymap.DAR, citymap.PER);
    citymap.AddRoad(citymap.DAR, citymap.ALI);
    citymap.AddRoad(citymap.DAR, citymap.BRI);
    citymap.AddRoad(citymap.DAR, citymap.SYD);

    citymap.AddRoad(citymap.HOB, citymap.SYD);
    citymap.AddRoad(citymap.HOB, citymap.BRI);
    citymap.AddRoad(citymap.HOB, citymap.ADE);

    citymap.AddRoad(citymap.MEL, citymap.HOB);
    citymap.AddRoad(citymap.MEL, citymap.ADE);

    citymap.AddRoad(citymap.PER, citymap.ADE);
    citymap.AddRoad(citymap.PER, citymap.ALI);
    citymap.AddRoad(citymap.PER, citymap.SYD);

    //citymap.AddRoad(citymap.SYD, citymap.BRI);
    citymap.AddRoad(citymap.SYD, citymap.ADE);
    citymap.AddRoad(citymap.SYD, citymap.ALI);

    //citymap.PrintPath(citymap.SYD, citymap.BRI);
    //citymap.PrintPath(citymap.SYD, citymap.PER);
    //citymap.PrintPath(citymap.SYD, citymap.ALI);
    //citymap.PrintPath(citymap.HOB, citymap.DAR);
    //citymap.PrintPath(citymap.HOB, citymap.PER);
    //citymap.PrintPath(citymap.HOB, citymap.DAR);
    //citymap.PrintPath(citymap.ADE, citymap.HOB);
    //citymap.PrintPath(citymap.CAN, citymap.DAR);
    //citymap.PrintPath(citymap.CAI, citymap.PER);
    //citymap.PrintPath(citymap.ALI, citymap.HOB);
    //citymap.PrintPath(citymap.ALI, citymap.SYD);

    cout << "From Brisbane to Sydney: " << citymap.FindDistance(citymap.BRI, citymap.SYD) << "km" << endl;
    citymap.PrintPath(citymap.BRI, citymap.SYD);
    cout << "------------------------------------------------------------------------" << endl;


    cout << "From Brisbane to Melbourne: " << citymap.FindDistance(citymap.BRI, citymap.MEL) << "km" << endl;
    citymap.PrintPath(citymap.BRI, citymap.MEL);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Sydney to Canberra: " << citymap.FindDistance(citymap.SYD, citymap.CAN) << "km" << endl;
    citymap.PrintPath(citymap.SYD, citymap.CAN);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "Removing Sydney..." << endl;
    citymap.RemoveCity(citymap.SYD);
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Removing Canberra..." << endl;
    citymap.RemoveCity(citymap.CAN);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Brisbane to Melbourne: " << citymap.FindDistance(citymap.BRI, citymap.MEL) << "km" << endl;
    citymap.PrintPath(citymap.BRI, citymap.MEL);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "Adding Sydney again..." << endl;
    citymap.AddCity(citymap.SYD, 1649, 689.0);
    citymap.AddRoad(citymap.SYD, citymap.BRI);
    citymap.AddRoad(citymap.CAN, citymap.SYD);
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Removing Cairns..." << endl;
    citymap.RemoveCity(citymap.CAI);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Brisbane to Melbourne: " << citymap.FindDistance(citymap.BRI, citymap.MEL) << "km" << endl;
    citymap.PrintPath(citymap.BRI, citymap.MEL);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "Adding Alice Springs..." << endl;
    citymap.AddCity(citymap.ALI, -56.56, -440.6);
    citymap.AddRoad(citymap.ALI, citymap.DAR);
    citymap.AddRoad(citymap.ALI, citymap.ADE);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Brisbane to Alice Springs: " << citymap.FindDistance(citymap.BRI, citymap.ALI) << "km" << endl;
    citymap.PrintPath(citymap.BRI, citymap.ALI);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "Removing the road between Darwin and Perth..." << endl;
    citymap.RemoveRoad(citymap.DAR, citymap.PER);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Hobart to Perth: " << citymap.FindDistance(citymap.HOB, citymap.PER) << "km" << endl;
    citymap.PrintPath(citymap.HOB, citymap.PER);
    cout << "------------------------------------------------------------------------" << endl;
*/
    /*
    CityMap<double> citymap;

    // City positions are only examples
    citymap.AddCity("Canberra", 1445, 849.8);
    citymap.AddCity("Sydney", 1649, 689.0);
    citymap.AddCity("Melbourne", 1035, 1128);
    citymap.AddCity("Brisbane", 1829, -21.78);
    citymap.AddCity("Perth", -1829, 476.9);
    citymap.AddCity("Adelaide", 409.3, 807.4);
    citymap.AddCity("Hobart", 1268, 1692);
    citymap.AddCity("Darwin", -355.6, -1692);
    //citymap.AddCity("Alice Springs", -56.56, -440.6);
    citymap.AddCity(citymap.CAI, 1745, -1503.4);

    citymap.AddRoad(citymap.ADE, citymap.MEL);
    citymap.AddRoad(citymap.ADE, citymap.ALI);
    citymap.AddRoad(citymap.ADE, citymap.SYD);
    citymap.AddRoad(citymap.ADE, citymap.HOB);
    citymap.AddRoad(citymap.ADE, citymap.CAN);

    citymap.AddRoad(citymap.ALI, citymap.DAR);
    citymap.AddRoad(citymap.ALI, citymap.ADE);
    citymap.AddRoad(citymap.ALI, citymap.SYD);

    citymap.AddRoad(citymap.CAN, citymap.SYD);
    citymap.AddRoad(citymap.CAN, citymap.MEL);
    citymap.AddRoad(citymap.CAN, citymap.BRI);

    citymap.AddRoad(citymap.CAI, citymap.BRI);
    citymap.AddRoad(citymap.CAI, citymap.DAR);
    citymap.AddRoad(citymap.CAI, citymap.SYD);

    citymap.AddRoad(citymap.BRI, citymap.DAR);
    citymap.AddRoad(citymap.BRI, citymap.ALI);
    citymap.AddRoad(citymap.BRI, citymap.CAI);

    citymap.AddRoad(citymap.DAR, citymap.PER);
    citymap.AddRoad(citymap.DAR, citymap.ALI);
    citymap.AddRoad(citymap.DAR, citymap.BRI);
    citymap.AddRoad(citymap.DAR, citymap.SYD);

    citymap.AddRoad(citymap.HOB, citymap.SYD);
    citymap.AddRoad(citymap.HOB, citymap.BRI);
    citymap.AddRoad(citymap.HOB, citymap.ADE);

    citymap.AddRoad(citymap.MEL, citymap.HOB);
    citymap.AddRoad(citymap.MEL, citymap.ADE);

    citymap.AddRoad(citymap.PER, citymap.ADE);
    citymap.AddRoad(citymap.PER, citymap.ALI);
    citymap.AddRoad(citymap.PER, citymap.SYD);

    //citymap.AddRoad(citymap.SYD, citymap.BRI);
    citymap.AddRoad(citymap.SYD, citymap.ADE);
    citymap.AddRoad(citymap.SYD, citymap.ALI);

    cout << "From Brisbane to Sydney: " << endl;
    citymap.PrintPath(citymap.BRI, citymap.SYD);
    cout << "------------------------------------------------------------------------" << endl;


    cout << "From Brisbane to Melbourne: " << endl;
    citymap.PrintPath(citymap.BRI, citymap.MEL);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Sydney to Canberra: " << endl;
    citymap.PrintPath(citymap.SYD, citymap.CAN);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "Removing Sydney..." << endl;
    citymap.RemoveCity(citymap.SYD);
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Removing Canberra..." << endl;
    citymap.RemoveCity(citymap.CAN);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Brisbane to Melbourne: " << endl;
    citymap.PrintPath(citymap.BRI, citymap.MEL);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "Adding Sydney again..." << endl;
    citymap.AddCity(citymap.SYD, 1649, 689.0);
    citymap.AddRoad(citymap.SYD, citymap.BRI);
    citymap.AddRoad(citymap.CAN, citymap.SYD);
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Removing Cairns..." << endl;
    citymap.RemoveCity(citymap.CAI);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Brisbane to Melbourne: " << endl;
    citymap.PrintPath(citymap.BRI, citymap.MEL);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "Adding Alice Springs..." << endl;
    citymap.AddCity(citymap.ALI, -56.56, -440.6);
    citymap.AddRoad(citymap.ALI, citymap.DAR);
    citymap.AddRoad(citymap.ALI, citymap.ADE);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Brisbane to Alice Springs: " << endl;
    citymap.PrintPath(citymap.BRI, citymap.ALI);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "Removing the road between Darwin and Perth..." << endl;
    citymap.RemoveRoad(citymap.DAR, citymap.PER);
    cout << "------------------------------------------------------------------------" << endl;

    cout << "From Hobart to Perth: " << endl;
    citymap.PrintPath(citymap.HOB, citymap.PER);
    cout << "------------------------------------------------------------------------" << endl;
    */
    /*
    cout << "From Brisbane to Sydney: " << citymap.FindDistance("Brisbane", "Sydney") << "km" << endl;
    cout << "From Sydney to Canberra: " << citymap.FindDistance("Sydney", "Canberra") << "km" << endl;
    cout << "From Canberra to Melbourne: " << citymap.FindDistance("Canberra", "Melbourne") << "km" << endl;
    cout << "From Sydney to Melbourne: " << citymap.FindDistance("Sydney", "Melbourne") << "km" << endl;
    cout << "From Melbourne to Hobart: " << citymap.FindDistance("Melbourne", "Hobart") << "km" << endl;
    cout << "From Brisbane to Melbourne: " << citymap.FindDistance("Brisbane", "Melbourne") << "km" << endl;
    cout << "From Brisbane to Adelaide: " << citymap.FindDistance("Brisbane", "Adelaide") << "km" << endl;
    cout << "From Brisbane to Hobart: " << citymap.FindDistance("Brisbane", "Hobart") << "km" << endl;
    cout << "From Brisbane to Canberra: " << citymap.FindDistance("Brisbane", "Canberra") << "km" << endl;
    cout << "From Brisbane to Perth: " << citymap.FindDistance("Brisbane", "Perth") << "km" << endl;

    cout << "Removing Sydney..." << endl;
    citymap.RemoveCity("Sydney");

    cout << "From Brisbane to Melbourne: " << citymap.FindDistance("Brisbane", "Melbourne") << "km" << endl;

    cout << "Adding Alice Springs..." << endl;

    citymap.AddCity("Alice Springs", -56.56, -440.6);
    citymap.AddRoad("Alice Springs", "Darwin");
    citymap.AddRoad("Alice Springs", "Adelaide");

    cout << "From Brisbane to Alice Springs: " << citymap.FindDistance("Brisbane", "Alice Springs") << "km" << endl;
    cout << "From Brisbane to Melbourne: " << citymap.FindDistance("Brisbane", "Melbourne") << "km" << endl;

    cout << "Removing the road between Darwin and Perth..." << endl;
    citymap.RemoveRoad("Darwin", "Perth");

    cout << "From Brisbane to Perth: " << citymap.FindDistance("Brisbane", "Perth") << "km" << endl;
    */

    return 0;
}

