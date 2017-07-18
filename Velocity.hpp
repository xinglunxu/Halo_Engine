//
//  Velocity.hpp
//  Halo_World
//
//  Created by 许兴伦 on 7/4/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef Velocity_hpp
#define Velocity_hpp

#include <stdio.h>
#include "Component.hpp"

class Velocity : Component<Velocity>{
public:
    float x;
    float y;
    float z;
};

#endif /* Velocity_hpp */
