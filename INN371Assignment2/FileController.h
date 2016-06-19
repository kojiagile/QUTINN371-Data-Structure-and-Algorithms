#ifndef FILECONTROLLER_H_INCLUDED
#define FILECONTROLLER_H_INCLUDED

#include <string>
#include <vector>

using namespace std;



/**
 * FileController class.
 *  The class is used to import file containing information about cities and connection between them.
 */
class FileController
{
public:

    /**
     * Constructor
     * @param cityFile: A file name containing city name and its coordinate.
     * @param roadFile: A file name containing information about connection between a city and another.
     */
    FileController(string, string);

    /**
     * Get information of cities imported.
     * @return vector<string>: Information of cities imported.
     */
    vector<string> GetCities();

    /**
     * Get information of connections imported.
     * @return vector<string>: Information of connections imported.
     */
    vector<string> GetRoads();

    /**
     * Import content of city and road file.
     * @return bool: Returns true if importing process is successfully done.
     */
    bool ReadFiles();


private:

    ///
    /// City information
    ///
    vector<string> cities;

    ///
    /// Road information
    ///
    vector<string> roads;

    ///
    /// A file name containing city information
    ///
    string cityFileName;

    ///
    /// A file name containing road information
    ///
    string roadFileName;

    /**
     * Get content of a file.
     * @param ifs: A pointer of ifstream object to opne a file.
     * @return vector<string>: Information of a files separated by single space.
     */
    vector<string> GetFileContent(ifstream *ifs);

};


#endif // FILECONTROLLER_H_INCLUDED
