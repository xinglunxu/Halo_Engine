//
//  Component.hpp
//  Halo_Engine
//
//  Created by 许兴伦 on 7/17/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <stdio.h>
#include <unordered_map>
#include "World.hpp"

using namespace std;

template <typename DataType>
class Component{
private:
    static unordered_map<int, DataType> dataMaps;
    friend class World;
};

template <typename DataType>
unordered_map<int, DataType> Component<DataType>::dataMaps = unordered_map<int, DataType>();


#endif /* Component_hpp */
