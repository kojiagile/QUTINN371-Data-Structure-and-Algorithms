#include <iostream>
#include <stdlib.h>
#include <errno.h>
#include <string>

#include <vector>
#include "BankBranchDeployer.h"
#include "TestBankBranchDeployer.h"

using namespace std;


int main(int argc, char **argv)
{
    BankBranchDeployer deployer = BankBranchDeployer();
    deployer.Deploy(argc, argv);


    //TestBankBranchDeployer tbbd = TestBankBranchDeployer();
    //tbbd.TestNumberOfK();
    //tbbd.TestImportCityMapData();
    //tbbd.CalcExecutionTime5();
    //tbbd.TestQOSDistance5();
    //tbbd.CalcExecutionTimeForQOS5();

    /*
    CityMap citymap = CityMap();

    // City positions are only examples
    citymap.AddCity("Canberra", 1445, 849.8);
    citymap.AddCity("Sydney", 1649, 689.0);
    citymap.AddCity("Melbourne", 1035, 1128);
    citymap.AddCity("Brisbane", 1829, -21.78);
    citymap.AddCity("Perth", -1829, 476.9);
    citymap.AddCity("Adelaide", 409.3, 807.4);
    citymap.AddCity("Hobart", 1268, 1692);
    citymap.AddCity("Darwin", -355.6, -1692);
    citymap.AddCity("Cairns", 1788, -1525);
    citymap.AddCity("Alice Springs", -56.56, -440.6);

    citymap.AddRoad("Canberra", "Sydney");
    citymap.AddRoad("Canberra", "Melbourne");
    citymap.AddRoad("Sydney", "Brisbane");
    citymap.AddRoad("Brisbane", "Darwin");
    citymap.AddRoad("Darwin", "Perth");
    citymap.AddRoad("Perth", "Adelaide");
    citymap.AddRoad("Adelaide", "Melbourne");
    citymap.AddRoad("Melbourne", "Hobart");
    citymap.AddRoad("Alice Springs", "Darwin");
    citymap.AddRoad("Alice Springs", "Adelaide");
    citymap.AddRoad("Cairns", "Brisbane");
    citymap.AddRoad("Cairns", "Darwin");
    citymap.AddRoad("Cairns", "Alice Springs");


    cout << "From Cairns to Brisbane: " << citymap.FindDistance("Cairns", "Brisbane") << "km" << endl;
    cout << "From Cairns to Darwin: " << citymap.FindDistance("Cairns", "Darwin") << "km" << endl;
    cout << "From Cairns to Alice Springs: " << citymap.FindDistance("Cairns", "Alice Springs") << "km" << endl;

    cout << "From Darwin to Perth: " << citymap.FindDistance("Darwin", "Perth") << "km" << endl;

    cout << "From Brisbane to Sydney: " << citymap.FindDistance("Brisbane", "Sydney") << "km" << endl;
    cout << "From Brisbane to Darwin: " << citymap.FindDistance("Brisbane", "Darwin") << "km" << endl;

    cout << "From Sydney to Canberra: " << citymap.FindDistance("Sydney", "Canberra") << "km" << endl;

    cout << "From Canberra to Melbourne: " << citymap.FindDistance("Canberra", "Melbourne") << "km" << endl;

    cout << "From Melbourne to Adelaide: " << citymap.FindDistance("Melbourne", "Adelaide") << "km" << endl;
    cout << "From Melbourne to Hobart: " << citymap.FindDistance("Melbourne", "Hobart") << "km" << endl;

    cout << "From Adelaide to Alice Springs: " << citymap.FindDistance("Adelaide", "Alice Springs") << "km" << endl;
    cout << "From Adelaide to Perth: " << citymap.FindDistance("Adelaide", "Perth") << "km" << endl;

    cout << "From Alice Springs to Darwin: " << citymap.FindDistance("Alice Springs", "Darwin") << "km" << endl;


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

    //citymap.PrintPath("Brisbane", "Perth");
    */
    return 0;
}
