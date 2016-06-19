#include <iostream>
#include <map>
#include <cstdlib>
#include <vector>

#include "CityCombination.h"

using namespace std;

/**
 * Constructor
 */
CityCombination::CityCombination()
{

}

/**
 * Constructor
 * @param string firstCity: First city
 * @param string firstCity: Second city
 * @param double distance: Distance between the first city and the second city.
 */
CityCombination::CityCombination(string firstCity, string secondCity, double distance)
{
    this->firstCity = firstCity;
    this->secondCity = secondCity;
    this->distance = distance;
}

/**
 * Get distance between the first city and the second city.
 * @return double: Distance between the first city and the second city.
 */
double CityCombination::GetDistance()
{
    return this->distance;
}

/**
 * Get first city name
 * @return string: First city name.
 */
string CityCombination::GetFirstCity()
{
    return this->firstCity;
}

/**
 * Get second city name
 * @return string: Second city name.
 */
string CityCombination::GetSecondCity()
{
    return this->secondCity;
}

///
/// Overload method of "<" operator
/// @param const CityCombination &city1: City 1
/// @param const CityCombination &city2: City 2
/// @return bool true when city1->totalCost is bigger than city1->totalCost.
///
bool operator< (const CityCombination &city1, const CityCombination &city2)
{
    return city1.distance < city2.distance;
}

///
/// Overload method of "<" operator
/// @param const CityCombination &city1: City 1
/// @param const CityCombination &city2: City 2
/// @return bool true when city1->totalCost is bigger than city1->totalCost.
///
bool operator> (const CityCombination &city1, const CityCombination &city2)
{
    return city1.distance > city2.distance;
}
