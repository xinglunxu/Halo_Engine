//
//  World.cpp
//  Halo_World
//
//  Created by 许兴伦 on 7/4/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#include "World.hpp"

const int interval = 1000000;

void World::Run(){
    while(true){
        Update();
        usleep(interval);
    }
}

World::World(){
    frame_num = 0;
    systems = unordered_map<type_index,ISystem*>();
    datas = unordered_map<type_index, unordered_map<int, void*>*>();
}

void World::Update(){
    frame_num++;
    for(auto it = systems.begin(); it!= systems.end(); it++){
        (*it).second->Update();
    }
}

int World::nextId = 0;
