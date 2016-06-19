#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>

#include "TestBankBranchDeployer.h"
#include "BankBranchDeployer.h"
#include "FileController.h"


using namespace std;
void TestNumberOfArguments()
{

}

/**
 * The test method ensures that the application runs correctly when different number of cities is specified as K.
 */
void TestBankBranchDeployer::TestNumberOfK()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "0";
    char *argv[] = {arg0, arg1, arg2, arg3};

    cout << "Case 1: Specifying the number of K(0) - Error message should be displayed - " << endl;
    BankBranchDeployer deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);
    cout << endl;

    argv[3] = "1";
    cout << "Case 2: Specifying the number of K(1) - One cluster should be displayed - " << endl;
    deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);
    cout << endl;

    argv[3] = "9";
    cout << "Case 3: Specifying the number of K(9) that is the same as the number of cities" << endl;
    cout << "- Nine clusters should be displayed - " << endl;
    deployer.Deploy(4, argv);
    cout << endl;

    argv[3] = "10";
    cout << "Case 4: Specifying the number of K(10) that exceeds the number of cities" << endl;
    cout << "- Error message should be displayed - " << endl;
    deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);
    cout << endl;
}


/**
 * The test method ensures that the application runs correctly when appropriate/inappropriate file names are specified.
 */
void TestBankBranchDeployer::TestImportCityMapData()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "3";
    char *argv[] = {arg0, arg1, arg2, arg3};

    cout << "Case 1: Specifying wrong city file name (wrong.txt)" << endl;
    argv[1] = "wrong.txt";
    argv[2] = "roads.txt";
    BankBranchDeployer deployer = BankBranchDeployer();
    deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);
    cout << endl;

    cout << "Case 2: Specifying wrong road file name (wrong.txt)" << endl;
    argv[1] = "cities.txt";
    argv[2] = "wrong.txt";
    deployer.Deploy(4, argv);
    cout << endl;

    cout << "Case 3: Specifying correct city and road file names (cities.txt, roads.txt)" << endl;
    argv[1] = "cities.txt";
    argv[2] = "roads.txt";
    deployer.Deploy(4, argv);
    cout << endl;

}



/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTime1()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "1";
    char *argv[] = {arg0, arg1, arg2, arg3};

    cout << "Case 1: Place one bank branch (K = 1)" << endl;
    argv[3] = "1";
    BankBranchDeployer deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);

}

/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTime2()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "3";
    char *argv[] = {arg0, arg1, arg2, arg3};

    cout << "Case 2: Place one bank branch (K = 3)" << endl;
    BankBranchDeployer deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);
}

/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTime3()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "5";
    char *argv[] = {arg0, arg1, arg2, arg3};

    cout << "Case 3: Place one bank branch (K = 5)" << endl;
    BankBranchDeployer deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);

}


/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTime4()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "7";
    char *argv[] = {arg0, arg1, arg2, arg3};

    cout << "Case 4: Place one bank branch (K = 7)" << endl;
    BankBranchDeployer deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);

}


/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTime5()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "9";
    char *argv[] = {arg0, arg1, arg2, arg3};

    cout << "Case 5: Place one bank branch (K = 9)" << endl;
    BankBranchDeployer deployer = BankBranchDeployer();
    deployer.Deploy(4, argv);

}


/**
 * The test method ensures that the application runs correctly
 * when appropriate/inappropriate distance is specified.
 */
void TestBankBranchDeployer::TestQOSDistance1()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "-1km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 1: Specify -1km" << endl;
    deployer.Deploy(4, argv);
}


/**
 * The test method ensures that the application runs correctly
 * when appropriate/inappropriate distance is specified.
 */
void TestBankBranchDeployer::TestQOSDistance2()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "0km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 2: Specify 0km" << endl;
    deployer.Deploy(4, argv);
}




/**
 * The test method ensures that the application runs correctly
 * when appropriate/inappropriate distance is specified.
 */
void TestBankBranchDeployer::TestQOSDistance3()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "1000km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 3: Specify 1000km" << endl;
    deployer.Deploy(4, argv);
}



/**
 * The test method ensures that the application runs correctly
 * when appropriate/inappropriate distance is specified.
 */
void TestBankBranchDeployer::TestQOSDistance4()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "10000km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 4: Specify 10000km" << endl;
    argv[3] = "10000km";
    deployer.Deploy(4, argv);

}

/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTimeForQOS1()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "0km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 1: Specify 0km" << endl;
    argv[3] = "0km";
    deployer.Deploy(4, argv);
}

/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTimeForQOS2()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "300km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 2: Specify 300km" << endl;
    deployer.Deploy(4, argv);
}

/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTimeForQOS3()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "500km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 3: Specify 500km" << endl;
    deployer.Deploy(4, argv);
}

/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTimeForQOS4()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "1000km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 4: Specify 1000km" << endl;
    deployer.Deploy(4, argv);
}

/**
 * The test method measures execution time.
 */
void TestBankBranchDeployer::CalcExecutionTimeForQOS5()
{
    char arg0[] = "";
    char arg1[] = "cities.txt";
    char arg2[] = "roads.txt";
    char arg3[] = "1500km";
    char *argv[] = {arg0, arg1, arg2, arg3};
    BankBranchDeployer deployer = BankBranchDeployer();

    cout << "Case 5: Specify 1500km" << endl;
    deployer.Deploy(4, argv);
}



