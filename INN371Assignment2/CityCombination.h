#ifndef CITYCOMBINATION_H_INCLUDED
#define CITYCOMBINATION_H_INCLUDED

#include <string>
#include <vector>
#include <map>

using namespace std;


/**
 * CityCombination class.
 *  The class is used to store two city name and the distance between them.
 */
class CityCombination
{

public:

    /**
     * Constructor
     */
    CityCombination();

    /**
     * Constructor
     * @param string firstCity: First city
     * @param string firstCity: Second city
     * @param double distance: Distance between the first city and the second city.
     */
    CityCombination(string, string, double);

    /**
     * Get first city name
     * @return string: First city name.
     */
    string GetFirstCity();

    /**
     * Get second city name
     * @return string: Second city name.
     */
    string GetSecondCity();

    /**
     * Get distance between the first city and the second city.
     * @return double: Distance between the first city and the second city.
     */
    double GetDistance();


    ///
    /// Overload method of "<" operator
    /// @param const CityCombination &city1: City 1
    /// @param const CityCombination &city2: City 2
    /// @return bool true when city1->totalCost is smaller than city1->totalCost.
    ///
    friend bool operator< (const CityCombination &city1, const CityCombination &city2);

    ///
    /// Overload method of "<" operator
    /// @param const CityCombination &city1: City 1
    /// @param const CityCombination &city2: City 2
    /// @return bool true when city1->totalCost is bigger than city1->totalCost.
    ///
    friend bool operator> (const CityCombination &city1, const CityCombination &city2);

private:

    ///
    /// First city name
    ///
    string firstCity;

    ///
    /// Second city name
    ///
    string secondCity;

    ///
    /// Distance between the first city and the second city
    ///
    double distance;

};

#endif // CITYCOMBINATION_H_INCLUDED
