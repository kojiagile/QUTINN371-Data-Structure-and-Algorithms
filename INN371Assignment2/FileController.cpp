#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include "FileController.h"

using namespace std;


/**
 * Constructor
 * @param cityFile: A file name containing city name and its coordinate.
 * @param roadFile: A file name containing information about connection between a city and another.
 */
FileController::FileController(string cityFile, string roadFile)
{
    this->cityFileName = cityFile;
    this->roadFileName = roadFile;
}

/**
 * Get information of cities imported.
 * @return vector<string>: Information of cities imported.
 */
vector<string> FileController::GetCities()
{
    return this->cities;
}

/**
 * Get information of connections imported.
 * @return vector<string>: Information of connections imported.
 */
vector<string> FileController::GetRoads()
{
    return this->roads;
}


/**
 * Import content of city and road file.
 * @return bool: Returns true if importing process is successfully done.
 */
bool FileController::ReadFiles()
{
    //read cities.txt
    ifstream ifs(this->cityFileName.c_str(), ios::in);
    if (ifs.fail())
    {
        return false;
    }
    this->cities = GetFileContent(&ifs);
    if(this->cities.empty())
    {
        return false;
    }
    ifs.close();

    //read roads.txt
    ifstream ifs2(this->roadFileName.c_str(), ios::in);
    if (ifs2.fail())
    {
        return false;
    }
    this->roads = GetFileContent(&ifs2);
    if(this->roads.empty())
    {
        return false;
    }
    ifs2.close();

    return true;
}


/**
 * Get content of a file.
 * @param ifs: A pointer of ifstream object to opne a file.
 * @return vector<string>: Information of a files separated by single space.
 */
vector<string> FileController::GetFileContent(ifstream *ifs)
{
    vector<string> vec;

    string str;
    while (getline(*ifs, str))
    {
        //split by space
        stringstream sStream(str);
        string buffer;
        int i = 0;
        while(getline(sStream, buffer, ' '))
        {
            if(i > 2)
            {
                //if there are unnecessary data after the coordinate in the same line, ignore it.
                break;
            }
            //separated values are stored in the vector
            vec.push_back(buffer);
            i++;
        }
    }
    return vec;
}

