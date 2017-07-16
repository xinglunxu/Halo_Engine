//
//  World.hpp
//  Halo_World
//
//  Created by 许兴伦 on 7/4/17.
//  Copyright © 2017 SparkLight. All rights reserved.
//

#ifndef World_hpp
#define World_hpp

#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include "ISystem.hpp"
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <typeindex>
#include <functional>

using namespace std;


template <class ... A>
struct AddEntityClass;



class World{
    friend struct AddEntityClass<>;
    template <class ... A> friend struct AddEntityClass;
public:
    void Run();
    World();
    template <typename T> void AddSystem();
    template <typename T> void AddData();
    template <typename ... types> int AddEntity();
    
private:
    int frame_num;
    void Update();
    unordered_map<type_index, ISystem*> systems;
    unordered_map<type_index, unordered_map<int, void*>*> datas;
    unordered_map<type_index, function<void(int)>> dataFunctions;
    static int nextId;
    template <typename T, typename ... res> void _AddEntity(int id, typename enable_if<sizeof...(res)!=0, int>::type = 0);
    template <typename T> void _AddEntity(int id);
    template <typename T> void __AddEntity(int id);
    template <typename dataType> void AddEntityData(int id);
};









//–––––––––––––––––––––––––––––––––––––
//Template Initiation
//-------------------------------------
template <typename T>
void World::AddSystem(){
    T* system = new T();
    systems[type_index(typeid(T))] = system;
    std::list<type_index>* typeInfos = system->GetDataTypes();
    std::list<void*> datasList;
    for(auto it = typeInfos->begin(); it!=typeInfos->end();it++){
        type_index ti = *it;
        void* voidP = static_cast<void*>(datas[ti]);
        datasList.insert(datasList.end(), voidP);
    }
    system->InjectData(datasList);
}


template <typename T>
void World::AddData(){
    unordered_map<int, T*>* data = new unordered_map<int, T*>;
    datas[type_index(typeid(T))] = (unordered_map<int, void*>*)data;
    type_index ti = type_index(typeid(T));
    dataFunctions[ti] = [this](int id){
        this->AddEntityData<T>(id);
    };
}


template <typename ... types>
int World::AddEntity(){
    int entityId = (nextId++);
    _AddEntity<types...>(entityId);
    return entityId;
}

//private____________________________________

template <typename T, typename ... res>
void World::_AddEntity(int id, typename enable_if<sizeof...(res)!=0, int>::type){
    __AddEntity<T>(id);
//    AddEntityClass<res...>::call(id, this);
    _AddEntity<res...>(id);
}

template <typename T>
void World::_AddEntity(int id){
    __AddEntity<T>(id);
}

template <typename T>
void World::__AddEntity(int id){
    ISystem *system = systems[type_index(typeid(T))];
    system->AddEntity(id);
    list<type_index>* dataTypes = system->GetDataTypes();
    for(auto it = dataTypes->begin(); it!=dataTypes->end();it++){
        type_index ti = *it;
        dataFunctions[ti](id);
    }
}


template <typename dataType>
void World::AddEntityData(int id){
    type_index ti = type_index(typeid(dataType));
    void* dataP = datas[ti];
    unordered_map<int, dataType*>* data = static_cast<unordered_map<int, dataType*>*>(dataP);
    if(data->find(id)==data->end()){
        (*data)[id] = new dataType();
    }
}


#endif /* World_hpp */
