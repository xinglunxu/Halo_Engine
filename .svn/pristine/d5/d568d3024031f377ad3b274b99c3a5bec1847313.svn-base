//
//  MovingSystem.hpp
//  Halo_Engine
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
    void InjectData(std::list<void*> *datas) override;
    MovingSystem();
    template <typename ... types> void InjectDatas(std::unordered_map<std::type_index, void*>* datas){
        _InjectDatas<types... >(datas);
    }
    
private:
    std::unordered_map<int, Transform*>* transforms;
    std::unordered_map<int, Velocity*>* velocities;
    
    template <typename T, typename ... types> void _InjectDatas(std::unordered_map<std::type_index, void*>* datas){
        void* dataP = (*datas)[std::type_index(typeid(T))];
        std::unordered_map<int, T*>* data = static_cast<std::unordered_map<int, T*>*>(dataP);
    }
    
    
};

template <typename ... types>
struct InjectDataClass{
public:
    static void call(std::unordered_map<std::type_index, void*>* datas,MovingSystem* ms){
        ms->_InjectDatas<types...>(datas,ms);
    }
};

template <>
struct InjectDataClass<>{
public:
    static void call(std::unordered_map<std::type_index, void*>* datas,MovingSystem* ms){}
};

#endif /* MovingSystem_hpp */
