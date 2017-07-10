//
//  Engine.cpp
//  Halo_Engine
//
//  Created by 许兴伦 on 7/4/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#include "Engine.hpp"

const int interval = 1000000;

void Engine::Run(){
    while(true){
        Update();
        usleep(interval);
    }
}

Engine::Engine(){
    frame_num = 0;
    systems = new unordered_map<type_index,ISystem*>();
    datas = new unordered_map<type_index, void*>();
}

void Engine::Update(){
    frame_num++;
    for(auto it = systems->begin(); it!= systems->end(); it++){
        (*it).second->Update();
    }
}

int Engine::nextId = 0;
