#pragma once

#ifndef GENERATORACCESSOR_H_INCLUDED
#define GENERATORACCESSOR_H_INCLUDED


#include <vector>
#include "CityMap.h"
#include "CityMapGenerator.h"

//#ifndef CITYMAP_H

using namespace std;

class GeneratorAccessor
{
    public:
        template <typename T>
        void GenerateCityMap(CityMap<T> *cmap, vector<string> path);
    private:


};


    template <typename T>
    void GeneratorAccessor::GenerateCityMap(CityMap<T> *cmap, vector<string> path)
    {
        CityMapGenerator cmg;
        cmg.GenerateCityMap(cmap, path);
    }

//#endif // CITYMAP_H
//#include "GeneratorAccessor.cpp"

#endif // GENERATORACCESSOR_H_INCLUDED
