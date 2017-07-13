//
//  MovingSystem.hpp
//  Halo_World
//
//  Created by 许兴伦 on 7/4/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef MovingSystem_hpp
#define MovingSystem_hpp

#include <stdio.h>
#include "ISystem.hpp"
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <typeindex>
#include <list>
#include "Transform.hpp"
#include "Velocity.hpp"


class MovingSystem:public ISystem{
public:
    void Update() override;
    std::list<std::type_index>* GetDataTypes() override;
    void InjectData(std::list<void*> &datas) override;
    MovingSystem();
private:
    std::unordered_map<int, Transform*>* transforms;
    std::unordered_map<int, Velocity*>* velocities;
};

#endif /* MovingSystem_hpp */
