//
//  MovingSystem.cpp
//  Halo_World
//
//  Created by 许兴伦 on 7/4/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#include "MovingSystem.hpp"

MovingSystem::MovingSystem(){
    
}

void MovingSystem::Update(){
    std::cout<<"MovingSystemRun!"<<std::endl;
    for(auto it = entityIds.begin();it!=entityIds.end();it++){
        int id = *it;
        Transform* t = (*transforms)[id];
        Velocity* v = (*velocities)[id];
        t->pX+=v->x;
        t->pY+=v->y;
        t->pZ+=v->z;
    }
    
    for(auto it = entityIds.begin();it!=entityIds.end();it++){
        int id = *it;
        Transform* t = (*transforms)[id];
        Velocity* v = (*velocities)[id];
        std::cout<<t->pX<<std::endl;
        std::cout<<t->pY<<std::endl;
        std::cout<<t->pZ<<std::endl;
    }
}



std::list<type_index>* MovingSystem::GetDataTypes(){
    std::list<type_index>* retList = new std::list<type_index>();
    retList->insert(retList->end(), type_index(typeid(Transform)));
    retList->insert(retList->end(), type_index(typeid(Velocity)));
    return retList;
}

void MovingSystem::InjectData(std::list<void*> &datas){
    
    void* transformP = datas.front(); datas.pop_front();
    this->transforms = static_cast<unordered_map<int, Transform*>*>(transformP);
    void* velocityP = datas.front(); datas.pop_front();
    this->velocities = static_cast<std::unordered_map<int, Velocity*>*>(velocityP);
}



