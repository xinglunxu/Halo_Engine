//
//  ISystem.hpp
//  Halo_Engine
//
//  Created by 许兴伦 on 7/4/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef ISystem_hpp
#define ISystem_hpp

#include <stdio.h>
#include <list>
#include <typeindex>
#include <unordered_set>
#include <iostream>

using namespace std;

class ISystem{
public:
    virtual void Update()=0;
    virtual std::list<std::type_index>* GetDataTypes()=0;
    virtual void InjectData(std::list<void*>* datas)=0;
    void AddEntity(int id){
        if(entityIds.find(id)==entityIds.end()){
            entityIds.insert(id);
        }
    }
protected:
    unordered_set<int> entityIds;
};

#endif /* ISystem_hpp */
